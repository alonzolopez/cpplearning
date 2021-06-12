#include <iostream>
#include <string>
#include <array>
#include <random>
#include <algorithm>
#include <ctime>

namespace MyRandom
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
}

namespace Rules
{
    int cards_in_deck{ 52 };
    int max_score{ 21 };
    int dealer_max_score{ 17 };
}

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
    number_ranks,
    unset
};

enum class Suits
{
    clubs,
    diamonds,
    hearts,
    spades,
    number_suits,
    unset
};

struct Card
{
    Ranks rank{};
    Suits suit{};
};

void printCard(const Card card)
{
    switch(card.rank)
    {
        case Ranks::two:
            std::cout << '2';
            break;
        case Ranks::three:
            std::cout << '3';
            break;
        case Ranks::four:
            std::cout << '4';
            break;
        case Ranks::five:
            std::cout << '5';
            break;
        case Ranks::six:
            std::cout << '6';
            break;
        case Ranks::seven:
            std::cout << '7';
            break;
        case Ranks::eight:
            std::cout << '8';
            break;
        case Ranks::nine:
            std::cout << '9';
            break;
        case Ranks::ten:
            std::cout << "10";
            break;
        case Ranks::jack:
            std::cout << 'J';
            break;
        case Ranks::queen:
            std::cout << 'Q';
            break;
        case Ranks::king:
            std::cout << 'K';
            break;
        case Ranks::ace:
            std::cout << 'A';
            break;
        case Ranks::unset:
            break;
        default:
            std::cout << "Unknown card rank\n";
            break;
    }
    switch (card.suit)
    {
        case Suits::clubs:
            std::cout << 'C';
            break;
        case Suits::diamonds:
            std::cout << 'D';
            break;
        case Suits::hearts:
            std::cout << 'H';
            break;
        case Suits::spades:
            std::cout << 'S';
            break;
        case Suits::unset:
            break;
        default:
            std::cout << "Unknown card suit\n";
    }
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
    
    std::shuffle(deck.begin(), deck.end(), MyRandom::mt);
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
        case Ranks::unset:
        default:
            return 0;
    }
}

Card drawCard(const deck_type &deck)
{
    // draw from a uniform distribution
    static std::uniform_int_distribution<> random_card_index{ 0, (sizeof(deck) / sizeof(deck[0])) - 1 };
    return deck[random_card_index(MyRandom::mt)];
}

struct Player
{
    std::array<Card, 21> cards{};
    int cards_in_hand{};
    std::string name;
    int score{};
};

struct Table
{
    Player player{};
    Player dealer{};
};

int calculateScore(const Player &player)
{
    int score{};
    for (Card card : player.cards)
    {
        score += getCardValue(card);
    }
    return score;
}

void printHand(const Player &player)
{
    std::cout << player.name << " has hand: ";
    for (Card card : player.cards)
    {
        printCard(card);
        std::cout << ' ';
    }
    std::cout << '\n';
}

void printStatus(const Player &player)
{
    printHand(player);
    std::cout << player.name << " has score: " << player.score << '\n';
}

Table setupTable(const deck_type &deck)
{
    Table table{};

    // initialize the player's hand
    for (Card &card : table.player.cards)
    {
        card.rank = Ranks::unset;
        card.suit = Suits::unset;
    }
    table.player.name = "Player";

    // initialize the dealer's hand
    for (Card &card : table.dealer.cards)
    {
        card = Card{ Ranks::unset, Suits::unset};
    }
    table.dealer.name = "Dealer";

    // give the player two cards
    table.player.cards[table.player.cards_in_hand] = drawCard(deck);
    ++table.player.cards_in_hand;
    table.player.cards[table.player.cards_in_hand] = drawCard(deck);
    ++table.player.cards_in_hand;
    table.player.score = calculateScore(table.player);

    // print the player's initial hand and score
    printStatus(table.player);
    

    // give the dealer one card
    table.dealer.cards[table.dealer.cards_in_hand] = drawCard(deck);
    ++table.dealer.cards_in_hand;
    table.dealer.score = calculateScore(table.dealer);

    // print the dealer's hand and score
    printStatus(table.dealer);

    std::cout << "Table setup complete.\n---\n";

    return table;
}

bool playersTurn(const deck_type &deck, Table &table)
{
    // return true if the player busted, false otherwise
    bool bust = false;
    char move{};

    while ( table.player.score < Rules::max_score )
    {
        std::cout << "Your move. Enter 'h' to hit or 's' to stay: ";
        std::cin >> move;
        if (move == 's')
        {
            break;
        }
        else if (move == 'h')
        {
            table.player.cards[table.player.cards_in_hand] = drawCard(deck);
            ++table.player.cards_in_hand;
            table.player.score = calculateScore(table.player);
        }
        printStatus(table.player);
    }

    if (table.player.score > Rules::max_score)
    {
        bust = true;
        std::cout << "BUST!\n";
    }
    std::cout << "Your turn is over.\n---\n";

    return bust;
}

bool dealersTurn(const deck_type &deck, Table &table)
{
    // return true if the dealer busted, false otherwise
    bool bust = false;

    while (table.dealer.score < Rules::dealer_max_score)
    {
        table.dealer.cards[table.dealer.cards_in_hand] = drawCard(deck);
        ++table.dealer.cards_in_hand;
        table.dealer.score = calculateScore(table.dealer);
        printStatus(table.dealer);
    }

    if (table.dealer.score > Rules::max_score)
    {
        bust = true;
        std::cout << "BUST!\n";
    }
    std::cout << "The dealer's turn is over\n---\n";

    return bust;

}

void calculateWinner(const Table &table, bool player_bust, bool dealer_bust)
{
    bool player_has_greater_score{ table.player.score > table.dealer.score};
    if (player_bust && !dealer_bust)
    {
        std::cout << "Game over! You lost.\n";
        return;
    }
    else if (dealer_bust && !player_bust)
    {
        std::cout << "Congrats! You won.\n";
        return;
    }
    else if (table.player.score == table.dealer.score)
    {
        std::cout << "You tied! Split the pot.\n";
        return;
    }
    else if (player_has_greater_score)
    {
        std::cout << "Congrats! You won.\n";
        return;
    }
    else if (!player_has_greater_score)
    {
        std::cout << "Game over! You lost.\n";
        return;
    }
}

void playBlackjack(const deck_type &deck)
{
    Table table{ setupTable(deck) };
    bool player_bust{ playersTurn(deck, table)};
    if (player_bust)
    {
        std::cout << "Game over! You lost.\n";
        return;
    }
    bool dealer_bust{ dealersTurn(deck, table) };
    calculateWinner(table, player_bust, dealer_bust);
}

int main()
{

    MyRandom::mt(); // throw the first value away
    

    // create and shuffle the deck
    deck_type deck;
    createDeck(deck);
    shuffleDeck(deck);
    // printDeck(deck);

    // draw a card from the shuffled deck
    drawCard(deck);

    // play the game
    playBlackjack(deck);

    return 0;
}