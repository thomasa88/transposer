#include "gtest/gtest.h"
#include "chord.h"

TEST(Chord, CreateFromString)
{
   Chord chord{"C#sus4"};
   EXPECT_EQ("C#sus4", chord.str());
}

TEST(Chord, GetRootFromNoteWithoutAccidental)
{
   Chord chord{"G7"};
   EXPECT_EQ("G", chord.root());
}

TEST(Chord, GetRootFromSharpNote)
{
   Chord chord{"D#sus2"};
   EXPECT_EQ("D#", chord.root());
}

TEST(Chord, GetRootFromFlatNote)
{
   Chord chord{"Cb"};
   EXPECT_EQ("Cb", chord.root());
}

TEST(Chord, TransposeUpNoQualities)
{
   Chord chord{"A"};
   chord.transpose(3);
   EXPECT_EQ("C", chord.str());
}
