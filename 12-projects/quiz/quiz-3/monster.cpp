#include "monster.h"

Monster::Monster(Monster::Type type, std::string name, std::string roar, int hit_points)
	: m_type(type), m_name(name), m_roar(roar), m_hit_points(hit_points){}

std::string Monster::getTypeString() const
{
	switch (m_type)
	{
		case Type::dragon: return "dragon";
		case Type::goblin: return "goblin";
		case Type::ogre: return "ogre";
		case Type::orc: return "orc";
		case Type::skeleton: return "skeleton";
		case Type::troll: return "troll";
		case Type::vampire: return "vampire";
		case Type::zombie: return "zombie";
		default: return "uknown monster";
	}
}

void Monster::print() const
{
    std::cout << m_name << " the " << this->getTypeString() << " has " << m_hit_points << " hit points and says " << m_roar << '\n';
}

int MonsterGenerator::getRandomNumber(int min, int max)
{
	static constexpr double fraction{ 1.0 / (static_cast<double>(RAND_MAX) + 1.0) };  // static used for efficiency, so we only calculate this value once
	// evenly distribute the random number across our range
	return static_cast<int>(std::rand() * fraction * (max - min + 1) + min);
}

Monster MonsterGenerator::generateMonster()
{
	static std::array<std::string, 6> s_names{ "Doug", "Jimothy", "Billiam", "Dougett", "Jimmy Johnson", "Martin"};
	static std::array<std::string, 6> s_roars{ "heyo", "hola", "howdy", "hi", "top o' the mornin'", "helo g'vnah"};
	int rand_int{ MonsterGenerator::getRandomNumber(0, static_cast<int>(Monster::Type::max_monster_types) - 1)};
	return Monster(
		static_cast<Monster::Type>(MonsterGenerator::getRandomNumber(0, static_cast<int>(Monster::Type::max_monster_types) - 1)), 
		s_names[MonsterGenerator::getRandomNumber(0, 5)], 
		s_roars[MonsterGenerator::getRandomNumber(0, 5)], 
		MonsterGenerator::getRandomNumber(0, 100));
}