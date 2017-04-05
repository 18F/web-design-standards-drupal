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
// Include all our form alter hooks.
$files = file_scan_directory(dirname(__FILE__) . '/forms', '/.form.inc/');
foreach ($files as $filepath => $file) {
  require_once $filepath;
}

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
 * Implements hook_menu_alter().
 */
function uswds_menu_alter(&$items) {
  // Consistency of login-related menu titles.
  $items['user/login']['title'] = 'Sign in';
  $items['user/login']['weight'] = -10;
  $items['user/password']['title'] = 'Forgot password?';
  $items['user/register']['title'] = 'Create an account';
}

/**
 * Helper function to get a simple fieldset/legend around form controls.
 *
 * @param $element
 *   The element array which will be altered by reference.
 *
 * @param $legend_text
 *   The text to include in the fieldset legend.
 */
function _uswds_simple_form_fieldset(&$element, $legend_text) {
  $element['fieldset_start'] = array(
    '#weight' => -999,
    '#markup' => '<fieldset><legend>' . $legend_text . '</legend>',
  );
  $element['fieldset_end'] = array(
    '#weight' => 999,
    '#markup' => '</fieldset>',
  );
}

/**
 * Helper function to convert a Drupal "container" into an accordion.
 */
function _uswds_container_to_fieldset(&$element, $button_text) {
  $element['#type'] = 'fieldset';
  $element['#collapsible'] = TRUE;
  $element['#title'] = $button_text;
}

/**
 * Implements hook_block_view_alter().
 *
 * This is used to tell what region a block is placed in, and is what allows us
 * to automatically tweak the markup of side navigation.
 */
function uswds_block_view_alter(&$build, $block) {

  if ('sidebar_first' != $block->region) {
    return;
  }

  if (empty($build['content']) || !is_array($build['content'])) {
    return;
  }

  if (empty($build['content']['#theme_wrappers'][0])) {
    return;
  }

  if (strpos($build['content']['#theme_wrappers'][0], 'menu_tree__') === FALSE) {
    return;
  }

  // If we're still here, we must be looking at a core menu block in a sidebar.
  _uswds_mark_side_navigation_items($build['content']);
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

/**
 * Implements hook_theme().
 */
function uswds_theme($existing, $type, $theme, $path) {
  return array(
    'government_banner' => array(
      'path' => $path . '/templates/uswds',
      'variables' => array(
        'image_base' => array(),
      ),
    ),
  );
}