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

TEST_F(AsciiParserTest, LateLyricsOnlyLineAddedToSheet)
{
   std::string ascii = "   late lyrics";
   Sheet sheet = m_parser.parse(ascii);

   Sheet expect_sheet;
   expect_sheet.add_line({LinePart{Chord{}, "late lyrics"}});

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

TEST_F(AsciiParserTest, LateChordsOnlyLineAddedToSheet)
{
   std::string ascii = "    A   C#   G7";
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

TEST_F(AsciiParserTest, ChordAndLyricsLineWithLateChordAddedToSheet)
{
   std::string ascii =
      "  A  D#\n"
      "Sing song";
   Sheet sheet = m_parser.parse(ascii);

   Sheet expect_sheet;
   expect_sheet.add_line({LinePart{"Si"}, LinePart{Chord{"A"}, "ng "}, LinePart{Chord{"D#"}, "song"}});

   EXPECT_EQ(expect_sheet, sheet);
}

TEST_F(AsciiParserTest, ChordAndLyricsLineWithLateSongAddedToSheet)
{
   std::string ascii =
      "A   D#\n"
      "  Sing song";
   Sheet sheet = m_parser.parse(ascii);

   Sheet expect_sheet;
   expect_sheet.add_line({LinePart{Chord{"A"}, "  Si"}, LinePart{Chord{"D#"}, "ng song"}});

   EXPECT_EQ(expect_sheet, sheet);
}

TEST_F(AsciiParserTest, ChordAndLyricsLineWithLateChordAndLyricsAddedToSheet)
{
   std::string ascii =
      "  A   D#\n"
      "  Sing song";
   Sheet sheet = m_parser.parse(ascii);

   Sheet expect_sheet;
   expect_sheet.add_line({LinePart{Chord{"A"}, "Sing"}, LinePart{Chord{"D#"}, " song"}});

   EXPECT_EQ(expect_sheet, sheet);
}

TEST_F(AsciiParserTest, ChordAndLyricsLineWithLyricsStartingAfterSecondChordAddedToSheet)
{
   std::string ascii =
      "A   D#\n"
      "      Sing song";
   Sheet sheet = m_parser.parse(ascii);

   Sheet expect_sheet;
   expect_sheet.add_line({LinePart{Chord{"A"}}, LinePart{Chord{"D#"}, "  Sing song"}});

   EXPECT_EQ(expect_sheet, sheet);
}
