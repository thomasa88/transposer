#include <algorithm>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <vector>
#include "chord.h"

static const std::vector<std::string>
notes{"A", "A#", "B", "C", "C#", "D",
	 "D#", "E", "F", "F#", "G", "G#"};

static const std::vector<std::string>
flat_notes{"Ab", "A", "Bb", "Cb", "C", "Db",
	      "D", "Eb", "Fb", "F", "Gb", "G"};

bool valid_root(const std::string &root)
{
   return find(notes.begin(), notes.end(), root) != notes.end() ||
      find(flat_notes.begin(), flat_notes.end(), root) != flat_notes.end();
}

Chord::Chord(const std::string& chord_string)
{
   auto root_length = find_root_length(chord_string);
   m_root = chord_string.substr(0, root_length);
   if(!valid_root(m_root))
   {
      throw std::invalid_argument{"Invalid chord root: " + m_root};
   }
   m_quality = chord_string.substr(root_length);
}

Chord::Chord()
{
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
   auto root_pos_it = std::find(notes.begin(), notes.end(), m_root);
   auto root_pos = root_pos_it - notes.begin();
   int notes_size_signed = notes.size();
   int new_root_pos = (root_pos + half_steps) % notes_size_signed;
   assert(notes.size() < std::numeric_limits<decltype(new_root_pos)>::max());
   if(new_root_pos < 0)
   {
      new_root_pos += notes.size();
   }
   m_root = notes[new_root_pos];
}

bool Chord::operator==(const Chord &other) const
{
   return other.m_root == m_root && other.m_quality == m_quality;
}

bool Chord::has_chord() const
{
   return m_root.length() > 0;
}

std::ostream &operator<<(std::ostream& os, const Chord &chord)
{
   return os << "Chord{root=" + chord.m_root + ", quality=" + chord.m_quality + "}";
}
