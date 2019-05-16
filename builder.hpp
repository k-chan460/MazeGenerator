
// #ifndef BUILDER_HPP
// #define BUILDER_HPP


class builder: public MazeGenerator
{
public:
	virtual void generateMaze(Maze& maze);
	builder();

};

// #endif