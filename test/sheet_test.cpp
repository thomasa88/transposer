#include "gtest/gtest.h"
#include "sheet.h"

#include <memory>
#include <stdexcept>
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

TEST(ChordLineTest, FromAsciiWithInvalidChordRootsThrowsException)
{
   std::string invalid_string{"D thing C"};
   EXPECT_THROW(ChordLine{invalid_string}, std::invalid_argument);
}

TEST(ChordLineTest, ToStringReturnsInput)
{
   std::string chord_string(" C7 Dsus2   G");
   auto line = ChordLine{chord_string};
   EXPECT_EQ(chord_string, line.str());
}

TEST(Line, FromAsciiLyricsStringReturnsLyricsLine)
{
   std::string lyrics{"One two three."};
   auto line = Line::from_ascii(lyrics);
   EXPECT_TRUE(dynamic_cast<LyricsLine *>(line.get()));
   EXPECT_EQ(lyrics, line->str());
}

TEST(Line, FromAsciiChordStringReturnsChordLine)
{
   std::string chord_string{"A B C"};
   auto line = Line::from_ascii(chord_string);
   EXPECT_TRUE(dynamic_cast<ChordLine *>(line.get()));
   EXPECT_EQ(chord_string, line->str());
}
