<?php
/**
 * @file
 * Theme code, mostly to make Drupal 7's markup work with USWDS.
 *
 * Note: If you are looking for theme overrides or preprocess functions, check
 * the uswds/theme and uswds/preprocess folders.
 */

// Bring in our includes. Constants must be required first.
require_once dirname(__FILE__) . '/includes/uswds.constants.inc';
require_once dirname(__FILE__) . '/includes/uswds.stolen-from-omega.inc';

/**
 * Helper function to see if a menu name is one of our special USWDS menus.
 */
function _uswds_get_region_for_menu($menu_name) {

  // Cache this statically since this is called for each menu link.
  $uswds_region = &drupal_static(__FUNCTION__ . $menu_name);
  if (!isset($uswds_region)) {
    $uswds_region = FALSE;
    $uswds_regions = array(
      USWDS_MENU_REGION_PRIMARY => theme_get_setting(USWDS_MENU_REGION_PRIMARY),
      USWDS_MENU_REGION_SECONDARY => theme_get_setting(USWDS_MENU_REGION_SECONDARY),
      USWDS_MENU_REGION_SIDE => theme_get_setting(USWDS_MENU_REGION_SIDE),
      USWDS_MENU_REGION_FOOTER => theme_get_setting(USWDS_MENU_REGION_FOOTER),
    );
    foreach ($uswds_regions as $region => $configured_menu) {
      // If the menu matches exactly, we can stop.
      if ($menu_name == $configured_menu) {
        $uswds_region = $region;
        break;
      }
      // If the region is configured to use a pattern, check that for a match.
      if (USWDS_MENU_PATTERN_OPTION == $configured_menu) {
        $pattern = theme_get_setting($region . '_pattern');
        if (!empty($pattern) && strpos($menu_name, $pattern) !== FALSE) {
          $uswds_region = $region;
          break;
        }
      }
    }
  }
  return $uswds_region;
}
