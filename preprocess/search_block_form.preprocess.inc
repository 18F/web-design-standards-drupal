<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_serach_block_form().
 */
function uswds_preprocess_search_block_form(&$variables) {
  // This is totally hacky, but seems necessary in order to change the form's
  // input type to "search" instead of "text". Though, perhaps a better
  // alternative might be to add the Elements module as a dependency and simply
  // change the #type in a form alter hook to "searchfield".
  $markup = $variables['search_form'];
  $markup = str_replace('type="text"', 'type="search"', $markup);
  $variables['search_form'] = $markup;
}
