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
