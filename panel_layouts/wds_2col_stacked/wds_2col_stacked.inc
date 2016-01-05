<?php
/**
 * @file
 * wds_2col_stacked.inc
 */

$plugin = array(
  'title' => t('WDS: stacked 2 column'),
  'category' => t('WDS: 2'),
  'icon' => 'wds_2col_stacked.png',
  'theme' => 'wds_2col_stacked',
  'admin css' => '../wds_admin_panels.css',
  'regions' => array(
    'top' => t('Top'),
    'left' => t('Left'),
    'right' => t('Right'),
    'bottom' => t('Bottom'),
  ),
);