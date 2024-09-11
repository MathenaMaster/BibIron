
#include <iostream>

//#include "Player.hpp"
#include "Attack.hpp"

//template class Array<Effect>;
//template class Array<Attack>;

#include "Ground.hpp"


Attack::Attack(std::string name,CharacterBase* owner, CharacterBase * target, AttackType type, int manaCost, int energyCost, int roundConservation, int loads, int damages, int range, Bonus * bonus, Malus *malus) : name(name), owner(owner), target(target), attackType(type), manaCost(manaCost), energyCost(energyCost), roundConservation(roundConservation), loads(loads), damages(damages), range(range), bonus(bonus), malus(malus)
{
}

Attack::Attack(Attack * attack) : Attack(attack->GetName(), attack->GetOwner(), attack->GetTarget(), attack->Type(), attack->GetManaCost(), attack->GetEnergyCost(), attack->GetRoundConservation(), attack->GetLoads(), attack->GetDamages(), attack->GetRange(), attack->GetBonus(), attack->GetMalus())
{
}

Attack::~Attack()
{
}

void Attack::ApplyEffects()
{
	//if (this->bonus) {
		//this->bonus->ApplyEffect();
	//} if (this->malus)
	if (this->bonus) {
		//Effect * bonus = &this->bonus->GetBonusCopy();
		//this->owner->AddEffect
		this->owner->GetBenedictions()->AddAffect(this->bonus->GetBonusCopy());
	}
	if (this->malus) {
		this->target->GetCurses()->AddAffect(this->malus->GetMalusCopy());
	}
}


int Attack::UseLoad()
{
	if (this->loads) {
		return --this->loads;
	}
	return 0;
}

int Attack::UseRound()
{
	if (this->roundConservation) {
		return --this->roundConservation;
	}
	return 0;
}

const std::string Attack::GetName() const
{
	return this->name;
}

CharacterBase * Attack::GetOwner() const
{
	return this->owner;
}

CharacterBase * Attack::GetTarget() const
{
	return this->target;
}

AttackType Attack::Type() const
{
	return this->attackType;
}

int Attack::GetManaCost() const
{
	return this->manaCost;
}

int Attack::GetEnergyCost() const
{
	return this->energyCost;
}

int Attack::GetRoundConservation() const
{
	return this->roundConservation;
}

int Attack::GetLoads() const
{
	return this->loads;
}

int Attack::GetDamages() const
{
	return this->damages;
}

int Attack::GetRange() const
{
	return this->range;
}

int Attack::GetSize() const
{
	return 0;
}

Bonus * Attack::GetBonus() const
{
	return this->bonus;
}

Malus * Attack::GetMalus() const
{
	return this->malus;
}

int Attack::ApplyDamages()
{
	if (this->target->GetStased()) {
		std::cout << target->GetName() << " is in stase" << std::endl;
		return 0;
	}
	this->ApplyEffects();
	if (this->attackType == PHYSIC) {
		return this->target->ApplyDamages(this->damages + this->owner->GetPhysicalPower(), 0);
	} else if (this->attackType == MAGIC) {
		return this->target->ApplyDamages(0, this->damages + this->owner->GetMagicalPower());
	} else {
		return 0;
	}
}

int Attack::UseAttack(CharacterBase * owner, CharacterBase * target)
{
	//this->owner = owner;
	//this->target = target;
	return this->ApplyDamages();
}

/*
Attack * Attack::GetCopy() const
{
	return new Attack(this);
}
*/

int Attack::AskFor(Ground * ground, int i, int j)
{
	std::cout << "Enter a target index in the range of your spell" << std::endl;
	Array<CharacterBase> * presents = ground->GetGround0()->CheckRangedPresence(this->owner->GetTeam(), i, j, this->GetRange());
	if (presents->AffectCount() == 0) {
		std::cout << "No target in the range of your spell" << std::endl;
		return 0;
	}
	std::cout << "Enter a target number or 0:" << std::endl;
	for (int idx = 1; idx <= presents->AffectCount(); ++idx) {
		std::cout << std::to_string(idx)  << ": " << presents->GetIdx(idx - 1)->GetName() << std::endl;
	}
	//int target = -1;
	// target = GetInt();
	int target = GetInRange(0, presents->AffectCount());
	if (target <= 0) {
		return 0;
	}
	this->target = presents->GetIdx(target - 1);
	//return this->ApplyDamages();
	if (owner->GetLife() > 0) {
		return this->ApplyAttack(ground, ground->GetX(this->owner), ground->GetY(this->owner));
	} else {
		return this->ApplyDamages();
	}
}

// TargetedAttack

TargetedAttack::TargetedAttack(TargetedAttack * tAttack) : Attack(tAttack)
{
}


TargetedAttack::TargetedAttack(Attack * tAttack) : Attack(tAttack)
{
}

TargetedAttack::TargetedAttack(std::string name, CharacterBase * owner, CharacterBase * target, AttackType type, int manaCost, int energyCost, int roundConservation, int loads, int damages, int range, Bonus * bonus, Malus *malus): Attack(name, owner, target, type, manaCost, energyCost, roundConservation, loads, damages, range, bonus, malus)
{
}



TargetedAttack::~TargetedAttack()
{
}

Attack * TargetedAttack::GetCopy()
{
	return new TargetedAttack(this);
}

int TargetedAttack::ApplyAttack(Ground * ground, int i, int j)
{
	//int size = ground->GetSize();
	
	return ground->GetGround0()->ApplyTargetedAttack(i, j, this->owner, this);
	//return 0;
}


// ZoneAttack

ZoneAttack::ZoneAttack(Attack * attack, int size) : Attack(attack), size(size)
{
}

ZoneAttack::ZoneAttack(ZoneAttack * zoneAttack) : ZoneAttack(zoneAttack, zoneAttack->GetSize())
{
}

ZoneAttack::ZoneAttack(std::string name, CharacterBase * owner, CharacterBase * target, AttackType type, int manaCost, int energyCost, int roundConservation, int loads, int damages, int range, Bonus * bonus, Malus *malus, int size): Attack(name, owner, target, type, manaCost, energyCost, roundConservation, loads, damages, range, bonus, malus), size(size)
{
}



ZoneAttack::~ZoneAttack()
{
}

int ZoneAttack::GetSize() const
{
	return this->size;
}

Attack * ZoneAttack::GetCopy()
{
	return new ZoneAttack(this);
}

int ZoneAttack::ApplyAttack(Ground  * ground, int i, int j)
{
	enum ZoneLaunchType type = this->TargetOrThrow();
	if (type == TARGET) {
		return ground->GetGround0()->ApplyZoneAttack(i, j, this->owner, this);
	} else if (type == THROW) {
		int x = -1, y = -1;
		bool bounded = false;
		while (!bounded) {
			std::cout << "Enter a x coordinate: ";
			//x = GetInt();
			x = GetInRange(0, ground->GetSize() - 1);
			std::cout << "Enter a y coordinate";
			//y = GetInt();
			y = GetInRange(0, ground->GetSize() - 1);
			bounded = ground->GetGround0()->CheckBounds(x, y);
			if (!bounded) {
				std::cout << "Coordinates do not fit the ground size" << std::endl;
			} else if (!ground->GetIfAttackInRange(this->owner, this, x, y)/* not in player range */) {
				std::cout << "You do not have enougth range" << std:: endl;
				//bounded = false;
				break;
			}
		}
		ground->GetGround0()->ApplyZoneAttack(x, y, this->owner, this);
	} else return 0;
	//return ground->GetGround0()->ApplyZoneAttack(i, j, this->owner, this);
	return 0;
}

enum ZoneLaunchType ZoneAttack::TargetOrThrow()
{
	std::string command("");
	std::cout << "Commands are: target, throw, back" << std::endl;
	while (!command.compare("")) {
		command = GetString();
		if (!command.compare("target")) {
			return TARGET;
		} else if (!command.compare("throw")) {				return THROW;
		} else if (!command.compare("back")) {
			return BACK;
		} else {
			std::cout << "Command unknown" << std::endl;
			command = "";
		}
	}
	return BACK; // INUTILE NORMALEMENT
}

