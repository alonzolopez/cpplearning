#include <iostream>
#include <string>

enum class MonsterType
{
    ogre,
    dragon,
    orc,
    giant_spider,
    slime
};

struct Monster
{
    
    MonsterType monster_type {};
    std::string monster_name {};
    int monster_health {}; 
};

std::string getMonsterName(Monster monster)
{
    switch (monster.monster_type)
    {
        case MonsterType::ogre:
            return "Ogre";
        case MonsterType::dragon:
            return "Dragon";
        case MonsterType::orc:
            return "Orc";
        case MonsterType::giant_spider:
            return "Giant Spider";
        case MonsterType::slime:
            return "Slime";
        default:
            return "unknown monster";
    }
}

void printMonster(Monster monster)
{
    std::cout << "This " << getMonsterName(monster) << " is named " 
        << monster.monster_name << " and has " << monster.monster_health
        << " health.\n";
}

int main()
{
    Monster ogre{ MonsterType::ogre, "Lenny", 150};
    printMonster(ogre);
    Monster slime{ MonsterType::slime, "Sam", 50};
    printMonster(slime);
    return 0;
}