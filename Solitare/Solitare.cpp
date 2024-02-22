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
	std::string result;
	if (value == 0)
	{
		result = "A";
	}
	else if (value == 10)
	{
		result = "J";
	}
	else if (value == 11)
	{
		result = "Q";
	}
	else if (value == 12)
	{
		result = "K";
	}
	else {
		result = std::to_string(value + 1);
	}
	if (!is_open) {
		result = "*";
		return result;
	}

	if (suit == Diamonds) {
		result = result + u8"\u2666";
		return result;
	}
	else if (suit == Hearts) {
		result = result + u8"\u2665";
		return result;
	}
	else if (suit == Clubs) {
		result = result + u8"\u2663";
		return result;
	}
	result = result + u8"\u2660";
	return result;
}





Card* Deck::getRandomCard() {
	if (countCards > 0) {
		int index = rand() % countCards;
		Card* tmp = cards[index];
		cards.erase(cards.begin() + index);
		countCards--;
		return tmp;
	}
	else {
		throw std::out_of_range("Empty row");
	}
}


std::string Deck::Draw() {
	return "DK";
}

void Deck::takeNewCards(std::vector<Card*>& newCards)
{
	cards = newCards;
	countCards = newCards.size();
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
	if (count < 1) {
		if (card->getValue() == 12)
		{
			cards.push_back(card);
			count++;
			return;
		}
		else {
			throw std::invalid_argument("Wrong card");
		}
	}
	else {
		if ((isCardBlack(card) != isCardBlack(cards.back())) && (card->getValue() == (cards.back()->getValue() - 1))) {
			cards.push_back(card);
			count++;
		}
		else {
			throw std::invalid_argument("Wrong card");
		}
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
		count--;
		return tmp;
	}
	else {
		throw std::out_of_range("Empty row");
	}
}


std::string Row::Draw() {
	std::string result = "";
	for (auto i = cards.begin(); i < cards.end(); i++) {
		result+="|"+(*i)->Draw();
	}
	return result;
}


std::vector<Card*> Row::takeAllCards() {
	if (count < 1) {
		throw std::out_of_range("Empty row");
	}
	std::vector<Card*> tmp = cards;
	cards = std::vector<Card*>();
	count = 0;
	return tmp;
}

void Row::openLastCard() {
	if (count > 0) {
		cards.back()->open();
	}
}



void Stack::addCard(Card* card) {
	if (count >= 1) {
		if (((card->getSuit() == cards.back()->getSuit()) && (card->getValue() == (cards.back()->getValue() + 1))) || (cards.size() == 0 && card->getValue() == 0)) {
			cards.push_back(card);

			if (card->getValue() == 12) {
				is_finished = true;
			}
			count++;
		}
		else {
			throw std::invalid_argument("Wrong card");
		}
	}
	else {
		if (card->getValue() == 0) {
			cards.push_back(card);
			count++;
		}
		else {
			throw std::invalid_argument("Wrong card");
		}
	}
}


bool Stack::getFlag() {
	return is_finished;
}


std::string Stack::Draw() {
	if (count < 1) {
		return "0";
	}
	return cards.back()->Draw();
}





Desk::Desk() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			CardPull.emplace_back(j, Suit(i));
		}
	}

	this->initialize();
}


void Desk::moveCardFromRowToRow(int first, int second) {
	if (first > 7 || first < 0 || second > 6 || second < 0) {
		return;
	}
	Card* tmp;

	if (first == 7) {
		try {
			tmp = RowForDeck.takeCard();
		}
		catch (std::out_of_range) {
			return;
		}
	}
	else {
		try {
			tmp = rows[first].takeCard();
		}
		catch (std::out_of_range) {
			return;
		}
	}

	try {
		rows[second].addCard(tmp);
		rows[second].openLastCard();
	}
	catch (std::invalid_argument) {
		if (first == 7) {
			RowForDeck.addCardForce(tmp);
		}
		else {
			rows[first].addCardForce(tmp);
		}
	}
}


void Desk::moveCardFromRowToStack(int first, int second) {
	if (first > 7 || first < 0 || second > 3 || second < 0) {
		return;
	}
	Card* tmp;

	if (first == 7){
		try {
			tmp = RowForDeck.takeCard();
		}
		catch (std::out_of_range) {
			return;
		}
	}
	else {
		try {
			tmp = rows[first].takeCard();
		}
		catch (std::out_of_range) {
			return;
		}
	}


	try {
		stacks[second].addCard(tmp);
		rows[second].openLastCard();
	}
	catch (std::invalid_argument) {
		if (first == 7) {
			RowForDeck.addCardForce(tmp);
		}
		else {
			rows[first].addCardForce(tmp);
		}
	}
}


void Desk::takeCardFromDeck() {
	Card* tmp;
	try {
		tmp = deck.getRandomCard();
	}
	catch (std::out_of_range) {
		return;
	}
	tmp->open();
	RowForDeck.addCardForce(tmp);
}

void Desk::returnCardsToDeck() {
	if (deck.getCount() != 0) {
		return;
	}
	std::vector<Card*> tmp;
	try {
		tmp = RowForDeck.takeAllCards();
	}
	catch (std::invalid_argument){
		return;
		}
	deck.takeNewCards(tmp);
}


std::string Desk::Draw() {
	std::string result;
	result = deck.Draw() + "|" + RowForDeck.Draw() + "|..............|";
	for (auto i = stacks.begin(); i < stacks.end(); i++) {
		result += (*i).Draw() + "|";
	}
	result += "\n";
	for (int i = 0; i < rows.size(); i++) {
		result += "(" + std::to_string(i) + ")" + rows[i].Draw() + "\n";
	}
	return result;
}

void Desk::initialize() {
	deck = Deck();
	std::vector<Card*> cards;
	for (auto i = CardPull.begin(); i < CardPull.end(); i++) {
		cards.push_back( &(*i));
	}
	deck.takeNewCards(cards);
	RowForDeck = Row();
	rows = std::vector<Row>(7);

	for (int i = 0; i < 7; i++) {
		rows[i] = Row();
		for (int j = 0; j < i + 1;j++) {
			Card* tmp = deck.getRandomCard();
			if (j == i) {
				tmp->open();
			}
			rows[i].addCardForce(tmp);

		}
	}

	stacks = std::vector<Stack>(4);
	for (int i = 0; i < 4; i++) {
		stacks[i] = Stack();
	}
	
}

bool Desk::checkWin() {
	for (auto i = stacks.begin(); i < stacks.end(); i++){
		if (!(*i).getFlag()) {
			return false;
		}
	}
	return true;
}