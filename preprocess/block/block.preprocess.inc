<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_block().
 */
function uswds_preprocess_block(&$variables) {
  $variables['attributes']['class'][] = 'uswds-block';
  $variables['attributes']['class'][] = 'uswds-block-' . $variables['plugin_id'];
}
