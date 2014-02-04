#include "gtest/gtest.h"
#include "ascii.h"

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
