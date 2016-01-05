<?php
/**
 * @file
 * wds_3col_fauxsidebar_stacked.inc
 */

$plugin = array(
  'title' => t('WDS: stacked 3 faux sidebars'),
  'category' => t('WDS: 3'),
  'icon' => 'wds_3col_fauxsidebar_stacked.png',
  'theme' => 'wds_3col_fauxsidebar_stacked',
  'admin css' => '../wds_admin_panels.css',
  'regions' => array(
    'top' => t('Top'),
    'left' => t('Left'),
    'middle' => t('Middle'),
    'right' => t('Right'),
    'bottom' => t('Bottom'),
  ),
);