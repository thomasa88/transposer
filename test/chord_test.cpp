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

TEST(Chord, TransposeZeroStepsNoQualities)
{
   Chord chord{"D"};
   chord.transpose(0);
   EXPECT_EQ("D", chord.str());
}

TEST(Chord, TransposeUpNoQualities)
{
   Chord chord{"A"};
   chord.transpose(3);
   EXPECT_EQ("C", chord.str());
}

TEST(Chord, TransposeUpPastBoundaryNoQualities)
{
   Chord chord{"G#"};
   chord.transpose(2);
   EXPECT_EQ("A#", chord.str());
}

TEST(Chord, TransposeUpLargeValueNoQualities)
{
   // Was going to use int max, but it is plaftform dependent
   Chord chord{"A"};
   chord.transpose(1000);
   EXPECT_EQ("C#", chord.str());
}

TEST(Chord, TransposeDownNoQualities)
{
   Chord chord{"F"};
   chord.transpose(-2);
   EXPECT_EQ("D#", chord.str());
}

TEST(Chord, TransposeDownPastBoundaryNoQualities)
{
   Chord chord{"B"};
   chord.transpose(-5);
   EXPECT_EQ("F#", chord.str());
}

TEST(Chord, TransposeDownLargeValueNoQualities)
{
   // Was going to use int min, but it is plaftform dependent
   Chord chord{"A"};
   chord.transpose(-1000);
   EXPECT_EQ("F", chord.str());
}
