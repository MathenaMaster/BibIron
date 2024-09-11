

#include <iostream>
#include <string>


#include "IronDefines.hpp"
#include "AffectsArray.hpp"
#include "Player.hpp"

CharacterBase::CharacterBase(std::string & name, LifeSpecAttribute * life, /* LifeRegenAttribute * lifeRegen, ManaRegenAttribute * manaRegen, */ Deplacement * deplacement, int baseRange, bool stased) : team(0), name(name), baseRange(baseRange), stased(stased), characterLife(life), deplacement(deplacement), benedictions(new Array<Bonus>(0)), curses(new Array<Malus>(0)), loads(new Array<Attack>(0)), personalAttacks(new Array<Attack>(5))
{
}

int CharacterBase::GetLife()
{
	return this->characterLife->GetLife()->GetActual();
}

int CharacterBase::GetBaseRange() const
{
	return this->baseRange;
}

bool CharacterBase::GetStased() const
{
	return this->stased;
}

void CharacterBase::SetStase(bool stased)
{
	this->stased = stased;
}

int CharacterBase::GetPhysicalPower()
{
	return this->characterLife->GetPhysicalPower();
}

int CharacterBase::GetMagicalPower()
{
	return this->characterLife->GetMagicalPower();
}

int CharacterBase::ApplyDamages(int physicalDamages, int magicalDamages)
{
	return this->characterLife->ApplyDamages(this->UseShields(physicalDamages), this->UseShields(magicalDamages));
}

int CharacterBase::ApplyAttack(Attack * attack, CharacterBase * target)
{
	//this->ApplyDamages(attack->)
	return attack->UseAttack(this, target);
}

int CharacterBase::Regenerate(int regen)
{
	//return this->characterLife->GetLife()->Regenerate(regen);
	return this->characterLife->Heal(regen);
}

int CharacterBase::UseShields(int damages)
{
	//Bonus *toApply;
	if (damages <= 0) {
		return 0;
	}
	Array<Bonus> * benedictions = this->GetBenedictions();
	int count = benedictions->AffectCount();
	for (int i = 0; i < count; ++i) {
		//Bonus * toApply = benedictions->GetAffects()[i];
		Bonus * toApply = benedictions->GetIdx(i);
		if (toApply->HasShield()) {
		 	if ((damages = toApply->ApplyShield(damages)) == 0) {
		 		break;
		 	}
		}
	}
	return damages; // return 0 if no more damages to apply to the player. Else apply damages left next
}

int CharacterBase::GetDeplacementLeft()
{
	return this->deplacement->GetActual();
}

int CharacterBase::GetTeam()
{
	return this->team;
}

const std::string CharacterBase::GetName() const
{
	return this->name;
}

Array<Bonus>  * CharacterBase::GetBenedictions()
{
	return this->benedictions;
}

Array<Malus>  * CharacterBase::GetCurses()
{
	return this->curses;
}

Array<Attack>  * CharacterBase::GetLoads()
{
	return this->loads;
}

Array<Attack> * CharacterBase::GetPersonalAttacks()
{
	return this->personalAttacks;
}

int CharacterBase::AskForWith(Array<Attack>* attacks, Ground * ground, int i, int j, bool loadOrPerso)
{
	if (attacks->AffectCount() == 0) {
		std::cout << "No attack to use" <<std::endl;
		return 0;
	}
	std::cout << "Enter an attack to use or 0:" <<std::endl;
	for (int idx = 1; idx <= attacks->AffectCount(); ++idx) {
		std::cout << std::to_string(idx)  << ": " << attacks->GetIdx(idx - 1)->GetName() << std::endl;
	}
	//int target = -1;
	//target = GetInt();
	int target = GetInRange(0, attacks->AffectCount());
	if (target <= 0) {
		return 0;
	}
	Attack * loadToUse = attacks->GetIdx(target - 1);
	if (this->characterLife->GetEnergy()->GetActual() >= loadToUse->GetEnergyCost() && (loadOrPerso || this->characterLife->GetMana()->GetActual() >= loadToUse->GetManaCost())) {
		this->characterLife->GetEnergy()->Use(loadToUse->GetEnergyCost());
		if (!loadOrPerso) {
			this->characterLife->GetMana()->UseMana(loadToUse->GetManaCost());
		}
		return loadToUse->AskFor(ground, i, j);
	}
	return 0;
}

int CharacterBase::AskForLoads(Ground * ground, int i, int j)
{
	return this->AskForWith(this->loads, ground, i, j, false);
}

int CharacterBase::AskForPersonal(Ground * ground, int i, int j)
{
	return this->AskForWith(this->personalAttacks, ground, i, j, true);
}

int CharacterBase::AskForBaseAttack(Ground * ground)
{
	int selected = 0;
	
	if (this->characterLife->GetEnergy()->GetActual() < BASE_ATTACK_ENERGY) {
		std::cout << "You have " << this->characterLife->GetEnergy()->GetActual() << " energy left and you need " << BASE_ATTACK_ENERGY << " to attack" << std::endl;
		return 0;
	}
	Array<CharacterBase> * inRange = ground->GetGround0()->CheckRangedPresence(this->GetTeam(), /*i, j,*/ ground->GetX(this), ground->GetY(this), this->GetBaseRange());
	// continue here
	if (inRange->AffectCount() > 0) {
		std::cout << "Select a player displayed in your range. 0 to cancel" << std::endl;
		
		for (int playerIdx = 0; playerIdx < inRange->AffectCount(); ++playerIdx) {
			std::cout << playerIdx + 1 << ": " << inRange->GetIdx(playerIdx)->GetName() << std::endl;
		}
		//selected = GetInt();
		selected = GetInRange(0, inRange->AffectCount());
		if (selected <= 0) {
			return 0;
		}
		this->characterLife->GetEnergy()->Use(BASE_ATTACK_ENERGY);
		return inRange->GetIdx(selected - 1)->ApplyDamages(this->GetPhysicalPower(), 0);
	} else {
		std::cout << "Ther is no player in your range" << std::endl;
	}
	return 0;
}


ActionEntry CharacterBase::AskAction()
{
	std::cout << "You can ask to 'save', 'move', 'attack', 'base' attack, or use a remaining attack 'load'" << std::endl;
	std::cout << "Write 'end' to close your turn" << std::endl;
	std::string entry("");
	while (entry.compare("end") && entry.compare("move") && entry.compare("attack") && entry.compare("load") && entry.compare("save")) {
		entry = GetString();
		tolower(entry);
	}
	if (!entry.compare("end")) {
		return END;
	} else if (!entry.compare("move")) {
		return MOVE;
	} else if (!entry.compare("base")) {
		return BASE;
	} else if (!entry.compare("attack")) {
		return ATTACK;
	} else if (!entry.compare("load")) {
		return LOAD;
	} else if (!entry.compare("save")) {
		// code save action
		return SAVE;
	}
	return END;
}



int CharacterBase::AskForMove(Ground * ground)
{
	std::cout << "Do you want to move? [yes/no]: ";
	if (this->GetDeplacementLeft() <= 0) {
		std::cout << "You can't move anymore" << std::endl;
		return 0;
	}
	std::string answer("");
	bool yes = false, no = false;
	while (!(yes = (answer == "yes" || answer == "y")) && !(no = (answer == "no" || answer == "n"))) {
		answer = GetString();
		//answer = tolower(answer);
		tolower(answer);
	}
	if (yes) {
		std::cout << "Enter values between 1 and " << ground->GetSize() << std::endl;
		int x = -1, y = -1;
		/*while (x <= -1 || x > ground->GetSize()) {
			std::cout << "Enter a new x: ";
			x = GetInt() - 1;
		}*/
		x = GetInRange(1, ground->GetSize()) - 1;
		y = GetInRange(1, ground->GetSize()) - 1;
		/*while (y <= -1 || y > ground->GetSize()) {
			std::cout << "Enter a new y: ";
			y = GetInt() - 1;
		}*/
		if (ground->HasPlayer(x, y)) {
			std::cout << "A player is alredy present on the tile" << std::endl;
			return 0;
		}
		//int maxAbs = x >= y ? abs(x) : abs(y);
		int diffX = (x <= ground->GetX(this) ? ground->GetX(this) - x : x - ground->GetX(this));
		int diffY = (y <= ground->GetY(this) ? ground->GetY(this) - y : y - ground->GetY(this));
		int maxDiff = (diffX >= diffY ? diffX : diffY);
		if (maxDiff <= this->GetDeplacementLeft()) {
			int retired = this->deplacement->Move(maxDiff);
			std::cout << "You used " << retired << " deplacement points" << std::endl;
			ground->MovePlayer(this, x, y);
			return retired;
		} else {
			std::cout << "You can't move that far. Try somewhere closer." << std::endl;
			std::cout << "You have still " << this->GetDeplacementLeft() << " deplacement points left ";
			return 0;
		}
	}
	return 0;
}

int CharacterBase::AskForTurn(Ground * ground)
{
	int totalDmg = 0;
	std::cout << "This is the turn of the player: " << this->name << std::endl;
	ActionEntry aEntry = END;
	do {
		aEntry = this->AskAction();
		if (aEntry == MOVE) {
			this->AskForMove(ground);
		} else if (aEntry == BASE) {
			totalDmg += this->AskForBaseAttack(ground);
		} else if (aEntry == ATTACK) {
			totalDmg += this->AskForPersonal(ground, ground->GetX(this), ground->GetY(this));
		} else if(aEntry == LOAD) {
			totalDmg += this->AskForLoads(ground, ground->GetX(this), ground->GetY(this));
		} else if (aEntry == END) {
			std::cout << "End of the turn of player " << this->name << std::endl;
		} else if (aEntry == SAVE) {
			// save action to code
		}
	} while (aEntry != END);
	return 0;
}

void CharacterBase::EndTurnRegen()
{
	this->characterLife->Regenerate();
}
