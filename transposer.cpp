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

måste kolla substräng. tex D eller C#
	 
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
   cout << text << endl;
   cout << endl;
   cout << transposed << endl;
}
