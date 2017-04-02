<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_vertical_tabs().
 */
function uswds_preprocess_vertical_tabs(&$variables) {
  $prefix = '<ul class="usa-accordion-bordered usa-unstyled-list">';
  $suffix = '</ul><!-- USWDS fieldset end -->';
  $content = $variables['children'];
  $content = str_replace($prefix, '', $content);
  $content = str_replace($suffix, '', $content);
  $variables['children'] = \Drupal\Core\Render\Markup::create($content);

  $variables['attributes']['class'][] = 'usa-accordion-bordered';
}
