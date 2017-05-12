# U.S. Web Design Standards (USWDS)

Drupal integration of the [U.S. Web Design Standards](https://standards.usa.gov/) library.

This base theme focuses on tweaking Drupal's markup so that it will work with the USWDS library. Some CSS is added to deal with unavoidable Drupal quirks, but only as a last resort.

The theme makes no assumptions about how you would like to add site-specific CSS. You can either:

1. use normal CSS files loaded after the pre-compiled USWDS library, or
2. use npm to include the USWDS Sass source files in your own front-end workflow

You can either use this theme directly, or copy /examples/my_subtheme out as subtheme, following the instructions in /exmaples/my_subtheme/README.md.

After installation, see the theme settings inside Drupal for various customizations, like configuring the header, footer, and menus.

Note: This code was originally forked from [this repository](https://github.com/18F/web-design-standards-drupal), and was split off at 18F's suggestion. It is now maintained [here](https://www.drupal.org/project/uswds).
