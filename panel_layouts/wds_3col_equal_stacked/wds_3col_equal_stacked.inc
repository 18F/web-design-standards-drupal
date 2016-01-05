<?php
/**
 * @file
 * wds_3col_equal_stacked.inc
 */

$plugin = array(
  'title' => t('WDS: Stacked 3 equal columns'),
  'category' => t('WDS: 3'),
  'icon' => 'wds_3col_equal_stacked.png',
  'theme' => 'wds_3col_equal_stacked',
  'admin css' => '../wds_admin_panels.css',
  'regions' => array(
    'top' => t('Top'),
    'left' => t('Left'),
    'middle' => t('Middle'),
    'right' => t('Right'),
    'bottom' => t('Bottom'),
  ),
);