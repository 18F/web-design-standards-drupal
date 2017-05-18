<?php

/**
 * @file
 * Alterations for ALL forms.
 */

/**
 * Implements hook_form_alter().
 */
function uswds_form_alter(&$form, $form_state) {
  // Add custom validation for inline form errors.
  $form['#validate'][] = '_uswds_form_validation';
  // For public-facing pages, limit the width of forms.
  if (!path_is_admin(current_path())) {
    $form['#attributes']['class'][] = 'usa-form-large';
  }
}

/**
 * Custom validation callback to set any inline errors needed.
 */
function _uswds_form_validation(&$form, &$form_state) {
  $form_errors = form_get_errors();
  if (!empty($form_errors)) {
    _uswds_element_errors_set($form);
  }
}

/**
 * Recursive function to set inline error messages on elements.
 *
 * Credit goes to Inline Form Errors (ife) module for this code.
 */
function _uswds_element_errors_set(&$element) {
  if (!isset($_SESSION['messages']['error'])) {
    return;
  }

  // Check for errors and settings.
  $errors = form_get_errors();
  $element_id = implode('][', $element['#parents']);
  if (!empty($errors[$element_id])) {
    $error_message = $errors[$element_id];

    // Get error id.
    $error_id = array_search($error_message, $_SESSION['messages']['error']);

    if ($error_id !== FALSE) {
      unset($_SESSION['messages']['error'][$error_id]);
      $_SESSION['messages']['error'] = array_values($_SESSION['messages']['error']);

      if (count($_SESSION['messages']['error']) <= 0) {
        unset($_SESSION['messages']['error']);
      }

      $error_label = t('Form error');
      $element['#prefix'] = '<div class="usa-input-error">';
      $element['#prefix'] .= '<label class="usa-input-error-label" for="input-error">' . $error_label . '</label>';
      $element['#prefix'] .= '<span class="usa-input-error-message" id="input-error-message" role="alert">' . $error_message . '</span>';
      $element['#suffix'] = '</div>';

      // Found a matching error, no need to continue.
      return;
    }
  }

  // Recurse through all children.
  foreach (element_children($element) as $key) {
    if (isset($element[$key]) && $element[$key]) {
      _uswds_element_errors_set($element[$key]);
    }
  }
}
