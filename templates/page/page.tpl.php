<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>

<div id="main" class="main-content" role="main">

  <header class="header" id="header" role="banner">

    <section class="usa-banner">
      <div class="usa-grid">
        <div class="usa-banner-content" id="main-content">

          <h1><?php print $site_name; ?></h1>

          <?php if ($site_slogan): ?>
            <h2 class="usa-font-lead"><?php print $site_slogan; ?></h2>
          <?php else: ?>
            <h2 class="usa-font-lead"><?php print t('Open source UI components and visual style
             guide to create consistency and beautiful user experiences across
             U.S. federal government websites'); ?></h2>
          <?php endif; ?>

        </div>
      </div>
    </section>

    <section class="usa-section">
      <div class="usa-grid">
        <?php print render($page['header']); ?>
      </div>
    </section>

  </header>

  <nav>

    <?php print render($page['navigation']); ?>

  </nav>

  <section class="usa-section">
    <div class="usa-grid">
      <?php print $breadcrumb; ?>
      <a id="main-content"></a>
      <?php print $messages; ?>
      <?php print render($tabs); ?>
      <?php print render($page['help']); ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
      <?php print $feed_icons; ?>

      <?php
        // Render the sidebars to see if there's anything in them.
        $sidebar_first  = render($page['sidebar_first']);
        $sidebar_second = render($page['sidebar_second']);
      ?>

      <?php if ($sidebar_first || $sidebar_second): ?>
        <aside class="usa-width-one-fourth">
          <?php print $sidebar_first; ?>
          <?php print $sidebar_second; ?>
        </aside>
      <?php endif; ?>

    </div>
  </section>

  <footer class="usa-section">

    <?php print render($page['footer']); ?>

  </footer>

</div>

<section class="usa-section">

  <?php print render($page['bottom']); ?>

</section>
