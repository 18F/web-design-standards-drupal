<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_menu_local_tasks().
 */
function uswds_preprocess_menu_local_tasks(&$variables) {
  if (!empty($variables['primary'])) {
    foreach($variables['primary'] as $menu_item_key => $menu_attributes) {
      $variables['primary'][$menu_item_key]['#link']['localized_options']['attributes']['class'][] = 'usa-button';
      if (!empty($variables['primary'][$menu_item_key]['#active'])) {
        $variables['primary'][$menu_item_key]['#link']['localized_options']['attributes']['class'][] = 'usa-button-active';
      }
    }
  }
  if (!empty($variables['secondary'])) {
    foreach($variables['secondary'] as $menu_item_key => $menu_attributes) {
      $variables['secondary'][$menu_item_key]['#link']['localized_options']['attributes']['class'][] = 'usa-button';
      $variables['secondary'][$menu_item_key]['#link']['localized_options']['attributes']['class'][] = 'usa-button-secondary';
      if (!empty($variables['secondary'][$menu_item_key]['#active'])) {
        $variables['secondary'][$menu_item_key]['#link']['localized_options']['attributes']['class'][] = 'usa-button-active';
      }
    }
  }
}
