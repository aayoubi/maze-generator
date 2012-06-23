#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;

#include "Maze.h"

int main(){
	
	cout<<"THE GENERATED MAZE:\n"<<endl;
	Maze m;
	m.generate();

	/*Read From file*/
	ifstream in("generatedMaze.txt");
	if(!in){
		cout<< "Cannot open file.\n";
		return 1;
	}
	//first two lines of the file should contain the size of the maze
	int w, h;
	in>>w;
	in>>h;

	cout<<"Size:"<<w<<"*"<<h<<endl<<endl;
	
	char *mazePointer = (char*)malloc(w*h*sizeof(char));
	
	for(int i = 0; i< w;i++){
		for(int j=0 ;j<h; j++){
			in>> mazePointer[i*w+j];
		}
	}	
	in.close();


	for(int i = 0; i< w;i++){
		for(int j=0 ;j<h; j++){
			cout<< mazePointer[i*w+j];
		}
		cout<< endl;
	}
	
	cout<<endl<<endl;
	
	Position s;
	Position e;

	for(int i=0;i <w;i++){
		if(mazePointer[i*w+0] == '.'){
			s.setX(i);
			s.setY(0);
		}
	}
	for(int i=0;i <w;i++){
		if(mazePointer[i*w+(w-1)] == '.'){
			e.setX(i);
			e.setY(w-1);
		}
	}
	
	
	cout<<"THE SOLVED MAZE:\n"<<endl;
	usleep(1000*1000);
	Maze maze(mazePointer, s , e, w, h);
	maze.traverse();
	
	for(int i = 0; i< w;i++){
		for(int j=0 ;j<h; j++){
			cout<< mazePointer[i*w+j];
		}
		cout<< endl;
	}
	
	

	return 0;

}