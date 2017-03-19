<?php

/**
 * @file
 * Alterations for this form.
 */

 /**
 * Implements hook_form_FORM_ID_alter().
 */
function uswds_form_user_register_form_alter(&$form) {
  _uswds_simple_form_fieldset($form, t('Create an account'));
}
