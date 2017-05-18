<?php

/**
 * @file
 * Alterations for ALL forms.
 */

use \Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_form_alter().
 */
function uswds_form_alter(&$form, FormStateInterface $form_state, $form_id) {
  // For public-facing pages, limit the width of forms.
  if (!\Drupal::service('router.admin_context')->isAdminRoute()) {
    $form['#attributes']['class'][] = 'usa-form-large';
  }
}
