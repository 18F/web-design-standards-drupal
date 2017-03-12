<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_html().
 */
function uswds_preprocess_html(&$variables) {
  // set the path to the theme and make it available in html.tpl.php
  $variables['theme_path'] = drupal_get_path('theme', 'uswds');
}
