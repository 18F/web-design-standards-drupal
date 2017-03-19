<?php

/**
 * @file
 * Alterations for this form.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function uswds_form_user_login_alter(&$form) {

  // For accessibility, wrap in fieldset.
  _uswds_simple_form_fieldset($form, t('Sign in'));

  // Remove unnecessary help text.
  unset($form['name']['#description']);
  unset($form['pass']['#description']);

  // Submit text consistent with page title.
  $form['actions']['submit']['#value'] = t('Sign in');

  // Allow logging in with username OR email.
  $form['name']['#title'] = t('Username or email address');
  $form['name']['#element_validate'][] = '_uswds_user_login_validate';

  // Add some helpful links.
  $form['link_register'] = array(
    '#weight' => -10,
    '#markup' => '<span>' . t('or') . ' ' . l(t('create an account'), 'user/register') . '</span>',
  );
  $form['link_forgot_password'] = array(
    '#weight' => 10,
    '#markup' => '<p>' . l(t('Forgot password?'), 'user/password') . '</p>',
  );
}

/**
 * Callback to validate the user login form.
 *
 * Credit for this code/approach goes to login_emailusername module.
 */
function _uswds_user_login_validate($form, &$form_state) {
  $name_input = $form_state['values']['name'];

  // Try loading by email.
  if ($user = user_load_by_mail($name_input)) {
    // Set the username for further validation.
    $form_state['values']['name'] = $user->name;
    return TRUE;
  }

  // Try loading by username.
  if ($user = user_load_by_name($name_input)) {
    return TRUE;
  }

  return FALSE;
}
