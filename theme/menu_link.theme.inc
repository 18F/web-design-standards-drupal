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

  // For sidebar menus, we look for a certain flag.
  if (!empty($variables['element']['#uswds_sidebar'])) {
    $uswds_region = USWDS_MENU_REGION_SIDE;
  }
  // For all other menus we look for a specific menu. The reason for this
  // difference is that sidebar menus must be placed as blocks, whereas other
  // menus can be placed using the theme settings form.
  else {
    $uswds_region = _uswds_get_region_for_menu($menu_name);
  }
  if ($uswds_region) {

    switch ($uswds_region) {

      // Primary navigation tweaks.
      case USWDS_MENU_REGION_PRIMARY:
        return _uswds_theme_primary_menu_link($variables);
        break;

      // Secondary navigation tweaks.
      case USWDS_MENU_REGION_SECONDARY:
        // Nothing needed yet.
        break;

      // Side navigation tweaks.
      case USWDS_MENU_REGION_SIDE:
        return _uswds_theme_side_menu_link($variables);
        break;

      // Footer navigation tweaks.
      case USWDS_MENU_REGION_FOOTER:
        return _uswds_theme_footer_menu_link($variables);
        break;
    }
  }

  // If still here, fallback to regular Drupal menu links.
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

/**
 * Helper function to render side menu links.
 */
function _uswds_theme_side_menu_link($variables) {
  $element = $variables['element'];

  // Some info we'll need in this complex function.
  $depth = (int) $element['#original_link']['depth'];
  $has_children = !empty($element['#below']);
  $active_trail = (!empty($element['#original_link']['in_active_trail']));

  // we only show up to 3 levels.
  if ($depth > 3) {
    return '';
  }

  // The active link gets a class.
  if ($active_trail) {
    $element['#localized_options']['attributes']['class'][] = 'usa-current';
  }

  // Mark top-level links, purely as a message to uswds_preprocess_menu_tree().
  if (1 === $depth && $has_children) {
    $element['#attributes']['class'][] = 'uswds-side-nav-top';
  }
  // Similarly give all links a mark.
  $element['#attributes']['class'][] = 'uswds-side-nav-link';

  // Make the actual menu link.
  $link = l($element['#title'], $element['#href'], $element['#localized_options']);

  // Open the <li>.
  $output = '<li' . drupal_attributes($element['#attributes']) . '>' . $link;

  // We only care about hierarchy if this is in the active trail.
  if ($active_trail && $has_children) {
    $output .= drupal_render($element['#below']);
  }

  // Close the <li>.
  $output .= "</li>\n";

  return $output;
}

function _uswds_theme_footer_menu_link($variables) {

  $element = $variables['element'];

  // The footer menu items are very different depending on the footer style.
  $big = ('big' == theme_get_setting('uswds_footer_style'));

  if (!$big) {
    $element['#attributes']['class'][] = 'usa-width-one-sixth';
    $element['#attributes']['class'][] = 'usa-footer-primary-content';
    $element['#localized_options']['attributes']['class'][] = 'usa-footer-primary-link';

    $link = l($element['#title'], $element['#href'], $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $link . "</li>\n";
  }

  // Otherwise, we will need to render this as a hierarchical menu, assuming the
  // top level is columns titles, and the 2nd level is the actual menu items.
  $depth = (int) $element['#original_link']['depth'];

  // We only care about the first level of a menu.
  if ($depth > 1) {
    return '';
  }

  $output = '';
  // Only render the top-level items that actually have children.
  if (!empty($element['#below'])) {
    $output .= '<ul class="usa-unstyled-list usa-width-one-fourth usa-footer-primary-content">' . "\n";
    $output .= '<li class="usa-footer-primary-link"><h4>' . $element['#title'] . "</h4></li>\n";
    foreach (element_children($element['#below']) as $key) {
      $child = $element['#below'][$key];
      $link = l($child['#title'], $child['#href'], $child['#localized_options']);
      $output .= '<li>' . $link . "</li>\n";
    }
    $output .= "</ul>\n";
  }
  return $output;
}
