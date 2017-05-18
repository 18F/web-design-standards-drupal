<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_html().
 */
function uswds_preprocess_html(&$variables) {

  // Set the paths to the favicons.
  $main_favicon = $GLOBALS['base_url'] . '/' . uswds_theme_trail_file('assets/img/favicons/favicon.png');
  $variables['favicon_path'] = str_replace('favicon.png', '', $main_favicon);
}
