#ifndef STREAM_JOIN_H
#define STREAM_JOIN_H

#include <algorithm>
#include <iostream>
#include <iterator>

template<typename Container>
void stream_join(std::ostream& os, const Container &elements, const char *delim = ", ")
{
   if(!elements.empty())
   {
      std::ostream_iterator<typename Container::value_type> os_it{os, delim};
      auto end = elements.end();
      --end;
      std::copy(elements.begin(), end, os_it);
      os << *end;
   }
}


#endif
