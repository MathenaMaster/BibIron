
//#include "Player.hpp"

#ifndef EFFECTS_HPP
#define EFFECTS_HPP

//#include "Player.hpp"
class CharacterBase;
class Effect;

//#define MALUS (false)
//#define BONUS (true)


enum BonusType
{
	MALUS,
	BONUS
};


class Effect
{
	 protected :
	 	BonusType effectType;
	 	int duration;
	 	CharacterBase * target;
		//int physicalDamages;
		//int magicalDamages;
		
	public :
		Effect(BonusType type, int duration, CharacterBase * target = nullptr);
		//Effect(int, CharacterBase *);
		//virtual ~Effect() {};
		enum BonusType Type();
		virtual int ApplyEffect() = 0;
		void ApplyTarget(CharacterBase *);
};

class Malus : public Effect
{
	protected :
		int physicalDamages;
		int magicalDamages;
	
	public :
		Malus(int, int, int, CharacterBase *);
		Malus(Malus *);
		virtual int ApplyEffect();
		Malus * GetMalusCopy();
		//Malus * operator=(Malus *);
};

class Bonus : public Effect
{
	protected :
		int heal;
		int shield;
		bool stase;
	
	public :
		Bonus(int, int, int, bool, CharacterBase *);
		Bonus(Bonus *);
		~Bonus();
		virtual int ApplyEffect();
		int ApplyShield(int); // renvoie les dommages restants
		int GetShield();
		bool HasShield();
		bool HasStase();
		Bonus * GetBonusCopy();
		//Bonus * operator=(Bonus *);
};


#endif