#ifndef THOMASMAZE_HPP
#define THOMASMAZE_HPP


#include "MazeSolver.hpp"
#include <vector>
#include "Maze.hpp"


class thomasSolver: public MazeSolver
{
public:
    thomasSolver();
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
    void mainRec(int x, int y, const Maze& maze, MazeSolution& mazeSolution);
    std::vector<Direction> checkPossibleMoves(int x, int y, const Maze& maze);
    int chooseRandom(int MAX_SIZE);
    void change_X_Y(int& x, int& y, int ranChoice, std::vector<Direction>);
    void assignValues(int x, int y);
    bool checkRight(int& x, int& y,const Maze& maze);
    bool checkLeft(int& x, int& y, const Maze& maze);
    bool checkUp(int& x, int& y, const Maze& maze);
    bool checkDown(int& x, int& y, const Maze& maze);

private:
    int nx, ny;
    std::vector<std::vector<bool>> mainMaze;
    
};


#endif