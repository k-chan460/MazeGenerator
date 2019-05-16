#include "MazeSolver.hpp"

class solver: public MazeSolver
{
public:
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
	solver();
};