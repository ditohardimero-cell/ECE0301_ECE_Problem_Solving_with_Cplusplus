#include "Resistor.hpp"

#include <stdexcept>

// Resistance cannot be negative (0 is allowed).
void Resistor::set_value(double r)
{
  if (r < 0)
  {
    throw std::invalid_argument("Resistance cannot be negative");
  }
  Component::set_value(r);
}

// Ohm's law: I = V / R. get_voltage throws if a terminal is not connected.
double Resistor::get_current() const
{
  if (get_value() == 0)
  {
    throw std::logic_error("Cannot calculate current through a 0 ohm resistor");
  }
  return get_voltage() / get_value();
}
