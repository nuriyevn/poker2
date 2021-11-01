// HeartAndDiamond.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "core.h"

int main()
{
	Deck d;
	d.shuffle();
	d.show();

	Hand h1(5);
	h1.push(Card(A, SPADES));
	h1.push(Card(A, DIAMONDS));
	h1.push(Card(3, SPADES));
	h1.push(Card(4, DIAMONDS));
	h1.push(Card(5, SPADES));


	if (d.isFlush(h1))
		std::cout << "Flush" << std::endl;
	else
		std::cout << "not Flush" << std::endl;

	if (d.isStraight(h1))
		std::cout << "Straight" << std::endl;
	else
		std::cout << "not Straight" << std::endl;
}


/*
void debug_random_test()
{
	Deck d;
	int s = 0;
	float avg = 0.0;

	int max = 0;
	int min = 100000000;
	const int runs = 10000;
	for (int i = 0; i < runs; i++)
	{
		int g = d.shuffle();
		if (g > max)
			max = g;
		if (g < min)
			min = g;
		s = s + g;
	}

	std::cout << min << std::endl;
	std::cout << max << std::endl;
	std::cout << avg / (float)runs << std::endl;
}*/
