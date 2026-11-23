// Citation notes: inheritance, polymorphism and virtual functions follow the lecture notes
// and in-class code examples (Lecture 9) and REVEL Chapter 13. Starter code provided by the
// course. Claude (Anthropic) assisted with attempts after the first.
#include "CurrentSource.hpp"

// A source current is constant, independent of the node voltages.
double CurrentSource::get_current() const
{
  return get_value();
}
