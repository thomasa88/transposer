#include "gtest/gtest.h"
#include "ascii.h"

class AsciiParserTest : public ::testing::Test
{
protected:
   virtual void SetUp()
   {
      
   }
   AsciiParser m_parser;
};

TEST_F(AsciiParserTest, LyricsOnlyLineAddedToSheet)
{
   std::string ascii = "Some lyrics";
   Sheet sheet = m_parser.parse(ascii);

   Sheet expect_sheet;
   expect_sheet.add_line({LinePart{Chord{}, ascii}});

   EXPECT_EQ(expect_sheet, sheet);
}

TEST_F(AsciiParserTest, MultipleLyricsOnlyLinesAddedToSheet)
{
   std::string ascii = "Line 1\nLine 2\nLine 3";
   Sheet sheet = m_parser.parse(ascii);

   Sheet expect_sheet;
   expect_sheet.add_line({LinePart{Chord{}, "Line 1"}});
   expect_sheet.add_line({LinePart{Chord{}, "Line 2"}});
   expect_sheet.add_line({LinePart{Chord{}, "Line 3"}});

   EXPECT_EQ(expect_sheet, sheet);
}

TEST_F(AsciiParserTest, ChordsOnlyLineAddedToSheet)
{
   std::string ascii = "A   C#   G7";
   Sheet sheet = m_parser.parse(ascii);

   Sheet expect_sheet;
   expect_sheet.add_line({LinePart{Chord{"A"}}, LinePart{Chord{"C#"}}, LinePart{Chord{"G7"}}});

   EXPECT_EQ(expect_sheet, sheet);
}

TEST_F(AsciiParserTest, MultipleChordsOnlyLinesAddedToSheet)
{
   std::string ascii = "A   C#   G7\n  B E";
   Sheet sheet = m_parser.parse(ascii);

   Sheet expect_sheet;
   expect_sheet.add_line({LinePart{Chord{"A"}}, LinePart{Chord{"C#"}}, LinePart{Chord{"G7"}}});
   expect_sheet.add_line({LinePart{Chord{"B"}}, LinePart{Chord{"E"}}});

   EXPECT_EQ(expect_sheet, sheet);
}

TEST_F(AsciiParserTest, ChordAndLyricsLineAddedToSheet)
{
   std::string ascii =
      "A    B\n"
      "Sing song";
   Sheet sheet = m_parser.parse(ascii);

   Sheet expect_sheet;
   expect_sheet.add_line({LinePart{Chord{"A"}, "Sing "}, LinePart{Chord{"B"}, "song"}});

   EXPECT_EQ(expect_sheet, sheet);
}
