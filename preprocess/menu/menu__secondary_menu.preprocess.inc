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
function uswds_preprocess_menu__secondary_menu(&$variables) {

  if (\Drupal::moduleHandler()->moduleExists('search') && theme_get_setting('uswds_search')) {
    // If this is a basic header, we put the search form after the menu.
    if ('extended' == theme_get_setting('uswds_header_style')) {
      $search_form = \Drupal::formBuilder()->getForm('\Drupal\search\Form\SearchBlockForm');
      $variables['search_form'] = $search_form;
      $search_item = '<li class="js-search-button-container"><button class="usa-header-search-button js-search-button">Search</button></li>';
      $variables['search_item'] = $search_item;
    }
  }
}
