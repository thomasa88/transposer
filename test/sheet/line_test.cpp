#include "gtest/gtest.h"
#include "sheet/line.h"

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
