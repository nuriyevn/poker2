#pragma once

#include <random>
#include <vector>
#include <assert.h>


enum RANK { A = 1, TWO=2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K, RMAX };
enum SUIT { HEARTS = 0, DIAMONDS, CLUBS, SPADES, SMAX };
const short DECK_SIZE = 52;

class Card // Should be easy  to creat algo around this
{
public:
	short rank;
	short suit;
	Card(short r, short s) :
		rank(r), suit(s)
	{
	}
	Card() {};
	~Card() {};
	Card& operator=(const Card& right)
	{
		if (this != &right)
		{
			this->rank = right.rank;
			this->suit = right.suit;

		}
		return *this;
	}

	Card(const Card& other)
	{
		rank = other.rank;
		suit = other.suit;
	}
};

// Extra Class
class Hand
{
public:
	unsigned short expected_size;
	std::vector<Card> cards;
	Hand(unsigned short size)

	{
		expected_size = size;
		assert(expected_size > 1);
	}
	bool push(Card card)
	{
		bool result = true;
		if (cards.size() < expected_size)
			cards.push_back(card);
		else
			result = false;
		return result;
	}
	~Hand() {};

private:
	Hand() {};
};

class Deck // Should be easy  to creat algo around this
{
public:
	Card cards[DECK_SIZE];
	Deck() {
		int c = 0;
		for (int r = A; r < RANK::RMAX; r++)
		{
			for (int s = HEARTS; s < SUIT::SMAX; s++)
			{
				cards[c].rank = r;
				cards[c].suit = s;
				c++;
			}
		}
	}

	//  not the best shuffle algorithm. 
	//  but I want to make this task in 30-40 minutes
	//  a lot of ideas come to my head but it needs time to check and optimize them.
	void shuffle() {
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> distrib(0, DECK_SIZE - 1);

		short count = 0;
		// for debug only in average  236 attempts required to create ; around ~750 at the worst case  ~102 in the best case.
		//short generation_attepmts = 0;  


		std::vector<short> v;
		while (count < DECK_SIZE)
		{
			// this algorithm is far from ideal
			// it's probably better to generate SUIT and RANK distinclty
			// to prevent situation when consequent SUITS appear. 
			// like consequent DIAMOND 9,  DIAMOND 10, DIAMOND 5. 

			short number = distrib(gen);

			std::vector<short>::iterator it =
				std::find(v.begin(), v.end(), number);

			if (it == v.end())
			{
				v.push_back(number);
				count++;
			}

			//generation_attepmts++;
		}


		assert(v.size() == DECK_SIZE);

		for (int i = 0; i < DECK_SIZE; i++)
		{
			short last_card = v.back();
			v.pop_back();

			cards[i].rank = (last_card % RANK::RMAX) + 1; // ranks in enum is started from one
			cards[i].suit = last_card / RANK::RMAX;  // suits in enum starts from zero , so we can use quotient as index
		}

		//return generation_attepmts;

		/*
		std::cout << generation_attepmts << std::endl;
		for (std::vector<short>::iterator it = v.begin();
			it != v.end(); it++)
		{
			std::cout << *it << " ";
		}*/
	}

	bool isFlush(Hand hand)
	{
		bool is_same_suit = true;
		int suit_comparing_with = hand.cards[0].suit;

		for (short i = 1; i < hand.expected_size; i++)
		{
			if (hand.cards[i].suit != suit_comparing_with)
			{
				is_same_suit = false;
				break;
			}
		}

		return is_same_suit;
	}

	bool isStraight(Hand hand)
	{
		bool is_straight1 = true; // for ACE as 1
		bool is_straight2 = true; // for ace as 14

		assert(hand.expected_size > 1);

		std::vector<short> ranks;

		while (!hand.cards.empty())
		{
			short last_rank = hand.cards.back().rank;
			ranks.push_back(last_rank);
			hand.cards.pop_back();
		}

		std::sort(ranks.begin(), ranks.end());

		short prev = *(ranks.begin());

		for (std::vector<short>::iterator it = ranks.begin() + 1; it != ranks.end(); it++)
		{
			if (*it - prev != 1)
			{
				is_straight1 = false;
				break;
			}

			prev = *it;
		}

		// Ace = 14
		std::replace(ranks.begin(), ranks.end(), 1, 14);
		std::sort(ranks.begin(), ranks.end());

		prev = *(ranks.begin());

		for (std::vector<short>::iterator it = ranks.begin() + 1; it != ranks.end(); it++)
		{
			if (*it - prev != 1)
			{
				is_straight2 = false;
				break;
			}

			prev = *it;
		}

		// one is_straight1 or  is_straight2 must be true.
		// However there can be a special case/situation when we is_straight1 and is_straight2 both true both as A=1 and A=14, when the hand size is 13
		// it will work fine
		return is_straight1 || is_straight2;
	}


	// Helper functions
	void show()
	{
		for (short i = 0; i < DECK_SIZE; i++)
		{
			std::cout << suit_str(cards[i].suit).c_str() << " ";
			std::cout << rank_str(cards[i].rank).c_str() << std::endl;
		}
	}

	std::string suit_str(short suit)
	{
		std::string  suits[SUIT::SMAX] = { "HEART", "DIAMOND", "CLUB", "SPADE" };
		return suits[suit];
	}

	std::string rank_str(short rank)
	{
		std::string ranks[RANK::RMAX] = { "A", "2", "3",
		"4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
		return ranks[rank];
	}
};
