#ifndef SHEET_H
#define SHEET_H

#include <memory>
#include <string>
#include <vector>
#include "chord.h"

typedef std::string lyrics_t;

class Line;
class LinePart;

class Sheet
{
public:
   Sheet &add_line(const Line &line);
   const std::vector<Line> &lines() const;
private:
   std::vector<Line> m_lines;
};

class Line
{
public:
   using value_type = LinePart;
   Line &operator+=(const LinePart &rhs);
   const std::vector<LinePart> &parts() const;
private:
   std::vector<LinePart> m_parts;
};

class LinePart
{
public:
   explicit LinePart(const Chord &chord, const lyrics_t lyrics);
   const Chord &chord() const;
   const lyrics_t &lyrics() const;
private:
   Chord m_chord;
   lyrics_t m_lyrics;
};

Sheet sheet_from_ascii(const std::string &ascii);
std::string sheet_to_ascii(const Sheet &sheet);

bool operator==(const Line &lhs, const Line &rhs);

bool operator==(const LinePart &lhs, const LinePart &rhs);

#endif
