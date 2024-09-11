


#ifndef ARMORY_HPP
#define ARMORY_HPP

#include <string>
#include "Attack.hpp"
#include "Effects.hpp"


class Armory
{
	public:
		
		Attack * CreateNewAttack();
// CreateAttack
		std::string CreateAttackName();
		AttackType CreateAttackType();
		int CreateManaCost(int &);
		int CreateEnergyCost(int &);
		int CreateRoundConservation(int &);
		int CreateLoads(int &);
		int CreateDamages(int &);
		int CreateAttackRange(int &);
		
		ZoneLaunchType CreateLaunchType();
		int ZoneTypeSize(int &);
		Attack * TargetOrZone();

// CreateEffect

		std::string CreateEffectName();
		BonusType CreateEffectType();
		int CreateDuration(int &);
		
		Bonus * CreateBonus(int &);
		Malus * CreateMalus(int &);
		
		
		
// Bonus
		
		int CreateHeal(int &);
		int CreateShield(int &);
		bool CreateStase(int &);

// Malus
		int CreatePhysicalDamages(int &);
		int CreateMagicalDamages(int &);
		
		void DisplayAllSpecPossibilities();
		std::string* CreateAttackPropertiesString();
};


#endif

