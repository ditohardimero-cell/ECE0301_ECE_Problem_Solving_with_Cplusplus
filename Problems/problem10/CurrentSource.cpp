#include "CurrentSource.hpp"

// A source current is constant, independent of the node voltages.
double CurrentSource::get_current() const
{
  return get_value();
}
