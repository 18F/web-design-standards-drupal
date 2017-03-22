<?php

/**
 * Custom theme setting form elements for the USWDS theme.
 */

include_once(__DIR__ . '/includes/uswds.constants.inc');

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function uswds_form_system_theme_settings_alter(&$form, $form_state) {
  $menu_options[USWDS_MENU_NONE] = t('-- None --');
  $menu_options += menu_get_menus();
  $menu_options[USWDS_MENU_PATTERN_OPTION] = t('-- Use a wildcard pattern --');

  $pattern_description = t('Any menu whose machine name matches this pattern will be treated as this type of menu. For example, entering "menu-og" here will match "menu-og-123".');

  // Menu settings.
  $form['uswds_menu_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('USWDS menu settings'),
  );

  // Some help text about primary/secondary menus.
  $form['uswds_menu_fieldset']['menu-help'] = array(
    '#markup' => t('NOTE: To set sources for your primary and secondary navigation, go to !link.', array(
      '!link' => l('/admin/structure/menu/settings', 'admin/structure/menu/settings')
    )),
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

  // Whether to display the search bar in the secondary menu.
  $form['uswds_menu_fieldset']['uswds_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display a search form in the navigation area?'),
    '#default_value' => theme_get_setting('uswds_search'),
  );
  if (!module_exists('search')) {
    $form['uswds_menu_fieldset']['uswds_search']['#description'] = t('Requires the core Search module to be enabled.');
  }

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
    'uswds_footer_agency' => array(
      '#type' => 'checkbox',
      '#title' => t('Add agency information in the footer?'),
      '#default_value' => theme_get_setting('uswds_footer_agency'),
    ),
    'uswds_footer_agency_name' => array(
      '#type' => 'textfield',
      '#title' => t('Footer agency name'),
      '#default_value' => theme_get_setting('uswds_footer_agency_name'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_agency"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_footer_agency_url' => array(
      '#type' => 'textfield',
      '#title' => t('Footer agency URL'),
      '#default_value' => theme_get_setting('uswds_footer_agency_url'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_agency"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_footer_agency_logo' => array(
      '#type' => 'textfield',
      '#title' => t("Path to footer agency logo (from this theme's folder)"),
      '#description' => t('For example: images/footer-agency.png'),
      '#default_value' => theme_get_setting('uswds_footer_agency_logo'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_agency"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_contact_center' => array(
      '#type' => 'textfield',
      '#title' => t('Name of contact center'),
      '#default_value' => theme_get_setting('uswds_contact_center'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_agency"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_email' => array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#default_value' => theme_get_setting('uswds_email'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_agency"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_phone' => array(
      '#type' => 'textfield',
      '#title' => t('Phone'),
      '#default_value' => theme_get_setting('uswds_phone'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_agency"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_facebook' => array(
      '#type' => 'textfield',
      '#title' => t('Facebook link'),
      '#default_value' => theme_get_setting('uswds_facebook'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_agency"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_twitter' => array(
      '#type' => 'textfield',
      '#title' => t('Twitter link'),
      '#default_value' => theme_get_setting('uswds_twitter'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_agency"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_youtube' => array(
      '#type' => 'textfield',
      '#title' => t('Youtube link'),
      '#default_value' => theme_get_setting('uswds_youtube'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_agency"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'uswds_rss' => array(
      '#type' => 'textfield',
      '#title' => t('RSS feed'),
      '#default_value' => theme_get_setting('uswds_rss'),
      '#states' => array(
        'visible' => array(
          ':input[name="uswds_footer_agency"]' => array('checked' => TRUE),
        ),
      ),
    ),
  );
}
