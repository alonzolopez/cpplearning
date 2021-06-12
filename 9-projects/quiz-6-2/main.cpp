#include <iostream>
#include <string>
#include <array>
#include <random>
#include <algorithm>
#include <ctime>

enum class Ranks
{
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace, 
    number_ranks
};

enum class Suits
{
    clubs,
    diamonds,
    hearts,
    spades,
    number_suits
};

struct Card
{
    Ranks rank{};
    Suits suit{};
};

void printCard(const Card card)
{
    char suits[4]{ 'C', 'D', 'H', 'S'};
    std::string ranks[]{ "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    std::cout << ranks[static_cast<int>(card.rank)] << suits[static_cast<int>(card.suit)];
}

using deck_type = std::array<Card, 52>;

void createDeck(deck_type &deck)
{
    int suits{ static_cast<int>(Suits::number_suits)};
    int ranks{ static_cast<int>(Ranks::number_ranks)};

    for (int s{}; s < suits; ++s)
    {
        for (int r{}; r < ranks; ++r)
        {
            deck[ranks * s + r] = { static_cast<Ranks>(r), static_cast<Suits>(s) };
        }
    }
}

void printDeck(const deck_type &deck)
{
    for (Card card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }
    std::cout << '\n';
}

void shuffleDeck(deck_type &deck)
{
    // mt is static so it only gets seeded once
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(const Card &card)
{
    switch (card.rank)
    {
        case Ranks::two:
            return 2;
        case Ranks::three:
            return 3;
        case Ranks::four:
            return 4;
        case Ranks::five:
            return 5;
        case Ranks::six:
            return 6;
        case Ranks::seven:
            return 7;
        case Ranks::eight:
            return 8;
        case Ranks::nine:
            return 9;
        case Ranks::ten:
        case Ranks::jack:
        case Ranks::queen:
        case Ranks::king:
            return 10;
        case Ranks::ace:
            return 11;
        default:
            return 0;
    }
}

int main()
{
    std::cout << "Creating deck:\n";
    deck_type deck;
    createDeck(deck);
    printDeck(deck);

    std::cout << "Shuffled deck:\n";
    shuffleDeck(deck);
    printDeck(deck);

    Card card{ Ranks::queen, Suits::clubs };

    std::cout << getCardValue( card ) << '\n';

    return 0;
}