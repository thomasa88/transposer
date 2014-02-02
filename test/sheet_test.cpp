#include "gtest/gtest.h"
#include "sheet.h"

TEST(LinePartTest, ShouldInitializeChordCorrectly)
{
   Chord chord{"A7"};
   LinePart part{chord, lyrics_t{}};
   EXPECT_EQ(chord, part.chord());
}

TEST(LinePartTest, ShouldInitializeLyricsCorrectly)
{
   lyrics_t lyrics{"One two"};
   LinePart part{Chord{}, lyrics};
   EXPECT_EQ(lyrics, part.lyrics());
}
