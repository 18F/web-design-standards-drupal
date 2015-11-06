<?php

/**
 *
 * Implements hook_preprocess_html().
 *
 */
function us_web_design_standards_preprocess_html(&$variables) {
  // set the path to the theme and make it available in html.tpl.php
  $variables['theme_path'] = drupal_get_path('theme', 'us_web_design_standards');
}
