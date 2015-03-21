<?php
/**
 * @file
 *  Exposes the nodes menu depth as a context condition.
 */
class context_menu_depth extends context_condition {
  // Omit values as they could be anything.
  public function condition_values() {
    return array();
  }

  public function condition_form($context) {
    $form = array();
    $defaults = $this->fetch_from_context($context, 'values');

    $form['min_depth'] = array(
      '#type' => 'textfield',
      '#title' => t('Start Depth'),
      '#description' => t('The level at which the context starts. Home is level 0.'),
      '#default_value' => isset($defaults['min_depth']) ? $defaults['min_depth'] : '',
    );

    $form['max_depth'] = array(
      '#type' => 'textfield',
      '#title' => t('End Depth'),
      '#description' => t('The level at which the context ends. Home is level 0.'),
      '#default_value' => isset($defaults['max_depth']) ? $defaults['max_depth'] : '',
    );

    return $form;
  }

  /**
   * Condition form submit handler.
   */
  public function condition_form_submit($values) {
    return array(
      'min_depth'   => $values['min_depth'],
      'max_depth' => $values['max_depth'],
    );
  }

  /**
   * Check whether the context should be executed.
   * 
   * @string $menu_dpeth
   *  The depth of the nodes menu link if it has one.
   */
  public function execute($menu_depth) {
    // If a menu level was returned from the node.
    if (isset($menu_depth)) {
      foreach ($this->get_contexts() as $context) {
        $options = $this->fetch_from_context($context, 'values');
        if ($options['max_depth'] !== '' && $options['min_depth'] !== '') {
          if ($menu_depth >= $options['min_depth'] && $menu_depth <= $options['max_depth']) {
            $this->condition_met($context);
          }
        }
        elseif ($options['min_depth'] == '' && $options['max_depth'] !== '') {
          if ($menu_depth <= $options['max_depth']) {
            $this->condition_met($context);
          }
        }
        else {
          if ($menu_depth >= $options['min_depth']) {
            $this->condition_met($context);
          }
        }
      }
    }
  }
}
