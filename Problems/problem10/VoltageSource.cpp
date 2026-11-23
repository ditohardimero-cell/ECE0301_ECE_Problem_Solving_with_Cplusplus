// Citation notes: inheritance, polymorphism and virtual functions follow the lecture notes
// and in-class code examples (Lecture 9) and REVEL Chapter 13. Starter code provided by the
// course. Claude (Anthropic) assisted with attempts after the first.
#include "VoltageSource.hpp"

// A source voltage is constant, independent of the node voltages.
double VoltageSource::get_voltage() const
{
  return get_value();
}
