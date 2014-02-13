<?php

/**
 * @file
 *
 * Admin settings for Overview
 */

function overview_admin_form($form, &$form_state) {
  $form_state['types'] = array();
  foreach (node_type_get_types() as $type => $info) {
    $key = 'overview__' . $type;
    $form_state['types'][] = $key;

    $form['overview_node_type__' . $type] = array(
      '#title' => $info->name,
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['overview_node_type__' . $type][$key] = array(
      '#type' => 'textfield',
      '#title' => t('Overview URL'),
      '#default_value' => variable_get($key, ''),
    );
  }

  return system_settings_form($form);
}

function overview_admin_form_validate($form, &$form_state) {
  foreach ($form_state['types'] as $type) {
    if (!empty($form_state['values'][$type])) {
      $internal_path = drupal_get_normal_path($form_state['values'][$type]);

      if (!drupal_valid_path($internal_path)) {
        form_set_error($type, t("The path '@link_path' is either invalid or you do not have access to it.", array(
          '@link_path' => $internal_path
        )));
      }
      else {
        $form_state['values'][$type] = $internal_path;
      }
    }
  }
}