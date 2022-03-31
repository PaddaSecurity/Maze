#include <ics46/factory/DynamicFactory.hpp>
#include "thomasMaze.hpp"
#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <algorithm>
#include <random>    
#include <vector>    



ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, thomasMaze, "Thomas Maze");

//Standard constructor
thomasMaze::thomasMaze()
{

}

//Overidden generate maze function
void thomasMaze::generateMaze(Maze& maze)
{
    //Add all walls
    maze.addAllWalls();

    //Fill in main vector
    mainMaze.resize(maze.getWidth());
    for (int i = 0; i < maze.getWidth(); ++i)
    {
        mainMaze[i].resize(maze.getHeight());
        fill(mainMaze[i].begin(), mainMaze[i].end(), false);
    }
    
    //Call main recursive function
    myRecursive(0,0, maze);
}

//Main recursive function(haha)... Main recursive function(haha)... Main recursive function (haha)...
void thomasMaze::myRecursive(int x, int y, Maze& maze)
{
    //Visited
    mainMaze[x][y] = true;
    std::vector<Direction> notYetVisited = checkPossibleMoves(x, y, maze);

    while(notYetVisited.size() != 0)
    {
        int ranChoice = chooseRandom(notYetVisited.size());
        assignValues(x, y);
        change_X_Y(nx,ny,ranChoice, notYetVisited);

        if (checkVal() == false)
        {
            maze.removeWall(x, y, notYetVisited[ranChoice]);
            myRecursive(nx, ny, maze);  
        }
        notYetVisited = checkPossibleMoves(x,y,maze);
    }
}

std::vector<Direction> thomasMaze::checkPossibleMoves(int x, int y, Maze& maze)
{
    std::vector<Direction> bob;

    if (checkLeft(x, y))
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
    if (checkUp(x, y))
    {
        bob.push_back(Direction::up);
    }

    return bob;
}

int thomasMaze::chooseRandom(int MAX_SIZE)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr(0, MAX_SIZE - 1);

    return distr(eng);
}

void thomasMaze::change_X_Y(int& x, int& y,int ranChoice ,std::vector<Direction> notYetVisited)
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

void thomasMaze::assignValues(int x, int y)
{
    nx = x;
    ny = y;
}

bool thomasMaze::checkVal()
{
    if(mainMaze[nx][ny])
    {
        return true;
    }
    return false;
}

bool thomasMaze::checkRight(int& x, int& y, Maze& maze)
{
    if (x != maze.getWidth() - 1)
    {
        if (mainMaze[x + 1][y] == false)
        {
            return true;
        }
    }
    return false;
}
bool thomasMaze::checkLeft(int& x, int& y)
{
    if (x != 0)
    {
        if(mainMaze[x - 1][y] == false)
        {
            return true;
        }
    }
    return false;
}
bool thomasMaze::checkUp(int& x, int& y)
{
    if (y != 0)
    {
        if (mainMaze[x][y - 1] == false)
        {
            return true;
        }
    }
    return false;
}
bool thomasMaze::checkDown(int& x, int& y, Maze& maze)
{
    if (y != maze.getHeight() - 1)
    {
        if (mainMaze[x][y + 1] == false)
        {
            return true;
        }
    }
    return false;
}  

