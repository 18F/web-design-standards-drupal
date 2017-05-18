<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_page_title().
 */
function uswds_preprocess_page_title(&$variables) {
  $variables['title_attributes']['class'][] = 'uswds-page-title';
}
