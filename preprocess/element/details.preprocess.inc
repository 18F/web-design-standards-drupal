<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_details().
 */
function uswds_preprocess_details(&$variables) {

  // Add the necessary class to the summary (which we'll render as a button).
  $variables['summary_attributes']->addClass('usa-accordion-button');

  // Check to see if this should be uncollapsible. This could be the case if
  // if has errors in it, or if it has been specifically flagged as such.
  $uncollapsible = !empty($variables['element']['#uswds_uncollapsible']);
  if (!$uncollapsible) {
    $inline_form_errors = \Drupal::moduleHandler()->moduleExists('inline_form_errors');
    if ($inline_form_errors) {
      $uncollapsible = _uswds_is_error_in_array($variables['element']);
    }
  }
  if ($uncollapsible) {
    $variables['element']['#open'] = TRUE;
    $variables['uncollapsible'] = TRUE;
  }
  else {
    // Otherwise is this is going to be collapsible, we need to force a title.
    if (empty($variables['title'])) {
      $variables['title'] = '&nbsp;';
    }
  }

  // Drupal defaults to open/expanded details, unless '#open' is FALSE, so we
  // have to match that, even though it would be nice to default to closed.
  $open = 'true';
  if (isset($variables['element']['#open']) && !$variables['element']['#open']) {
    $open = 'false';
  }
  $variables['summary_attributes']['aria-expanded'] = $open;
}

/**
 * Helper method to find errors in a render array.
 */
function _uswds_is_error_in_array($element) {
  if (!empty($element['#errors'])) {
    return TRUE;
  }
  foreach (\Drupal\Core\Render\Element::children($element) as $key) {
    if (_uswds_is_error_in_array($element[$key])) {
      return TRUE;
    }
  }
  return FALSE;
}
