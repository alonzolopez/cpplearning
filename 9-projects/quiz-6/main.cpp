#include <iostream>
#include <string>
#include <array>
#include <random>
#include <algorithm>

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

void createDeck(std::array<Card, 52> &deck)
{
    for (int s{}; static_cast<Suits>(s) < Suits::number_suits; ++s)
    {
        for (int r{}; static_cast<Ranks>(r) < Ranks::number_ranks; ++r)
        {
            deck[static_cast<int>(Ranks::number_ranks) * s + r] = { static_cast<Ranks>(r), static_cast<Suits>(s) };
        }
    }
}

void printDeck(const std::array<Card, 52> &deck)
{
    for (Card card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }
    std::cout << '\n';
}

void shuffleDeck(std::array<Card, 52> &deck, std::mt19937 g)
{
    std::shuffle(deck.begin(), deck.end(), g);
}

int main()
{
    // seed the rng
    std::random_device rd;
    std::mt19937 g(rd());

    std::cout << "Creating deck:\n";
    std::array<Card, 52> deck;
    createDeck(deck);
    printDeck(deck);

    std::cout << "Shuffled deck:\n";
    shuffleDeck(deck, g);
    printDeck(deck);

    return 0;
}