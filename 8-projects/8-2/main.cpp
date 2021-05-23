#include <iostream>
#include <string>

enum MonsterType
{
    monster_orc,
    monster_goblin,
    monster_troll,
    monster_ogre,
    monster_skeleton
};

std::string getMonsterName(MonsterType monster_type)
{
    switch (monster_type)
    {
        case monster_orc:
            return "Orc";
        case monster_goblin:
            return "Goblin";
        case monster_troll:
            return "Troll";
        case monster_ogre:
            return "Ogre";
        case monster_skeleton:
            return "Skeleton";
        default:
            return "Uknown monster!";
    }
}

int main()
{
    // use the MonsterType prefix to be consisten with the next lesson,
    // though technically we don't need it
    MonsterType monster{ MonsterType::monster_troll }; 
    std::cout << "This monster is a " << getMonsterName( monster ) << '\n';

    return 0;
}
