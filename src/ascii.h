#ifndef ASCII_H
#define ASCII_H

#include <string>
#include "sheet.h"

class AsciiParser
{
public:
   Sheet parse(const std::string &ascii);
private:
   class not_chord_line {};
   void append_chord_buffer_to_sheet();
   void parse_chord_line(const std::string &ascii_line);
   void parsed_chords_to_buffer();
   void append_lyrics_with_chords_to_sheet(const std::string &ascii_line);
   void append_lone_lyrics_line_to_sheet(const std::string &ascii_line);
   bool has_chords_in_buffer();
   Sheet m_sheet;
   std::vector<Chord> m_chord_buffer;
   std::vector<size_t> m_position_buffer;
   std::vector<Chord> m_parsed_line_chords;
   std::vector<size_t> m_parsed_line_positions;
};

std::string sheet_to_ascii(const Sheet &sheet);

#endif
