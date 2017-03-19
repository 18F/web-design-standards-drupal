<?php

function uswds_password($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'password';
  element_set_attributes($element, array('id', 'name', 'size', 'maxlength'));
  _form_set_class($element, array('form-text'));
  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';
  $output .= '
    <p class="usa-form-note">
      <a title="Show password" href="javascript:void(0);" class="usa-show_password" aria-controls="' . $element['#id'] . '">Show Password</a>
    </p>
  ';
  return $output;
}
