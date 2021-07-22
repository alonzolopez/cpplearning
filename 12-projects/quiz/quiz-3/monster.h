#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <iostream>
#include <ctime> // for time()
#include <cstdlib> // for rand() and srand()
#include <array>

class Monster
{
public:
    enum class Type
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
        max_monster_types
    };

    Monster(Monster::Type type, std::string name, std::string roar, int hit_points);
    void print() const;
    std::string getTypeString() const;

private:
    Type m_type;
    std::string m_name;
    std::string m_roar;
    int m_hit_points;
};

class MonsterGenerator
{
private:
    static int getRandomNumber(int min, int max);
public:
    // static Monster generateMonster() { return Monster(Monster::Type::skeleton, "Bones", "*rattle*", 4);}
    static Monster generateMonster();
};

#endif