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

  <header class="header" id="header" role="banner">

    <section class="usa-banner">
      <div class="usa-grid">
        <div class="usa-banner-content" id="main-content">

          <?php if ($site_name): ?>
            <h1><?php print $site_name; ?></h1>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <h2 class="usa-font-lead"><?php print $site_slogan; ?></h2>
          <?php endif; ?>

        </div>
      </div>
    </section>

    <?php if ($page['header']): ?>
      <section class="usa-section">
        <div class="usa-grid">
          <?php print render($page['header']); ?>
        </div>
      </section>
    <?php endif; ?>

  </header>

  <?php if ($page['navigation']): ?>
    <nav>
      <?php print render($page['navigation']); ?>
    </nav>
  <?php endif; ?>

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

      <?php if ($page['sidebar_first'] || $page['sidebar_second']): ?>
        <aside class="usa-width-one-fourth">
          <?php print render($page['sidebar_first']); ?>
          <?php print render($page['sidebar_second']); ?>
        </aside>
      <?php endif; ?>

    </div>
  </section>

  <?php if ($page['footer']): ?>
    <footer class="usa-section">
      <?php print render($page['footer']); ?>
    </footer>
  <?php endif; ?>

</div>

<?php if ($page['bottom']): ?>
  <section class="usa-section">
    <?php print render($page['bottom']); ?>
  </section>
<?php endif; ?>
