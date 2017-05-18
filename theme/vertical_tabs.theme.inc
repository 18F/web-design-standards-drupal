<?php

/**
 * Theme overrides for this hook.
 */

/**
 * Overrides theme_vertical_tabs().
 */
function uswds_vertical_tabs($variables) {
  $element = $variables['element'];
  $contents = $element['#children'];
  // Fieldsets are themed as complete unordered lists, but proper multi-item
  // accordions need to be a single unordered list. So, here we remove the
  // beginning and end of any themed fieldsets in the vertical tab contents.
  $contents = str_replace(USWDS_FIELDSET_START, '', $contents);
  $contents = str_replace(USWDS_FIELDSET_END, '', $contents);
  $output = '<div class="uswds-vertical-tabs usa-accordion-bordered"><ul>' . $contents . '</ul></div>';
  return $output;
}
