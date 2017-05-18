<?php

/**
 * @file
 * Alterations for this form.
 */

use \Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_form_FORM_ID_alter().
 */
function uswds_form_user_login_form_alter(&$form, FormStateInterface $form_state, $form_id) {

  // Remove unnecessary help text.
  unset($form['name']['#description']);
  unset($form['pass']['#description']);

  // Allow logging in with username OR email.
  $form['name']['#title'] = t('Username or email address');
  $form['name']['#element_validate'][] = '_uswds_user_login_validate';
}

/**
 * Callback to validate the user login form.
 *
 * Credit for this code/approach goes to login_emailusername module.
 */
function _uswds_user_login_validate($element, FormStateInterface &$form_state) {
  $name_input = $form_state->getValue('name');

  // Try loading by email.
  if ($user = user_load_by_mail($name_input)) {
    // Set the username for further validation.
    $form_state->setValue('name', $user->getUsername());
    return TRUE;
  }

  // Try loading by username.
  if ($user = user_load_by_name($name_input)) {
    return TRUE;
  }

  return FALSE;
}
