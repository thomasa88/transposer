#ifndef SHEET_H
#define SHEET_H

#include <memory>
#include <string>
#include <vector>
#include "chord.h"

class Line;

class Sheet
{
public:
   static Sheet from_ascii(const std::string &ascii);
//   Sheet &from_ascii(const std::ostream &ascii);
   const std::string &str() const;
private:
   void parse(const std::string &ascii);
   std::vector<Line> m_lines;
};

class Line
{
public:
   virtual ~Line() { /* vtable */ };
   static std::unique_ptr<Line> from_ascii(const std::string &ascii);
   virtual std::string str() const = 0;
};

class LyricsLine : public Line
{
public:
   explicit LyricsLine(const std::string &ascii);
   std::string str() const override;
private:
   std::string m_lyrics;
};

class ChordLine : public Line
{
public:
   explicit ChordLine(const std::string &ascii);
   std::string str() const override;
   const std::vector<Chord> &chords() const;
private:
   std::vector<Chord> m_chords;
   std::vector<size_t> m_positions;
};

class NotatedLine : public Line
{
   //lyricsline, positioned chords?
};

#endif
