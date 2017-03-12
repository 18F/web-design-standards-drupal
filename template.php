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
      USWDS_MENU_REGION_PRIMARY => variable_get('menu_main_links_source', USWDS_MENU_NONE),
      USWDS_MENU_REGION_SECONDARY => variable_get('menu_secondary_links_source', USWDS_MENU_NONE),
      USWDS_MENU_REGION_SIDE => theme_get_setting(USWDS_MENU_REGION_SIDE),
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
      // If the region is configured to use a pattern, check that for a match.
      elseif (USWDS_MENU_PATTERN_OPTION == $configured_menu) {
        $pattern = theme_get_setting($region . '_pattern');
        if (!empty($pattern) && strpos($menu_name, $pattern) !== FALSE) {
          // If we found a match, we can stop looping.
          $uswds_region = $region;
          break;
        }
      }
    }
  }
  return $uswds_region;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function uswds_form_search_block_form_alter(&$form) {
  $form['#attributes']['class'][] = 'usa-search';
  $form['#attributes']['class'][] = 'usa-search-small';

  // Add javascript classes if this is the extended header.
  if (USWDS_HEADER_STYLE_EXTENDED == theme_get_setting('uswds_header_style')) {
    $form['#attributes']['class'][] = 'js-search-form';
    $form['#attributes']['class'][] = 'usa-sr-only';
  }

  // Remove the "value" so that the search button is only the icon, but hack
  // around the submit button for accessibility reasons.
  $form['actions']['submit']['#value'] = '';
  $form['actions']['submit']['#attributes']['style'][] = 'display:none;';
  $form['actions']['submit']['#prefix'] = '<button type="submit"><span class="usa-sr-only">Search';
  $form['actions']['submit']['#suffix'] = '</button>';
}
