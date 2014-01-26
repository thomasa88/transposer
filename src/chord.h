#ifndef CHORD_H
#define CHORD_H

#include <string>

class Chord
{
public:
   Chord(const std::string &chord_string);
   const std::string &str() const;
private:
   const std::string chord_string;
};

#endif
