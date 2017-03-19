<?php

/**
 * @file
 * Alterations for this form.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function uswds_form_user_login_alter(&$form) {
  drupal_set_title(t('Sign in'));
  $form['pass']['#description'] = '';
  $form['#attributes']['class'][] = 'usa-form';
  $form['actions']['submit']['#value'] = t('Sign in');
  unset($form['name']['#description']);
}
