<?php

/**
 * Custom theme setting form elements for the USWDS theme.
 */

include_once(__DIR__ . '/includes/uswds.constants.inc');

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function uswds_form_system_theme_settings_alter(&$form, $form_state) {
  $menu_options = menu_get_menus();
  $menu_options[USWDS_MENU_PATTERN_OPTION] = t('-- Use a wildcard pattern --');
  $pattern_description = t('Any menu whose machine name matches this pattern will be treated as this type of menu. For example, entering "menu-og" here will match "menu-og-123".');

  // Menu settings.
  $form['uswds_menu_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('USWDS menu settings'),
  );
  // Primary menus.
  $form['uswds_menu_fieldset'][USWDS_MENU_REGION_PRIMARY] = array(
    '#type' => 'select',
    '#options' => $menu_options,
    '#title' => t('Primary menu'),
    '#default_value' => theme_get_setting(USWDS_MENU_REGION_PRIMARY),
    '#description' => t('Choose a menu to treat as the primary menu.'),
  );
  $form['uswds_menu_fieldset'][USWDS_MENU_REGION_PRIMARY . '_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Primary menu wildcard pattern'),
    '#default_value' => theme_get_setting(USWDS_MENU_REGION_PRIMARY . '_pattern'),
    '#description' => $pattern_description,
    '#states' => array(
      'visible' => array(
        ':input[name="' . USWDS_MENU_REGION_PRIMARY . '"]' => array('value' => USWDS_MENU_PATTERN_OPTION),
      ),
    ),
  );

  // The secondary menu.
  $form['uswds_menu_fieldset'][USWDS_MENU_REGION_SECONDARY] = array(
    '#type' => 'select',
    '#options' => $menu_options,
    '#title' => t('Secondary menu'),
    '#default_value' => theme_get_setting(USWDS_MENU_REGION_SECONDARY),
    '#description' => t('Choose a menu to treat as the secondary menu.'),
  );
  $form['uswds_menu_fieldset'][USWDS_MENU_REGION_SECONDARY . '_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Secondary menu wildcard pattern'),
    '#default_value' => theme_get_setting(USWDS_MENU_REGION_SECONDARY . '_pattern'),
    '#description' => $pattern_description,
    '#states' => array(
      'visible' => array(
        ':input[name="' . USWDS_MENU_REGION_SECONDARY . '"]' => array('value' => USWDS_MENU_PATTERN_OPTION),
      ),
    ),
  );

  // The side menu.
  $form['uswds_menu_fieldset'][USWDS_MENU_REGION_SIDE] = array(
    '#type' => 'select',
    '#options' => $menu_options,
    '#title' => t('Side menu'),
    '#default_value' => theme_get_setting(USWDS_MENU_REGION_SIDE),
    '#description' => t('Choose a menu to treat as the side menu.'),
  );
  $form['uswds_menu_fieldset'][USWDS_MENU_REGION_SIDE . '_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Side menu wildcard pattern'),
    '#default_value' => theme_get_setting(USWDS_MENU_REGION_SIDE . '_pattern'),
    '#description' => $pattern_description,
    '#states' => array(
      'visible' => array(
        ':input[name="' . USWDS_MENU_REGION_SIDE . '"]' => array('value' => USWDS_MENU_PATTERN_OPTION),
      ),
    ),
  );

  // The footer menu.
  $form['uswds_menu_fieldset'][USWDS_MENU_REGION_FOOTER] = array(
    '#type' => 'select',
    '#options' => $menu_options,
    '#title' => t('Footer menu'),
    '#default_value' => theme_get_setting(USWDS_MENU_REGION_FOOTER),
    '#description' => t('Choose a menu to treat as the footer menu.'),
  );
  $form['uswds_menu_fieldset'][USWDS_MENU_REGION_FOOTER . '_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Footer menu wildcard pattern'),
    '#default_value' => theme_get_setting(USWDS_MENU_REGION_FOOTER . '_pattern'),
    '#description' => $pattern_description,
    '#states' => array(
      'visible' => array(
        ':input[name="' . USWDS_MENU_REGION_FOOTER . '"]' => array('value' => USWDS_MENU_PATTERN_OPTION),
      ),
    ),
  );

  // Header style.
  $form['header_style_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Header settings'),
    'uswds_header_style' => array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Choose a style of header to use'),
      '#options' => array(
        USWDS_HEADER_STYLE_BASIC => t('Basic'),
        USWDS_HEADER_STYLE_EXTENDED => t('Extended'),
      ),
      '#default_value' => theme_get_setting('uswds_header_style'),
    ),
    'uswds_header_mega' => array(
      '#type' => 'checkbox',
      '#title' => t('Use megamenus in the header?'),
      '#description' => t('Site building note: Megamenus require hierarchical three-level menus, where the second level of menu items is not rendered, but instead is used to determine the "columns" for the megamenu.'),
      '#default_value' => theme_get_setting('uswds_header_mega'),
    ),
  );

  // Footer style.
  $form['footer_style_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Footer settings'),
    'uswds_footer_style' => array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Choose a style of footer to use'),
      '#options' => array(
        USWDS_FOOTER_STYLE_BIG => t('Big'),
        USWDS_FOOTER_STYLE_MEDIUM => t('Medium'),
        USWDS_FOOTER_STYLE_SLIM => t('Slim'),
      ),
      '#default_value' => theme_get_setting('uswds_footer_style'),
    ),
    'uswds_footer_secondary' => array(
      '#type' => 'checkbox',
      '#title' => t('Add agency information in the footer\'s secondary section?'),
      '#default_value' => theme_get_setting('uswds_footer_secondary'),
    ),
    'uswds_footer_secondary_agency_name' => array(
      '#type' => 'textfield',
      '#title' => t('Footer agency name'),
      '#default_value' => theme_get_setting('uswds_footer_secondary_agency_name'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_secondary"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_footer_secondary_agency_url' => array(
      '#type' => 'textfield',
      '#title' => t('Footer agency URL'),
      '#default_value' => theme_get_setting('uswds_footer_secondary_agency_url'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_secondary"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_footer_secondary_agency_logo' => array(
      '#type' => 'textfield',
      '#title' => t("Path to footer agency logo (from this theme's folder)"),
      '#description' => t('For example: images/footer-agency.png'),
      '#default_value' => theme_get_setting('uswds_footer_secondary_agency_logo'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_secondary"]' => array('checked' => TRUE),
        ),
      ),
    ),
  );
}
