#include "gtest/gtest.h"
#include "sheet.h"

#include <algorithm>
#include <vector>
#include "chord.h"

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

TEST(LinePartTest, EqualShouldReturnTrueForEqualLineParts)
{
   auto part = LinePart{Chord{}, lyrics_t{}};
   auto part_copy = part;
   EXPECT_TRUE(part == part_copy);

   part = LinePart{Chord{"D7"}, lyrics_t{"text"}};
   part_copy = part;
   EXPECT_TRUE(part == part_copy);
}

TEST(LinePartTest, EqualShouldReturnFalseForNonEqualLineParts)
{
   auto part1 = LinePart{Chord{"A"}, lyrics_t{}};
   auto part2 = LinePart{Chord{}, lyrics_t{}};
   EXPECT_FALSE(part1 == part2);
}

TEST(LineTest, ShouldStorePart)
{
   LinePart part{Chord{}, lyrics_t{}};
   Line line;
   line += LinePart{part};
   ASSERT_EQ(1, line.parts().size());
   EXPECT_EQ(part, line.parts()[0]);
}

TEST(LineTest, ShouldStorePartsInOrder)
{
   Line line;
   std::vector<LinePart> parts{LinePart{Chord{}, "Sing"},
				  LinePart{Chord{"B"}, "a song"},
				  LinePart{Chord{"C"}, "long"}};
//   std::for_each(parts.begin(), parts.end(), std::back_inserter(line));
   for(auto &part : parts)
   {
      line += part;
   }
   EXPECT_EQ(parts, line.parts());
}
