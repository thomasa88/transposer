#include "line_part.h"

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
