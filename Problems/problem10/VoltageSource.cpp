#include "VoltageSource.hpp"

// A source voltage is constant, independent of the node voltages.
double VoltageSource::get_voltage() const
{
  return get_value();
}
