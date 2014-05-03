<?php

/**
 * @file
 *
 * Admin settings for Overview
 */

function overview_admin_form($form, &$form_state) {
  $form['#tree'] = TRUE;

  $settings = variable_get('overview', array());
  $form['overview'] = array();
  foreach (node_type_get_types() as $type => $info) {
    $form['overview'][$type] = array(
      '#title' => $info->name,
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['overview'][$type]['url'] = array(
      '#type' => 'textfield',
      '#title' => t('Overview URL'),
      '#default_value' => (isset($settings[$type]) and isset($settings[$type]['url'])) ? $settings[$type]['url'] : '',
    );
  }

  $form = system_settings_form($form);
  unset($form['#submit']);
  return $form;
}

function overview_admin_form_validate($form, &$form_state) {
  foreach ($form_state['values']['overview'] as $type => &$vals) {
    if (!empty($vals['url'])) {
      $internal_path = drupal_get_normal_path($vals['url']);

      if (!drupal_valid_path($internal_path)) {
        form_set_error($type, t("The path '@link_path' is either invalid or you do not have access to it.", array(
          '@link_path' => $internal_path
        )));
      }
      else {
        $vals['url'] = $internal_path;
      }
    }
  }
}

function overview_admin_form_submit($form, &$form_state) {
  variable_set('overview', $form_state['values']['overview']);
  drupal_set_message(t('The configuration options have been saved.'));
}
