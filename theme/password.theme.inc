<?php

/**
 * @file
 * Override for this theme hook.
 */

/**
 * Overrides theme_password().
 */
function uswds_password($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'password';
  element_set_attributes($element, array('id', 'name', 'size', 'maxlength'));
  _form_set_class($element, array('form-text'));
  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';
  $title = t('Show password');
  $output .= '
    <p class="usa-form-note">
      <a title="' . $title . '" href="javascript:void(0);" class="usa-show_password" aria-controls="' . $element['#id'] . '">' . $title . '</a>
    </p>
  ';
  return $output;
}
