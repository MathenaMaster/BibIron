
#include <iostream>
#include <iomanip>

#include "IronDefines.hpp"
#include "Tile.hpp"

// Tile

Tile::Tile() : tilePlayer(nullptr)
{
}

Tile::~Tile()
{
}

bool Tile::PrintTile()
{
	int team = 0;
	
	if (this->tilePlayer) {
		team = this->tilePlayer->GetTeam();
	}
	if (team) {
		std::cout << "|" << std::setfill('0') << std::setw(3) << team << "|";
	} else {
		std::cout << "|" << "   " << "|";
	}
	return team; // peut etre renvoyer la reussite ou echec exceptions throw catch
}


bool Tile::CheckPlayer(CharacterBase * test)
{
	return this->tilePlayer == test;
}


bool Tile::AddPlayer(CharacterBase * player)
{
	if (this->tilePlayer == nullptr) {
		this->tilePlayer = player;
		return true;
	} else return false;
}

CharacterBase * Tile::RetirePlayer()
{
	CharacterBase * player = this->tilePlayer;
	if (player == nullptr) {
		return nullptr;
	} else {
		this->tilePlayer = nullptr;
		return player;
	}
}

CharacterBase * Tile::GetTilePlayer()
{
	return this->tilePlayer;
}

bool Tile::MovePlayer(Tile * tile)
{
	if (tile->AddPlayer(this->tilePlayer)) {
		return (this->RetirePlayer() != nullptr);
	}
	return false;
}


int Tile::ApplyAttack(CharacterBase * owner, Attack * attack)
{
	//this->tilePlayer->ApplyDamages(attack)
	if (this->tilePlayer && owner->GetTeam() != this->tilePlayer->GetTeam()) {
		return attack->UseAttack(owner, this->tilePlayer);
	}
	return 0;
}

		// TileArray

TileArray::TileArray(int size): size(size), tileArray(nullptr)
{
	if (this->size <= 0) throw(WRONG_VALUE);
	this->tileArray = new Tile**;
	for (int i = 0; i < size; ++i) {
		this->tileArray[i] = new Tile*[size];
		for (int j= 0; j < size; ++j) {
			this->tileArray[i][j] = new Tile;
		}
	}
}

TileArray::~TileArray()
{
	if (this->tileArray) {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				delete this->tileArray[i][j];
			}
			delete tileArray[i];
		}
		delete this->tileArray;
	}
}

Tile * TileArray::GetTile(int i, int j) const
{
	if (this->CheckBounds(i, j)) {
		return this->tileArray[i][j];
	}
	return nullptr;
}

int TileArray::GetSize() const
{
	return this->size;
}

bool TileArray::CheckSize(int idx) const
{
	return (idx >= 0 && idx < this->size);
}


bool TileArray::CheckBounds(int i, int j) const
{
	return (this->CheckSize(i) && this->CheckSize(j));
}


Array<CharacterBase> * TileArray::CheckRangedPresence(int team, int i, int j, int range)
{
	//if (i >= this->size || j >= this->size || i < 0 || j < 0)
	if (!this->CheckBounds(i, j)) {
		return nullptr;
	}
	
	int xBegin = (i - range < 0) ? 0 : i - range;
	int xEnd = (i + range >= this->size) ? this->size - 1 : i + range;
	
	int yBegin = (j - range < 0) ? 0 : j - range;
	int yEnd = (j + range >= this->size) ? this->size - 1 : j + range;
	
	Array<CharacterBase> * presents = new Array<CharacterBase>(0);
	
	for (int x = xBegin; x <= xEnd; ++x) {
		for (int y = yBegin; y <= yEnd; ++y) {
			CharacterBase * tilePlayer = this->tileArray[x][y]->GetTilePlayer();
			if (tilePlayer != nullptr && tilePlayer->GetTeam() != team) {
				presents->AddAffect(tilePlayer);
			}
		}
	}
	if (!presents->AffectCount()) {
		delete presents;
		return nullptr;
	}
	return presents;
}


int TileArray::ApplyTargetedAttack(int i, int j, CharacterBase * owner, Attack * attack)
{
	/*CharacterBase * tilePlayer = this->tileArray[i][j]->GetTilePlayer();
	if (tilePlayer != nullptr) {
		return attack->UseAttack(owner, target);
	}*/
	//int size = this->GetSize();
	//if (i < size && j < size && i >= 0 && j >= 0) 
	if (this->CheckBounds(i, j)) {
		return this->tileArray[i][j]->ApplyAttack(owner, attack);
	}
	return 0;
}


int TileArray::ApplyZoneAttack(int i, int j, CharacterBase * owner, Attack * zoneAttack)
{
	if (!this->CheckBounds(i, j)) {
		return 0;
	}
	Array<CharacterBase> * presents = this->CheckRangedPresence(owner->GetTeam(), i, j, zoneAttack->GetSize());
	CharacterBase ** playerArray = presents->GetAffects();
	if (playerArray == nullptr) return 0;
	int totalDamages = 0;
	for (int playerIdx = 0; playerArray[playerIdx]; ++playerIdx) {
		totalDamages += zoneAttack->UseAttack(owner, playerArray[playerIdx]);
	}
	return totalDamages;
}


