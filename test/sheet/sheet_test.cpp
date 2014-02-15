#include "gtest/gtest.h"
#include "sheet/sheet.h"

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
