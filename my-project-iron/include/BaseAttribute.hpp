
#ifndef BASE_ATTRIBUTE_HPP
#define BASE_ATTRIBUTE_HPP

//#define WRONG_VALUE "No negative value allowed."

#include "IronDefines.hpp"

class BaseAttribute
{
  protected:
	int max;
	int actual;

  public:
	BaseAttribute(int);
	//int	Init(int); // init the attribute totally
	int SetMax(int); // no changes on actual
	int UpgradeMax(int);
	int GetActual() const;
	int Use(int); // return left content. 0 means empty or dead
	//int		TakeDamages(int);
	int Regenerate(int);
	int RegenerateTotally(); // actual = max
	bool IsEmpty() const;
	int AddTemporary(int);
	bool RoundReset();
};

class VitalAttribute : public BaseAttribute
{
  public:
	VitalAttribute(int);
	int TakeDamages(int);
};

class ManaAttribute : public BaseAttribute
{
  public:
	ManaAttribute(int);
	int UseMana(int);
};

class Deplacement : public BaseAttribute
{
	public :
		Deplacement(int);
		bool Move(int/*Ground *, int i, int j */);
};

class GeneralArmorSpecAttribute
{
	protected :
		int armor;
		//VitalAttribute * life;
	public :
		GeneralArmorSpecAttribute(int armor); //, VitalAttribute * life = nullptr);
		virtual int ApplyArmor(int);
};

class ArmorAttribute : public GeneralArmorSpecAttribute
{
  //protected :
  	//VitalAttribute * life;
  public:
	ArmorAttribute(int);
	//virtual int ApplyArmor(int);
	//int apply(int);
};

class MagicResAttribute : public GeneralArmorSpecAttribute
{
  //protected :
  	//VitalAttribute * life;
  public:
	MagicResAttribute(int);
	//virtual int ApplyArmor(int);
	//int apply(int);
};


class RegenSpecAttribute
{
  protected:
	int regeneration;


  public:
	RegenSpecAttribute(int);
	int GetRegeneration() const;
	virtual void ApplyRegeneration() = 0;
};

class LifeRegenAttribute : public RegenSpecAttribute
{
  protected:
  	VitalAttribute * life;
  public:
	LifeRegenAttribute(VitalAttribute *, int);
	void ApplyRegeneration();
};

class ManaRegenAttribute : public RegenSpecAttribute
{
  protected:
  	ManaAttribute * mana;
  public:
	ManaRegenAttribute(ManaAttribute *, int);
	void ApplyRegeneration();
};

class EnergyRegenAttribute : public RegenSpecAttribute
{
	protected:
		BaseAttribute * energy;
	public:
		EnergyRegenAttribute(BaseAttribute *, int);
		void ApplyRegeneration();
};

class LifeSpecAttribute
{
	protected :
		int physic;
		int magic;
		VitalAttribute * life;
		ManaAttribute * mana;
		BaseAttribute * energy;
		ArmorAttribute * armor;
		MagicResAttribute * magicResistance;
		LifeRegenAttribute * lifeRegeneration;
		ManaRegenAttribute * manaRegeneration;
		EnergyRegenAttribute * energyRegeneration;
	public :
		LifeSpecAttribute(int, int, VitalAttribute *, ManaAttribute *,BaseAttribute *, ArmorAttribute *, MagicResAttribute *, LifeRegenAttribute *, ManaRegenAttribute *, EnergyRegenAttribute *);
		int ApplyArmor(int, int);
		int ApplyDamages(int, int);
		int Heal(int);
		int Regenerate();
		
		VitalAttribute * GetLife();
		ManaAttribute * GetMana();
		BaseAttribute * GetEnergy();
		int GetPhysicalPower();
		int GetMagicalPower();
};




#endif