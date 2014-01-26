#include "chord.h"

Chord::Chord(const std::string& chord_string) :
   chord_string(chord_string)
{
}

const std::string &Chord::str() const
{
   return chord_string;
}
