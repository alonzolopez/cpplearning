#include "monster.h"


int main()
{
	Monster skeleton{ Monster::Type::skeleton, "Bones", "*rattle*", 4 };
	skeleton.print();

	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
	std::rand(); // If using Visual Studio, discard first random value
 
	Monster m{ MonsterGenerator::generateMonster() };
	m.print();
 
	return 0;
}