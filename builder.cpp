#include "MazeGenerator.hpp"
#include "builder.hpp"
#include "Maze.hpp"
#include <ics46/factory/DynamicFactory.hpp>

#include <random>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, builder, "test builder(Required)");


std::random_device device;
std::default_random_engine engine{device()};
int r_int(int a){
	std::uniform_int_distribution<int> distribution{0,a-1};
	return distribution(engine);
}

Direction getDirection(int a){
	if(a == 0){
		return Direction::up;
	}
	else if(a == 1){
		return Direction::down;
	}
	else if(a == 2){
		return Direction::left;
	}
	else if(a == 3){
		return Direction::right;
	}
}

Direction pickDirection(std::vector<int> unvisited){
	int index = r_int(unvisited.size())-1;
	return getDirection(unvisited[index]);
}

void build(Maze& maze, std::vector<std::vector<bool>>& m, int width, int height){
	std::vector<int> unvisited; //unvisited directions
	m[width][height] = true;// mark as visited

	// to create a list of all unvisited adjacent cells
	int counter = 0;
	if((height>0) && (m[width][height-1] == false)){ //can move up if upper cell is unvisited and there is room to move up
		unvisited.push_back(0);//up
		counter=counter+1;
	}
	if((height< maze.getHeight()-1) && (m[width][height+1] == false)){ // not really sure about the height < h-1
		unvisited.push_back(1);//down
		counter=counter+1;
	}
	if((width > 0) && (m[width-1][height] == false)){
		unvisited.push_back(2);//left
		counter=counter+1;
	}
	if((width < maze.getWidth()-1) && (m[width+1][height] == false)){
		unvisited.push_back(3);//right
		counter=counter+1;
	}
	if(counter == 0){
		return;
	}


	int index = r_int(unvisited.size()); // random int in range (1,len), -1 to create (0,#) for indexing
	Direction random_direction = getDirection(unvisited[index]);
	maze.removeWall(width,height,random_direction);


	//updates cell location
	if(unvisited[index] == 0){
		height = height - 1;
	}
	if(unvisited[index] == 1){
		height = height + 1;
	}
	if(unvisited[index] == 2){
		width = width - 1;
	}
	if(unvisited[index] == 3){
		width = width + 1;
	}

	build(maze,m,width,height);
	if(m[width][height] == true){
		build(maze,m,width,height); 
	}

}

builder::builder(){
}

void builder::generateMaze(Maze& maze)
{
	maze.addAllWalls();
	
	std::vector<std::vector<bool>> m_vector;
	int h = maze.getHeight();
	int w = maze.getWidth();
	m_vector.resize(w, std::vector<bool>(h,false)); //resized to have w vectors, filled with vectors that have height amount of 0's

	int width = r_int(maze.getWidth()); //starting point
	int height = r_int(maze.getHeight()); //double check if getHeight is 0 - # or 1 - #

	build(maze,m_vector,width,height);
	//maze.removeWall(maze.getWidth()-1,0,Direction::right);

}