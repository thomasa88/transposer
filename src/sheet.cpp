#include <iterator>
#include <stdexcept>
#include <sstream>
#include <string>
//gcc 4.8 does not support c++11 regex
//#include <regex>
#include <boost/regex.hpp>

#include "sheet.h"

Sheet Sheet::from_ascii(const std::string &ascii)
{
   return Sheet{ascii};
}

Sheet::Sheet(const std::string &ascii)
{
   std::istringstream stream{ascii};
   std::string line_string;
   while(std::getline(stream, line_string))
   {
      m_lines.push_back(Line::from_ascii(line_string));
   }
}

std::string Sheet::str() const
{
   std::ostringstream stream;
   for(const auto &line : m_lines)
   {
      stream << line->str() << '\n';
   }
   return stream.str();
}


std::unique_ptr<Line> Line::from_ascii(const std::string &ascii)
{
   try
   {
      return std::unique_ptr<Line>(new ChordLine(ascii));
   }
   catch(const std::invalid_argument &)
   {
      return std::unique_ptr<Line>(new LyricsLine(ascii));
   }
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
   boost::regex chord_pattern{R"(\S+)"};
   boost::sregex_iterator begin{ascii.begin(), ascii.end(), chord_pattern};
   boost::sregex_iterator end;
   for(auto match = begin; match != end; ++match)
   {
      m_chords.push_back(Chord{(*match)[0]});
      m_positions.push_back(match->position());
   }
}

std::string ChordLine::str() const
{
   std::string line;
   auto inserter = back_inserter(line);
   for(size_t i = 0; i < m_chords.size(); ++i)
   {
      if(m_positions[i] > line.length())
      {
	 std::fill_n(inserter, m_positions[i] - line.length(), ' ');
      }
      line += m_chords[i].str();
   }
   return line;
}

const std::vector<Chord> &ChordLine::chords() const
{
   return m_chords;
}
