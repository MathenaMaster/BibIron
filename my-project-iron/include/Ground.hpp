


#ifndef GROUND_HPP
#define GROUND_HPP


#include "AffectsArray.hpp"

#include "Attack.hpp"
#include "Player.hpp"

#include "Tile.hpp"
class TileArray;

class Ground
{
	protected :
		int size;
		int roundNb;
		int playerTurn;
		int won;
		//int playerNb;
		Array<CharacterBase> * players;
		TileArray * ground0;
		
	public :
		Ground(int size);
		int GetX(CharacterBase *);
		int GetY(CharacterBase *);
		void CreateNewGround(int size);
		void AddPlayer(CharacterBase *);
		
		int GetSize() const;
		Array<CharacterBase> * GetPlayers() const;
		TileArray * GetGround0() const;
		
		void DrawGround() const;
		void DrawLine() const;
		void DrawTilesLine(int) const;
		
		bool HasPlayer(int, int);
		bool MovePlayer(CharacterBase *, int, int);
		
		void PrintWinners();
		void Round();
		int PlayerTurn();
		
		void RoundRegeneration();
		
		bool GetIfAttackInRange(CharacterBase *, Attack *, int, int);
};

#endif
