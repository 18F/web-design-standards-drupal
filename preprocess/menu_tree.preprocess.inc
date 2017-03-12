<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_menu_tree().
 */
function uswds_preprocess_menu_tree(&$variables) {

  // There is unfortunately not a clear indication of the menu that a menu tree
  // is rendered, so we have to resort to some string manipulation. :(
  $menu_name = str_replace('menu_tree__', '', $variables['theme_hook_original']);
  // Menus use hyphens instead of underscores, so we have to change that.
  $menu_name = strtr($menu_name, '_', '-');
  // Now look to see if this menu needs special USWDS tweaking.
  $uswds_region = _uswds_get_region_for_menu($menu_name);
  if (!$uswds_region) {
    return;
  }
  switch ($uswds_region) {

    // Primary navigation tweaks.
    case USWDS_MENU_REGION_PRIMARY:
      // Our low-tech way of identifying a submenu here.
      $is_submenu = (strpos($variables['tree'], 'usa-accordion-button') === FALSE);
      if ($is_submenu) {
        // If this is a submenu, the wrapper will be handled in our override of
        // theme_menu_link, so only output the tree itself here.
        $variables['uswds_menu_tree_only'] = TRUE;
      }
      else {
        // Otherwise if not a submenu, add a couple of classes.
        $variables['uswds_menu_attributes']['class'][] = 'usa-nav-primary';
        $variables['uswds_menu_attributes']['class'][] = 'usa-accordion';
        // Decide whether to include the search form.
        if (module_exists('search') && theme_get_setting('uswds_search')) {
          // If this is a basic header, we put the search form after the menu.
          if (USWDS_HEADER_STYLE_BASIC == theme_get_setting('uswds_header_style')) {
            $search_form = drupal_get_form('search_block_form');
            $search_box = drupal_render($search_form);
            $variables['uswds_menu_suffix'] = $search_box;
          }
        }
      }
      break;

    // Secondary navigation tweaks.
    case USWDS_MENU_REGION_SECONDARY:
      $variables['uswds_menu_attributes']['class'][] = 'usa-unstyled-list';
      $variables['uswds_menu_attributes']['class'][] = 'usa-nav-secondary-links';
      $variables['uswds_menu_prefix'] = '<div class="usa-nav-secondary">';
      $variables['uswds_menu_suffix'] = '</div>';
      // Decide whether to include the search form.
      if (module_exists('search') && theme_get_setting('uswds_search')) {
        // If this is an extended header, we put the search form before the menu.
        if (USWDS_HEADER_STYLE_EXTENDED == theme_get_setting('uswds_header_style')) {
          $search_form = drupal_get_form('search_block_form');
          $search_box = drupal_render($search_form);
          $variables['uswds_menu_prefix'] .= $search_box;
          // And we also add an extra item at the beginning of the menu.
          $search_item = '<li class="js-search-button-container"><button class="usa-header-search-button js-search-button">Search</button></li>';
          $variables['tree'] = $search_item . $variables['tree'];
        }
      }
      break;

    // Side navigation tweaks.
    case USWDS_MENU_REGION_SIDE:
      $variables['uswds_menu_attributes']['class'][] = 'usa-sidenav-list';
      $variables['uswds_menu_prefix'] = '<nav class="usa-footer-nav">';
      $variables['uswds_menu_suffix'] = '</nav>';
      break;

    // Footer navigation tweaks.
    case USWDS_MENU_REGION_FOOTER:
      // Nothing needed so far.
      break;
  }
}
