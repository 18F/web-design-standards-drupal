<?php
/**
 * @file
 * U.S. Web Design Standards theme implementation to display the default Drupal
 * page. Credit goes to the Bartik team for this awesome documentation!
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template normally located in the directory
 * above.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $hide_site_name: TRUE if the site name has been toggled off on the theme
 *   settings page. If hidden, the "element-invisible" class is added to make
 *   the site name visually hidden, but still accessible.
 * - $hide_site_slogan: TRUE if the site slogan has been toggled off on the
 *   theme settings page. If hidden, the "element-invisible" class is added to
 *   make the site slogan visually hidden, but still accessible.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['header']: Items for the header region.
 * - $page['navigation']: Items for the featured region.
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['footer']: Items for the footer region.
 * - $page['bottom']: Items for the bottom region.
 *
 */
?>

<div id="main" class="main-content" role="main">

  <header class="<?php print $header_classes ?>" id="header" role="banner">

    <?php if ($page['header_top']): ?>
      <section class="usa-banner">

        <div class="usa-banner-inner">
          <?php print render($page['header_top']); ?>
        </div>

      </section>
    <?php endif; ?>

    <?php if ($header_basic): ?>
      <div class="usa-nav-container">
    <?php endif; ?>

    <div class="usa-navbar">

      <?php if ($main_menu || $secondary_menu): ?>
        <button class="usa-menu-btn">Menu</button>
      <?php endif; ?>

      <div class="usa-logo" id="logo">

        <?php if ($logo): ?>
          <a class="logo-img" href="<?php print $front_page ?>" accesskey="1" title="<?php print t('Home'); ?>" aria-label="Home">
            <img src="<?php print $logo ?>" alt="<?php print t('Home'); ?>" />
          </a>
        <?php endif; ?>

        <?php if ($site_name): ?>
          <h1>
            <a href="<?php print $front_page ?>" accesskey="1" title="<?php print t('Home'); ?>" aria-label="Home">
              <?php print $site_name; ?>
            </a>
          </h1>
        <?php endif; ?>

          <?php if ($site_slogan): ?>
            <h2 class="usa-font-lead"><?php print $site_slogan; ?></h2>
          <?php endif; ?>

        </a>

      </div>

    </div>

    <?php if ($page['header'] || $main_menu || $secondary_menu): ?>

      <nav class="usa-nav" role="navigation">
        <div class="usa-nav-inner">

          <?php if ($main_menu || $secondary_menu): ?>
            <button class="usa-nav-close">
              <img src="<?php print $base_theme_path; ?>/assets/img/close.svg" alt="close" />
            </button>
          <?php endif; ?>

          <?php if ($main_menu): ?>
            <?php print render($main_menu) ?>
          <?php endif; ?>
          <?php if ($secondary_menu): ?>
            <?php print render($secondary_menu) ?>
          <?php endif; ?>

          <?php print render($page['header']); ?>

        </div>
      </nav>

    <?php endif; ?>

    <?php if ($header_basic): ?>
      </div>
    <?php endif; ?>

  </header>

  <section class="usa-section">
    <div class="usa-grid">
      <div class="usa-width-full">
        <?php print $breadcrumb; ?>
        <a id="main-content"></a>
        <?php print $messages; ?>
        <?php print render($tabs); ?>
        <?php print render($page['help']); ?>

        <?php if ($action_links): ?>
          <ul class="action-links"><?php print render($action_links); ?></ul>
        <?php endif; ?>

      </div>
    </div>
    <div class="usa-grid uswds-content-section">

      <?php if ($page['sidebar_first']): ?>
        <aside class="usa-width-one-fourth">
          <?php print render($page['sidebar_first']); ?>
        </aside>
      <?php endif; ?>

      <div class="<?php print $content_class ?>">
        <?php print render($title_prefix); ?>

        <?php if ($title): ?>
          <h1 class="page-title"><?php print $title; ?></h1>
        <?php endif; ?>

        <?php print render($title_suffix); ?>
        <?php print render($page['content']); ?>
        <?php print $feed_icons; ?>
      </div>

      <?php if ($page['sidebar_second']): ?>
        <aside class="usa-width-one-fourth">
          <?php print render($page['sidebar_second']); ?>
        </aside>
      <?php endif; ?>

    </div>
  </section>

  <footer class="<?php print $footer_classes ?>" role="contentinfo">
    <div class="usa-grid usa-footer-return-to-top">
      <a href="#">Return to top</a>
    </div>

    <?php if ($page['footer'] || $footer_menu): ?>
      <div class="usa-footer-primary-section">
        <div class="usa-grid-full">

          <?php if ($footer_menu): ?>
            <?php print render($footer_menu) ?>
          <?php endif; ?>

          <?php print render($page['footer']); ?>

        </div>
      </div>
    <?php endif; ?>

    <?php if ($page['footer_secondary'] || $footer_agency): ?>
      <div class="usa-footer-secondary_section">
        <div class="usa-grid">

          <?php if ($footer_agency): ?>
            <div class="usa-footer-logo">

              <?php if ($footer_agency_url): ?>
                <a href="<?php print $agency_url ?>">
              <?php endif; ?>

              <?php if ($footer_agency_logo): ?>
                <img class="<?php print $footer_style ?>-logo-img" src="<?php print $footer_agency_logo ?>" alt="Agency logo">
              <?php endif; ?>

              <?php if ($footer_agency_name): ?>
                <h3 class="<?php print $footer_style ?>-logo-heading"><?php print $footer_agency_name ?></h3>
              <?php endif; ?>

              <?php if ($footer_agency_url): ?>
                </a>
              <?php endif; ?>

            </div>
          <?php endif; ?>

        </div>
      </div>
    <?php endif; ?>

  </footer>
</div>
