

#include <iostream>
#include "IronDefines.hpp"
#include "Armory.hpp"

// Base attack

std::string Armory::CreateAttackName()
{
	std::cout << "Enter your attack name: ";
	return GetString();
}

AttackType Armory::CreateAttackType()
{
	int newType = -1;
	std::cout << "Is your attack: " << std::endl << "0: physic," << std::endl << "1: magic" << std::endl;
	/*while (newType < 0 || newType > 1) {
		newType = GetInt();
	}*/
	newType = GetInRange(0, 1);
	return (AttackType) newType;
}

int Armory::CreateManaCost(int & points)
{
	int manaBaseCost = 200;
	int usedPoints = -1;
	
	std::cout << "Use points to reduce the mana cost" << std::endl << "Max 15 points, and 0 to skip" << std::endl;
	/*while (usedPoints < 0 || usedPoints > 15) {
		std::cout << "Enter a number of mana reduction (Max 15): ";
		usedPoints = GetInt();
		if (usedPoints > points) {
			std::cout << "You dont have enough points. You have " << points << std::endl;
			usedPoints = -1;
		}
	}*/
	usedPoints = GetPointsInRange(0, 15, points);
	manaBaseCost -= usedPoints * 10;
	//points -= usedPoints;
	return manaBaseCost;
}

int Armory::CreateEnergyCost(int & points)
{
	std::cout << "Use points to increase your energy maximum quantity" << std::endl;
	int energyValue = GetInPoints(points) * 4 + 100;
	return energyValue;
}

int Armory::CreateRoundConservation(int & points)
{
	std::cout << "Add round durability for the unused loads: 2 for 1" << std::endl;
	int roundConservation = GetInPoints(points) / 2;
	return roundConservation;
}

int Armory::CreateLoads(int & points)
{
	std::cout << "Add loads to your attack: 2 for 1" << std::endl;
	int loads = GetInPoints(points) / 2;
	return loads;
}

int Armory::CreateDamages(int & points)
{
	std::cout << "Add damages for your attack" << std::endl;
	int damages = GetInPoints(points) * 10 + 100;
	return damages;
}

int Armory::CreateAttackRange(int & points)
{
	std::cout << "Extend the range of the attack" << std::endl;
	int range = GetInPoints(points) + 1;
	return range;
}

// Base effects

std::string Armory::CreateEffectName()
{
	std::cout << "Enter the name of your effect: ";	return GetString();
}

BonusType Armory::CreateEffectType()
{
	int effectType = -1;
	/*while (effectType < 0 || effectType > 1) {
		std::cout << "Is your effect a malus (0) or a bonus (1): ";
		effectType = GetInt();
	}*/
	std::cout << "Is your effect a malus (0) or a bonus (1): ";
	effectType = GetInRange(0, 1);
	return (BonusType) effectType;
}

int Armory::CreateDuration(int & points)
{
	std::cout << "Increase the effect duration (2 for 1)" << std::endl;
	int duration = GetInPoints(points) / 2 + 1;
	return duration;
}

int Armory::CreateHeal(int & points)
{
	std::cout << "Add a heal to your effect" << std::endl;
	int heal = GetInPoints(points) * 20;
	return heal;
}

int Armory::CreateShield(int & points)
{
	std::cout << "Add a shield to your effect" << std::endl;
	int shield = GetInPoints(points) * 30;
	return shield;
}

bool Armory::CreateStase(int & points)
{
	int stased = -1;
	if (points < 6) {
		std::cout << "You don't have enought points to add a stase" << std::endl;
		return false;
	}
	while (stased < 0 || stased > 1) {
		std::cout << "Do you want to add a stase effect (0 no/1 yes)" << std::endl;
		stased = GetInt();
	}
	if (stased) {
		points -= 6;
	}
	return (bool) stased;
}

int Armory::CreatePhysicalDamages(int & points)
{
	std::cout << "Use points to increase physical damages" << std::endl;
	int damages = GetInPoints(points) * 15 + 50;
	return damages;
}

int Armory::CreateMagicalDamages(int & points)
{
	std::cout << "Use points to increase magical damages" << std::endl;
	int damages = GetInPoints(points) * 15 + 50;
	return damages;
}

Bonus * Armory::CreateBonus(int & points)
{
	int duration = this->CreateDuration(points);
	int heal = this->CreateHeal(points);
	int shield = this->CreateShield(points);
	bool stase = this->CreateStase(points);
	return new Bonus(duration, heal, shield, stase, nullptr);
}


Malus * Armory::CreateMalus(int & points)
{
	int duration = this->CreateDuration(points);
	int physicalDmg = this->CreatePhysicalDamages(points);
	int magicalDmg = this->CreateMagicalDamages(points);
	return new Malus(duration, physicalDmg, magicalDmg, nullptr);
}




void Armory::DisplayAllSpecPossibilities()
{
	std::string * properties = this->CreateAttackPropertiesString();
	PropertyDisplayLoop(16, properties);
}

std::string * Armory::CreateAttackPropertiesString()
{
	std::string * properties = new std::string[16];
	
	properties[0] = "Attack specs";
	properties[1] = "-Attack type (physic/magic)";
	properties[2] = "-Mana cost reduction";
	properties[3] = "-Energy cost reduction";
	properties[4] = "-Round Conservation";
	properties[5] = "-Loads";
	properties[6] = "-Damages";
	properties[7] = "-Range";
	properties[8] = "Effect";
	properties[9] = "Bonus";
	properties[10] = "-Heal";
	properties[11] = "-Shield";
	properties[12] = "-Stase";
	properties[13] = "Malus";
	properties[14] = "-Physical damages";
	properties[15] = "-Magical damages";
	return properties;
}

ZoneLaunchType Armory::CreateLaunchType()
{
	int type = -1;
	
	std::cout << "Is your attack targeted (0) or thrown (1)" << std::endl;
	/*while (type < 0 || type > 1) {
		type = GetInt();
	}*/
	type = GetInRange(0, 1);
	return (ZoneLaunchType) type;
}

int Armory::ZoneTypeSize(int & points)
{
	std::cout << "Enter points to extend the attack zone (limited to 20 points and 2 points for 1 of range more" << std::endl;
	int sizePoints = -1;
	/*while (sizePoints < 0 || sizePoints > points || sizePoints > 20) {
		sizePoints = GetInt();
	}*/
	sizePoints = GetPointsInRange(0, 20, points);
	return (sizePoints / 2) + 2;
}


Attack * Armory::CreateNewAttack()
{
	Bonus * bonus = nullptr;
	Malus * malus = nullptr;
	int points = 100;
	
	std::cout << "you have " << points << " points to use to define your attack" << std::endl;
	std::string name = this->CreateAttackName();
	AttackType type = this->CreateAttackType();
	int manaCost = this-> CreateManaCost(points);
	int energyCost = this->CreateEnergyCost(points);
	int roundConservation = this->CreateRoundConservation(points);
	int loads = this->CreateLoads(points);
	int damages = this->CreateDamages(points);
	int range = this->CreateAttackRange(points);
	int wantEffect = -1;
	std::cout << "Do you want a bonus ? (0/1)" << std::endl;
	/*while (wantEffect < 0 || wantEffect > 1) {
		wantEffect = GetInt();
	}*/
	wantEffect = GetInRange(0, 1);
	if (wantEffect) {
		bonus = this->CreateBonus(points);
	}
	wantEffect = -1;
	std::cout << "Do you want a malus ? (0/1)" << std::endl;
	/*while (wantEffect < 0 || wantEffect > 1) {
		wantEffect = GetInt();
	}*/
	wantEffect = GetInRange(0, 1);
	if (wantEffect) {
		malus = this->CreateMalus(points);
	}
	ZoneLaunchType finalType = this->CreateLaunchType();
	if (finalType) {
		return new TargetedAttack(name, nullptr, nullptr, type, manaCost, energyCost, roundConservation, loads, damages, range, bonus, malus);
	} else {
		int size = this->ZoneTypeSize(points);
		return new ZoneAttack(name, nullptr, nullptr, type, manaCost, energyCost, roundConservation, loads, damages, range, bonus, malus, size);
	}
}

