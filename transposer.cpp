#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const vector<string> notes = {"A", "A#", "B", "C", "C#", "D",
				 "D#", "E", "F", "G", "G#"};

class Transposer
{
public:
   string transpose(const string &text, int halfsteps) const;
};

class Chord
{
public:
   Chord(std::string& chord_line, const std::string::size_type& position) :
      chord_line(chord_line),
      position(position)
   {
   }

   Chord() :
      chord_line(""),
      position(0)
   {
   }
   
   const std::string& str() const
   {
      return chord_line;
   }
private:
   std::string& chord_line;
   std::string::size_type position;
};

ostream& operator<<(ostream& stream, const Chord& chord)
{
   stream << chord.str();
   return stream;
}

class ChordIterator : public std::iterator<std::input_iterator_tag,
					   Chord>
{
public:
   ChordIterator(std::string &chord_line) :
      chord_line(chord_line),
      line_position(0)
   {
   }

   ChordIterator begin()
   {
      return ChordIterator(chord_line);
   }

   ChordIterator end()
   {
      ChordIterator it(chord_line);
      it.line_position = std::string::npos;
      return it;
   }

   ChordIterator& operator++()
   {
      // use regex! :D
      std::string::size_type next_space;
/*      if(line_position == 0)
      {
	 next_space = 0;
      }
      else
      {*/
	 next_space = chord_line.find_first_of(' ', line_position);
//      }
      line_position = chord_line.find_first_not_of(' ', next_space);
      std::cout << "++: next_space = " << next_space << endl;
      std::cout << "++: line_position=" << line_position << endl;
      return *this;
   }

   bool operator==(const ChordIterator& rhs)
   {
      std::cout << "==: chordline: " << chord_line << " " << rhs.chord_line << endl;
      std::cout << "==: line_position: " << line_position << " " << rhs.line_position << endl;
      if(this->chord_line == rhs.chord_line)
	 std::cout << "==: chord_line equal" << std::endl;
      if(this->line_position == rhs.line_position)
	 std::cout << "==: line_postion equal" << std::endl;
      return (this->chord_line == rhs.chord_line)
	 && (this->line_position == rhs.line_position);
   }

   bool operator!=(const ChordIterator& rhs)
   {
      return !(*this == rhs);
   }

   value_type& operator*()
   {
      return current_chord;
   }
private:
   std::string &chord_line;
//   std::string::iterator line_position;
   std::string::size_type line_position;
   Chord current_chord;
};

string Transposer::transpose(const string &text, int halfsteps) const
{
   istringstream text_stream(text);
   ostringstream transposed_stream;
   string line;
   for(int line_number = 0; !text_stream.eof(); ++line_number)
   {
      getline(text_stream, line);
      if(line_number % 2 == 0)
      {
	 // Chord line
	 char prev_char = ' ';

//måste kolla substräng. tex D eller C#
	 
	 for(size_t i = 0; i < line.length(); ++i)
	 {
	    char cur_char = line[i];
	    if(prev_char == ' ' && cur_char != ' ')
	    {
	       cout << "FOUND: " << cur_char << endl;
	    }
	    prev_char = cur_char;
	 }
      }
      else
      {
	 transposed_stream << line << endl;
      }
   }
   return transposed_stream.str();
}

int main(/*int argc, char** argv*/)
{
   string text{"C    Am    F    G\n"
	 "I am a winner!"};
   Transposer t;
   string transposed = t.transpose(text, 2);
//   t.transpose(text, "D");

   std::string chord_line{"C  Am   F#  D7 G#sus4"};
   ChordIterator it{chord_line};

   auto it2(it);

   std::string empty;
   ChordIterator empty_it{empty};
   ++empty_it;
   if(empty_it == empty_it.end())
   {
      std::cout << "At end" << std::endl;
   }
   
   for(auto &chord : it)
   {
      std::cout << "C: " << chord << std::endl;
   }
   
   cout << text << endl;
   cout << endl;
   cout << transposed << endl;
}
