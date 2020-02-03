#include "Minefield.h"
#include <assert.h>
#include <random>
Minefield::Minefield(int nMines)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);
	
	for (int i = 0; i < nMines; i++) {
	Vei2 spawnPos;
		do {
			spawnPos = { xDist(rng),yDist(rng) };

		} while (TileAt(spawnPos).HasMine());
		TileAt(spawnPos).SpawnMine();
	}
	

}
Minefield::Tile& Minefield::TileAt(Vei2 & gridPos)
{
	return field[gridPos.y * width + gridPos.x];
}

RectI Minefield::getRect() const
{
	return RectI(0, width * SpriteCodex::tileSize, 0 , height * SpriteCodex::tileSize);
}

void Minefield::OnRevealClick(Vei2 & screenPos)
{
	if (getRect().Contains(screenPos)) {
		Vei2 gridPos = ScreenToGrid(screenPos);
		Tile& tile = TileAt(gridPos);
		if (!tile.isRevealed()) {

			tile.Reveal();
		}

	}
	

}

const Minefield::Tile& Minefield::TileAt(Vei2 & gridPos) const
{
	return field[gridPos.y * width + gridPos.x];
}

void Minefield::Draw(Graphics & gfx)
{
	gfx.DrawRect(getRect(), SpriteCodex::baseColor);
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++) {
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++) {
		
			TileAt(gridPos).Draw(gfx, gridPos * SpriteCodex::tileSize);
		}
	
	}
}

Vei2 & Minefield::ScreenToGrid(Vei2 & screenPos) const
{
	return screenPos / SpriteCodex::tileSize;
}

void Minefield::Tile::SpawnMine()
{
	assert(!hasMine);
	hasMine = true;
}

bool Minefield::Tile::HasMine() const
{
	return hasMine;
}

void Minefield::Tile::Reveal()
{
	assert(state != State::Revealed);
	state = State::Revealed;
}

bool Minefield::Tile::isRevealed()
{
	return state == State::Revealed;
}

void Minefield::Tile::Draw(Graphics & gfx, Vei2 & screenPos)
{
	switch (state) {
	case State::Hidden:
		SpriteCodex::DrawTileButton(screenPos, gfx);
		break;
	case State::Flagged:
		SpriteCodex::DrawTileButton(screenPos, gfx);
		SpriteCodex::DrawTileFlag(screenPos, gfx);
		break;
	case State::Revealed:
		if (!HasMine()) {
			SpriteCodex::DrawTile0(screenPos, gfx);
		}
		else {
			SpriteCodex::DrawTile0(screenPos, gfx);
			SpriteCodex::DrawTileBomb(screenPos, gfx);
		}
		break;
	
	
	}
}




