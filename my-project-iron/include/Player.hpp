
//#include "Effects.hpp"
//#include "Attack.hpp"


#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "Effects.hpp"
#include "Attack.hpp"
#include "AffectsArray.hpp"
#include "BaseAttribute.hpp"
#include "Ground.hpp"
//#include "Tile.hpp"
#include "IronDefines.hpp"

//class Effect;
//class Attack;

enum ActionEntry {
	END,
	MOVE,
	BASE,
	ATTACK,
	LOAD,
	SAVE
};



class CharacterBase
{
	protected:
		int 								team;
		std::string				  name;
		int								baseRange;
		bool							stased;

		LifeSpecAttribute	   * characterLife;
	
	//LifeRegenAttribute     * lifeRegen;
	//ManaRegenAttribute * manaRegen; // mana regen
	Deplacement 			  * deplacement;
	
	Array<Bonus>    *benedictions;
	Array<Malus>	 *curses;
	
	Array<Attack>    *loads;
	Array<Attack>    *personalAttacks;
	
	public:
		CharacterBase(std::string &, LifeSpecAttribute * /* , LifeRegenAttribute *, ManaRegenAttribute * */, Deplacement *, int, bool stased = false);
		
		int GetLife();
		int GetBaseRange() const;
		bool GetStased() const;
		void SetStase(bool);
		int GetPhysicalPower();
		int GetMagicalPower();
		int ApplyDamages(int, int);
		int ApplyAttack(Attack *, CharacterBase *);
		int Regenerate(int);
		//virtualint TakeDamages(
		int UseShields(int); // retourne les dommages restants a appliquer au joueur
		
		int GetDeplacementLeft();
		
		int GetTeam();
		const std::string GetName() const;
		
		Array<Bonus> * GetBenedictions();
		Array<Malus>  * GetCurses();
		
		Array<Attack> * GetLoads();
		Array<Attack> * GetPersonalAttacks();
		
		int AskForWith(Array<Attack>*, Ground *, int, int, bool);
		int AskForLoads(Ground *, int, int);
		int AskForPersonal(Ground *, int, int);
		int AskForBaseAttack(Ground *);
		
		ActionEntry AskAction();
		
		int AskForMove(Ground *);
		int AskForTurn(Ground *);
		
		void EndTurnRegen();
		
};



#endif
