<?php

/**
 * @file
 * Override for this theme hook.
 */

/**
 * Override theme_status_messages().
 */
function uswds_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  $status_mapping = array(
    'status' => 'usa-alert-info',
    'error' => 'usa-alert-error',
    'warning' => 'usa-alert-warning',
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $classes = 'messages usa-alert';
    if (isset($status_mapping[$type])) {
      $classes .= ' ' . $status_mapping[$type];
    }
    $output .= "<div class=\"$classes\"><div class=\"usa-alert-body\">\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="usa-alert-heading element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul class=\"usa-alert-text\">\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= "<p class=\"usa-alert-text\">" . reset($messages) . "</p>";
    }
    $output .= "</div></div>\n";
  }
  return $output;
}
