<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_menu__REGION().
 *
 * This made possible by our custom theme suggestion.
 * @see uswds_theme_suggestions_menu_alter().
 */
function uswds_preprocess_menu__primary_menu(&$variables) {

  $variables['megamenu'] = theme_get_setting('uswds_header_mega');

  if (\Drupal::moduleHandler()->moduleExists('search') && theme_get_setting('uswds_search')) {
    // If this is a basic header, we put the search form after the menu.
    if ('basic' == theme_get_setting('uswds_header_style')) {
      $search_form = \Drupal::formBuilder()->getForm('\Drupal\search\Form\SearchBlockForm');
      $variables['search_form'] = $search_form;
    }
  }
}
