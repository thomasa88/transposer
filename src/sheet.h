#ifndef SHEET_H
#define SHEET_H

#include <initializer_list>
#include <iostream>
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
   bool empty() const;
   int line_count() const;
   bool operator==(const Sheet &rhs) const;
   Line &operator[](int line_index);
   const Line &operator[](int line_index) const;
private:
   friend std::ostream& operator<<(std::ostream& os, const Sheet &sheet);
   std::vector<Line> m_lines;
};

class Line
{
public:
   using value_type = LinePart;
   Line();
   Line(std::initializer_list<LinePart> parts);
   Line &operator+=(const LinePart &rhs);
   const std::vector<LinePart> &parts() const;
private:
   std::vector<LinePart> m_parts;
};

class LinePart
{
public:
   explicit LinePart(const Chord &chord, const lyrics_t &lyrics);
   explicit LinePart(const Chord &chord);
   explicit LinePart(const lyrics_t &lyrics);
   const Chord &chord() const;
   const lyrics_t &lyrics() const;
private:
   Chord m_chord;
   lyrics_t m_lyrics;
};

bool operator==(const Line &lhs, const Line &rhs);
bool operator==(const LinePart &lhs, const LinePart &rhs);
std::ostream& operator<<(std::ostream& os, const Line &line);
std::ostream& operator<<(std::ostream& os, const LinePart &part);

#endif
