#ifndef _BOARD
#define _BOARD

#include "io_utilities.h"
#include "Color.h"
#include "Point.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <queue>

class Board {
    Color c;
    int rows, cols;
    std::string board [25];
    Point gho[4], pac, score;
    int numofdots = 0, TotalDots, GhostIndex;
public:
    void printBoard(bool NoColor) const;
    void setColor(Color color) { c = color; }
    bool ReadBoard();
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int getIndex() const { return GhostIndex; }
    void setBoard(int y, int x, char c) { board [y][x] = c; }
    const std::string* getBoard()const { return board; }
    Point getGhost(int i)const { return gho[i]; }
    Point getpac() const { return pac; }
    Point getScore() const { return score; }
    int getTotal() const { return TotalDots; }
    void IncreaseNumOfDots() { numofdots++; }
    int ReturnNumOfDots()const { return numofdots; }
    void WakaWaka() { numofdots--; }
    void AddToTotal(int power) { TotalDots += power; }
    void nextscore() { TotalDots += numofdots; numofdots = 0; };
};
#endif