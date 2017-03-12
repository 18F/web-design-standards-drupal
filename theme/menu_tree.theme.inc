<?php

/**
 * @file
 * Override for this theme hook.
 */

/**
 * Override markup of all menu trees to allow easier adding of classes/wrappers.
 *
 * This supports four items that can be added to the $variables array in
 * preprocessor functions:
 *   - uswds_menu_attributes: An associative array of attributes to place on
 *     the <ul> element.
 *   - uswds_menu_prefix: A string of text to add before the <ul> element.
 *   - uswds_menu_suffix: A string of text to add after the <ul> element.
 *   - uswds_menu_tree_only: If TRUE, the <ul> wrapper will not be added.
 */
function uswds_menu_tree($variables) {
  $output = '';
  if (!empty($variables['uswds_menu_attributes'])) {
    $output = '<ul ' . drupal_attributes($variables['uswds_menu_attributes']) . '>' . $variables['tree'] . '</ul>';
  }
  elseif (!empty($variables['uswds_menu_tree_only'])) {
    $output = $variables['tree'];
  }
  else {
    $output = theme_menu_tree($variables);
  }
  if (!empty($variables['uswds_menu_prefix'])) {
    $output = $variables['uswds_menu_prefix'] . $output;
  }
  if (!empty($variables['uswds_menu_suffix'])) {
    $output = $output . $variables['uswds_menu_suffix'];
  }
  return $output;
}
