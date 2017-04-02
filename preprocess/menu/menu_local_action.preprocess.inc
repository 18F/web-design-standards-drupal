<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_menu_local_action().
 */
function uswds_preprocess_menu_local_action(&$variables) {
  $variables['link']['#options']['attributes']['class'][] = 'usa-button';
  $variables['link']['#options']['attributes']['class'][] = 'usa-button-outline';
}
