<?php

/**
 * @file
 * Utility code related to menus and menu blocks.
 */

use \Drupal\block\Entity\Block;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function uswds_theme_suggestions_block_alter(array &$suggestions, array $variables) {
  // We need to suggest our custom theming for menu blocks in certain regions.
  if (in_array('block__system_menu_block', $suggestions)) {
    if (!empty($variables['elements']['#id'])) {
      $block = Block::load($variables['elements']['#id']);
      $menu_regions = ['primary_menu', 'secondary_menu', 'sidebar_first', 'footer_menu'];
      if (in_array($block->getRegion(), $menu_regions)) {
        $suggestions[] = 'block__system_menu_block__' . $block->getRegion();
      }
    }
  }
  return $suggestions;
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function uswds_theme_suggestions_menu_alter(array &$suggestions, array $variables) {
  if (!empty($variables['items'])) {
    foreach ($variables['items'] as $item) {
      if (!empty($item['#uswds_region'])) {
        $suggestions[] = 'menu__' . $item['#uswds_region'];
      }
      // We only need to look at one.
      break;
    }
  }
  return $suggestions;
}

/**
 * Helper function to mark menu items as being in one of our menu regions.
 *
 * This is the way we communicate a menu block's region to its preprocessor
 * and template.
 * @see preprocess/uswds_preprocess_block__system_menu_block__*
 */
function _uswds_mark_menu_items(&$variables, $region) {
  foreach ($variables['content']['#items'] as $key => &$item) {
    $item['#uswds_region'] = $region;
  }
}
