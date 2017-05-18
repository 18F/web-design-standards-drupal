<?php

/**
 * @file
 * Alterations for this form.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function uswds_form_user_profile_form_alter(&$form) {
  if (!empty($form['account'])) {
    _uswds_container_to_fieldset($form['account'], t('Account settings'));
  }
  if (!empty($form['picture'])) {
    _uswds_container_to_fieldset($form['picture'], t('Picture'));
  }
}
