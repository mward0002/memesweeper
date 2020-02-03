#pragma once
#pragma once
#include "Vei2.h"
#include "RectI.h"
#include "Graphics.h"
#include "SpriteCodex.h"

class Minefield {
private:
	class Tile {
	public:
		enum class State {
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SpawnMine();
		bool HasMine() const;
		void Reveal();
		bool isRevealed();
		bool isFlagged();
		void ToggleFlag();
		void Draw(Graphics& gfx, Vei2& screenPos);
	private:
		State state = State::Hidden;
		bool hasMine = false;

	};
public:
	Minefield(int nMines);
	Tile& TileAt( Vei2& gridPos);
	RectI getRect() const;
	void OnRevealClick(Vei2& screenPos);
	void OnFlagClick(Vei2& screenPos);
	void Draw(Graphics& gfx);
private:
	const Tile& TileAt(Vei2& gridPos) const;
	
	Vei2& ScreenToGrid(Vei2& screenPos) const;
private:
	static constexpr int height = 20;
	static constexpr int width = 16;
	Tile field[height * width];

};