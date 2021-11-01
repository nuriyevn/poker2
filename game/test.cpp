#include "pch.h"
#include "../HeartAndDiamond/Core.h"



TEST(Straight1, TestSpades)
{
	Hand h1(5);
	
	h1.push(Card(A, SPADES));
	h1.push(Card(5, SPADES));
	h1.push(Card(2, SPADES));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, SPADES));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}

TEST(Straight1, TestDiamonds)
{
	Hand h1(5);

	h1.push(Card(A, DIAMONDS));
	h1.push(Card(5, DIAMONDS));
	h1.push(Card(2, DIAMONDS));
	h1.push(Card(3, DIAMONDS));
	h1.push(Card(4, DIAMONDS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}

TEST(Straight1, TestHearts)
{
	Hand h1(5);

	h1.push(Card(A, HEARTS));
	h1.push(Card(5, HEARTS));
	h1.push(Card(2, HEARTS));
	h1.push(Card(3, HEARTS));
	h1.push(Card(4, HEARTS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}


TEST(Straight1, TestClubs )
{
	Hand h1(5);

	h1.push(Card(A, CLUBS));
	h1.push(Card(5, CLUBS));
	h1.push(Card(2, CLUBS));
	h1.push(Card(3, CLUBS));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}

TEST(Straight1, TestMixedSuits1)
{
	Hand h1(5);

	h1.push(Card(A, CLUBS));
	h1.push(Card(5, SPADES));
	h1.push(Card(2, DIAMONDS));
	h1.push(Card(3, HEARTS));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}



TEST(Straight1, TestMixedSuits2)
{
	Hand h1(5);

	h1.push(Card(A, DIAMONDS));
	h1.push(Card(5, HEARTS));
	h1.push(Card(2, CLUBS));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}

TEST(Straight1, TestMixedSuits3)
{
	Hand h1(5);

	h1.push(Card(A, SPADES));
	h1.push(Card(5, HEARTS));
	h1.push(Card(2, CLUBS));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}

TEST(Straight1, TestMixedSuits4)
{
	Hand h1(5);

	h1.push(Card(A, HEARTS));
	h1.push(Card(5, HEARTS));
	h1.push(Card(2, HEARTS));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}


// NotStraight 2 ----------------------------------------

TEST(NotStraight2, TestSpades)
{
	Hand h1(5);

	h1.push(Card(A, SPADES));
	h1.push(Card(5, SPADES));
	h1.push(Card(6, SPADES));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, SPADES));

	Deck d;
	EXPECT_FALSE(d.isStraight(h1));
}

TEST(NotStraight2, TestDiamonds)
{
	Hand h1(5);

	h1.push(Card(A, DIAMONDS));
	h1.push(Card(5, DIAMONDS));
	h1.push(Card(6, DIAMONDS));
	h1.push(Card(3, DIAMONDS));
	h1.push(Card(4, DIAMONDS));

	Deck d;
	EXPECT_FALSE(d.isStraight(h1));
}

TEST(NotStraight2, TestHearts)
{
	Hand h1(5);

	h1.push(Card(A, HEARTS));
	h1.push(Card(5, HEARTS));
	h1.push(Card(6, HEARTS));
	h1.push(Card(3, HEARTS));
	h1.push(Card(4, HEARTS));

	Deck d;
	EXPECT_FALSE(d.isStraight(h1));
}


TEST(NotStraight2, TestClubs)
{
	Hand h1(5);

	h1.push(Card(A, CLUBS));
	h1.push(Card(5, CLUBS));
	h1.push(Card(6, CLUBS));
	h1.push(Card(3, CLUBS));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_FALSE(d.isStraight(h1));
}

TEST(NotStraight2, TestMixedSuits1)
{
	Hand h1(5);

	h1.push(Card(A, CLUBS));
	h1.push(Card(5, SPADES));
	h1.push(Card(6, DIAMONDS));
	h1.push(Card(3, HEARTS));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_FALSE(d.isStraight(h1));
}



TEST(NotStraight2, TestMixedSuits2)
{
	Hand h1(5);

	h1.push(Card(A, DIAMONDS));
	h1.push(Card(5, HEARTS));
	h1.push(Card(6, CLUBS));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_FALSE(d.isStraight(h1));
}

TEST(NotStraight2, TestMixedSuits3)
{
	Hand h1(5);

	h1.push(Card(A, SPADES));
	h1.push(Card(5, HEARTS));
	h1.push(Card(3, CLUBS));
	h1.push(Card(4, SPADES));
	h1.push(Card(6, CLUBS));

	Deck d;
	EXPECT_FALSE(d.isStraight(h1));
}

TEST(NotStraight2, TestMixedSuits4)
{
	Hand h1(5);

	h1.push(Card(A, HEARTS));
	h1.push(Card(5, HEARTS));
	h1.push(Card(3, HEARTS));
	h1.push(Card(4, SPADES));
	h1.push(Card(6, CLUBS));

	Deck d;
	EXPECT_FALSE(d.isStraight(h1));
}


// Straight 3 - -------------------------------------

TEST(Straight3, TestMixedSuits1)
{
	Hand h1(5);

	h1.push(Card(6, HEARTS));
	h1.push(Card(7, DIAMONDS));
	h1.push(Card(10, CLUBS));
	h1.push(Card(9, SPADES));
	h1.push(Card(8, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}
TEST(Straight3, TestMixedSuits2)
{
	Hand h1(5);

	h1.push(Card(6, SPADES));
	h1.push(Card(7, HEARTS));
	h1.push(Card(10, CLUBS));
	h1.push(Card(9, HEARTS));
	h1.push(Card(8, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}

TEST(Straight3, TestMixedSuits3)
{
	Hand h1(5);

	h1.push(Card(6, CLUBS));
	h1.push(Card(7, CLUBS));
	h1.push(Card(10, SPADES));
	h1.push(Card(9, SPADES));
	h1.push(Card(8, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}


TEST(Straight3, TestMixedSuits4)
{
	Hand h1(5);

	h1.push(Card(6, SPADES));
	h1.push(Card(7, SPADES));
	h1.push(Card(10, HEARTS));
	h1.push(Card(9, DIAMONDS));
	h1.push(Card(8, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}



// 

TEST(Straight4, TestMixedSuits1)
{
	Hand h1(5);

	h1.push(Card(10, SPADES));
	h1.push(Card(K, SPADES));
	h1.push(Card(A, HEARTS));
	h1.push(Card(J, DIAMONDS));
	h1.push(Card(Q, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}


TEST(Straight4, TestMixedSuits2)
{
	Hand h1(5);

	h1.push(Card(10, DIAMONDS));
	h1.push(Card(K, SPADES));
	h1.push(Card(A, HEARTS));
	h1.push(Card(J, DIAMONDS));
	h1.push(Card(Q, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}

TEST(Straight4, TestMixedSuits3)
{
	Hand h1(5);

	h1.push(Card(10, CLUBS));
	h1.push(Card(K, SPADES));
	h1.push(Card(A, CLUBS));
	h1.push(Card(J, DIAMONDS));
	h1.push(Card(Q, HEARTS));

	Deck d;
	EXPECT_TRUE(d.isStraight(h1));
}


// FLUSH
TEST(Flush1, TestSpades)
{
	Hand h1(5);

	h1.push(Card(A, SPADES));
	h1.push(Card(5, SPADES));
	h1.push(Card(2, SPADES));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, SPADES));

	Deck d;
	EXPECT_TRUE(d.isFlush(h1));
}

TEST(Flush1, TestDiamonds)
{
	Hand h1(5);

	h1.push(Card(A, DIAMONDS));
	h1.push(Card(5, DIAMONDS));
	h1.push(Card(2, DIAMONDS));
	h1.push(Card(3, DIAMONDS));
	h1.push(Card(4, DIAMONDS));

	Deck d;
	EXPECT_TRUE(d.isFlush(h1));
}

TEST(Flush1, TestHearts)
{
	Hand h1(5);

	h1.push(Card(A, HEARTS));
	h1.push(Card(5, HEARTS));
	h1.push(Card(2, HEARTS));
	h1.push(Card(3, HEARTS));
	h1.push(Card(4, HEARTS));

	Deck d;
	EXPECT_TRUE(d.isFlush(h1));
}


TEST(Flush1, TestClubs)
{
	Hand h1(5);

	h1.push(Card(A, CLUBS));
	h1.push(Card(5, CLUBS));
	h1.push(Card(2, CLUBS));
	h1.push(Card(3, CLUBS));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_TRUE(d.isFlush(h1));
}

TEST(Flush1, TestMixedSuits1)
{
	Hand h1(5);

	h1.push(Card(A, CLUBS));
	h1.push(Card(5, SPADES));
	h1.push(Card(2, DIAMONDS));
	h1.push(Card(3, HEARTS));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_FALSE(d.isFlush(h1));
}



TEST(Flush1, TestMixedSuits2)
{
	Hand h1(5);

	h1.push(Card(A, DIAMONDS));
	h1.push(Card(5, HEARTS));
	h1.push(Card(2, CLUBS));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_FALSE(d.isFlush(h1));
}

TEST(Flush1, TestMixedSuits3)
{
	Hand h1(5);

	h1.push(Card(A, SPADES));
	h1.push(Card(5, HEARTS));
	h1.push(Card(2, CLUBS));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_FALSE(d.isFlush(h1));
}

TEST(Flush1, TestMixedSuits4)
{
	Hand h1(5);

	h1.push(Card(A, HEARTS));
	h1.push(Card(5, HEARTS));
	h1.push(Card(2, HEARTS));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, CLUBS));

	Deck d;
	EXPECT_FALSE(d.isFlush(h1));
}


