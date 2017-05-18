<?php

/**
 * @file
 * Alterations for this form.
 */

use \Drupal\Core\Form\FormStateInterface;

function uswds_form_node_form_alter(&$form, FormStateInterface $form_state, $form_id) {

  // Make the delete button on node forms pop.
  $form['actions']['delete']['#attributes']['class'][] = 'usa-button';
  $form['actions']['delete']['#attributes']['class'][] = 'usa-button-secondary';
}
