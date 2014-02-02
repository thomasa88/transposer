#ifndef CHORD_H
#define CHORD_H

#include <string>

class Chord
{
public:
   explicit Chord(const std::string &chord_string);
   explicit Chord();
   std::string str() const;
   const std::string &root() const;
   void transpose(const int half_steps);
   bool operator==(const Chord &other) const;
   bool has_chord() const;
private:
   std::string::size_type find_root_length(const std::string &chord_string) const;
   std::string m_quality;
   std::string m_root;
};

#endif
