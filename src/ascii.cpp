#include <sstream>
#include <vector>
//gcc 4.8 does not support c++11 regex
//#include <regex>
#include <boost/regex.hpp>

#include "ascii.h"
#include "chord.h"

Sheet sheet_from_ascii(const std::string &ascii)
{
   Sheet sheet;
   std::istringstream stream{ascii};
   std::string ascii_line;
   std::vector<Chord> chord_buffer;
   std::vector<size_t> position_buffer;
   while(getline(stream, ascii_line))
   {
      Line line;

      try
      {
	 boost::regex chord_pattern(R"(\S+)");
	 boost::sregex_iterator chord_it_begin{ascii_line.begin(), ascii_line.end(), chord_pattern};
	 boost::sregex_iterator chord_it_end{};
	 std::vector<Chord> chords;
	 std::vector<size_t> positions;
	 for(auto chord_it = chord_it_begin; chord_it != chord_it_end; ++chord_it)
	 {
	    const auto &match = *chord_it;
//	    std::cout << "chord: " << match.str() << std::endl;
	    chords.push_back(Chord{match.str()});
	    positions.push_back(match.position());
	 }

	 if(chord_buffer.size() != 0)
	 {
	    for(auto &chord : chord_buffer)
	    {
	       LinePart part{std::move(chord), lyrics_t{}};
	       line += part;
	    }
	    sheet.add_line(line);
	 }
	 chord_buffer = std::move(chords);
	 position_buffer = std::move(positions);
//	 chords = std::vector<Chord>{};
      }
      catch(std::invalid_argument)
      {
	 line = Line{};
	 
	 if(chord_buffer.size() != 0)
	 {
	    position_buffer.push_back(std::string::npos);
	    auto chord_it = chord_buffer.begin();
	    auto position_it = position_buffer.begin();
	    size_t position = *position_it;
	    size_t next_position = *(++position_it);
	    for(; chord_it != chord_buffer.end(); ++chord_it)
	    {
	       line += LinePart{*chord_it, ascii_line.substr(position, next_position - position)};
	       position = next_position;
	       next_position = *(++position_it);
	    }
	    chord_buffer.clear();
	 }
	 else
	 {
	    line += LinePart{Chord{}, ascii_line};
	 }
	 sheet.add_line(line);
      }
   }
   if(chord_buffer.size() != 0)
   {
      Line line;
      for(auto &chord : chord_buffer)
      {
	 LinePart part{std::move(chord), lyrics_t{}};
	 line += part;
      }
      sheet.add_line(line);
   }
   
   return sheet;
}
