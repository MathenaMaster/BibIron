
#include <iostream>
#include <exception>

#include "Ground.hpp"

Ground::Ground(int size) : size(size), roundNb(0), playerTurn(0), won(0), players(nullptr), ground0(new TileArray(size))
{
}

void Ground::CreateNewGround(int size)
{
	this->size = size;
	this->roundNb = 0;
	this->playerTurn = 0;
	this->won = 0;
	delete this->ground0;
	this->ground0 = new TileArray(size);
	//this->players = nullptr;
}

int Ground::GetX(CharacterBase * player)
{
	//int playerIdx = -1;
	for (int i = 0; i < this->size; ++i) {
		for (int j = 0; j < this->size; ++j) {
			if (this->ground0->GetTile(i, j)->GetTilePlayer() == player) {
				return i;
			}
		}
	}
	return -1;
}

int Ground::GetY(CharacterBase * player)
{
	for (int i = 0; i < this->size; ++i) {
		for (int j = 0; j < this->size; ++j) {
			if (this->ground0->GetTile(i, j)->GetTilePlayer() == player) {
				return j;
			}
		}
	}
	return -1;
}

void Ground::AddPlayer(CharacterBase * player)
{
	this->players->AddAffect(player);
}

Array<CharacterBase> * Ground::GetPlayers() const
{
	return this->players;
}

TileArray * Ground::GetGround0() const
{
	return this->ground0;
}

int Ground::GetSize() const
{
	return this->size;
}


void Ground::DrawGround() const
{
	if (this->size <= 0 || this->ground0 == nullptr) {
		throw("invalid ground size or array null");
	}
	for (int i = 0; i < this->size; ++i) {
		this->DrawLine();
		this->DrawTilesLine(i);
	}
	this->DrawLine();
}

void Ground::DrawLine() const
{
	try {
		for (int line = 0; line < this->size; ++line) {
			std::cout << "_____";
		}
		std::cout << std::endl;
	} catch (std::exception & e) {
		std::cout << "Error writting ground with error: " << e.what() << std::endl;
	}
}

void Ground::DrawTilesLine(int i) const
{
	try {
		for (int j = 0; j < this->size; ++j) {
			try {
				this->ground0->GetTile(i, j)->PrintTile();
			} catch (std::exception & e) {
		std::cout << "Error writting tile x: " << i << " y: " << j << std::endl << "With error: " << e.what() << std::endl;
			}
		}
		std::cout << std::endl;
	} catch (std::exception & e) {
		std::cout << "Error writing line " << i << " with error: " << e.what() << std::endl;
	}
}


bool Ground::HasPlayer(int x, int y)
{
	return (this->ground0->GetTile(x, y)->GetTilePlayer() != nullptr);
}

bool Ground::MovePlayer(CharacterBase * player, int x, int y)
{
	Tile * playerTile = this->ground0->GetTile(this->GetX(player), this->GetY(player));
	playerTile->RetirePlayer();
	playerTile = this->ground0->GetTile(x, y);
	return playerTile->AddPlayer(player);
}
		

void Ground::PrintWinners()
{
	std::cout << "Team " << std::to_string(this->won) << " won with players:" << std::endl;
	for (int i = 0; i < this->players->AffectCount(); ++i) {
		if (this->players->GetIdx(i)->GetTeam() == this->won) {
			std::cout << "Player " << std::to_string(i) << ": " << this->players->GetIdx(i)->GetName() << std::endl;
		}
	}
}


void Ground::Round()
{
	while (this->won == 0) {
		std::cout << "This is the round " << this->roundNb << std::endl;
		for (this->playerTurn = 0; this->playerTurn < this->players->AffectCount(); ++this->playerTurn) {
			std::cout << "Turn " << this->playerTurn + 1 << std::endl;
			this->PlayerTurn();
		}
		//this->playerTurn = 0;
		this->RoundRegeneration();
		++this->roundNb;
	}
	this->PrintWinners();
}

int Ground::PlayerTurn()
{
	return this->players->GetIdx(this->playerTurn)->AskForTurn(this);
}

void Ground::RoundRegeneration()
{
	for (int i = 0; i < this->players->AffectCount(); ++i) {
		this->players->GetIdx(i)->EndTurnRegen();
	}
}

bool Ground::GetIfAttackInRange(CharacterBase * player, Attack * attack, int xTarget, int yTarget)
{
	int x = this->GetX(player), y = this->GetY(player);
	int xDiff = abs(xTarget - x);
	int yDiff = abs(yTarget - y);
	int baseRange = (attack == nullptr ? player->GetBaseRange() : attack->GetRange());
	if (xDiff <= baseRange && yDiff <= baseRange) return true;
	return false;
}


