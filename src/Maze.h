#ifndef _MAZE_H
#define _MAZE_H

struct boolean{
public:
	int x;
	int y;
	int getX();
	int getY();
	void setX(int a);
	void setY(int a);
	bool accessible;
	void setBool(bool b);
	bool getBool();
};

struct Position{
public:
	int x;
	int y;
	void setX(int a);
	void setY(int a);
	int getX();
	int getY();
	bool operator==(Position op2);
	bool operator!=(Position op2);
};
ostream& operator <<(ostream& o, Position a);

class Maze{
public:
	int width;
	int height;
	char *maze;
	Position currentLocation;
	Position startLocation;
	Position endLocation;

	Maze(char *m, Position start, Position end, int w, int h);
	Maze();
	~Maze();
	
	Position getStart();
	Position getEnd();
	void generate();
	void traverse();
	void printMaze();
};




#endif

