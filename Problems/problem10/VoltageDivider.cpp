#include "VoltageDivider.hpp"

#include <stdexcept>

// Nodes: 0 is ground, 1..num_res. Components: 0 is the source, resistor i is component i + 1.
VoltageDivider::VoltageDivider(double v, double res[], int num_res) : Network(num_res + 1, num_res + 1)
{
  if (num_res < 1)
  {
    throw std::invalid_argument("Need at least one resistor");
  }

  // The source runs from ground (terminal A) to node 1 (terminal B).
  VoltageSource *vs = new VoltageSource();
  set_component(0, vs);
  connect_component_terminal_a(0, 0);
  connect_component_terminal_b(0, 1);

  // Resistor i drops from node i + 1 (B) to node i + 2 (A); the last one returns to ground.
  for (int i = 0; i < num_res; i++)
  {
    Resistor *r = new Resistor();
    set_component(i + 1, r);
    connect_component_terminal_b(i + 1, i + 1);
    connect_component_terminal_a(i + 1, (i == num_res - 1) ? 0 : i + 2);
  }

  set_component_value(0, v);
  for (int i = 0; i < num_res; i++)
  {
    set_component_value(i + 1, res[i]);
  }
  update_node_voltages();
}

// Node 1 is at the source voltage; each resistor then drops I * R.
void VoltageDivider::update_node_voltages()
{
  int num_res = get_num_resistors();
  double total = 0;
  for (int i = 0; i < num_res; i++)
  {
    total += get_component_value(i + 1);
  }
  double v = get_component_value(0);
  double current = v / total;

  set_node_voltage(0, 0.0);
  set_node_voltage(1, v);
  double node_v = v;
  for (int i = 0; i < num_res - 1; i++)
  {
    node_v -= current * get_component_value(i + 1);
    set_node_voltage(i + 2, node_v);
  }
}

void VoltageDivider::check_resistor_idx(int idx) const
{
  if (idx < 0 || idx >= get_num_resistors())
  {
    throw std::out_of_range("Resistor index out of range");
  }
}

int VoltageDivider::get_num_resistors() const
{
  return get_num_components() - 1;
}

double VoltageDivider::get_source_voltage() const
{
  return get_component_voltage(0);
}

double VoltageDivider::get_resistance(int idx) const
{
  check_resistor_idx(idx);
  return get_component_value(idx + 1);
}

double VoltageDivider::get_resistor_voltage(int idx) const
{
  check_resistor_idx(idx);
  return get_component_voltage(idx + 1);
}

// The same current flows through every component; read it from the first resistor.
double VoltageDivider::get_loop_current() const
{
  return get_component_current(1);
}

void VoltageDivider::set_source_voltage(double v)
{
  set_component_value(0, v);
  update_node_voltages();
}

void VoltageDivider::set_resistance(int idx, double r)
{
  check_resistor_idx(idx);
  set_component_value(idx + 1, r);
  update_node_voltages();
}
