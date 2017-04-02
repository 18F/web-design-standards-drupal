<?php

/**
 * @file
 * Utility code related to base themes.
 *
 * The concepts/wording in this file are inspired by (ie, stolen from) the D7
 * Omega base theme.
 */

/**
 * Gets the full theme trail, from active to top-level base.
 *
 * @return array
 *   An array of all themes in the trail, ordered from active to top-level base.
 */
function uswds_theme_trail() {
  $theme = \Drupal::theme()->getActiveTheme();
  return [$theme->getName() => $theme] + $theme->getBaseThemes();
}

/**
 * Finds the first occurrence of a given file in the theme trail.
 *
 * @param string $file
 *   The relative path to a file.
 *
 * @return string
 *   The path to the file. If the file does not exist at all, it will simply
 *   return the path of the file as it would be if it existed in the given theme
 *   directly. This ensures that the code that uses this function does not break
 *   if a file does not exist anywhere.
 */
function uswds_theme_trail_file($file) {
  $trail = uswds_theme_trail();
  foreach ($trail as $name => $theme) {
    $current = $theme->getPath() . '/' . $file;
    if (file_exists($current)) {
      return $current;
    }
  }
  // The default (fallback) path is the path of the active theme, even if it
  // does not actually have that file.
  $active = array_shift($trail);
  return $active->getPath() . '/' . $file;
}

/**
 * Implements hook_theme_registry_alter().
 */
function uswds_theme_registry_alter(&$registry) {

  $trail = uswds_theme_trail();
  // For the purpose of this, we want the theme trail in reverse order: from
  // root base theme to active theme. This way we can let base themes run their
  // functions before the active theme.
  $trail = array_reverse($trail);

  foreach ($trail as $theme) {
    uswds_register_theme_hooks($registry, $theme);
  }
}

/**
 * Helper function to register preprocessor functions for a theme.
 */
function uswds_register_theme_hooks(&$registry, $theme) {

  // Iterate over all preprocess/process files in the current theme.
  foreach (array('process', 'preprocess') as $type) {
    $length = -(strlen($type) + 1);

    // Only look for files that match the 'something.preprocess.inc' pattern.
    $mask = '/.' . $type . '.inc$/';

    $theme_name = $theme->getName();

    // Recursively scan the folder for the current step for (pre-)process
    // files and write them to the registry.
    $files = file_scan_directory($theme->getPath() . '/' . $type, $mask);
    foreach ($files as $file) {
      $hook = strtr(substr($file->name, 0, $length), '-', '_');
      $callback = "{$theme_name}_{$type}_{$hook}";

      // If there is no hook with that name, continue.
      if (!array_key_exists($hook, $registry)) {
        continue;
      }

      // Append the included (pre-)process hook to the array of functions.
      $registry[$hook]["$type functions"][] = $callback;

      // By adding this file to the 'includes' array we make sure that it is
      // available when the hook is executed.
      $registry[$hook]['includes'][] = $file->uri;
    }
  }
}
