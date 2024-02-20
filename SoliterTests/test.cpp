#include "gtest/gtest.h"
#include "../Solitare/Solitare.h"

TEST(CardTests, ConstructorTest) {
	Card card(5, Diamonds);
	Row f(false);
	f.getCount();
	EXPECT_EQ(card.getValue(), 5);
	EXPECT_EQ(card.getSuit(), Diamonds);
}

TEST(CardTests, DrawTest) {
	Card card(10, Spades);
	EXPECT_EQ(card.Draw(), std::string("*"));
	card.open();
	EXPECT_EQ(card.Draw(), std::string("10♠️"));
}

TEST(DeckTests, ConstructorTest) {
	std::vector<Card*> cards;
	for (int i = 0; i < 10; i++) {
		Card card(i, Diamonds);
		cards.push_back(&card);
	}
	Deck deck(cards);
	EXPECT_EQ(deck.getCount(), 10);

}

TEST(DeckTests, TakeNewCardsAndGetRandomTest) {
	std::vector<Card*> cards;
	for (int i = 0; i < 10; i++) {
		Card card(i, Diamonds);
		cards.push_back(&card);
	}
	Deck deck(cards);

	for (int i = 10; i < 12; i++) {
		Card card(i, Hearts);
		cards.push_back(&card);
	}
	deck.takeNewCards(cards);
	EXPECT_EQ(deck.getCount(), 12);
	Card* test = deck.getRandomCard();
	EXPECT_TRUE(test->getSuit() == Hearts || test->getSuit() == Diamonds || test->getValue() >= 0 || test->getValue() <= 12);
}


TEST(DeckTests, DrawTest) {
	std::vector<Card*> cards;
	for (int i = 0; i < 3; i++) {
		Card card(i, Diamonds);
		cards.push_back(&card);
	}
	Deck deck(cards);
	EXPECT_EQ(deck.Draw(), "DK");
}