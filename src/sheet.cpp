#include <sstream>
#include "sheet.h"

std::unique_ptr<Line> Line::from_ascii(const std::string &ascii)
{
   return std::unique_ptr<Line>(new LyricsLine(ascii));
}


LyricsLine::LyricsLine(const std::string &ascii) :
   m_lyrics{ascii}
{
}

std::string LyricsLine::str() const
{
   return m_lyrics;
}


ChordLine::ChordLine(const std::string &ascii)
{
   std::stringstream stream(ascii);
   // Use algo + iterator insted of stringstream?
   std::string word;
   while(stream >> word)
   {
      m_chords.push_back(word);
   }
}

std::string ChordLine::str() const
{
   return "";
}

const std::vector<Chord> &ChordLine::chords() const
{
   return m_chords;
}
