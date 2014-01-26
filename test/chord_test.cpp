#include "gtest/gtest.h"
#include "chord.h"

TEST(Chord, CreateFromString)
{
   Chord chord("C#sus4");
   EXPECT_EQ("C#sus4", chord.str());
}
