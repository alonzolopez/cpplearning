#include "monster.h"

Monster::Monster(Monster::Type type, std::string name, std::string roar, int hit_points)
        : m_type(type), m_name(name), m_roar(roar), m_hit_points(hit_points){}

Monster::print()
{
    
}