<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_block__local_actions_block().
 */
function uswds_preprocess_block__local_actions_block(&$variables) {
  $variables['attributes']['class'][] = 'uswds-horizontal-list';
  $variables['attributes']['class'][] = 'usa-unstyled-list';
}
