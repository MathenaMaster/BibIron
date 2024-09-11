

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <string>

#include "BaseAttribute.hpp"

#include "Player.hpp"
#include "Attack.hpp"
#include "Effects.hpp"


class Factory
{
	public:
		//int GetInPoints(int & points);
	
		CharacterBase * CreateCharacter();
		Attack * CreateAttack();
		Effect * CreateEffect(int & points);
		
		void AddAttack(CharacterBase *);
		void EscapeAttack(CharacterBase *);
		void ManageAttacks(CharacterBase *);


// CreateCharacter

		std::string CreateCharacterName();
		int CreateCharacterRange(int & points);
		
		LifeSpecAttribute * CreateLifeSpec(int & points);
		VitalAttribute * CreateVitalAttribute(int & points);
		ManaAttribute * CreateManaAttribute(int & points);
		BaseAttribute * CreateEnergy(int & points);
		ArmorAttribute * CreateArmor(int & points);
		MagicResAttribute * CreateMagicRes(int & points);
		LifeRegenAttribute * CreateLifeRegen(int &, VitalAttribute *);
		ManaRegenAttribute * CreateManaRegen(int &, ManaAttribute *);
		EnergyRegenAttribute * CreateEnergyRegen(int &, BaseAttribute *);
		
		Deplacement * CreateDeplacement(int &);
		int CreateBaseRange(int &);

		void DisplayAllSpecPossibilities();
		std::string* CreateSpecsPropertiesString();
};

// IronIO a mettre dans un autre fichier



#endif


