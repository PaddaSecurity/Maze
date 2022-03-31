#ifndef THOMASMAZE_HPP
#define THOMASMAZE_HPP


#include "MazeGenerator.hpp"
#include <vector>
#include "Maze.hpp"



class thomasMaze: public MazeGenerator
{

public:
    thomasMaze();
    void generateMaze(Maze& maze) override;
    void myRecursive(int x, int y, Maze& maze);
    std::vector<Direction> checkPossibleMoves(int x, int y, Maze& maze);
    int chooseRandom(int MAX_SIZE);
    void change_X_Y(int& x, int& y, int ranChoice, std::vector<Direction>);
    void assignValues(int x, int y);
    bool checkVal();
    bool checkRight(int& x, int& y, Maze& maze);
    bool checkLeft(int& x, int& y);
    bool checkUp(int& x, int& y);
    bool checkDown(int& x, int& y, Maze& maze);


private:
    std::vector<std::vector<bool>> mainMaze;
    int nx;
    int ny;

};

#endif