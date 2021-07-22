#ifndef MONSTER_H
#define MONSTER_H

#include <string>

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
    void print();

private:
    Type m_type;
    std::string m_name;
    std::string m_roar;
    int m_hit_points;
};

#endif