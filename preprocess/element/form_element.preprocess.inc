<?php

function uswds_preprocess_form_element(&$variables) {
  if (!empty($variables['errors'])) {
    $variables['error_id'] = $variables['element']['#attributes']['id'];
    $variables['attributes']['class'][] = 'usa-input-error';
  }
}
