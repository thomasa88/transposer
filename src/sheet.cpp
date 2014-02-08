#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <sstream>
#include <string>

#include "sheet.h"

template<typename Container>
void stream_join(std::ostream& os, const Container &elements, const char *delim = ", ");

Sheet &Sheet::add_line(const Line &line)
{
   m_lines.push_back(line);
   return *this;
}

const std::vector<Line> &Sheet::lines() const
{
   return m_lines;
}

Line &Line::operator+=(const LinePart &rhs)
{
   m_parts.push_back(rhs);
   return *this;
}

std::ostream& operator<<(std::ostream& os, const Sheet &sheet)
{
   const auto &lines = sheet.lines();
   os << "Sheet{";
   stream_join(os, lines);
   os << "}";
   return os;
}


Line::Line()
{
}

Line::Line(std::initializer_list<LinePart> parts)
   : m_parts(parts)
{
}

std::ostream& operator<<(std::ostream& os, const Line &line)
{
   const auto &parts = line.parts();
   os << "Line{";
   stream_join(os, parts);
   os << "}";
   return os;
}

const std::vector<LinePart> &Line::parts() const
{
   return m_parts;
}

bool operator==(const Line &lhs, const Line &rhs)
{
   return lhs.parts() == rhs.parts();
}


LinePart::LinePart(const Chord &chord, const lyrics_t &lyrics) :
   m_chord(chord), m_lyrics(lyrics)
{
}

LinePart::LinePart(const Chord &chord) :
   m_chord(chord)
{
}

LinePart::LinePart(const lyrics_t &lyrics) :
   m_lyrics(lyrics)
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

std::ostream& operator<<(std::ostream& os, const LinePart &part)
{
   return os << "LinePart{chord=" << part.chord() << ", lyrics=" << part.lyrics() << "}";
}


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
