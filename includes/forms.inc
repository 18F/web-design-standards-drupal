<?php

/**
 * @file
 * Utility code related to forms.
 */

/**
 * Helper function to convert a Drupal "container" into an accordion.
 */
function _uswds_container_to_fieldset(&$element, $button_text) {
  $element['#type'] = 'fieldset';
  $element['#collapsible'] = TRUE;
  $element['#title'] = $button_text;
}
