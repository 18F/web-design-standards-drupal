<?php
/**
 * @file
 * Theme code, mostly to make Drupal 7's markup work with USWDS.
 *
 * Note: If you are looking for theme overrides or preprocess functions, check
 * the uswds/theme and uswds/preprocess folders.
 */

// Bring in our includes. Constants must be required first.
require_once dirname(__FILE__) . '/includes/uswds.constants.inc';
require_once dirname(__FILE__) . '/includes/uswds.stolen-from-omega.inc';

/**
 * Helper function to see if a menu name is one of our special USWDS menus.
 */
function _uswds_get_region_for_menu($menu_name) {

  // Cache this statically since this is called for each menu link.
  $uswds_region = &drupal_static(__FUNCTION__ . $menu_name);
  if (!isset($uswds_region)) {
    $uswds_region = FALSE;
    $uswds_regions = array(
      USWDS_MENU_REGION_PRIMARY => variable_get('menu_main_links_source', USWDS_MENU_NONE),
      USWDS_MENU_REGION_SECONDARY => variable_get('menu_secondary_links_source', USWDS_MENU_NONE),
      USWDS_MENU_REGION_SIDE => theme_get_setting(USWDS_MENU_REGION_SIDE),
      USWDS_MENU_REGION_FOOTER => theme_get_setting(USWDS_MENU_REGION_FOOTER),
    );
    foreach ($uswds_regions as $region => $configured_menu) {
      if (USWDS_MENU_NONE == $configured_menu || empty($configured_menu)) {
        continue;
      }
      // If the menu matches exactly, we can stop looping.
      elseif ($menu_name == $configured_menu) {
        $uswds_region = $region;
        break;
      }
      // If the region is configured to use a pattern, check that for a match.
      elseif (USWDS_MENU_PATTERN_OPTION == $configured_menu) {
        $pattern = theme_get_setting($region . '_pattern');
        if (!empty($pattern) && strpos($menu_name, $pattern) !== FALSE) {
          // If we found a match, we can stop looping.
          $uswds_region = $region;
          break;
        }
      }
    }
  }
  return $uswds_region;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function uswds_form_search_block_form_alter(&$form) {
  $form['#attributes']['class'][] = 'usa-search';
  $form['#attributes']['class'][] = 'usa-search-small';

  // Add javascript classes if this is the extended header.
  if (USWDS_HEADER_STYLE_EXTENDED == theme_get_setting('uswds_header_style')) {
    $form['#attributes']['class'][] = 'js-search-form';
    $form['#attributes']['class'][] = 'usa-sr-only';
  }

  // Remove the "value" so that the search button is only the icon, but hack
  // around the submit button for accessibility reasons.
  $form['actions']['submit']['#value'] = '';
  $form['actions']['submit']['#attributes']['style'][] = 'display:none;';
  $form['actions']['submit']['#prefix'] = '<button type="submit"><span class="usa-sr-only">Search';
  $form['actions']['submit']['#suffix'] = '</button>';
}

/**
 * Implements hook_form_alter().
 */
function uswds_form_alter(&$form, $form_state) {
  $form['#validate'][] = '_uswds_form_validation';
}

/**
 * Custom validation callback to set any inline errors needed.
 */
function _uswds_form_validation(&$form, &$form_state) {
  $form_errors = form_get_errors();
  if (!empty($form_errors)) {
    _uswds_element_errors_set($form);
  }
}

/**
 * Recursive function to set inline error messages on elements.
 *
 * Credit goes to Inline Form Errors (ife) module for this code.
 */
function _uswds_element_errors_set(&$element) {
  if (!isset($_SESSION['messages']['error'])) {
    return;
  }

  // Check for errors and settings.
  $errors = form_get_errors();
  $element_id = implode('][', $element['#parents']);
  if (!empty($errors[$element_id])) {
    $error_message = $errors[$element_id];

    // Get error id.
    $error_id = array_search($error_message, $_SESSION['messages']['error']);

    if ($error_id !== FALSE) {
      unset($_SESSION['messages']['error'][$error_id]);
      $_SESSION['messages']['error'] = array_values($_SESSION['messages']['error']);

      if (count($_SESSION['messages']['error']) <= 0) {
        unset($_SESSION['messages']['error']);
      }

      $error_label = t('Form error');
      $element['#prefix'] = '<div class="usa-input-error">';
      $element['#prefix'] .= '<label class="usa-input-error-label" for="input-error">' . $error_label . '</label>';
      $element['#prefix'] .= '<span class="usa-input-error-message" id="input-error-message" role="alert">' . $error_message . '</span>';
      $element['#suffix'] = '</div>';

      // Found a matching error, no need to continue.
      return;
    }
  }

  // Recurse through all children.
  foreach (element_children($element) as $key) {
    if (isset($element[$key]) && $element[$key]) {
      _uswds_element_errors_set($element[$key]);
    }
  }
}
