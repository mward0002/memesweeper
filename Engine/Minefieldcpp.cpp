#pragma once
#include "Vei2.h"
#include "RectI.h"
#include "Graphics.h"
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
		bool hasMine();
		void Draw(Graphics& gfx, Vei2& screenPos);
	private:
		State state = State::Hidden;
		bool hasMine = false;

	};
public:
	Minefield(int nMines);
	Tile& TileAt(Vei2& gridPos);
	const Tile& TileAt(Vei2& gridPos) const;
	void Draw(Graphics& gfx);
private:
	static constexpr int height = 20;
	static constexpr int width = 16;
	Tile field[height * width];

};