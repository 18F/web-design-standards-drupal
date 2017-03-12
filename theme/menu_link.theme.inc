<?php

/**
 * @file
 * Override for this theme hook.
 */

/**
 * Override markup of all menu links to control them based on their menu.
 */
function uswds_menu_link(&$variables) {
  $element = $variables['element'];
  $menu_name = $element['#original_link']['menu_name'];

  $uswds_region = _uswds_get_region_for_menu($menu_name);
  if ($uswds_region) {

    $active = (current_path() == $variables['element']['#href']);

    switch ($uswds_region) {

      // Primary navigation tweaks.
      case USWDS_MENU_REGION_PRIMARY:
        // This very complex, so split out to a separate function.
        return _uswds_theme_primary_menu_link($variables);
        break;

      // Secondary navigation tweaks.
      case USWDS_MENU_REGION_SECONDARY:
        // Nothing needed yet.
        break;

      // Side navigation tweaks.
      case USWDS_MENU_REGION_SIDE:
        if ($active) {
          $element['#localized_options']['attributes']['class'][] = 'usa-current';
        }
        break;

      // Footer navigation tweaks.
      case USWDS_MENU_REGION_FOOTER:
        $element['#attributes']['class'][] = 'usa-width-one-sixth';
        $element['#attributes']['class'][] = 'usa-footer-primary-content';
        $element['#localized_options']['attributes']['class'][] = 'usa-footer-primary-link';
        break;
    }
  }

  $link = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $link . "</li>\n";
}

/**
 * Helper function for overriding menu link markup in the primary menu.
 *
 * This is split into a separate function because of its complexity.
 */
function _uswds_theme_primary_menu_link(&$variables) {
  $element = $variables['element'];

  // Some info we'll need in this complex function.
  $depth = (int) $element['#original_link']['depth'];
  $has_children = !empty($element['#below']);
  $megamenu = theme_get_setting('uswds_header_mega');

  // We only care about the first three levels of a menu.
  if ($depth > 3) {
    return '';
  }

  // The button needs to be associated with the submenu.
  $parent_id = (1 === $depth) ? $element['#original_link']['mlid'] : $element['#original_link']['p1'];
  $submenu_id = 'submenu-' . $parent_id;

  // If this is first level and has children, treat it as the button for
  // triggering a submenu.
  if (1 === $depth && $has_children) {
    $button = '<button class="usa-accordion-button usa-nav-link" aria-expanded="false" aria-controls="' . $submenu_id . '">';
    $button .= '<span>' . $element['#title'] . '</span>';
    $button .= '</button>';
    $sub_menu = drupal_render($element['#below']);
    $sub_menu_classes = 'usa-nav-submenu';
    if ($megamenu) {
      $sub_menu_classes .= ' usa-megamenu usa-grid-full';
    }
    $sub_menu_prefix = '<ul class="' . $sub_menu_classes . '" id="' . $submenu_id . '" aria-hidden="true">';
    $sub_menu_suffix = '</ul>';
    return '<li>' . $button . $sub_menu_prefix . $sub_menu . $sub_menu_suffix . '</li>';
  }

  // We treat the second level as a column grouping for a megamenu.
  elseif ($megamenu && 2 === $depth && $has_children) {
    $sub_menu = drupal_render($element['#below']);
    $sub_menu_prefix = '<ul>';
    $sub_menu_suffix = '</ul>';
    return '<li class="usa-megamenu-col">' . $sub_menu_prefix . $sub_menu . $sub_menu_suffix . '</li>';
  }

  // For single-level menu links, make sure it has the "usa-nav-link" class.
  // And it needs to be in a span too.
  elseif (1 === $depth) {
    $element['#localized_options']['attributes']['class'][] = 'usa-nav-link';
    $element['#localized_options']['html'] = TRUE;
    $element['#title'] = '<span>' . $element['#title'] . '</span>';
  }

  // If still here, treat as a normal link.
  $link = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $link . "</li>\n";
}
