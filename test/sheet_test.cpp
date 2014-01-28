#include "gtest/gtest.h"
#include "sheet.h"

#include <memory>
#include <string>

TEST(LyricsLineTest, FromAscii)
{
   std::string lyrics{"Hi ho hay!"};
   std::unique_ptr<Line> line = Line::from_ascii(lyrics);
   EXPECT_EQ(lyrics, line->str());
}

TEST(ChordLineTest, FromValidAsciiPopulatesVector)
{
   std::string chord_string{"C7  Gsus4    F#"};
   auto line = ChordLine{chord_string};
   const auto &chords = line.chords();
   EXPECT_EQ(3, chords.size());
   EXPECT_EQ("C7", chords[0].str());
   EXPECT_EQ("Gsus4", chords[1].str());
   EXPECT_EQ("F#", chords[2].str());
}

TEST(ChordLineTest, FromInvalidAscii)
{

}
