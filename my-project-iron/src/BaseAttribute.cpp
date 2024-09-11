#include <exception>
#include "BaseAttribute.hpp"

// BaseAttribute

BaseAttribute::BaseAttribute(int max) : max(max), actual(max)
{
	if (max < 0)
		throw(WRONG_VALUE);
}

int BaseAttribute::SetMax(int max)
{
	//if (max > 0) this->max = max;
	return (this->max = (max > 0 ? max : 0));
}

int BaseAttribute::UpgradeMax(int upgrade)
{
	return (this->max += (upgrade > 0 ? upgrade : 0));
}

int BaseAttribute::GetActual() const
{
	return this->actual;
}

int BaseAttribute::Use(int retired)
{
	int toRetire = 0;
	if (retired > 0)
	{
		toRetire = ((this->actual - retired < 0) ? this->actual : retired);
		this->actual -= toRetire;
	}
	//return this->actual;
	return toRetire;
}

/*class VitalAttribute : public BaseAttribute
{
	public:
		VitalAttribute();
		TakeDommages(int);
};*/

int BaseAttribute::Regenerate(int regeneration)
{
	if (regeneration > 0)
	{
		if (this->actual + regeneration <= this->max)
		{
			this->actual += regeneration;
			return regeneration;
		}
		else
		{
			int regenerated = this->max - this->actual;
			this->actual = this->max;
			return regenerated;
		}
	}
	else
		return 0;
}

int BaseAttribute::RegenerateTotally()
{
	int regenerated = this->max - this->actual;
	this->actual = this->max;
	return regenerated;
}

bool BaseAttribute::IsEmpty() const
{
	return (this->actual > 0 ? false : true);
}

int BaseAttribute::AddTemporary(int add)
{
	return this->actual += add;
}

bool BaseAttribute::RoundReset()
{
	return this->actual = this->max;
}

// VitalAttribute

VitalAttribute::VitalAttribute(int life) : BaseAttribute(life)
{
	if (life < 0)
		throw(WRONG_VALUE);
}

int VitalAttribute::TakeDamages(int damages)
{
	return this->Use(damages);
}

// ManaAttribute

ManaAttribute::ManaAttribute(int mana) : BaseAttribute(mana)
{
	if (mana < 0)
		throw(WRONG_VALUE);
}

int ManaAttribute::UseMana(int usedMana)
{
	if (this->actual >= usedMana)
	{
		//return this->Use(usedMana);
		this->Use(usedMana);
		return usedMana;
	}
	return 0;
}

// Deplacement

Deplacement::Deplacement(int deplacement) : BaseAttribute(deplacement)
{
}

bool Deplacement::Move(int maxDist/*Ground *ground, int i, int j */)
{
	//if (ground->)
	if (maxDist <= this->actual) {
		this->Use(maxDist);
		return true;
	}
	return false;
}

// GeneralArmorSpecAttribute

GeneralArmorSpecAttribute::GeneralArmorSpecAttribute(int armor) : armor(armor)
{
	if (armor < 0)
		throw(WRONG_VALUE);
}


int GeneralArmorSpecAttribute::ApplyArmor(int damages)
{
	if (damages <= 0)
		return 0;
	int filteredDamages = damages * this->armor / 100;
	int finalDamages = damages - filteredDamages;
	//return this->life->TakeDamages(finalDamages);
	return finalDamages;
}

// ArmorAttribute

ArmorAttribute::ArmorAttribute(int armor) : GeneralArmorSpecAttribute(armor)
{
}

/*
int ArmorAttribute::ApplyArmor(int damages)
{
	if (damages <= 0)
		return 0;
	int filteredDamages = damages * this->armor / 100;
	int finalDamages = damages - filteredDamages;
	//return this->life->TakeDamages(finalDamages);
	return finalDamages;
}
*/

// MagicResAttribute

MagicResAttribute::MagicResAttribute(int armor) : GeneralArmorSpecAttribute(armor)
{
}

/*
int MagicResAttribute::ApplyArmor(int damages)
{
	if (damages <= 0)
		return 0;
	int filteredDamages = damages * this->armor / 100;
	int finalDamages = damages - filteredDamages;
	//return this->life->TakeDamages(finalDamages);
	return finalDamages;
}
*/

 // RegenSpecAttribute
 
 int RegenSpecAttribute::GetRegeneration() const
 {
 	return this->regeneration;
 }

// LifeSpecAttribute

LifeSpecAttribute::LifeSpecAttribute(int physic, int magic, VitalAttribute *life, ManaAttribute * mana, BaseAttribute * energy, ArmorAttribute *armor, MagicResAttribute *mr, LifeRegenAttribute * lifeRegen, ManaRegenAttribute * manaRegen, EnergyRegenAttribute * energyRegen) : physic(physic), magic(magic), life(life), mana(mana), energy(energy), armor(armor), magicResistance(mr), lifeRegeneration(lifeRegen), manaRegeneration(manaRegen), energyRegeneration(energyRegen)
{
}

int LifeSpecAttribute::ApplyArmor(int physicalDamages, int magicalDamages)
{
	int finalDamages = this->armor->ApplyArmor(physicalDamages);
	finalDamages += this->magicResistance->ApplyArmor(magicalDamages);
	return finalDamages; //this->life->TakeDamages(finalDamages);
}

int LifeSpecAttribute::ApplyDamages(int physical, int magical)
{
	if (physical < 0 || magical < 0)
		throw(WRONG_VALUE);
	// int totalDamages = this->armor->ApplyArmor(physical);
	// totalDamages += this->magicResistance->ApplyArmor(magical);
	int totalDamages = this->ApplyArmor(physical, magical);
	return this->life->TakeDamages(totalDamages);
}

int LifeSpecAttribute::Regenerate()
{
	//this->life->Regenerate(this->lifeRegeneration->GetRegeneration());
	this->lifeRegeneration->ApplyRegeneration();
	// this->energy->Regenerate(this->energyRegeneration->GetRegeneration());
	// continue
	this->manaRegeneration->ApplyRegeneration();
	this->energyRegeneration->ApplyRegeneration();
	return 0;
}

int LifeSpecAttribute::Heal(int heal)
{
	return this->life->Regenerate(heal);
}

VitalAttribute *LifeSpecAttribute::GetLife()
{
	return this->life;
}

ManaAttribute * LifeSpecAttribute::GetMana()
{
	return this->mana;
}

BaseAttribute * LifeSpecAttribute::GetEnergy()
{
	return this->energy;
}

int LifeSpecAttribute::GetPhysicalPower()
{
	return this->physic;
}

int LifeSpecAttribute::GetMagicalPower()
{
	return this->magic;
}

// RegenSpecAttribute

RegenSpecAttribute::RegenSpecAttribute(int regeneration) : regeneration(regeneration)
{
	if (regeneration < 0)
		throw(WRONG_VALUE);
}

/*
int RegenSpecAttribute::ApplyRegeneration(int regeneration)
{
}
*/

// LifeRegenAttribute

LifeRegenAttribute::LifeRegenAttribute(VitalAttribute *life, int regeneration) : RegenSpecAttribute(regeneration), life(life)
{
}

void LifeRegenAttribute::ApplyRegeneration()
{
	this->life->Regenerate(this->regeneration);
}

ManaRegenAttribute::ManaRegenAttribute(ManaAttribute *mana, int regeneration) : RegenSpecAttribute(regeneration), mana(mana)
{
}

void ManaRegenAttribute::ApplyRegeneration()
{
	this->mana->Regenerate(this->regeneration);
}

// EnergyRegenAttribute


EnergyRegenAttribute::EnergyRegenAttribute(BaseAttribute * energy, int regeneration) : RegenSpecAttribute(regeneration), energy(energy)
{
}


void EnergyRegenAttribute::ApplyRegeneration()
{
	this->energy->Regenerate(this->regeneration);
}
