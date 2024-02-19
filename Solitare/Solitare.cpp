#include "Solitare.h"
#include <stdexcept>



void Card::open() {
	is_open = true;
}


int Card::getValue(){
	return value;
}


Suit Card::getSuit() {
	return suit;
}


std::string Card::Draw() {
	std::string result = std::to_string(value);
	if (!is_open) {
		result = "*";
		return result;
	}
	if (suit == Diamonds) {
		result = result + "♦️";
		return result;
	}
	else if (suit == Hearts) {
		result = result + "♥️";
		return result;
	}
	else if (suit == Clubs) {
		result = result + "♣️";
		return result;
	}
	result = result + "♠️";
	return result;
}





Card* Deck::getRandomCard() {
	if (countCards > 0) {
		int index = rand() % countCards;
		Card* tmp = cards[rand() % countCards];
		cards.erase(cards.begin() + index);
		return tmp;
		countCards--;
	}
	else {
		throw std::out_of_range("Empty row");
	}
}


std::string Deck::Draw() {
	std::string result = "DK";
	return result;
}





bool Row::isCardBlack(Card* card) {
	Suit suit = card->getSuit();
	if (suit == Diamonds || suit == Hearts) {
		return false;
	}
	else {
		return true;
	}
}


void Row::addCard(Card* card) {
	if ((isCardBlack(card) != isCardBlack(cards.back())) && (card->getValue() == (cards.back()->getValue() - 1))) {
		cards.push_back(card);
		count++;
	}
	else {
		throw std::invalid_argument("Wrong card");
	}
}


void Row::addCardForce(Card* card) {
		cards.push_back(card);
		count++;
}


Card* Row::takeCard()
{
	if (count > 0) {
		Card* tmp = cards.back();
		cards.pop_back();
		cards.back()->open();
		return tmp;
	}
	else {
		throw std::out_of_range("Empty row");
	}
}


std::vector<std::string> Row::Draw() {
	std::vector<std::string> result;
	for (auto i = cards.begin(); i < cards.end(); i++) {
		result.push_back((*i)->Draw());
	}
	return result;
}




void Stack::addCard(Card* card) {
	if (	((card->getSuit() == cards.back()->getSuit())	&&	(card->getValue() == (cards.back()->getValue() + 1)))	||	(cards.size() == 0 && card->getValue() == 0) ){
		cards.push_back(card);

		if (card->getValue() == 12) {
			is_finished = true;
		}
	}
	else {
		throw std::invalid_argument("Wrong card");
	}
}


bool Stack::getFlag() {
	return is_finished;
}


std::vector<std::string> Stack::Draw() {
	std::vector<std::string> result;
	for (auto i = cards.begin(); i < cards.end(); i++) {
		result.push_back((*i)->Draw());
	}
	return result;
}





Desk::Desk() {
	std::vector<Card*> cards;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 13; j++) {
			CardPull.emplace_back(j, Suit(i));
			cards.push_back(&CardPull.back());
			
		}
	}

	deck = Deck(cards);
	RowForDeck = Row(true);
	
	for (int i = 0; i < 7; i++) {
		rows.emplace_back(Row(false));
	}

	for (int i = 0; i < 4; i++) {
		stacks.emplace_back(Stack());
	}
}


void Desk::moveCardFromRowToRow(int first, int second) {
	if (first > 6 || first < 0 || second > 6 || second < 0) {
		throw std::out_of_range("Wrong nunber");
	}
	Card* tmp = rows[first].takeCard();
	try {
		rows[second].addCard(tmp);
	}
	catch (std::invalid_argument) {
		rows[first].addCardForce(tmp);
	}
}


void Desk::moveCardFromRowToStack(int first, int second) {
	if (first > 6 || first < 0 || second > 3 || second < 0) {
		throw std::out_of_range("Wrong nunber");
	}
	Card* tmp = rows[first].takeCard();
	try {
		stacks[second].addCard(tmp);
	}
	catch (std::invalid_argument) {
		rows[first].addCardForce(tmp);
	}
}


void Desk::takeCardFromDeck() {
	Card* tmp = deck.getRandomCard();
	tmp->open();
	RowForDeck.addCardForce(tmp);
}