<?php

/**
 * Custom theme setting form elements for the USWDS theme.
 */

use \Drupal\Core\Link;
use \Drupal\Core\Url;

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function uswds_form_system_theme_settings_alter(&$form, \Drupal\Core\Form\FormStateInterface &$form_state, $form_id = NULL) {

  // Header style.
  $form['header_style_fieldset'] = [
    '#type' => 'details',
    '#title' => t('Header settings'),
    '#open' => TRUE,
    'menu-help' => [
      '#markup' => t('NOTE: To set sources for your navigation, go to /admin/structure/block and place menu blocks into the desired "[blank] Menu" region. For example, your primary menu block should go into the "Primary Menu" region.'),
    ],
    'uswds_header_style' => [
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Choose a style of header to use'),
      '#options' => [
        'basic' => t('Basic'),
        'extended' => t('Extended'),
      ],
      '#default_value' => theme_get_setting('uswds_header_style'),
    ],
    'uswds_header_mega' => [
      '#type' => 'checkbox',
      '#title' => t('Use megamenus in the header?'),
      '#description' => t('Site building note: Megamenus require hierarchical three-level menus, where the second level of menu items is not rendered, but instead is used to determine the "columns" for the megamenu.'),
      '#default_value' => theme_get_setting('uswds_header_mega'),
    ],
    'uswds_search' => [
      '#type' => 'checkbox',
      '#title' => t('Display a search form in the primary navigation area?'),
      '#default_value' => theme_get_setting('uswds_search'),
    ],
    'uswds_government_banner' => [
      '#type' => 'checkbox',
      '#title' => t('Display the official U.S. government banner at the top of each page?'),
      '#default_value' => theme_get_setting('uswds_government_banner'),
    ],
  ];

  if (!\Drupal::moduleHandler()->moduleExists('search')) {
    $form['header_style_fieldset']['uswds_search']['#description'] = t('Requires the core Search module to be enabled.');
  }

  // Footer style.
  $form['footer_style_fieldset'] = [
    '#type' => 'details',
    '#title' => t('Footer settings'),
    '#open' => TRUE,
    'uswds_footer_style' => [
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Choose a style of footer to use'),
      '#options' => [
        'big' => t('Big'),
        'medium' => t('Medium'),
        'slim' => t('Slim'),
      ],
      '#default_value' => theme_get_setting('uswds_footer_style'),
    ],
    'uswds_big_footer_help' => [
      '#type' => 'container',
      'markup' => [
        '#markup' => t('Site building note: In the "Big" footer style, the footer menu must be a two-level menu, because the first level of menu items is only rendered as column headers.'),
      ],
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_style"]' => ['value' => 'big'],
        ],
      ],
    ],
    'uswds_footer_agency' => [
      '#type' => 'checkbox',
      '#title' => t('Add agency information in the footer?'),
      '#default_value' => theme_get_setting('uswds_footer_agency'),
    ],
    'uswds_footer_agency_name' => [
      '#type' => 'textfield',
      '#title' => t('Footer agency name'),
      '#default_value' => theme_get_setting('uswds_footer_agency_name'),
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_agency"]' => ['checked' => TRUE],
        ],
      ],
    ],
    'uswds_footer_agency_url' => [
      '#type' => 'textfield',
      '#title' => t('Footer agency URL'),
      '#default_value' => theme_get_setting('uswds_footer_agency_url'),
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_agency"]' => ['checked' => TRUE],
        ],
      ],
    ],
    'uswds_footer_agency_logo' => [
      '#type' => 'textfield',
      '#title' => t("Path to footer agency logo (from this theme's folder)"),
      '#description' => t('For example: images/footer-agency.png'),
      '#default_value' => theme_get_setting('uswds_footer_agency_logo'),
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_agency"]' => ['checked' => TRUE],
        ],
      ],
    ],
    'uswds_contact_center' => [
      '#type' => 'textfield',
      '#title' => t('Name of contact center'),
      '#default_value' => theme_get_setting('uswds_contact_center'),
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_agency"]' => ['checked' => TRUE],
        ],
      ],
    ],
    'uswds_email' => [
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#default_value' => theme_get_setting('uswds_email'),
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_agency"]' => ['checked' => TRUE],
        ],
      ],
    ],
    'uswds_phone' => [
      '#type' => 'textfield',
      '#title' => t('Phone'),
      '#default_value' => theme_get_setting('uswds_phone'),
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_agency"]' => ['checked' => TRUE],
        ],
      ],
    ],
    'uswds_facebook' => [
      '#type' => 'textfield',
      '#title' => t('Facebook link'),
      '#default_value' => theme_get_setting('uswds_facebook'),
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_agency"]' => ['checked' => TRUE],
        ],
      ],
    ],
    'uswds_twitter' => [
      '#type' => 'textfield',
      '#title' => t('Twitter link'),
      '#default_value' => theme_get_setting('uswds_twitter'),
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_agency"]' => ['checked' => TRUE],
        ],
      ],
    ],
    'uswds_youtube' => [
      '#type' => 'textfield',
      '#title' => t('Youtube link'),
      '#default_value' => theme_get_setting('uswds_youtube'),
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_agency"]' => ['checked' => TRUE],
        ],
      ],
    ],
    'uswds_rss' => [
      '#type' => 'textfield',
      '#title' => t('RSS feed'),
      '#default_value' => theme_get_setting('uswds_rss'),
      '#states' => [
        'visible' => [
          ':input[name="uswds_footer_agency"]' => ['checked' => TRUE],
        ],
      ],
    ],
  ];
}
