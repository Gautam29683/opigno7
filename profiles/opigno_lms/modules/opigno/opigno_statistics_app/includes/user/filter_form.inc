<?php

/**
 * Implements hook_form().
 */
function opigno_statistics_app_user_filter_form(array $form, array &$form_state) {
  $form['#attributes'] = array('class' => 'clearfix');
  $years = range(opigno_statistics_app_install_year(), opigno_statistics_app_current_year());
  $default_value = variable_get('opigno_statistics_app_user_filter_form_values');
  $year = opigno_statistics_app_current_year();
  if (isset($default_value[request_uri()]['year'])) {
    $year = $default_value[request_uri()]['year'];
  }
  $month = NULL;
  if (isset($default_value[request_uri()]['month'])) {
    $month = $default_value[request_uri()]['month'];
  }
  $form['year'] = array(
    '#title' => t('Year'),
    '#type' => 'select',
    '#options' => array_combine($years, $years),
    '#ajax' => array(
      'callback' => 'opigno_statistics_app_user_filter_form_ajax_submit',
      'wrapper' => 'opigno-statistics-app-user',
      'method' => 'append'
    ),
    '#default_value' => $year,
  );

  $months = date_month_names();
  $form['month'] = array(
    '#title' => t('Month'),
    '#type' => 'select',
    '#options' => $months,
    '#ajax' => array(
      'callback' => 'opigno_statistics_app_user_filter_form_ajax_submit',
      'wrapper' => 'opigno-statistics-app-user',
      'method' => 'append'
    ),
    '#default_value' => $month,
  );
  return $form;
}

/**
 * Implements hook_form_ajax_submit().
 */
function opigno_statistics_app_user_filter_form_ajax_submit($form, &$form_state) {
  $form_request_uri = $form['#action'];
  $form_values = $form_state['values'];
  variable_set('opigno_statistics_app_user_filter_form_values', array($form_request_uri => $form_values));
  $has_month = !empty($form_values['month']);
  $month_year = ($has_month ? mktime(0, 0, 0, $form_values['month'], 1, $form_values['year']) : mktime(0, 0, 0, 1, 1, $form_values['year']));
  variable_set('opigno_statistics_app_user_month_year', array($form_request_uri => $month_year));
  variable_set('opigno_statistics_app_user_has_month', array($form_request_uri => $has_month));
  return '<script type="text/javascript">document.location.reload();</script>';
}
