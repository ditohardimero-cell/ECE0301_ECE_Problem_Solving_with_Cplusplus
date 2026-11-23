#ifndef CURRENT_DIVIDER_HPP
#define CURRENT_DIVIDER_HPP

#include "Network.hpp"
#include "CurrentSource.hpp"
#include "Resistor.hpp"

class CurrentDivider : public Network
{
private:
  // Recompute the voltage of node 1 from the source and resistor values.
  void update_node_voltages();

  // Throw std::out_of_range if idx is not a valid resistor index.
  void check_resistor_idx(int idx) const;

public:
  CurrentDivider(double c, double res[], int num_res);
  int get_num_resistors() const;
  double get_source_current() const;
  double get_resistance(int idx) const;
  double get_resistor_voltage() const;
  double get_resistor_current(int idx) const;

  void set_source_current(double c);
  void set_resistance(int idx, double r);
};

#endif