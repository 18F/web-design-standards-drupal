<?php
/**
 * @file
 * Template for a 3 column panel layout.
 *
 * This template provides a three column 25%-50%-25% panel display layout, with
 * additional areas for the top and the bottom.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['left']: Content in the left column.
 *   - $content['middle']: Content in the middle column.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>
<div <?php print !empty($css_id) ? 'id="' . $css_id . '"' : ''; ?> class="wds-panel-container wds-3col-equal-stacked">
  <?php if ($content['top']): ?>
    <div class="usa-grid-full">
      <div class="usa-width-one-whole">
        <?php print $content['top']; ?>
      </div>
    </div>
  <?php endif ?>

  <div class="usa-grid-full">
    <div class="usa-width-one-third">
      <?php print $content['left']; ?>
    </div>
    <div class="usa-width-one-third">
      <?php print $content['middle']; ?>
    </div>
    <div class="usa-width-one-third">
      <?php print $content['right']; ?>
    </div>
  </div>

  <?php if ($content['bottom']): ?>
    <div class="usa-grid-full">
      <div class="usa-width-one-whole">
        <?php print $content['bottom']; ?>
      </div>
    </div>
  <?php endif ?>
</div>
