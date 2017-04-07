<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_form_element_label().
 */
function uswds_preprocess_form_element_label(&$variables) {
  if (!empty($variables['required'])) {
    $variables['attributes']['class'][] = 'usa-input-required';
  }
}
