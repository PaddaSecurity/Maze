#include "thomasSolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "MazeSolution.hpp"
#include <iostream>
#include "Maze.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <utility>



ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, thomasSolver, "Thomas Solver");


thomasSolver::thomasSolver()
{

}

void thomasSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    mazeSolution.restart();
    mainMaze.resize(maze.getWidth());
    for (int i = 0; i < maze.getWidth(); ++i)
    {
        mainMaze[i].resize(maze.getHeight());
        fill(mainMaze[i].begin(), mainMaze[i].end(), false);
    }
    
    //Call main recursive function
    mainRec(0, 0, maze, mazeSolution);
}

void thomasSolver::mainRec(int x, int y, const Maze& maze, MazeSolution& mazeSolution)
{
    mainMaze[x][y] = true;
    std::vector<Direction> notYetVisited = checkPossibleMoves(x, y, maze);
    


    while(notYetVisited.size() != 0)
    {
        
        int ranChoice = chooseRandom(notYetVisited.size());
        assignValues(x, y);
        change_X_Y(nx,ny,ranChoice, notYetVisited);
        
        if (mainMaze[nx][ny] == false)
        {
            if (maze.wallExists(x,y,notYetVisited[ranChoice]) == false)
            {   
               
                mazeSolution.extend(notYetVisited[ranChoice]);
                mainRec(nx, ny, maze, mazeSolution);         
            }
        }  
        notYetVisited = checkPossibleMoves(x,y,maze);  
        mazeSolution.backUp();
        
        
    } 

 
}

std::vector<Direction> thomasSolver::checkPossibleMoves(int x, int y, const Maze& maze)
{
    std::vector<Direction> bob;
    
    if (checkLeft(x, y, maze))
    {
        bob.push_back(Direction::left);
    }
    if (checkRight(x, y, maze))
    {
        bob.push_back(Direction::right);
    }
    if (checkDown(x, y, maze))
    {
        bob.push_back(Direction::down);  
    }
    if (checkUp(x, y, maze))
    {
        bob.push_back(Direction::up);
    }

    return bob;
}

int thomasSolver::chooseRandom(int MAX_SIZE)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr(0, MAX_SIZE - 1);

    return distr(eng);
}

void thomasSolver::change_X_Y(int& x, int& y,int ranChoice ,std::vector<Direction> notYetVisited)
{
    if (notYetVisited[ranChoice] == Direction::right)
    {
        x += 1;
    }
    else if (notYetVisited[ranChoice] == Direction::left)
    {
        x -= 1;
    }
    else if (notYetVisited[ranChoice] == Direction::up)
    {
        y -= 1;
    }
    else if (notYetVisited[ranChoice] == Direction::down)
    {
        y += 1;
    }
}

void thomasSolver::assignValues(int x, int y)
{
    nx = x;
    ny = y;
}

bool thomasSolver::checkRight(int& x, int& y, const Maze& maze)
{
    if (x != maze.getWidth() - 1)
    {
        if (mainMaze[x + 1][y] == false)
        {
            if (maze.wallExists(x,y,Direction::right) == false)
            {
                return true;
            }
        }
    }
    return false;
}
bool thomasSolver::checkLeft(int& x, int& y, const Maze& maze)
{
    if (x != 0)
    {
        if(mainMaze[x - 1][y] == false)
        {
            if (maze.wallExists(x,y,Direction::left) == false)
            {
                return true;
            }
        }
    }
    return false;
}
bool thomasSolver::checkUp(int& x, int& y, const Maze& maze)
{
    if (y != 0)
    {
        if (mainMaze[x][y - 1] == false)
        {
            if (maze.wallExists(x,y,Direction::up) == false)
            {
                return true;
            }
        }
    }
    return false;
}
bool thomasSolver::checkDown(int& x, int& y, const Maze& maze)
{
    if (y != maze.getHeight() - 1)
    {
        if (mainMaze[x][y + 1] == false)
        {
            if (maze.wallExists(x,y,Direction::down) == false)
            {
                return true;
            }
        }
    }
    return false;
} 