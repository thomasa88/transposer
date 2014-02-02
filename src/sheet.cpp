#include <iterator>
#include <stdexcept>
#include <sstream>
#include <string>
//gcc 4.8 does not support c++11 regex
//#include <regex>
#include <boost/regex.hpp>

#include "sheet.h"

// std::string Sheet::str() const
// {
//    std::ostringstream stream;
//    for(const auto &line : m_lines)
//    {
//       stream << line->str() << '\n';
//    }
//    return stream.str();
// }

Line &Line::operator+=(const LinePart &rhs)
{
   m_parts.push_back(rhs);
   return *this;
}

const std::vector<LinePart> &Line::parts() const
{
   return m_parts;
}


LinePart::LinePart(const Chord &chord, const lyrics_t lyrics) :
   m_chord(chord), m_lyrics(lyrics)
{
}

const Chord &LinePart::chord() const
{
   return m_chord;
}

const lyrics_t &LinePart::lyrics() const
{
   return m_lyrics;
}

bool operator==(const LinePart &lhs, const LinePart &rhs)
{
   return lhs.chord() == rhs.chord() && lhs.lyrics() == rhs.lyrics();
}
