#include "solver.hpp"
#include "Maze.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include <ics46/factory/DynamicFactory.hpp>

#include <iostream>
#include <random>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, solver, "test solver (Required)");

std::random_device device1;
std::default_random_engine engine1{device1()};
int random_int(int a){
	std::uniform_int_distribution<int> distribution{0,a-1};
	return distribution(engine1);
}

solver::solver(){
}

void build(std::vector<std::vector<int>> s, const Maze& maze, MazeSolution& mazeSolution, int x , int y){
	if(mazeSolution.isComplete() == true){
		return;
	}
	s[x][y] = 2; // visited
	std::vector<Direction> possible;
	int counter = 0;
	if((y > 0) && !(maze.wallExists(x,y, Direction::up)) && (s[x][y-1] == 0) ){
		possible.push_back(Direction::up);
		counter++;
	}
	if((y < maze.getHeight()-1) && !(maze.wallExists(x,y, Direction::down)) && (s[x][y+1] == 0) ){
		possible.push_back(Direction::down);
		counter++;
	}
	if((x > 0) && !(maze.wallExists(x,y, Direction::left)) && (s[x-1][y] == 0) ){
		possible.push_back(Direction::left);
		counter++;
	}
	if((x < maze.getWidth()-1) && !(maze.wallExists(x,y, Direction::right)) && (s[x+1][y] == 0) ){
		possible.push_back(Direction::right);
		counter++;
	}
	if(counter > 0){
		s[x][y] = 1; // marks it as possible for multiple outcome
	}
	if(counter == 0){
		//begin backtracking
		while(s[mazeSolution.getCurrentCell().first][mazeSolution.getCurrentCell().second] == 2){
			mazeSolution.backUp(); // back up until fork
		}
		build(s, maze, mazeSolution, mazeSolution.getCurrentCell().first, mazeSolution.getCurrentCell().second);
		//mazeSolution.getMovements().back();
		//s[x][y] = 2; //useless
		return; // so you don't get random(0,-1) // this is deadend
	}

	int index = random_int(possible.size());
	mazeSolution.extend(possible[index]);
	int new_x = mazeSolution.getCurrentCell().first;
	int new_y = mazeSolution.getCurrentCell().second;
	build(s,maze,mazeSolution,new_x,new_y);
}

void solver::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
	int startx = mazeSolution.getStartingCell().first;
	int starty = mazeSolution.getStartingCell().second;
	std::vector<std::vector<int>> s;
	s.resize(mazeSolution.getWidth(), std::vector<int>(mazeSolution.getHeight(),0));

	build(s,maze, mazeSolution, startx, starty);


}