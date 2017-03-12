<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_page().
 */
function uswds_preprocess_page(&$variables) {
  // Set the path to the base theme.
  $variables['base_theme_path'] = drupal_get_path('theme', 'uswds');

  // Provide the agency name, URL, and logo.
  $variables['footer_agency'] = theme_get_setting('uswds_footer_secondary');
  $variables['footer_agency_name'] = theme_get_setting('uswds_footer_secondary_agency_name');
  $variables['footer_agency_url'] = theme_get_setting('uswds_footer_secondary_agency_url');
  $variables['footer_agency_logo'] = base_path() . uswds_theme_trail_file(theme_get_setting('uswds_footer_secondary_agency_logo'));

  // Decide what width the content area should have.
  $sidebar_first = (!empty($variables['page']['sidebar_first']));
  $sidebar_second = (!empty($variables['page']['sidebar_second']));
  if ($sidebar_first && $sidebar_second) {
    $variables['content_class'] = 'usa-width-one-half';
  }
  elseif ($sidebar_first || $sidebar_second) {
    $variables['content_class'] = 'usa-width-three-fourths';
  }
  else {
    $variables['content_class'] = 'usa-width-full';
  }

  // Decide on the type of header.
  $variables['header_style'] = 'usa-header-' . theme_get_setting('uswds_header_style');
  $variables['header_classes'] = 'usa-header ' . $variables['header_style'];
  if (theme_get_setting('uswds_header_mega')) {
    $variables['header_classes'] .= ' ' . $variables['header_style'] . '-megamenu';
  }
  // And some helpful flags.
  $variables['header_basic'] = ('usa-header-basic' == $variables['header_style']);
  $variables['header_extended'] = ('usa-header-extended' == $variables['header_style']);

  // Decide on the type of footer.
  $variables['footer_style'] = 'usa-footer-' . theme_get_setting('uswds_footer_style');
  $variables['footer_classes'] = 'usa-footer ' . $variables['footer_style'];
}
