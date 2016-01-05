<?php
/**
 * @file
 * wds-2col-stacked.tpl.php
 */

/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * additional areas for the top and the bottom.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['left']: Content in the left column.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>

<div <?php print !empty($css_id) ? 'id="' . $css_id . '"' : ''; ?> class="wds-panel-container wds-2col-stacked">
  <?php if ($content['top']): ?>
    <div class="usa-grid-full">
      <div class="usa-width-one-whole">
        <?php print $content['top']; ?>
      </div>
    </div>
  <?php endif; ?>

  <div class="usa-grid-full">
    <div class="usa-width-one-half">
      <?php print $content['left']; ?>
    </div>
    <div class="usa-width-one-half">
      <?php print $content['right']; ?>
    </div>
  </div>

  <?php if ($content['bottom']): ?>
    <div class="usa-grid-full">
      <div class="usa-width-one-whole">
        <?php print $content['bottom']; ?>
      </div>
    </div>
  <?php endif; ?>

</div>
