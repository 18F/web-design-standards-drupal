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
function uswds_preprocess_menu__footer_menu(&$variables) {

  $variables['footer_style'] = theme_get_setting('uswds_footer_style');
}
