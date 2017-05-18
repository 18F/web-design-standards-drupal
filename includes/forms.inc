<?php

/**
 * @file
 * Utility code related to forms.
 */

/**
 * Helper function to get a simple fieldset/legend around form controls.
 *
 * @param $element
 *   The element array which will be altered by reference.
 *
 * @param $legend_text
 *   The text to include in the fieldset legend.
 */
function _uswds_simple_form_fieldset(&$element, $legend_text) {
  $element['fieldset_start'] = [
    '#weight' => -999,
    '#markup' => '<fieldset><legend>' . $legend_text . '</legend>',
    '#allowed_tags' => ['fieldset', 'legend'],
  ];
  $element['fieldset_end'] = [
    '#weight' => 999,
    '#markup' => '</fieldset>',
    '#allowed_tags' => ['fieldset'],
  ];
}

/**
 * Helper function to convert a Drupal "container" into an accordion.
 */
function _uswds_container_to_details(&$element, $button_text, $uncollapsible = FALSE) {
  $element['#type'] = 'details';
  $element['#open'] = TRUE;
  $element['#title'] = $button_text;
  $element['#uswds_uncollapsible'] = $uncollapsible;
}
