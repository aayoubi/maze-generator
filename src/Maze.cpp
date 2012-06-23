#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
#include "Maze.h"

int boolean::getX(){return x;}
int boolean::getY(){return y;}
bool boolean::getBool(){return accessible;}
void boolean::setBool(bool b){ accessible = b;}
void boolean::setX(int a){x = a;}
void boolean::setY(int a){y = a;}

int Position::getX(){ return x;}
int Position::getY(){ return y;}
void Position::setX(int a){ x = a;}
void Position::setY(int a){ y = a;}
Position Maze::getStart(){return startLocation;}
Position Maze::getEnd(){return endLocation;}



ostream& operator << (ostream& o, Position a){
	o<<a.getX() <<" "<<a.getY();
	return o;
}

bool Position::operator==(Position op2){
	if(this->getX() == op2.getX() && this->getY()==op2.getY())
		return true;
	return false;
}
bool Position::operator!=(Position op2){
	if(this->getX() != op2.getX() || this->getY() != op2.getY())
		return false;
	return false;
}
Maze::Maze(char *m, Position start, Position end, int w, int h){
	width = w;
	height = h;
	maze = m;
	startLocation = start;
	endLocation = end;
}
Maze::Maze(){}
Maze::~Maze(){}

void Maze::traverse(){
	
	ofstream output("output.txt");
	
	Position cur;
	bool valid = true;
	bool valid_2 = true;
	boolean allChar[99][99];
	
	for(int i = 0; i< height;i++){
		for(int j=0 ;j<width; j++){
			allChar[i][j].setX(i);
			allChar[i][j].setY(j);
			allChar[i][j].setBool(true);
		}
	}
	cur = this->getStart();
	maze[cur.getX()*width + cur.getY()] = 'X';

	while(valid){
		//look for next possible move
		if(maze[(cur.getX()+1)*width + cur.getY()] == '.' && allChar[cur.getX()+1][cur.getY()].accessible != false ){
			cur.setX(cur.getX()+1);
			cur.setY(cur.getY());	
		
		}else if(maze[cur.getX()*width + cur.getY()+1] == '.' && allChar[cur.getX()][cur.getY()+1].accessible != false){
			cur.setX(cur.getX());
			cur.setY(cur.getY()+1);

		}else if(maze[(cur.getX()-1)*width + cur.getY()] == '.' && allChar[cur.getX()-1][cur.getY()].accessible != false){
			cur.setX(cur.getX()-1);
			cur.setY(cur.getY());

		}else if(maze[cur.getX()*width + cur.getY()-1] == '.' && allChar[cur.getX()][cur.getY()-1].accessible != false ){
			cur.setX(cur.getX());
			cur.setY(cur.getY()-1);

		}else{
			/*backtracking every step we took if we reach a dead-end*/
			while(valid_2){
				
				if(maze[(cur.getX()+1)*width + cur.getY()] == 'X'){
					maze[(cur.getX())*width + cur.getY()] ='.';
					allChar[cur.getX()][cur.getY()].accessible= false;
					cur.setX(cur.getX()+1);
					cur.setY(cur.getY());
					
				}else if(maze[cur.getX()*width + cur.getY()+1] == 'X'){
					maze[cur.getX()*width + cur.getY()] = '.';
					allChar[cur.getX()][cur.getY()].accessible= false;
					cur.setX(cur.getX());
					cur.setY(cur.getY()+1);
					
				}else if(maze[(cur.getX()-1)*width + cur.getY()] == 'X'){
					maze[(cur.getX())*width + cur.getY()] ='.';
					allChar[cur.getX()][cur.getY()].accessible= false;
					cur.setX(cur.getX()-1);
					cur.setY(cur.getY());
					
				}else if(maze[cur.getX()*width + cur.getY()-1] == 'X'){
					maze[cur.getX()*width + cur.getY()]='.';
					allChar[cur.getX()][cur.getY()].accessible= false;
					cur.setX(cur.getX());
					cur.setY(cur.getY()-1);					
				}
				
				if((maze[(cur.getX()-1)*width + cur.getY()] =='.' && allChar[cur.getX()-1][cur.getY()].accessible != false) ||
						(maze[(cur.getX()+1)*width + cur.getY()] =='.' && allChar[cur.getX()+1][cur.getY()].accessible != false) ||
							 (maze[(cur.getX())*width + cur.getY()+1] =='.' && allChar[cur.getX()][cur.getY()+1].accessible != false) ||
								 (maze[(cur.getX())*width + cur.getY()-1] =='.' && allChar[cur.getX()][cur.getY()-1].accessible != false))
					valid_2 = false;
				
			}
			
			
		}
		
		valid_2=true;
		maze[cur.getX()*width + cur.getY()] = 'X';

		for(int i = 0; i< height;i++){
			for(int j=0 ;j<width; j++){
				output<< maze[i*width+j];
			}
			output<< endl;
		}
		output <<endl<<endl;
		
		if(cur == this->getEnd())
			valid = false;
	}
 
	output<<"Maze Solved";
	output.close();
	
}

/**
*  The Best generate EHHHH
*
*/

void Maze::generate(){
	
	srand((int)time(0));
	int randW = rand()%(69-6+1)+6;
	//int randH = rand()%(98-6+1)+6;
	ofstream out("testMaze.txt");
	out<<randW<<endl;
	out<<randW<<endl;

	for(int i=0; i<randW; i++){
		for(int j=0; j<randW; j++){
			out<<"#";
		}
		out<<endl;
	}
	out.close();

	ifstream in("testMaze.txt");

	//first two lines of the file should contain the size of the maze
	int w, h;
	in>>w;
	in>>h;
	
	char *maze = (char*)malloc(w*h*sizeof(char));
	for(int i = 0; i< w;i++){
		for(int j=0 ;j<h; j++){
			in>> maze[i*w+j];
		}
	}	
	in.close();
	
	Position cur;
	Position EndLocation;

	int random, start, end;
	
	random= (rand()%(w));
	
	/*initialize start and end points */

	while(random == 0 || random == (w-1)){
		random = rand()%(w);
	}

	if(random != 0 && random != (w-1)){
			maze[random*w+0] = '.';
			cur.setY(0);
			cur.setX(random);
	}

	random =(rand()%(w));

	while(random == 0 || random == (w-1)){
		random =(rand()%(w));

	}

	if(random != 0 && random != (w-1)){
			maze[random*w+w-1] ='.';
			EndLocation.setY(w-1);
			EndLocation.setX(random);
	}

	
	int decision;
	bool valid = true;

	cur.setX(cur.getX());
	cur.setY(cur.getY()+1);
	maze[cur.getX()*w+cur.getY()] ='.';
	
	boolean allChar[99][99];

	for(int i = 0; i< w;i++){
		for(int j=0 ;j<w; j++){
			allChar[i][j].setX(i);
			allChar[i][j].setY(j);
			allChar[i][j].setBool(true);
		}
	}
	
	//boundaries of the maze are inaccessible
	for(int i = 0; i< w;i++){
			allChar[i][0].setBool(false);
            allChar[i][w-1].setBool(false);
            allChar[0][i].setBool(false);
            allChar[w-1][i].setBool(false);
	}
	
	//surroundings of the end point are inaccessible for now
	allChar[EndLocation.getX()-1][EndLocation.getY()-1].setBool(false);
	allChar[EndLocation.getX()][EndLocation.getY()-1].setBool(false);
	allChar[EndLocation.getX()+1][EndLocation.getY()-1].setBool(false);
	allChar[EndLocation.getX()-1][EndLocation.getY()-2].setBool(false);
	allChar[EndLocation.getX()][EndLocation.getY()-2].setBool(false);
	allChar[EndLocation.getX()+1][EndLocation.getY()-2].setBool(false);

	
	//just to keep count(for testing)
	int x =1;
	
	//1 for North
	//2 for south
	//3 for east
	//4 for west
	Position chooser;
	int rando;
	//to keep track of all our moves
	vector<Position> pVector;
	pVector.push_back(cur);
	
	for(int i=0 ; valid!= false; i++){
		decision = rand()%4+1;
		if(decision == 1 && allChar[cur.getX()-1][cur.getY()].accessible != false){
			
			if((maze[(cur.getX()-1)*w+cur.getY()-1]=='.'&&maze[(cur.getX())*w+cur.getY()-1]=='.'))
					continue;
			if((maze[(cur.getX()-1)*w+cur.getY()+1]=='.'&&maze[(cur.getX())*w+cur.getY()+1]=='.'))
					continue;
			if((maze[(cur.getX()-2)*w+cur.getY()]=='.'))
					continue;
			if(maze[(cur.getX()-1)*w+cur.getY()+1]=='.'|| maze[(cur.getX()-1)*w+cur.getY()-1]=='.')
					continue;
			allChar[cur.getX()][cur.getY()].accessible = false;
			cur.setX(cur.getX()-1);
			cur.setY(cur.getY());
			pVector.push_back(cur);
			maze[cur.getX()*w+cur.getY()]='.';
			
		}else if(decision == 2 && allChar[cur.getX()+1][cur.getY()].accessible != false){
			if((maze[(cur.getX()+1)*w+cur.getY()+1]=='.'&&maze[(cur.getX())*w+cur.getY()+1]=='.'))
					continue;
			if((maze[(cur.getX()+1)*w+cur.getY()-1]=='.'&&maze[(cur.getX())*w+cur.getY()-1]=='.'))
					continue;
			if((maze[(cur.getX()+2)*w+cur.getY()]=='.'))
					continue;
			if(maze[(cur.getX()+1)*w+cur.getY()+1]=='.'|| maze[(cur.getX()+1)*w+cur.getY()-1]=='.')
					continue;
			allChar[cur.getX()][cur.getY()].accessible = false;
			cur.setX(cur.getX()+1);
			cur.setY(cur.getY());
			pVector.push_back(cur);
			maze[cur.getX()*w+cur.getY()]='.';
			

		}else if(decision == 3 && allChar[cur.getX()][cur.getY()+1].accessible != false){
			if((maze[(cur.getX()-1)*w+cur.getY()+1]=='.'&&maze[(cur.getX()-1)*w+cur.getY()]=='.'))
					continue;
			if((maze[(cur.getX()+1)*w+cur.getY()+1]=='.'&&maze[(cur.getX()+1)*w+cur.getY()]=='.'))
					continue;
			if((maze[(cur.getX())*w+cur.getY()+2]=='.'))
					continue;
			if(maze[(cur.getX()+1)*w+cur.getY()+1]=='.'|| maze[(cur.getX()-1)*w+cur.getY()+1]=='.')
					continue;
			allChar[cur.getX()][cur.getY()].accessible = false;
			cur.setX(cur.getX());
			cur.setY(cur.getY()+1);
			pVector.push_back(cur);
			maze[cur.getX()*w+cur.getY()]='.';
			

		}else if(decision == 4 && allChar[cur.getX()][cur.getY()-1].accessible != false){
			if((maze[(cur.getX()-1)*w+cur.getY()-1]=='.'&&maze[(cur.getX()-1)*w+cur.getY()]=='.'))
					continue;
			if((maze[(cur.getX()+1)*w+cur.getY()-1]=='.'&&maze[(cur.getX()+1)*w+cur.getY()]=='.'))
					continue;
			if((maze[(cur.getX())*w+cur.getY()-2]=='.'))
					continue;
			if(maze[(cur.getX()-1)*w+cur.getY()-1]=='.'|| maze[(cur.getX()+1)*w+cur.getY()-1]=='.')
					continue;
			allChar[cur.getX()][cur.getY()].accessible = false;
			cur.setX(cur.getX());
			cur.setY(cur.getY()-1);
			pVector.push_back(cur);
			maze[cur.getX()*w+cur.getY()]='.';

		}else if (
			(allChar[cur.getX()-1][cur.getY()].accessible == false || 
			(maze[(cur.getX()-1)*w+cur.getY()+1]=='.')||
			(maze[(cur.getX()-1)*w+cur.getY()-1] =='.')||
			(maze[(cur.getX()-2)*w+cur.getY()]=='.')||
			 maze[(cur.getX()-1)*w+cur.getY()+1]=='.'||
			 maze[(cur.getX()-1)*w+cur.getY()-1]=='.')
			&& (allChar[cur.getX()+1][cur.getY()].accessible == false || 
			(maze[(cur.getX()+1)*w+cur.getY()+1]=='.')||
			(maze[(cur.getX()+1)*w+cur.getY()-1]=='.')||
			(maze[(cur.getX()+2)*w+cur.getY()]=='.')||
			maze[(cur.getX()+1)*w+cur.getY()-1]=='.'||
			maze[(cur.getX()+1)*w+cur.getY()+1]=='.')
			&& (allChar[cur.getX()][cur.getY()+1].accessible == false || 
			(maze[(cur.getX()-1)*w+cur.getY()+1]=='.')||
			(maze[(cur.getX()+1)*w+cur.getY()+1]=='.')||
			(maze[(cur.getX())*w+cur.getY()+2]=='.')||
			maze[(cur.getX()-1)*w+cur.getY()+1]=='.'||
			maze[(cur.getX()-1)*w+cur.getY()-1]=='.')
			&& (allChar[cur.getX()][cur.getY()-1].accessible == false || 
			(maze[(cur.getX()-1)*w+cur.getY()-1]=='.')||
			(maze[(cur.getX()+1)*w+cur.getY()-1]=='.')||
			(maze[(cur.getX())*w+cur.getY()-2]=='.')||
			maze[(cur.getX()+1)*w+cur.getY()-1]=='.'||
			maze[(cur.getX()-1)*w+cur.getY()-1]=='.')
			)
		{
			rando = rand()%(pVector.size()-1);
			cur = pVector.at(rando);
			continue;	
		}
		

		//increment the loop
		x++;

		//if we want less walls and easier maze chooser a smaller number
		//it has to be bigger than w*28 
		//this ratio is correct because the required deadends to build the maze are
		//approximated to this ratio

		//awwal marra jarrabet x == 1200 3a maze 12*12 w fawwalit kella
		// jarrabet 800 75% mfawle...w toli3 ma3eh hek ratio :D
		if(x==(w*101))
			valid = false;
	}

	
	/*reaching one of the chambers of the maze from the end position*/
	//in other words:_connecting the end point to the maze
	valid = true;
	EndLocation.setX(EndLocation.getX());
	EndLocation.setY(EndLocation.getY()-1);
	maze[EndLocation.getX()*w+EndLocation.getY()]='.';

	while(valid){

		 if(maze[EndLocation.getX()*w+EndLocation.getY()-2]=='.'){
			maze[EndLocation.getX()*w+EndLocation.getY()-1]='.';
			if(maze[(EndLocation.getX()-1)*w+EndLocation.getY()-2]=='.' && maze[(EndLocation.getX()-1)*w+EndLocation.getY()-1]=='.')
				maze[(EndLocation.getX()-1)*w+EndLocation.getY()-2]= '#';
			if(maze[(EndLocation.getX()+1)*w+EndLocation.getY()-2]=='.' && maze[(EndLocation.getX()+1)*w+EndLocation.getY()-1]=='.')
				maze[(EndLocation.getX()-1)*w+EndLocation.getY()-2]= '#';
			break;

		}else if(maze[(EndLocation.getX()-2)*w+EndLocation.getY()]=='.' && maze[(EndLocation.getX()-1)*w+EndLocation.getY()-1]!='.' ){
			maze[(EndLocation.getX()-1)*w+EndLocation.getY()]='.';
			break;

		}else if(maze[(EndLocation.getX()+2)*w+EndLocation.getY()]=='.'&& maze[(EndLocation.getX()+1)*w+EndLocation.getY()-1]!='.' ){
			maze[(EndLocation.getX()+1)*w+EndLocation.getY()]='.';
			break;
		}

		EndLocation.setX(EndLocation.getX());
		EndLocation.setY(EndLocation.getY()-1);
		maze[EndLocation.getX()*w+EndLocation.getY()]='.';

		if(maze[(EndLocation.getX()-1)*w+EndLocation.getY()-1]=='.' && maze[(EndLocation.getX()-2)*w+EndLocation.getY()-1]!='.'  ){
				maze[(EndLocation.getX()-1)*w+EndLocation.getY()]='.';
				break;
		}
		if(maze[(EndLocation.getX()+1)*w+EndLocation.getY()-1]=='.' && maze[(EndLocation.getX()+2)*w+EndLocation.getY()-1]!='.'){
			maze[(EndLocation.getX()+1)*w+EndLocation.getY()]='.';
			break;
		}

	}
	
	//printing the file we are going to use
	ofstream realOut("generatedMaze.txt");
	realOut<<w<<endl;
	realOut<<w<<endl;
	for(int i = 0; i< w;i++){
		for(int j=0 ;j<w; j++){
			realOut<< maze[i*w+j];
		}
		realOut<< endl;
	}
}