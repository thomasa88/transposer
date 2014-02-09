#include "gtest/gtest.h"
#include "sheet.h"

#include <algorithm>
#include <stdexcept>
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

TEST(LinePartTest, ShouldOutputRepresentationToStream)
{
   auto part1 = LinePart{Chord{"A"}, lyrics_t{}};
   auto part2 = LinePart{Chord{}, lyrics_t{}};
   std::ostringstream stream1, stream2, expect_stream1, expect_stream2;
   stream1 << part1;
   stream2 << part2;

   expect_stream1 << "LinePart{chord=" << Chord{"A"} << ", lyrics=" << lyrics_t{} << "}";
   expect_stream2 << "LinePart{chord=" << Chord{} << ", lyrics=" << lyrics_t{} << "}";

   EXPECT_EQ(expect_stream1.str(), stream1.str());
   EXPECT_EQ(expect_stream2.str(), stream2.str());
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

TEST(LineTest, ShouldOutputRepresentationToStreamWhenNonEmpty)
{
   auto part1 = LinePart{Chord{"A"}, lyrics_t{}};
   auto part2 = LinePart{Chord{}, lyrics_t{"text"}};
   Line line{part1, part2};

   std::ostringstream stream, expect_stream;
   stream << line;
   expect_stream << "Line{" << part1 << ", " << part2 << "}";

   EXPECT_EQ(expect_stream.str(), stream.str());
}

TEST(LineTest, ShouldOutputRepresentationToStreamWhenEmpty)
{
   Line line;

   std::ostringstream stream;
   stream << line;

   EXPECT_EQ("Line{}", stream.str());
}


TEST(SheetTest, ShouldStoreLine)
{
   Sheet sheet;
   Line line;
   sheet.add_line(line);
   ASSERT_EQ(1, sheet.line_count());
   EXPECT_EQ(line, sheet[0]);
}

TEST(SheetTest, ShouldStoreLinesInOrder)
{
   Sheet sheet;
   std::vector<Line> lines(2);
   lines[1] += LinePart{Chord{}, lyrics_t{}};
   sheet.add_line(lines[0]);
   sheet.add_line(lines[1]);
   EXPECT_EQ(lines[0], sheet[0]);
   EXPECT_EQ(lines[1], sheet[1]);
}

TEST(SheetTest, EqualSheetsShouldCompareEqual)
{
   Sheet sheet;
   std::vector<Line> lines(2);
   lines[1] += LinePart{Chord{}, lyrics_t{}};
   sheet.add_line(lines[0]);
   sheet.add_line(lines[1]);
   EXPECT_TRUE(sheet == sheet);
}

TEST(SheetTest, NonEqualSheetsShouldCompareNonEqual)
{
   Sheet sheet1;
   std::vector<Line> lines(2);
   lines[1] += LinePart{Chord{}, lyrics_t{}};
   sheet1.add_line(lines[0]);
   sheet1.add_line(lines[1]);

   Sheet sheet2;

   EXPECT_FALSE(sheet1 == sheet2);
}

TEST(SheetTest, ShouldOutputRepresentationToStreamWhenNonEmpty)
{
   Sheet sheet;
   Line line1;
   Line line2{LinePart{Chord{}, lyrics_t{"text"}}};
   sheet.add_line(line1);
   sheet.add_line(line2);

   std::ostringstream stream, expect_stream;
   stream << sheet;
   expect_stream << "Sheet{" << line1 << ", " << line2 << "}";

   EXPECT_EQ(expect_stream.str(), stream.str());
}

TEST(SheetTest, ShouldOutputRepresentationToStreamWhenEmpty)
{
   Sheet sheet;

   std::ostringstream stream;
   stream << sheet;

   EXPECT_EQ("Sheet{}", stream.str());
}

TEST(SheetTest, ShouldReportEmptyWhenNoLinesAdded)
{
   Sheet sheet;

   EXPECT_TRUE(sheet.empty());
}

TEST(SheetTest, ShouldReportNonEmptyWhenLinesAdded)
{
   Sheet sheet;
   sheet.add_line({});

   EXPECT_FALSE(sheet.empty());
}

TEST(SheetTest, ShouldReportNumberOfLines)
{
   Sheet sheet;
   sheet.add_line({});
   sheet.add_line({});

   EXPECT_EQ(2, sheet.line_count());
}

TEST(SheetTest, SubscriptShouldReturnLine)
{
   Sheet sheet;
   Line line2{{LinePart{"line2"}}};
   sheet.add_line({});
   sheet.add_line(line2);

   EXPECT_EQ(line2, sheet[1]);
}

TEST(SheetTest, ConstSubscriptShouldReturnLine)
{
   Sheet sheet;
   Line line2{{LinePart{"line2"}}};
   sheet.add_line({});
   sheet.add_line(line2);

   const Sheet &const_sheet = sheet;

   EXPECT_EQ(line2, const_sheet[1]);
}

TEST(SheetTest, SubscriptShouldThrowWhenPositiveOutOfBounds)
{
   Sheet sheet;

   EXPECT_THROW(sheet[0], std::out_of_range);
}

TEST(SheetTest, ConstSubscriptShouldThrowWhenPositiveOutOfBounds)
{
   const Sheet sheet;

   EXPECT_THROW(sheet[0], std::out_of_range);
}

TEST(SheetTest, SubscriptShouldThrowWhenNegativeOutOfBounds)
{
   Sheet sheet;

   EXPECT_THROW(sheet[-1], std::out_of_range);
}

TEST(SheetTest, ConstSubscriptShouldThrowWhenNegativeOutOfBounds)
{
   const Sheet sheet;

   EXPECT_THROW(sheet[-1], std::out_of_range);
}
