// Citation notes: inheritance, polymorphism and virtual functions follow the lecture notes
// and in-class code examples (Lecture 9) and REVEL Chapter 13. Starter code provided by the
// course. Claude (Anthropic) assisted with attempts after the first.
#include "PracticalVsCircuit.hpp"

#include <cmath>
#include <vector>

// Resistor 0 is the source resistance RS and resistor 1 is the load RL.
PracticalVsCircuit::PracticalVsCircuit(double vs, double rs, double rl)
    : VoltageDivider(vs, std::vector<double>{rs, rl}.data(), 2)
{
}

// Terminal voltage: the ideal source voltage minus the drop across RS.
double PracticalVsCircuit::get_source_voltage() const
{
  return VoltageDivider::get_source_voltage() - get_resistor_voltage(0);
}

void PracticalVsCircuit::set_load(double rl)
{
  set_resistance(1, rl);
}

// P = VL^2 / RL
double PracticalVsCircuit::get_load_power() const
{
  double vl = get_resistor_voltage(1);
  return vl * vl / get_resistance(1);
}

// Pmax = VS^2 / (4 RS), compared with the 1e-9 W tolerance.
bool PracticalVsCircuit::maximum_power_transfer(double rl)
{
  set_load(rl);
  double vs = VoltageDivider::get_source_voltage();
  double max_power = vs * vs / (4 * get_resistance(0));
  return std::abs(get_load_power() - max_power) <= 1e-9;
}
