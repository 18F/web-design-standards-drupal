<?php

/**
 * @file
 * Alterations for this form.
 */

use \Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_form_FORM_ID_alter().
 */
function uswds_form_search_block_form_alter(&$form, FormStateInterface $form_state, $form_id) {

  $form['#attributes']['class'][] = 'usa-search';
  $form['#attributes']['class'][] = 'usa-search-small';

  // No need to control the size.
  unset($form['keys']['#size']);

  // Add the role of search.
  $form['keys']['#prefix'] = '<div role="search">';
  $form['actions']['#suffix'] = '</div>';

  // Add javascript classes if this is the extended header.
  if ('extended' == theme_get_setting('uswds_header_style')) {
    $form['#attributes']['class'][] = 'js-search-form';
    $form['#attributes']['class'][] = 'usa-sr-only';
  }

  // Remove the "value" so that the search button is only the icon, but hack
  // around the submit button for accessibility reasons.
  $form['actions']['submit']['#value'] = '';
  $form['actions']['submit']['#prefix'] = '<button type="submit"><span class="usa-sr-only">Search</span>';
  $form['actions']['submit']['#suffix'] = '</button>';
}
