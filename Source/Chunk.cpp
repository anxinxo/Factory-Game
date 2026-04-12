#include "../Header/Chunk.hpp"

Chunk::Chunk(int _cx, int _cy): cx(_cx), cy(_cy) {}

CELL &Chunk::Get(int x, int y)
{
    return cells[x][y];
}