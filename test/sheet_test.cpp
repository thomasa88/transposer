#include "gtest/gtest.h"
#include "sheet.h"

#include <memory>
#include <string>

TEST(LyricsLineTest, FromAscii)
{
   std::string lyrics{"Hi ho hay!"};
   std::unique_ptr<Line> line = Line::from_ascii(lyrics);
   EXPECT_EQ(lyrics, line->str());
}
