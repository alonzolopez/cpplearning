#include <algorithm> // std::shuffle
#include <array>
#include <cassert>
#include <ctime> // std::time
#include <iostream>
#include <random> // std::mt19937
 
// Maximum score before losing.
static constexpr int maximumScore{ 21 };
 
// Minimum score that the dealer has to have.
constexpr int minimumDealerScore{ 17 };

class Card
{
public:
    enum Suit
    {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,
        max_suits
    };

    enum Rank
    {
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,
        rank_ace,
        max_ranks
    };

private:
    Suit m_suit;
    Rank m_rank;

public:
    Card(Rank rank = Rank::rank_ace, Suit suit = Suit::suit_spade) : m_suit(suit), m_rank(rank) {}

    void print() const
    {
        switch (m_rank)
        {
        case Rank::rank_2:      std::cout << '2';   break;
        case Rank::rank_3:      std::cout << '3';   break;
        case Rank::rank_4:      std::cout << '4';   break;
        case Rank::rank_5:      std::cout << '5';   break;
        case Rank::rank_6:      std::cout << '6';   break;
        case Rank::rank_7:      std::cout << '7';   break;
        case Rank::rank_8:      std::cout << '8';   break;
        case Rank::rank_9:      std::cout << '9';   break;
        case Rank::rank_10:     std::cout << 'T';   break;
        case Rank::rank_jack:   std::cout << 'J';   break;
        case Rank::rank_queen:  std::cout << 'Q';   break;
        case Rank::rank_king:   std::cout << 'K';   break;
        case Rank::rank_ace:    std::cout << 'A';   break;
        default:
            std::cout << '?';
            break;
        }
    
        switch (m_suit)
        {
        case Suit::suit_club:       std::cout << 'C';   break;
        case Suit::suit_diamond:    std::cout << 'D';   break;
        case Suit::suit_heart:      std::cout << 'H';   break;
        case Suit::suit_spade:      std::cout << 'S';   break;
        default:
            std::cout << '?';
            break;
        }
    }
 
    int value() const
    {
    switch (m_rank)
    {
    case Rank::rank_2:        return 2;
    case Rank::rank_3:        return 3;
    case Rank::rank_4:        return 4;
    case Rank::rank_5:        return 5;
    case Rank::rank_6:        return 6;
    case Rank::rank_7:        return 7;
    case Rank::rank_8:        return 8;
    case Rank::rank_9:        return 9;
    case Rank::rank_10:       return 10;
    case Rank::rank_jack:     return 10;
    case Rank::rank_queen:    return 10;
    case Rank::rank_king:     return 10;
    case Rank::rank_ace:      return 11;
    default:
        assert(false && "should never happen");
        return 0;
    }
    }
};



class Deck
{
public:
    using deck_type = std::array<Card, 52>;
    using index_type = deck_type::size_type;
private:
    deck_type m_deck;
    int m_card_index;
public:
    Deck() : m_card_index(0)
    {
        // We could initialize each card individually, but that would be a pain.  Let's use a loop.
        index_type index{ 0 };
        for (int suit{ 0 }; suit < static_cast<int>(Card::Suit::max_suits); ++suit)
        {
            for (int rank{ 0 }; rank < static_cast<int>(Card::Rank::max_ranks); ++rank)
            {
                m_deck[index] = { static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit) };
                ++index;
            }
        }
    }

    void print() const
    {
        for (const auto& card : m_deck)
        {
            card.print();
            std::cout << ' ';
        }
    
        std::cout << '\n';
    }
    

    
    void shuffle()
    {
        static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    
        std::shuffle(m_deck.begin(), m_deck.end(), mt);

        m_card_index = 0;
    }

    const Card& dealCard()
    {
        assert(m_card_index < m_deck.size());
        return m_deck[m_card_index++];
    }

};
 

class Player
{
private:
    int m_score;
public:
    Player() : m_score(0) {}

    void drawCard(Deck &deck)
    {
        m_score += static_cast<int>(deck.dealCard().value());
    }

    int score() const
    {
        return m_score;
    }

    bool isBust() const
    {
        return (m_score > maximumScore) ? true : false;
    }
};
 
bool playerWantsHit()
{
    while (true)
    {
        std::cout << "(h) to hit, or (s) to stand: ";
 
        char ch{};
        std::cin >> ch;
 
        switch (ch)
        {
        case 'h':
            return true;
        case 's':
            return false;
        }
    }
}
 
// Returns true if the player went bust. False otherwise.
bool playerTurn(Deck& deck, Player& player)
{
    while (true)
    {
        if (player.isBust())
        {
            // This can happen even before the player had a choice if they drew 2
            // aces.
            std::cout << "You busted! You lose!\n";
            return true;
        }
        else
        {
            if (playerWantsHit())
            {
                player.drawCard(deck);
                std::cout << "You now have " << player.score() << '\n';
                // std::cout << "You were dealt a card with value" << player.drawCard(deck) << " and now have " << player.score() << '\n';
            }
            else
            {
                // The player didn't go bust.
                return false;
            }
        }
    }
}
 
// Returns true if the dealer went bust. False otherwise.
bool dealerTurn(Deck& deck, Player& dealer)
{
    // Draw cards until we reach the minimum value.
    while (dealer.score() < minimumDealerScore)
    {
        dealer.drawCard(deck);
        std::cout << "The dealer now has " << dealer.score() << '\n';
        // std::cout << "The dealer turned up a " << dealer.drawCard(deck).print() << " and now has " << dealer.score() << '\n';
 
    }
 
    // If the dealer's score is too high, they went bust.
    if (dealer.isBust())
    {
        std::cout << "The dealer busted! You win!\n";
        return true;
    }
    
    return false;
}
 
bool playBlackjack(Deck& deck)
{
 
    // Create the dealer and give them 1 card.
    Player dealer{};
    dealer.drawCard(deck);
 
    // The dealer's card is face up, the player can see it.
    std::cout << "The dealer is showing: " << dealer.score() << '\n';
 
    // Create the player and give them 2 cards.
    Player player{};
    player.drawCard(deck);
    player.drawCard(deck);
 
    std::cout << "You have: " << player.score() << '\n';
 
    if (playerTurn(deck, player))
    {
        // The player went bust.
        return false;
    }
 
    if (dealerTurn(deck, dealer))
    {
        // The dealer went bust, the player wins.
        return true;
    }

    (player.score() > dealer.score()) ? std::cout << "You win!\n" : std::cout << "You lose!\n";
 
    return (player.score() > dealer.score());
}
 
int main()
{
    // test a 
    // const Card cardQueenHearts{ Card::rank_queen, Card::suit_heart };
    // cardQueenHearts.print();
    // std::cout << " has the value " << cardQueenHearts.value() << '\n';

    // test b
    // Deck deck{};
    // deck.print();
    // deck.shuffle();
    // deck.print();

    // test c
    // Deck deck{};
  
    // deck.shuffle();
    // deck.print();
    
    // std::cout << "The first card has value: " << deck.dealCard().value() << '\n';
    // std::cout << "The second card has value: " << deck.dealCard().value() << '\n';

    // test d
    // Deck deck{};
  
    // deck.shuffle();
    // deck.print();

    // Player player{};
    // Player dealer{};

    // player.drawCard(deck);
    // dealer.drawCard(deck);

    // std::cout << "The player drew a card with value: " << player.score() << '\n';
    // std::cout << "The dealer drew a card with value: " << dealer.score() << '\n';

    // play the game!
    Deck deck{};
    deck.shuffle();
    playBlackjack(deck);
 
    return 0;
}