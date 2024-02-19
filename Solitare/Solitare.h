#pragma once
#include <vector>
#include <string>
enum Suit { Diamonds, Hearts, Clubs, Spades };

class Card {
private:
	int value;
	Suit suit;
	bool is_open = false;
public:
	Card(int value, Suit suit): value(value), suit(suit) {};
	void open();
	int getValue();
	Suit getSuit();
	std::string& Draw();
};

class Deck {
private:
	std::vector<Card*> cards;
	int countCards;
public:
	Deck();
	Card* getRandomCard();
	std::string& Draw();
};



class Row {
private:
	std::vector<Card*> cards;
	bool isRowForDeck;
public:
	Row(bool isRowForDeck): cards(), isRowForDeck(isRowForDeck) {};
	void addCard(Card* card);
	Card* takeCard();
	std::vector<std::string>& Draw();
};


class Stack {
private:
	std::vector<Card*> cards;
	bool is_finished = false;
public:
	void addCard(Card* card);
	bool getFlag();
	std::vector<std::string>& Draw();
};

class Desk {
private:
	Deck deck;
	Row RowForDeck;
	std::vector<Row> rows;
	std::vector<Stack> stacks;
public:
	Desk() = default;
	void initialize();
	void moveCardFromRowToRow(int first, int second);
	void moveCardFromRowToStack(int first, int second);
	void takeCardFromDeck();
};
	