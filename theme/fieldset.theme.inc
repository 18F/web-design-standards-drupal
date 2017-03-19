<?php

/**
 * @file
 * Override for this theme hook.
 */

/**
 * Overrides theme_fieldset().
 */
function uswds_fieldset($variables) {
  $element = $variables['element'];

  // For now, only need to do stuff differently if this is collapsible.
  $override = (!empty($element['#collapsible']));

  // Support for a random webform page.
  if ('webform_component_select' == $element['#theme']) {
    $element['#collapsed'] = TRUE;
    $override = TRUE;
  }

  if (!$override) {
    return theme_fieldset($variables);
  }

  // Keep some of the typical Drupal attributes.
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));

  // Prepare some USWDS-specific attributes.
  $expanded = ($element['#collapsed']) ? 'false' : 'true';
  $hidden = ($element['#collapsed']) ? 'true' : 'false';
  $aria_expanded = 'aria-expanded="' . $expanded . '"';
  $aria_hidden = 'aria-hidden="' . $hidden . '"';
  $id = drupal_html_id('uswds-drop');
  $element['#attributes']['class'][] = 'usa-accordion-bordered';

  // Outer div.
  $output = '<div' . drupal_attributes($element['#attributes']) . '>';

  // Start an unordered list, even though we will only have one item.
  $output .= '<ul class="usa-unstyled-list"><li>';

  // Add the button for expanding the fieldset. If the fieldset doesn't have a
  // title, we need to force one here.
  $title = (empty($element['#title'])) ? '&nbsp;' : $element['#title'];
  $output .= '<button type="button" class="usa-button-unstyled" aria-controls="' . $id . '" ' . $aria_expanded . '>' . $title . '</button>';

  // An inner div to contain the fieldset contents.
  $output .= '<div id="' . $id . '" class="fieldset-wrapper usa-accordion-content" ' . $aria_hidden . '>';

  // Element description if any.
  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }

  // Add any children or value inside the fieldset.
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }

  // Close the inner div.
  $output .= '</div>';

  // Close the unordered list.
  $output .= '</li></ul>';

  // Close the outer div.
  $output .= "</div>\n";

  return $output;
}
