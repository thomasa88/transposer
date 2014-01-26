#include <iostream>
#include <string>
#include <sstream>
#include <vector>
//gcc 4.8 does not support c++11 regex
//#include <regex>
#include <boost/regex.hpp>

const std::vector<std::string> notes = {"A", "A#", "B", "C", "C#", "D",
					   "D#", "E", "F", "F#", "G", "G#"};

typedef std::string::difference_type line_position_t;

class Chord
{
public:
   Chord(const std::string& chord_string)
   {
      std::string::size_type copy_length;
if(chord_string.length() == 1 || (chord_string[1] != '#'
				     && chord_string[1] != 'b'))
      {
copy_length = 1;
      }
      else
      {
copy_length = 2;
      }
   root = chord_string.substr(0, copy_length);
   if(chord_string.length() > copy_length)
   {
      quality = chord_string.substr(copy_length);
}
   }

   std::string str() const
   {
      return root + quality;
   }

Chord& transpose(const int half_steps)
{
auto pos = std::find(notes.begin(), notes.end(), root);
if(pos != notes.end())
{
auto distance = std::distance(notes.begin(), pos);
auto new_distance = (distance + half_steps) % notes.size();
root = notes[new_distance];
}

//exception on failure?

return *this;
}
private:
   std::string root;
std::string quality;
};

struct PositionedChord
{
   PositionedChord(const std::string& chord_string,
		   const line_position_t position) :
      chord(Chord(chord_string)), position(position)
   {
   }

   Chord chord;
   line_position_t position;
};

std::ostream& operator<<(std::ostream& stream, const Chord& chord)
{
   stream << chord.str();
   return stream;
}


std::vector<PositionedChord> parse_chord_line(const std::string& chord_line)
{
   boost::regex chord_pattern{R"(\S+)"};
   boost::sregex_iterator regex_it{chord_line.begin(), chord_line.end(),
				 chord_pattern};
   boost::sregex_iterator regex_end;

std::vector<PositionedChord> chords;
auto insert_iterator(std::back_inserter(chords));

auto match_to_chord = [](const boost::smatch& match) {return PositionedChord{match[0], match.position()};};


std::transform(regex_it, regex_end, insert_iterator,
		  match_to_chord);

return chords;
}

std::string build_chord_line(const std::vector<PositionedChord> chords)
{
   std::string chord_line;
   auto chord_it = chords.begin();
   for(std::string::difference_type pos = 0; chord_it != chords.end(); )
   {
      if(chord_it->position == pos)
      {
	 const std::string& str = chord_it->chord.str() + ' ';
	 chord_line += str;
	 pos += str.length();
	 ++chord_it;
      }
      else if(chord_it->position < pos)
      {
++chord_it;
//++pos;
}
      else
      {
	 chord_line += ' ';
	 ++pos;
      }
   }

   return chord_line;
}

int main(/*int argc, char** argv*/)
{
   std::string text{"C    Am    F    G\n"
                    "I am a winner!"};
//   Transposer t;
//   std::string transposed = t.transpose(text, 2);
//   t.transpose(text, "D");

   std::string chord_line{"Cm9 Am   F#  D7 G#sus4"};

   std::vector<PositionedChord> chords = parse_chord_line(chord_line);
   for(auto &chord : chords)
   {
      std::cout << chord.chord << "->";
      std::cout << chord.chord.transpose(1) << std::endl;
   }

   std::cout << chord_line << std::endl;
   std::cout << build_chord_line(chords) << std::endl;

}
