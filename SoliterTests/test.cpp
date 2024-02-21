#include "gtest/gtest.h"
#include "../Solitare/Solitare.h"

TEST(CardTests, ConstructorTest) {
	Card card(5, Diamonds);
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
	EXPECT_EQ(deck.getCount(), 11);
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


TEST(RowTests, CounstructorTest) {
	Row row = Row();
	EXPECT_EQ(row.getCount(), 0);
}

TEST(RowTests, AddCardAndForceAddCardTest) {
	Row row = Row();
	Card card1(1, Clubs);
	EXPECT_THROW(row.addCard(&card1), std::invalid_argument);

	Card card2(12, Clubs);
	row.addCard(&card2);
	EXPECT_EQ(row.getCount(), 1);

	Card card3(11, Clubs);
	EXPECT_THROW(row.addCard(&card3), std::invalid_argument);

	Card card4(11, Hearts);
	row.addCard(&card4);
	EXPECT_EQ(row.getCount(), 2);

	Card card5(5, Hearts);
	row.addCardForce(&card5);
	EXPECT_EQ(row.getCount(), 3);
}

TEST(RowTests, TakeCardTest) {
	Row row = Row();
	Card card1(12, Clubs);
	row.addCard(&card1);
	EXPECT_EQ(row.takeCard(), &card1);
	EXPECT_EQ(row.getCount(), 0);
	EXPECT_THROW(row.takeCard(), std::out_of_range);

	row.addCard(&card1);
	Card card2(11, Hearts);
	row.addCard(&card2);
	EXPECT_EQ(row.takeCard(), &card2);
	EXPECT_EQ(row.takeCard(), &card1);
	EXPECT_THROW(row.takeCard(), std::out_of_range);
}


TEST(RowTests, DrawTest) {
	Row row = Row();
	Card card1(12, Clubs);
	Card card2(11, Hearts);
	card2.open();
	row.addCard(&card1);
	row.addCard(&card2);
	EXPECT_EQ(row.Draw(), "|*|11♥️");
	row.takeCard();
	EXPECT_EQ(row.Draw(), "|12♣️");
}

TEST(RowTests, TakeAllCardsTest) {
	Row row = Row();
	Card card1(12, Clubs);
	Card card2(11, Hearts);
	card2.open();
	row.addCard(&card1);
	row.addCard(&card2);
	std::vector<Card*> testing = row.takeAllCards();
	EXPECT_EQ(row.getCount(), 0);
	EXPECT_THROW(row.takeCard(), std::out_of_range);
	std::vector<Card*> test({ &card1, &card2 });
	EXPECT_EQ(testing, test);
	EXPECT_EQ(row.takeAllCards(), std::vector<Card*>());
}

TEST(StackTests, ConstructorTest) {
	Stack stack = Stack();
	EXPECT_EQ(stack.getCount(), 0);
}

TEST(StackTests, AddCardTest) {
	Stack stack = Stack();
	Card card1(12, Clubs);

	EXPECT_THROW(stack.addCard(&card1), std::invalid_argument);
	card1 = Card(1, Diamonds);
	stack.addCard(&card1);

	EXPECT_EQ(stack.getCount(), 1);
	Card card2(2, Clubs);
	EXPECT_THROW(stack.addCard(&card2), std::invalid_argument);

	Card card3(3, Diamonds);
	EXPECT_THROW(stack.addCard(&card3), std::invalid_argument);

	Card card4(2, Diamonds);
	stack.addCard(&card4);
	EXPECT_EQ(stack.getCount(), 2);
}


TEST(StackTests, DrawTest) {
	Stack stack = Stack();
	Card card1(1, Diamonds);
	stack.addCard(&card1);
	Card card2(2, Diamonds);
	card2.open();
	stack.addCard(&card2);
	EXPECT_EQ(stack.Draw(), "2♦️");
}