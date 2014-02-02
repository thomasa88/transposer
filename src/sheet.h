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
private:
};

Sheet sheet_from_ascii(const std::string &ascii);
std::string sheet_to_ascii(const Sheet &sheet);

class Line
{
public:
   Line &operator+=(const LinePart &rhs);
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

#endif
