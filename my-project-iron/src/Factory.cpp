

#include <iostream>
#include "IronDefines.hpp"
#include "Factory.hpp"



std::string Factory::CreateCharacterName()
{
	std::cout << "Enter the name of your character: ";
	return GetString();
}


int Factory::CreateCharacterRange(int & points)
{
	std::cout << "Enter the base range of your character: ";
	return GetInPoints(points) + 1;
}

LifeSpecAttribute * Factory::CreateLifeSpec(int & points)
{
	std::cout << "Enter the physical damages: ";
	int physic = GetInPoints(points) * 3 + 50;
	std::cout << "Enter the magical damages: ";
	int magic = GetInPoints(points) * 3 + 50;
	VitalAttribute * life = this->CreateVitalAttribute(points);
	ManaAttribute * mana = this->CreateManaAttribute(points);
	BaseAttribute * energy = this->CreateEnergy(points);
	ArmorAttribute * armor = this->CreateArmor(points);
	MagicResAttribute * mr = this->CreateMagicRes(points);
	LifeRegenAttribute * lifeRegen = this->CreateLifeRegen(points, life);
	ManaRegenAttribute * manaRegen = this->CreateManaRegen(points, mana);
	EnergyRegenAttribute * energyRegen = this->CreateEnergyRegen(points, energy);
	return new LifeSpecAttribute(physic, magic, life, mana, energy, armor, mr, lifeRegen, manaRegen, energyRegen);
}

VitalAttribute * Factory::CreateVitalAttribute(int & points)
{
	std::cout << "Enter points for your life spec: ";	int usedPoints = 1000 + GetInPoints(points) * 100;
	return new VitalAttribute(usedPoints);
}

ManaAttribute * Factory::CreateManaAttribute(int & points)
{
	std::cout << "Enter your mana points: ";
	int usedPoints = 700 + GetInPoints(points) * 50;
	return new ManaAttribute(usedPoints);
}

BaseAttribute * Factory::CreateEnergy(int & points)
{
	std::cout << "Enter your energy points: ";
	int usedPoints = 100 + GetInPoints(points) * 10;
	return new BaseAttribute(usedPoints);
}

ArmorAttribute * Factory::CreateArmor(int & points)
{
	std::cout << "Enter armor points: ";
	int usedPoints = 10 + GetInPoints(points);
	return new ArmorAttribute(usedPoints);
}

MagicResAttribute * Factory::CreateMagicRes(int & points)
{
	std::cout << "Enter magic resistance points: ";
	int usedPoints = 5 + GetInPoints(points);
	return new MagicResAttribute(usedPoints);
}

LifeRegenAttribute * Factory::CreateLifeRegen(int & points, VitalAttribute * life)
{
	std::cout << "Enter life regeneration points: ";
	int usedPoints = 20 + GetInPoints(points) * 20;
	return new LifeRegenAttribute(life, usedPoints);
}

ManaRegenAttribute * Factory::CreateManaRegen(int & points, ManaAttribute * mana)
{
	std::cout << "Enter mana regeneration points: ";
	int usedPoints = 15 + GetInPoints(points) * 10;
	return new ManaRegenAttribute(mana, usedPoints);
}


EnergyRegenAttribute * Factory::CreateEnergyRegen(int & points, BaseAttribute * energy)
{
	std::cout << "Enter energy regeneration: ";
	int usedPoints = 5 + GetInPoints(points) * 5;
	return new EnergyRegenAttribute(energy, usedPoints);
}


Deplacement * Factory::CreateDeplacement(int & points)
{
	std::cout << "Enter your deplacement points: ";
	int usedPoints = 2 + GetInPoints(points) * 1.5;
	return new Deplacement(usedPoints);
}

int Factory::CreateBaseRange(int & points)
{
	std::cout << "Enter your range points: ";
	int usedPoints = 1 + GetInPoints(points);
	return usedPoints;
}

CharacterBase * Factory::CreateCharacter()
{
	int points = 100;
	
	//std::cout << "Enter the name of your character: ";
	//std::string newName = GetString();
	std::string newName = this->CreateCharacterName();
	std::cout << "you have 100 points to use" << std::endl;
	std::cout << "Keep some for all specs and use them all :)" << std::endl;
	LifeSpecAttribute * newLifeSpec = this->CreateLifeSpec(points);
	Deplacement * newMove = this->CreateDeplacement(points);
	int newBaseRange = this->CreateBaseRange(points);
	return new CharacterBase(newName, newLifeSpec, newMove, newBaseRange);
}


void Factory::DisplayAllSpecPossibilities()
{
	std::string * properties = this->CreateSpecsPropertiesString();
	PropertyDisplayLoop(11, properties);
}

std::string * Factory::CreateSpecsPropertiesString()
{
	std::string * properties = new std::string[11];
	
	properties[0] = "Life Specs:";
	properties[1] = "-Vitality";
	properties[2] = "-Mana";
	properties[3] = "-Energy";
	properties[4] = "-Physical armor";
	properties[5] = "-Magical armor";
	properties[6] = "-Life regeneration";
	properties[7] = "-Mana regeneration";
	properties[8] = "-Energy regeneration";
	properties[9] = "-Character deplacement";
	properties[10] = "-Base attack range";
	return properties;
}
