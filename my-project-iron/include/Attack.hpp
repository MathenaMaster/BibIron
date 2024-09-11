

#ifndef ATTACK_HPP
#define ATTACK_HPP

#include <string>

#include "Effects.hpp"
#include "AffectsArray.hpp"
//#include "Ground.hpp"
//#include "Player.hpp"

class Ground;
class Player;


enum AttackType
{
	PHYSIC,
	MAGIC
};

enum ZoneLaunchType
{
	TARGET,
	THROW,
	BACK
};

class Attack
{
	protected :
		//Effect * bonus;
		//Effect * malus;
		std::string name;
		CharacterBase * owner;
		CharacterBase * target;
		AttackType attackType;
		int manaCost;
		int energyCost;
		
		int roundConservation;
		int loads;
		int damages;
		int range;
		Bonus * bonus;
		Malus * malus;
		
	public :
		Attack(std::string name, CharacterBase* owner, CharacterBase * target, AttackType type, int manaCost, int energyCost, int roundConservation, int loads, int damages, int range, Bonus * bonus = nullptr, Malus *malus = nullptr);
		Attack(Attack *);
		virtual ~Attack();
		
		
		void ApplyEffects();
		int UseLoad();
		int UseRound();
		
		const std::string GetName() const;
		CharacterBase * GetOwner() const;
		CharacterBase * GetTarget() const;
		
		AttackType Type() const;
		int GetManaCost() const;
		int GetEnergyCost() const;
		
		int GetRoundConservation() const;
		int GetLoads() const;
		int GetDamages() const;
		int GetRange() const;
		int GetSize() const;
		
		Bonus * GetBonus() const;
		Malus * GetMalus() const;
		
		
		virtual int ApplyAttack(Ground*, int i, int j) = 0; // return all damages done
		int ApplyDamages();
		int UseAttack(CharacterBase *, CharacterBase *);
		
		
		
		virtual Attack * GetCopy() = 0;
		virtual int AskFor(Ground *, int, int);
};

class TargetedAttack : public Attack
{
	public :
		TargetedAttack(Attack *);
		TargetedAttack(TargetedAttack *);
		TargetedAttack(std::string, CharacterBase *, CharacterBase *, AttackType, int, int, int, int, int, int, Bonus *, Malus *);
		virtual ~TargetedAttack();
		int ApplyAttack(Ground*, int i, int j); // return all damages done to the player on the position
		
		Attack * GetCopy();
};

class ZoneAttack : public Attack
{
	protected :
		int size;
	public :
		ZoneAttack(Attack *, int);
		ZoneAttack(ZoneAttack *);
		ZoneAttack(std::string, CharacterBase *, CharacterBase *, AttackType, int, int, int, int, int, int, Bonus *, Malus *, int);
		virtual ~ZoneAttack();
		int ApplyAttack(Ground*, int i, int j); // return all damages done on all players hitten
		int GetSize() const;
		Attack * GetCopy();
		enum ZoneLaunchType TargetOrThrow();
};

//#include "AffectsArray.hpp"

//template class Array<Effect>;
//template class Array<Attack>;


#endif

