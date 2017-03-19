<?php

/**
 * @file
 * Alterations for this form.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function uswds_form_user_pass_alter(&$form) {
  _uswds_simple_form_fieldset($form, t('Forgot password?'));
}
