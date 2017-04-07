<?php

/**
 * @file
 * Override for this theme hook.
 */

/**
 * Override markup of all form element labels to add required class if needed.
 */
function uswds_form_element_label($variables) {
$element = $variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  $attributes = array();

  // If the element is required, a required class is added.
  if (!empty($element['#required'])) {
    $attributes['class'][] = 'usa-input-required';
  }

  $title = filter_xss_admin($element['#title']);

  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'][] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'][] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $t('!title', array('!title' => $title)) . "</label>\n";
}
