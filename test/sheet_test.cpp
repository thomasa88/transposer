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

TEST(SheetAsciiTest, LyricsOnlyLineAddedToSheet)
{
   std::string ascii = "Some lyrics";
   Sheet sheet = sheet_from_ascii(ascii);

   // Very internal..
   ASSERT_EQ(1, sheet.lines().size());
   EXPECT_EQ(ascii, sheet.lines()[0].parts()[0].lyrics());
}

TEST(SheetAsciiTest, MultipleLyricsOnlyLinesAddedToSheet)
{
   std::string ascii = "Line 1\nLine 2\nLine 3";
   Sheet sheet = sheet_from_ascii(ascii);

   // Very internal..
   ASSERT_EQ(3, sheet.lines().size());
   EXPECT_EQ("Line 1", sheet.lines()[0].parts()[0].lyrics());
   EXPECT_EQ("Line 2", sheet.lines()[1].parts()[0].lyrics());
   EXPECT_EQ("Line 3", sheet.lines()[2].parts()[0].lyrics());
}

TEST(SheetAsciiTest, ChordsOnlyLineAddedToSheet)
{
   std::string ascii = "A   C#   G7";
   Sheet sheet = sheet_from_ascii(ascii);

   // Very internal..
   ASSERT_EQ(1, sheet.lines().size());
   EXPECT_EQ("A", sheet.lines()[0].parts()[0].chord().str());
   EXPECT_EQ("C#", sheet.lines()[0].parts()[1].chord().str());
   EXPECT_EQ("G7", sheet.lines()[0].parts()[2].chord().str());
}

TEST(SheetAsciiTest, MultipleChordsOnlyLinesAddedToSheet)
{
   std::string ascii = "A   C#   G7\n  B E";
   Sheet sheet = sheet_from_ascii(ascii);

   // Very internal..
   ASSERT_EQ(2, sheet.lines().size());
   
   EXPECT_EQ("A", sheet.lines()[0].parts()[0].chord().str());
   EXPECT_EQ("C#", sheet.lines()[0].parts()[1].chord().str());
   EXPECT_EQ("G7", sheet.lines()[0].parts()[2].chord().str());
   
   EXPECT_EQ("B", sheet.lines()[1].parts()[0].chord().str());
   EXPECT_EQ("E", sheet.lines()[1].parts()[1].chord().str());
}

TEST(SheetAsciiTest, ChordAndLyricsLineAddedToSheet)
{
   std::string ascii =
      "A    B\n"
      "Sing song";
   Sheet sheet = sheet_from_ascii(ascii);

   ASSERT_EQ(1, sheet.lines().size());
   EXPECT_EQ("A", sheet.lines()[0].parts()[0].chord().str());
   EXPECT_EQ("Sing ", sheet.lines()[0].parts()[0].lyrics());
   EXPECT_EQ("B", sheet.lines()[0].parts()[1].chord().str());
   EXPECT_EQ("song", sheet.lines()[0].parts()[1].lyrics());
}
