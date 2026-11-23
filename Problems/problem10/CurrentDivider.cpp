#include "CurrentDivider.hpp"

#include <stdexcept>

// Nodes: 0 is ground, 1. Components: 0 is the source, resistor i is component i + 1.
CurrentDivider::CurrentDivider(double c, double res[], int num_res) : Network(2, num_res + 1)
{
  if (num_res < 1)
  {
    throw std::invalid_argument("Need at least one resistor");
  }

  // Every component runs from ground (terminal A) to node 1 (terminal B).
  CurrentSource *cs = new CurrentSource();
  set_component(0, cs);
  connect_component_terminal_a(0, 0);
  connect_component_terminal_b(0, 1);

  for (int i = 0; i < num_res; i++)
  {
    Resistor *r = new Resistor();
    set_component(i + 1, r);
    connect_component_terminal_a(i + 1, 0);
    connect_component_terminal_b(i + 1, 1);
  }

  set_component_value(0, c);
  for (int i = 0; i < num_res; i++)
  {
    set_component_value(i + 1, res[i]);
  }
  update_node_voltages();
}

// V = I * R_parallel, where 1 / R_parallel is the sum of 1 / R_i.
void CurrentDivider::update_node_voltages()
{
  double conductance = 0;
  for (int i = 0; i < get_num_resistors(); i++)
  {
    conductance += 1.0 / get_component_value(i + 1);
  }
  set_node_voltage(0, 0.0);
  set_node_voltage(1, get_component_value(0) / conductance);
}

void CurrentDivider::check_resistor_idx(int idx) const
{
  if (idx < 0 || idx >= get_num_resistors())
  {
    throw std::out_of_range("Resistor index out of range");
  }
}

int CurrentDivider::get_num_resistors() const
{
  return get_num_components() - 1;
}

double CurrentDivider::get_source_current() const
{
  return get_component_current(0);
}

double CurrentDivider::get_resistance(int idx) const
{
  check_resistor_idx(idx);
  return get_component_value(idx + 1);
}

double CurrentDivider::get_resistor_voltage() const
{
  return get_component_voltage(1);
}

double CurrentDivider::get_resistor_current(int idx) const
{
  check_resistor_idx(idx);
  return get_component_current(idx + 1);
}

void CurrentDivider::set_source_current(double c)
{
  set_component_value(0, c);
  update_node_voltages();
}

void CurrentDivider::set_resistance(int idx, double r)
{
  check_resistor_idx(idx);
  set_component_value(idx + 1, r);
  update_node_voltages();
}
