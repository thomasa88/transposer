#ifndef LINE_PART_H
#define LINE_PART_H

#include <iostream>
#include "chord.h"
#include "lyrics.h"

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

bool operator==(const LinePart &lhs, const LinePart &rhs);
std::ostream& operator<<(std::ostream& os, const LinePart &part);

#endif
