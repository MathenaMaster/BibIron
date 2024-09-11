

#ifndef TILE_HPP
#define TILE_HPP


#include "Attack.hpp"
#include "Player.hpp"

#include "AffectsArray.hpp"

//class Attack;
//class CharacterBase;


class Tile
{
	protected :
		CharacterBase	*	tilePlayer;
		
	public :
		Tile();
		~Tile();
		bool			PrintTile();
		bool			CheckPlayer(CharacterBase *);
		bool			AddPlayer(CharacterBase *);
		CharacterBase* RetirePlayer();
		CharacterBase * GetTilePlayer();
		int			ApplyAttack(CharacterBase *, Attack *);
		bool 		MovePlayer(Tile *);
};

class TileArray
{
	protected :
		int				size;
		Tile		***	tileArray;
	public :
		TileArray(int);
		~TileArray();
		Array<CharacterBase> * CheckRangedPresence(int team, int i, int j, int range); // Verifie la presence de joueurs ennemis a portee, et renvoie la liste
		
		int ApplyTargetedAttack(int i, int j, CharacterBase * owner, Attack * attack);
		
		int ApplyZoneAttack(int i, int j, CharacterBase * owner, Attack * zoneAttack);

		Tile * GetTile(int, int) const;
		int GetSize() const;
		bool CheckSize(int) const;
		bool CheckBounds(int, int) const;

};


#endif


