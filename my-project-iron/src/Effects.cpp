
#include <iostream>


#include "IronDefines.hpp"
#include "Player.hpp"
#include "Effects.hpp"



// Effect

Effect::Effect(BonusType type, int duration, CharacterBase * target) : effectType(type), duration(duration), target(target)
{
	if (duration < 0) { // || target == nullptr) 		
		throw(WRONG_VALUE);
	}
}

enum BonusType Effect::Type()
{
	return this->effectType;
}

void Effect::ApplyTarget(CharacterBase * target)
{
	this->target = target;
}



// Malus

Malus::Malus(int duration, int physicalDamages, int magicalDamages, CharacterBase * target) : Effect(MALUS, duration, target), physicalDamages(physicalDamages), magicalDamages(magicalDamages)
{
	if (physicalDamages < 0 || magicalDamages < 0) throw(WRONG_VALUE);
}

Malus::Malus(Malus * malus) : Malus(malus->duration, malus->physicalDamages, malus->magicalDamages, malus->target) // Effect(malus->effectType, malus->duration, malus->target), physicalDamages(malus->physicalDamages), magicalDamages(malus->magicalDamages)
{
}


int Malus::ApplyEffect()
{
	return this->target->ApplyDamages(this->physicalDamages, this->magicalDamages);
}

Malus * Malus::GetMalusCopy()
{
	Malus * copy = new Malus(this);
	return copy;
}


// Bonus

Bonus::Bonus(int duration, int heal, int shield, bool stase, CharacterBase * target) : Effect(BONUS, duration, target), heal(heal), shield(shield), stase(stase)
{
}

Bonus::Bonus(Bonus * bonus) : Bonus(bonus->duration, bonus->heal, bonus->shield, bonus->stase, bonus->target)
{
}

Bonus::~Bonus()
{
	if (this->stase) {
		std::cout << this->target->GetName() << " gets out of stase" << std::endl;
		this->target->SetStase(false);
	}
}

int Bonus::ApplyEffect()
{
	return this->target->Regenerate(this->heal);
}


int Bonus::ApplyShield(int damages)
{
	 if (damages < 0) throw(WRONG_VALUE) ;
	 //int shieldSave = this->shield;
	 int shieldLeft = (this->shield - damages) < 0 ? 0 : this->shield - damages;
	 if (!shieldLeft) {
	 	damages -= this->shield;
	 } else {
	 	damages = 0;
	 }
	 this->shield = shieldLeft;
	 //return shieldSave - shieldLeft;
	 return damages;
	 //return this->shield;
}

int Bonus::GetShield()
{
	return this->shield;
}

bool Bonus::HasShield()
{
	return (this->shield > 0);
}

Bonus * Bonus::GetBonusCopy()
{
	Bonus * copy = new Bonus(this);
	return copy;
}

bool Bonus::HasStase()
{
	return this->stase;
}

