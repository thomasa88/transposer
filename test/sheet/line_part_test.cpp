#include "gtest/gtest.h"
#include "sheet/line_part.h"

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
