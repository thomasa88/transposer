#include <algorithm>
#include <sstream>
#include <vector>
//gcc 4.8 does not support c++11 regex
//#include <regex>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

#include "ascii_parser.h"

Sheet AsciiParser::parse(const std::string &ascii)
{
   std::istringstream stream{ascii};
   std::string ascii_line;
   bool prev_line_empty = true;

   while(getline(stream, ascii_line))
   {
      if(ascii_line.empty())
      {
	 append_chord_buffer_to_sheet();
	 prev_line_empty = true;
      }
      else
      {
	 if(prev_line_empty && !m_sheet.empty())
	 {
	    append_empty_line_to_sheet();
	 }
	 handle_nonempty_line(ascii_line);
	 prev_line_empty = false;
      }
   }
   append_chord_buffer_to_sheet();

   return m_sheet;
}

void AsciiParser::append_empty_line_to_sheet()
{
   m_sheet.add_line({});
}

void AsciiParser::handle_nonempty_line(const std::string &ascii_line)
{
   try
   {
      parse_chord_line(ascii_line);
      append_chord_buffer_to_sheet();
      parsed_chords_to_buffer();
   }
   catch(not_chord_line)
   {
      if(has_chords_in_buffer())
      {
	 append_lyrics_with_chords_to_sheet(ascii_line);
      }
      else
      {
	 append_lone_lyrics_line_to_sheet(ascii_line);
      }
   }
}

void AsciiParser::append_chord_buffer_to_sheet()
{
   if(has_chords_in_buffer())
   {
      Line line;
      for(auto &chord : m_chord_buffer)
      {
	 LinePart part{std::move(chord)};
	 line += part;
      }
      m_chord_buffer.clear();
      m_sheet.add_line(line);
   }
}

bool AsciiParser::has_chords_in_buffer() const
{
   return m_chord_buffer.size() != 0;
}

void AsciiParser::parse_chord_line(const std::string &ascii_line)
{
   if(ascii_line.empty())
   {
      throw not_chord_line{};
   }

   boost::regex chord_pattern(R"(\S+)");
   boost::sregex_iterator chord_it_begin{ascii_line.begin(), ascii_line.end(), chord_pattern};
   boost::sregex_iterator chord_it_end{};
   for(auto chord_it = chord_it_begin; chord_it != chord_it_end; ++chord_it)
   {
      const auto &match = *chord_it;
      try
      {
	 m_parsed_line_chords.emplace_back(match.str());
      }
      catch(std::invalid_argument)
      {
	 throw not_chord_line{};
      }
      m_parsed_line_positions.push_back(match.position());
   }
}

void AsciiParser::parsed_chords_to_buffer()
{
   m_chord_buffer = std::move(m_parsed_line_chords);
   m_position_buffer = std::move(m_parsed_line_positions);
}

void AsciiParser::append_lyrics_with_chords_to_sheet(const std::string &ascii_line)
{
   Line line;
   m_position_buffer.push_back(std::string::npos);
   auto position_it = m_position_buffer.begin();
   size_t position = *position_it;
   size_t next_position = *(++position_it);
   if(position != 0)
   {
      auto trimmed_ascii = boost::algorithm::trim_left_copy(ascii_line.substr(0, position));
      if(!trimmed_ascii.empty())
      {
	 line += LinePart{trimmed_ascii};
      }
   }
   for(const Chord &chord : m_chord_buffer)
   {
      std::string ascii_substr{ascii_line.substr(position, next_position - position)};
      erase_if_only_spaces(ascii_substr);
      line += LinePart{chord, ascii_substr};
      position = next_position;
      next_position = *(++position_it);
   }
   m_sheet.add_line(line);
   m_chord_buffer.clear();
}

void AsciiParser::erase_if_only_spaces(std::string &ascii) const
{
   if(std::all_of(ascii.begin(), ascii.end(),
		  [] (std::string::value_type character) {return character == ' ';}))
   {
      ascii.erase();
   }
}

void AsciiParser::append_lone_lyrics_line_to_sheet(std::string ascii_line)
{
   Line line;
   boost::algorithm::trim(ascii_line);
   line += LinePart{std::move(ascii_line)};
   m_sheet.add_line(line);
}
