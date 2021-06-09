#include <iostream>
#include <array>
#include <numeric> // std::reduce

enum class Player
{
    health_potions,
    torches,
    arrows, 
    max_items
};

// create an alias to make the function and array declaration easier to read
using inventory_type = std::array<int, static_cast<int>(Player::max_items)>;

int countTotalItems(inventory_type &player)
{
    return std::accumulate(player.begin(), player.end(), 0);
}

int main()
{
    inventory_type player1{ 2, 5, 10 };

    std::cout << player1[static_cast<int>(Player::arrows)] << '\n';

    std::cout << "The player has " << countTotalItems(player1) << " items.\n";

    return 0;

}