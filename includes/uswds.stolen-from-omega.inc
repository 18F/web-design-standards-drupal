<?php

/**
 * @file
 * The Omega theme has so many great ideas, steal them here. THANK YOU OMEGA!!!
 *
 * Seriously though, all of this code was written by the Omega folks. It feels
 * SO wrong to re-name it to "uswds" but it should be done to avoid PHP errors
 * if a site happens to also have both USWDS and Omega enabled.
 */

/**
 * Builds the full theme trail (deepest base theme first) for a theme.
 *
 * @param string $theme
 *   (Optional) The key (machine-readable name) of a theme. Defaults to the key
 *   of the current theme.
 *
 * @return array
 *   An array of all themes in the trail, keyed by theme key.
 */
function uswds_theme_trail($theme = NULL) {
  $theme = isset($theme) ? $theme : $GLOBALS['theme_key'];

  if (($cache = &drupal_static(__FUNCTION__)) && isset($cache[$theme])) {
    return $cache[$theme];
  }

  $cache[$theme] = array();

  if ($theme == $GLOBALS['theme'] && isset($GLOBALS['theme_info']->base_themes)) {
    $cache[$theme] = $GLOBALS['theme_info']->base_themes;
  }

  $themes = list_themes();
  if (empty($cache[$theme]) && isset($themes[$theme]->info['base theme'])) {
    $cache[$theme] = system_find_base_themes($themes, $theme);
  }

  // Add our current subtheme ($key) to that array.
  $cache[$theme][$theme] = $themes[$theme]->info['name'];

  return $cache[$theme];
}

/**
 * Finds the first occurrence of a given file in the theme trail.
 *
 * @param string $file
 *   The relative path to a file.
 * @param string $theme
 *   (Optional) The key (machine-readable name) of a theme. Defaults to the key
 *   of the current theme.
 *
 * @return string
 *   The path to the file. If the file does not exist at all, it will simply
 *   return the path of the file as it would be if it existed in the given theme
 *   directly. This ensures that the code that uses this function does not break
 *   if a file does not exist anywhere.
 */
function uswds_theme_trail_file($file, $theme = NULL) {
  $theme = isset($theme) ? $theme : $GLOBALS['theme_key'];

  // Iterate over all themes in the theme trail (starting with the active theme)
  // and return the first match.
  $current = NULL;
  foreach (array_reverse(uswds_theme_trail($theme)) as $name => $info) {
    $current = drupal_get_path('theme', $name) . '/' . $file;
    if (file_exists($current)) {
      return $current;
    }
  }

  // The default (fallback) path is the path of the active theme, even if it
  // does not actually have that file.
  return drupal_get_path('theme', $theme) . '/' . $file;
}

/**
 * Implements hook_theme_registry_alter().
 */
function uswds_theme_registry_alter(&$registry) {

  $handler = new UswdsThemeRegistryHandler($registry, $GLOBALS['theme']);

  // Allows themers to split preprocess / process / theme code across separate
  // files to keep the main template.php file clean. This is really fast because
  // it uses the theme registry to cache the paths to the files that it finds.
  $trail = uswds_theme_trail($GLOBALS['theme']);
  foreach ($trail as $theme => $name) {
    $handler->registerHooks($theme);
    $handler->registerThemeFunctions($theme, $trail);
  }
}

/**
 * Utility class for managing the theme registry.
 */
class UswdsThemeRegistryHandler {

  /**
   * The theme registry.
   *
   * @var array
   */
  protected $registry;

  /**
   * The name of the active theme.
   *
   * @var string
   */
  protected $theme;

  /**
   * Constructs a UswdsThemeRegistryHandler object.
   *
   * @param array &$registry
   *   The theme registry.
   * @param string $theme
   *   The name of the active theme.
   */
  public function __construct(&$registry, $theme) {
    $this->theme = $theme;
    $this->trail = uswds_theme_trail($theme);
    $this->registry = &$registry;
  }

  /**
   * Discovers and registers (pre-)process hooks on behalf of a given theme.
   *
   * @param string $theme
   *   The name of the theme for which to register (pre-)process hooks.
   */
  public function registerHooks($theme) {
    foreach (array('process', 'preprocess') as $type) {
      // Iterate over all preprocess/process files in the current theme.
      foreach ($this->discoverFiles($theme, $type) as $item) {
        $callback = "{$theme}_{$type}_{$item->hook}";

        // If there is no hook with that name, continue.
        if (!array_key_exists($item->hook, $this->registry)) {
          continue;
        }

        // Append the included (pre-)process hook to the array of functions.
        $this->registry[$item->hook]["$type functions"][] = $callback;

        // By adding this file to the 'includes' array we make sure that it is
        // available when the hook is executed.
        $this->registry[$item->hook]['includes'][] = $item->uri;
      }
    }
  }

  /**
   * Discovers and registers theme functions on behalf of a given theme.
   *
   * @param string $theme
   *   The name of the theme for which to register (pre-)process hooks.
   * @param array $trail
   *   The theme trail of the given theme.
   */
  public function registerThemeFunctions($theme, $trail) {
    // Recursively scan the folder for the current step for (pre-)process
    // files and write them to the registry.
    foreach ($this->discoverFiles($theme, 'theme') as $item) {
      // Keep a copy of the hook name to accomodate for theme hook suggestions.
      $base = $item->hook;
      if (($separator = strpos($item->hook, '__')) !== FALSE) {
        $base = substr($item->hook, 0, $separator);
      }

      // If there is no hook with that name, continue. This does not apply to
      // theme hook suggestions.
      if (!array_key_exists($base, $this->registry)) {
        continue;
      }

      // Skip theme function overrides if they are already declared 'final'.
      if (!empty($this->registry[$item->hook]['final'])) {
        continue;
      }

      // Name of the function (theme hook or theme function).
      $callback = "{$theme}_{$item->hook}";

      // Furthermore, we don't want to re-override sub-theme template file or
      // theme function overrides with theme functions from include files
      // defined in a lower-level base theme. Without this check this would
      // happen because our alter hook runs after the template file and theme
      // function discovery logic from Drupal core (theme engine).
      if (array_key_exists($item->hook, $this->registry) && in_array($this->registry[$item->hook]['type'], array('base_theme_engine', 'theme_engine'))) {
        foreach (array_reverse(array_keys($this->trail)) as $key) {
          // Do not look any further once we reach the current theme.
          if ($key === $theme) {
            break;
          }

          // We need to check if the declaration of that function or template
          // file lives further down the theme trail than the function we are
          // currently looking at.
          if ($this->registry[$item->hook]['theme path'] == drupal_get_path('theme', $key)) {
            continue(2);
          }
        }
      }

      // Check if this is a previously unknown theme hook suggestion.
      if (!array_key_exists($item->hook, $this->registry) && $base !== $item->hook) {
        $arg = isset($this->registry[$base]['variables']) ? 'variables' : 'render element';

        $this->registry[$item->hook] = array(
          $arg => $this->registry[$base][$arg],
          'base hook' => $base,
          'preprocess functions' => array(),
          'process functions' => array(),
        );
      }

      $this->registry[$item->hook]['function'] = $callback;
      $this->registry[$item->hook]['theme path'] = drupal_get_path('theme', $theme);
      $this->registry[$item->hook]['type'] = $theme == $this->theme ? 'theme_engine' : 'base_theme_engine';

      // By adding this file to the 'includes' array we make sure that it is
      // available when the hook is executed.
      $this->registry[$base]['includes'][] = $item->uri;
    }
  }

  /**
   * Overrides (pre-)process functions while maintaining execution order.
   *
   * Useful in cases where we want to take a completely different approach than
   * what the original implementation does. In some cases this is much more
   * practical than altering or undoing things that were added or changed in a
   * previous hook.
   *
   * @param string $hook
   *   The name of the theme hook (e.g. 'html', 'page' or 'block').
   * @param string $original
   *   The name of the original function.
   * @param string $override
   *   The name of the new function.
   * @param string $type
   *   (Optional) The type of the hook ('process' or 'preprocess'). Defaults to
   *   'process'.
   */
  public function overrideHook($hook, $original, $override, $type = 'process') {
    if (($index = array_search($original, $this->registry[$hook]["$type functions"], TRUE)) !== FALSE) {
      array_splice($this->registry[$hook]["$type functions"], $index, 1, $override);
    }
  }

  /**
   * Scans for files of a certain type in the given theme's path.
   *
   * @param string $theme
   *   The name of the theme scan.
   * @param string $type
   *   The file type (e.g. 'preprocess', 'process', or 'theme') to scan for.
   *
   * @return array
   *   An array of file objects that matched the given type.
   */
  protected function discoverFiles($theme, $type) {
    $length = -(strlen($type) + 1);

    $path = drupal_get_path('theme', $theme);
    // Only look for files that match the 'something.preprocess.inc' pattern.
    $mask = '/.' . $type . '.inc$/';

    // Recursively scan the folder for the current step for (pre-)process
    // files and write them to the registry.
    $files = array_merge(file_scan_directory($path . '/' . $type, $mask), file_scan_directory($path . '/layouts', $mask));
    foreach ($files as &$file) {
      $file->hook = strtr(substr($file->name, 0, $length), '-', '_');
    };

    return $files;
  }

}
