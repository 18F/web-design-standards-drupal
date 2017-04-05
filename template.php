<?php
/**
 * @file
 * Theme code, mostly to make Drupal 7's markup work with USWDS.
 *
 * Note: If you are looking for theme overrides or preprocess functions, check
 * the uswds/theme and uswds/preprocess folders.
 */

// Bring in our includes. Constants must be required first.
require_once dirname(__FILE__) . '/includes/constants.inc';
require_once dirname(__FILE__) . '/includes/base_themes.inc';
require_once dirname(__FILE__) . '/includes/forms.inc';
require_once dirname(__FILE__) . '/includes/menus.inc';

// Include all our form alter hooks.
$files = file_scan_directory(dirname(__FILE__) . '/forms', '/.form.inc/');
foreach ($files as $filepath => $file) {
  require_once $filepath;
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