#include <vector>
#include <algorithm>
#include "chord.h"

static const std::vector<std::string> notes = {"A", "A#", "B", "C", "C#", "D",
					       "D#", "E", "F", "F#", "G", "G#"};

Chord::Chord(const std::string& chord_string)
{
   auto root_length = find_root_length(chord_string);
   m_root = chord_string.substr(0, root_length);
   m_quality = chord_string.substr(root_length);
}

std::string::size_type Chord::find_root_length(const std::string &chord_string) const
{
   std::string::size_type root_length = 1;
   if(chord_string.length() >= 2)
   {
      char possible_accidental = chord_string[1];
      if(possible_accidental == '#' || possible_accidental == 'b')
      {
	 root_length = 2;
      }
   }
   return root_length;
}

std::string Chord::str() const
{
   return m_root + m_quality;
}

const std::string &Chord::root() const
{
   return m_root;
}

void Chord::transpose(const int half_steps)
{
   auto root_pos = std::find(notes.begin(), notes.end(), m_root);
   auto new_root_pos = (root_pos - notes.begin()) + half_steps;
   m_root = notes[new_root_pos];
}