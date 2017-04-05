<?php

/**
 * @file
 * Utility code related to menus and menu blocks.
 */

/**
 * Helper function to see if a menu name is one of our special USWDS menus.
 */
function _uswds_get_region_for_menu($menu_name) {

  // Cache this statically since this is called for each menu link.
  $uswds_region = &drupal_static(__FUNCTION__ . $menu_name);
  if (!isset($uswds_region)) {
    $uswds_region = FALSE;
    $uswds_regions = array(
      USWDS_MENU_REGION_PRIMARY => variable_get('menu_main_links_source', USWDS_MENU_NONE),
      USWDS_MENU_REGION_SECONDARY => variable_get('menu_secondary_links_source', USWDS_MENU_NONE),
      USWDS_MENU_REGION_FOOTER => theme_get_setting(USWDS_MENU_REGION_FOOTER),
    );
    foreach ($uswds_regions as $region => $configured_menu) {
      if (USWDS_MENU_NONE == $configured_menu || empty($configured_menu)) {
        continue;
      }
      // If the menu matches exactly, we can stop looping.
      elseif ($menu_name == $configured_menu) {
        $uswds_region = $region;
        break;
      }
    }
  }
  return $uswds_region;
}

/**
 * Helper function to recursively mark menu links as being in a sidebar.
 */
function _uswds_mark_side_navigation_items(&$element) {
  foreach (element_children($element) as $key) {
    // Drop a note in all the menu links for later use in uswds_menu_link().
    $element[$key]['#uswds_sidebar'] = TRUE;
    // Recurse if there are children.
    if (!empty($element[$key]['#below'])) {
      _uswds_mark_side_navigation_items($element[$key]['#below']);
    }
  }
}
