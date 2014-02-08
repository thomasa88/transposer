#include "gtest/gtest.h"
#include "sheet.h"

#include <algorithm>
#include <vector>
#include "chord.h"

TEST(LinePartTest, ShouldInitializeChordCorrectly)
{
   Chord chord{"A7"};
   LinePart part1{chord, lyrics_t{}};
   EXPECT_EQ(chord, part1.chord());

   LinePart part2{chord};
   EXPECT_EQ(chord, part2.chord());
}

TEST(LinePartTest, ShouldInitializeLyricsCorrectly)
{
   lyrics_t lyrics{"One two"};
   LinePart part1{Chord{}, lyrics};
   EXPECT_EQ(lyrics, part1.lyrics());

   LinePart part2{lyrics};
   EXPECT_EQ(lyrics, part2.lyrics());
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

TEST(LineTest, EqualShouldReturnTrueForEqualLines)
{
   Line line;
   auto line_copy = line;
   EXPECT_TRUE(line == line_copy);

   line += LinePart{Chord{"D7"}, lyrics_t{"text"}};
   line_copy = line;
   EXPECT_TRUE(line == line_copy);
}

TEST(LineTest, EqualShouldReturnFalseForNonEqualLines)
{
   auto part1 = LinePart{Chord{"A"}, lyrics_t{}};
   auto part2 = LinePart{Chord{}, lyrics_t{}};
   Line line1;
   line1 += part1;
   Line line2;
   line2 += part2;
   EXPECT_FALSE(line1 == line2);
}

TEST(LineTest, shouldAddInitializerListMembers)
{
   auto part1 = LinePart{Chord{"A"}, lyrics_t{}};
   auto part2 = LinePart{Chord{}, lyrics_t{}};
   Line line{part1, part2};
   ASSERT_EQ(2, line.parts().size());
   EXPECT_EQ(part1, line.parts()[0]);
   EXPECT_EQ(part2, line.parts()[1]);
}

TEST(SheetTest, ShouldStoreLine)
{
   Sheet sheet;
   Line line;
   sheet.add_line(line);
   ASSERT_EQ(1, sheet.lines().size());
   EXPECT_EQ(line, sheet.lines()[0]);
}

TEST(SheetTest, ShouldStoreLinesInOrder)
{
   Sheet sheet;
   std::vector<Line> lines(2);
   lines[1] += LinePart{Chord{}, lyrics_t{}};
   sheet.add_line(lines[0]);
   sheet.add_line(lines[1]);
   EXPECT_EQ(lines, sheet.lines());
}
