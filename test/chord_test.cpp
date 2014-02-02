#include "gtest/gtest.h"
#include "chord.h"

TEST(ChordTest, CreateFromString)
{
   Chord chord{"C#sus4"};
   EXPECT_EQ("C#sus4", chord.str());
}

TEST(ChordTest, GetRootFromNoteWithoutAccidental)
{
   Chord chord{"G7"};
   EXPECT_EQ("G", chord.root());
}

TEST(ChordTest, GetRootFromSharpNote)
{
   Chord chord{"D#sus2"};
   EXPECT_EQ("D#", chord.root());
}

TEST(ChordTest, GetRootFromFlatNote)
{
   Chord chord{"Cb"};
   EXPECT_EQ("Cb", chord.root());
}

TEST(ChordTest, TransposeZeroSteps)
{
   Chord chord{"D7"};
   chord.transpose(0);
   EXPECT_EQ("D7", chord.str());
}

TEST(ChordTest, TransposeUp)
{
   Chord chord{"Asus4"};
   chord.transpose(3);
   EXPECT_EQ("Csus4", chord.str());
}

TEST(ChordTest, TransposeUpPastBoundary)
{
   Chord chord{"G#5"};
   chord.transpose(2);
   EXPECT_EQ("A#5", chord.str());
}

TEST(ChordTest, TransposeUpLargeValue)
{
   // Was going to use int max, but it is plaftform dependent
   Chord chord{"Asus2"};
   chord.transpose(1000);
   EXPECT_EQ("C#sus2", chord.str());
}

TEST(ChordTest, TransposeDown)
{
   Chord chord{"FMaj7"};
   chord.transpose(-2);
   EXPECT_EQ("D#Maj7", chord.str());
}

TEST(ChordTest, TransposeDownPastBoundary)
{
   Chord chord{"B"};
   chord.transpose(-5);
   EXPECT_EQ("F#", chord.str());
}

TEST(ChordTest, TransposeDownLargeValue)
{
   // Was going to use int min, but it is plaftform dependent
   Chord chord{"A"};
   chord.transpose(-1000);
   EXPECT_EQ("F", chord.str());
}

TEST(ChordTest, ThrowsExceptionOnInvalidRoot)
{
   EXPECT_THROW(Chord{"i#7"}, std::invalid_argument);
}

TEST(ChordTest, EqualShouldReturnTrueForEqualChords)
{
   EXPECT_TRUE(Chord{"A"} == Chord{"A"});
   EXPECT_TRUE(Chord{"D7"} == Chord{"D7"});
   EXPECT_TRUE(Chord{"G#sus4"} == Chord{"G#sus4"});
   EXPECT_TRUE(Chord{} == Chord{});
}

TEST(ChordTest, EqualShouldReturnFalseForNonEqualChords)
{
   EXPECT_FALSE(Chord{"A"} == Chord{"B"});
   EXPECT_FALSE(Chord{"D7"} == Chord{"D#7"});
   EXPECT_FALSE(Chord{"G#"} == Chord{"G#sus4"});
   EXPECT_FALSE(Chord{"A"} == Chord{});
}

TEST(ChordTest, ShouldNotHaveChordIfConstructedWithoutArguments)
{
   Chord chord;
   EXPECT_FALSE(chord.has_chord());
   // Do we want explicit N.C. str()? Could mess up starts of lines.
}

TEST(ChordTest, ShouldHaveChordIfConstructedWithArguments)
{
   Chord chord{"A"};
   EXPECT_TRUE(chord.has_chord());
}
