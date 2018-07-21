//Madelaine Zinser
//Traveler's Guide- create world Xela with cheese, traps, gold, and monster named FUZZ. Logical AI agent will win the game by dodging traps, avoiding or killing FUZZ, eating cheese, and finding the gold. 
//					Program uses Fuzzy logic to determine road slope and weather conditions that affect the agent's path decisions
//					Agent creates a knowledge base by collecting percepts in a blind environment
//4/12/2016

#include <iostream>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

struct node {
	bool danger, cheese, fuzz, stench, wall, trap, gold, open;
	int roadcond;
	node() {
		danger=0;
		roadcond=0;
	}
};//end struct

struct spot {
	bool stench;
	int prob;
	bool wall;
	bool dead;
	int visited;
	bool glitter;
	int road;
	spot(){
		stench=false;
		prob=0;
		wall=false;
		dead=false;
		visited=0;
		glitter=false;
		road=0;
	}
};


bool getprob(int, int);
void printworld(int y, int x, node world[][37]);
void printkb(int y, int x, spot knob[][37], node world[][37], bool &sre, bool bmp, bool cheese, bool dang, float points);
void initalize(char maze[][37], spot knob[][37], node world[][37], int adjmax[][35], int hmatx[][2]);
void nextstep(int y, int x, int &nx, int &ny, float &sc, spot knob[][37], node world[][37], bool &sre);

int main() {
	const int sz=33;
	int y=1, x=3, nx, ny;
	float SCORE=10000;
	const bool DEBUG=false;
	bool scream=false, bump=false, cheese=false, danger=false;
	unsigned char wall=219, w='w',o=32;
	char maze[sz][37]={w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,o,o,o,w,w,w,w,w,w,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,o,o,o,o,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,o,w,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,o,o,o,w,o,w,w,o,w,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,o,o,o,o,o,o,o,o,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,o,o,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w};
	spot knob[sz][37];
	node world[sz][37];
	int adjmax[35][35]={0,	28,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	28,	0,	2,	0,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	17,
	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	14,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	2,	0,	24,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	24,	0,	0,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	2,	0,	0,	22,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	12,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	5,	22,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	4,	0,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	10,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	16,	0,	0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	16,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	9,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	5,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	3,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	10,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	10,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	10,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	3,
	0,	0,	0,	14,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	12,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	4,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	0,	0,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	2,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	9,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	18,
	0,	0,	17,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	0,	0,	0,	0,	0,	18,	0};
	int hmatx[35][2]={3,1,32,1,35,1,1,3,4,3,27,3,4,6,27,6,32,6,6,18,6,15,6,10,11,17,13,17,16,31,19,31,19,24,9,15,9,17,24,13,24,10,27,10,6,25,9,25,16,15,27,15,32,31,32,16,1,19,4,19,4,25,13,25,13,21,16,21,35,21};
	srand(time(NULL));
	
	initalize(maze, knob, world, adjmax, hmatx);
	//printworld(100,100,world);

	cout<<"##################################\n########  WELCOME TO THE #########\n########                 #########\n####### T R A P H O U S E ########\n##################################\n";
	
	do {
		nextstep(y, x, nx, ny, SCORE, knob, world, scream);

		//You are on a safe road
		if(world[y][x].roadcond==0)
			SCORE--;
		//You are on an okay road
		else if(world[y][x].roadcond==10)
			SCORE-=1.5;
		//You are on a risky road
		else if(world[y][x].roadcond==20)
			SCORE-=3;
	

		//if you hit a wall
		if(world[ny][nx].wall) {
			knob[ny][nx].wall=true;
			bump=true;
		}//end if

		//You are on an unsafe road
		else if(world[y][x].roadcond>=30) {			
		  if(getprob(1,2)) {
			SCORE-=10000;
			cout<<"You died on an unsafe road\n";
		  }//end if
		  else
			  SCORE-=6;
		}//end else if

		else {
			y=ny;
			x=nx;
			knob[y][x].visited++;

			if(world[y][x].danger) {
				int count=0;
				danger=true;
				DEBUG && cout<<"Danger in spot ("<<y<<","<<x<<")\n";

				//check to see how many spots around danger have not been visited
				if(knob[y-1][x].visited==0 && !knob[y-1][x].wall)
					count++;
				if(knob[y][x+1].visited==0 && !knob[y][x+1].wall)
					count++;
				if(knob[y+1][x].visited==0 && !knob[y+1][x].wall)
					count++;
				if(knob[y][x-1].visited==0 && !knob[y][x-1].wall)
					count++;

				//set adjacent locations probability according to number of possibilities for trap
				if(knob[y-1][x].visited==0)
					knob[y-1][x].prob=count;

				if(knob[y][x+1].visited==0)
					knob[y][x+1].prob=count;

				if(knob[y+1][x].visited==0)
					knob[y+1][x].prob=count;

				if(knob[y][x-1].visited==0)
					knob[y][x-1].prob=count;

			}//end if for danger

			if(world[y][x].stench) {
				int count=0;
				DEBUG && cout<<"stench in spot ("<<y<<","<<x<<")\n";

				//set adjacent locations probability according to number of possibilities for stench
				if(knob[y-1][x].visited==0)
					knob[y-1][x].stench=true;

				if(knob[y][x+1].visited==0)
					knob[y][x+1].stench=true;

				if(knob[y+1][x].visited==0)
					knob[y+1][x].stench=true;

				if(knob[y][x-1].visited==0)
					knob[y][x-1].stench=true;

			}//end if for stench

			//did you find gold?
			else if(world[y][x].gold) {
				cout<<"*\n************************************\nGOLD!!!!!! Congrats you won!!\n***************************************\n";
				SCORE+=10000;
				world[y][x].gold=false;
				knob[y][x].glitter=true;
			}//end else if

			//did you run into FUZZ?
			else if(world[y][x].fuzz) {
				SCORE-=10000;
				cout<<"\nACTION: you ran into FUZZ\n";
				world[y][x].fuzz=false;
			}//end else if

			//did you run into a trap?
			else if(world[y][x].trap) {
				SCORE-=10000;
				cout<<"\nACTION: you ran into a trap\n";
				world[y][x].trap=false;
			}//end else if

			//see if there is cheese
			else if(world[y][x].cheese) {
				cheese=true;
				SCORE+=2;
				cout<<"\nACTION: Found cheese!!\n";
				world[y][x].cheese=false;
			}//end else if

			//set dead ends to not backtrack into bad paths and save steps
			if((knob[y-1][x].wall && knob[y][x+1].wall && knob[y+1][x].wall) ||(knob[y][x-1].wall && knob[y+1][x].wall && knob[y][x+1].wall) || (knob[y-1][x].wall && knob[y][x-1].wall && knob[y+1][x].wall) ||(knob[y][x-1].wall && knob[y-1][x].wall && knob[y][x-1].wall))
				knob[y][x].dead=true;

		}//end else

		printkb(y,x, knob, world, scream, bump, cheese, danger, SCORE);
		system("pause");
		bump=false;
		cheese=false;
		danger=false;
	}while(SCORE>0  && SCORE <15000);

	
	return 0;
}//end main


void nextstep(int y, int x, int & nx, int & ny, float &sc, spot knob[][37], node world[][37], bool &sre) {
	const bool DBG=true;
	static bool stick=true, arrow=true;
	int right=0, down=0, left=0, up=0;
	
	//find risk of going right 
	(knob[y][x+1].wall)? right+=100000 : right+=0;
	(knob[y][x+1].dead)? right+=100000 : right+=0;
	(knob[y][x+1].stench)? right+=1050 : right+=0;
	right=right+knob[y][x+1].visited+knob[y][x+1].prob+world[y][x+1].roadcond;

	//find risk of going down 
	(knob[y+1][x].wall)? down+=100000 : down+=0;
	(knob[y+1][x].dead)? down+=100000 : down+=0;
	(knob[y+1][x].stench)? down+=1050 : down +=0;
	down=down+knob[y+1][x].visited+knob[y+1][x].prob+world[y+1][x].roadcond;

	//find risk of going left 
	(knob[y][x-1].wall)? left+=100000 : left+=0;
	(knob[y][x-1].dead)? left+=100000 : left+=0;
	(knob[y][x-1].stench)? left +=1050 : left+=0;
	left=left+knob[y][x-1].visited+knob[y][x-1].prob+world[y][x-1].roadcond;

	//find risk of going up 
	(knob[y-1][x].wall)? up+=100000 : up+=0;
	(knob[y-1][x].dead)? up+=100000 : up+=0;
	(knob[y-1][x].stench)? up+=1050 : up+=0;
	up=up+knob[y-1][x].visited+knob[y-1][x].prob+world[y-1][x].roadcond;
	
	int a[4] = {right, down, left, up};

	sort(a, a+4);

	//figure out which adjacent spot is the lowest risk factor
	if(a[0]==right) {
		ny=y;
		nx=x+1;
		DBG && cout<<"\nACTION: go right\n";
	}//end if
	else if(a[0]==down) {
		ny=y+1;
		nx=x;
		DBG && cout<<"\nACTION: go down";
	}//end if
	else if(a[0]==left) {
		ny=y;
		nx=x-1;
		DBG && cout<<"\nACTION: go left";
	}//end if
	else if(a[0]==up) {
		ny=y-1;
		nx=x;
		DBG && cout<<"\nACTION: go up";
	}//end if

	if(stick) {
		if((knob[ny][nx].prob>0 && knob[ny][nx].prob>0 && knob[ny][nx].prob>0) ||(knob[ny][nx].prob>0 && knob[ny][nx].prob>0 && knob[ny][nx].prob>0) || (knob[ny][nx].prob>0 && knob[ny][nx].prob>0 && knob[ny][nx].prob>0) ||(knob[ny][nx].prob>0 && knob[ny][nx].prob>0 && knob[ny][nx].prob>0)) {
		stick=false;
		cout<<"\nACTION: threw stick\n";
		sc-=5;
			if(world[ny][nx].trap) {
				cout<<"\nACTION: You set off the trap! it is safe now\n";
				world[ny][nx].trap=false;
				world[ny][nx+1].danger=false;
				world[ny+1][nx].danger=false;
				world[ny][nx-1].danger=false;
				world[ny-1][nx].danger=false;
				knob[y][x+1].prob=0;
				knob[y+1][x].prob=0;
				knob[y][x-1].prob=0;
				knob[y-1][x].prob=0;
			}//end if
			
		}//end if
	}//end if

	if(arrow) {
		if((knob[ny][nx].stench && knob[ny][nx].stench && knob[ny][nx].stench) ||(knob[ny][nx].stench && knob[ny][nx].stench && knob[ny][nx].stench) || (knob[ny][nx].stench && knob[ny][nx].stench && knob[ny][nx].stench) ||(knob[ny][nx].stench && knob[ny][nx].stench && knob[ny][nx].stench)) {
		arrow=false;
		cout<<"\nACTION: threw arrow\n";
		sc-=5;
			if(world[ny][nx].trap) {
				cout<<"\nACTION: you killed FUZZ\n";
				sre=true;
				world[ny][nx].fuzz=false;
				world[ny][nx+1].stench=false;
				world[ny+1][nx].stench=false;
				world[ny][nx-1].stench=false;
				world[ny-1][nx].stench=false;
			}//end if
		}//end if
	}//end if
}//end nextstep

void printkb(int y, int x, spot knob[][37], node world[][37], bool &sre, bool bmp, bool cheese, bool dang, float points) {
//INPUT:
//OUTPUT:
//PURPOSE:
	unsigned char w=219;

	cout<<"\n+";
	//prints out location lables on the side
	for(int k=0; k<37; k++)
		cout<<k%10;
	cout<<endl;

	for(int i=0; i<33; i++) {
		cout<<i%10;								//prints lables on side

		for(int j=0; j<37; j++) {
			if(i==y && j==x)
				cout<<'X';						 //prints mouse location

			//found stench in KB
			else if(knob[i][j].stench)			
				cout<<"S";

			//found a wall
			else if(knob[i][j].wall) 
				cout<<w;

			else if(!knob[i][j].prob==0)
				cout<<knob[i][j].prob;
			else 
				cout<<" ";
			if(i==32 && j==36) {
				cout<<"\n\nLegend: (stench, bump, danger, aroma, glitter, scream)\nPercepts: (";
				(knob[i][j].stench)? cout<<"stench," : cout<<"none,";
				(bmp)? cout<<" bump," : cout<<" none,";
				(dang)? cout<<" danger," : cout<<" none,";
				(cheese)? cout<<" aroma," : cout<<" none,";
				(knob[i][j].glitter)? cout<<" glitter," : cout<<" none,";
				(sre)? cout<<" scream)" : cout<<" none)";
				cout<<"\nDanger prob in maze is indicated as 1/X\n";
				cout<<"Road condition is: ";
				if(knob[i][j].road==0)
				  cout<<"SAFE\n";
				else if(knob[i][j].road==10)
				  cout<<"OK\n";
				else if(knob[i][j].road==20)
				  cout<<"RISKY\n";
				else if(knob[i][j].road==30)
				  cout<<"UNSAFE\n";
				cout<<"SCORE: "<<points<<endl;
			}//end if
		}//end for
		cout<<endl;
	}//end for

	
}//end printkb 

void printworld(int y, int x, node world[][37]){
//INPUT: none
//OUTPUT: none
//PURPOSE: print characters in world matrix accordingly
	unsigned char wall=219;
	cout<<'X';
	for(int k=0; k<37; k++)
		cout<<k%10;
	cout<<endl;
	for(int i=0; i<33; i++) {
		cout<<i%10;
		for(int j=0; j<37; j++) {
			if(i==y && j==x)
				cout<<'X';
			else if(world[i][j].danger) 
				cout<<"d";
			else if(world[i][j].cheese) {
				if(world[i][j].trap)
					cout<<"t";
				else
					cout<<"c";
			}//end if
			else if(world[i][j].fuzz)
				cout<<"F";
			else if(world[i][j].stench)
				cout<<"s";
			else if(world[i][j].wall)
				cout<<wall;
			else if(world[i][j].gold)
				cout<<'G';
			else				//if(world[i][j].open==true)
				cout<<" ";
		}//end for
		cout<<endl;
	}//end for
}//end print

bool getprob(int c, int max) {
//INPUT: upper limit on random number generator (1-max) and number that represents upper limit on acceptance
//OUTPUT: boolean to accept probability or not
//PURPOSE: calculate probability and determine acceptance
	bool retval;
	int val;
	val=rand()%max+1;
	//cout<<"value should be less than "<<c<<"\t"<<val<<endl;
	if(val<=c)
		retval=true;
	else 
		retval=false;
	return retval;
}//end getprob

void initalize(char maze[][37], spot knob[][37], node world[][37], int adjmax[][35], int hmatx[][2]) {
//INPUT: none
//OUTPUT: none
//PURPOSE: create node world from existing maze matrix. set all variables in accordance to an open spot or a wall. use probability to 
//		   put cheese, traps, FUZZ, and gold in locations. set danger and stench in adjacent locations
	srand(time(NULL));
	const bool DEBUG=false;
	int randx, randy, node1x,node1y, node2x, node2y;
	bool set=false;
	unsigned char w=219;	
	float Down=0.0, Level=0.0, Up=0.0, Clear=0.0, Rain=0.0, Ice=0.0, Snow=0.0, safety=0;
	float a1,b1,c1,a2,b2,c2,a3,b3,c3,a4,b4,c4,r;
	
	for(int i=0; i<33; i++) {
		for(int j=0; j<37; j++) {
			if(maze[i][j]=='w') {
				world[i][j].danger=false;
				world[i][j].cheese=false;
				world[i][j].fuzz=false;
				world[i][j].stench=false;
				world[i][j].wall=true;
				world[i][j].trap=false;
				world[i][j].gold=false;
				world[i][j].open=false;
			}//end if
			else if(maze[i][j]==' ') {
				world[i][j].danger=false;
				world[i][j].cheese=false;
				world[i][j].fuzz=false;
				world[i][j].stench=false;
				world[i][j].wall=false;
				world[i][j].trap=false;
				world[i][j].gold=false;
				world[i][j].open=true;
			}
		}//end for
	}//end for


	//Initialize cheese and trap
	for(int i=0; i<33; i++) {
		for(int j=0; j<37; j++) {
			if(getprob(10, 100) && !(i==1 && j==3)) {		//if 10% chance of cheese in location
				if(world[i][j].open==true) { 
					world[i][j].cheese=true;
					world[i][j].open=false;
					if(getprob(10, 100)) {	//if 50% chance of trap with cheese
						world[i][j].trap=true;
						if(world[i-1][j].wall==false) {	//set above danger to true if there is not a wall
							world[i-1][j].danger=true;
							world[i-1][j].open=false;
							DEBUG && cout<<"Went up\n";
						}
						if(world[i][j-1].wall==false) {	//set left danger to true if there is not a wall
							world[i][j-1].danger=true;
							world[i][j-1].open=false;
							DEBUG && cout<<"Went left\n";
						}
						if(world[i][j+1].wall==false) {	//set right danger to true if there is not a wall
							world[i][j+1].danger=true;
							world[i][j+1].open=false;
							DEBUG && cout<<"Went right\n";
						}
						if(world[i+1][j].wall==false) {	//set down danger to true if there is not a wall
							world[i+1][j].danger=true;
							world[i+1][j].open=false;
							DEBUG && cout<<"Went down\n";
						}
					}//end if
				}//end if
			}//end if	
		}//end for
	}//end for

	//Initalize FUZZ
	do{
		randy=rand()%33;
		randx=rand()%37;
		if(world[randy][randx].open) {
			world[randy][randx].fuzz=true;
			if(world[randy-1][randx].wall==false) {	//set above danger to true if there is not a wall
				world[randy-1][randx].stench=true;
			}
			if(world[randy][randx-1].wall==false) {	//set left danger to true if there is not a wall
				world[randy][randx-1].stench=true;
			}
			if(world[randy][randx+1].wall==false) {	//set right danger to true if there is not a wall
				world[randy][randx+1].stench=true;
			}
			if(world[randy+1][randx].wall==false) {	//set down danger to true if there is not a wall
				world[randy+1][randx].stench=true;
			}
			set=true;
		}//end if
	}while(!set);


	//Initalize Gold

	world[25][6].gold=true;
	world[25][6].open=false;
	world[25][6].cheese=false;
	world[25][6].danger=false;
	world[25][6].fuzz=false;
	world[25][6].stench=false;
	world[25][6].trap=false;
	world[25][6].wall=false;

	for(int i=0; i<35; i++){
		for(int j=0; j<35; j++) {
			if(adjmax[i][j]>0) {				//calculate road condition if there is a path

				r=rand()%901;
				r=(r-450)/10;

				a1=-45.0, b1=-44.9, c1=-5.0, a2=-10.0, b2=0.0, c2=10.0, a3=5.0, b3=44.9, c3=45.0;
				//Set probabilities for Down, Level, and UP road conditions
				if(r>=a1 && r<=b1)				//going up the first triangle
					Down=(r-a1)/(b1-a1);
				else if(r>=b1 && r<=a2)			//going down the first triangle
					Down=(r-c1)/(b1-c1);
				else if(r>a2 && r<c1) {			//intersection between first and second triangle
					Down=(r-c1)/(b1-c1);
					Level=(r-a2)/(b2-a2);
				}//end else if
				else if(r>=c1 && r<=b2)			//going up the second triangle
					Level=(r-a2)/(b2-a2);
				else if(r>b2 && r<=a3)			//going down the second triangle
					Level=(r-c2)/(b2-c2);
				else if(r>a3 && r<=c2) {		//intersection between second and third triangle
					Level=(r-c2)/(b2-c2);
					Up=(r-a3)/(b3-a3);
				}//end else if
				else if(r>c2 && r<=b3)			//going up the third triangle
					Up=(r-a3)/(b3-a3);
				else if(r>b3 && r<=c3)			//going down the third triangle
					Up=(r-c3)/(b3-c3);


				//Set probabilities for weather
				a1=0, b1=20, c1=3, a2=18, b2=40, c2=58, a3=40, b3=60, c3=81, a4=68, b4=88, c4=100;

				r=rand()%101;
				if(r>=a1 && r<=b1)				//going up first triangle
					Clear=(r-a1)/(b1-a1);
				else if(r>a2 && r<=b1) {		//first intersection between first and second triangles
					Clear=(r-a1)/(b1-a1);
					Rain=(r-a2)/(b2-a2);
				}//end else if
				else if(r>b1 && r<=c1) {		//second intersection between first and second triangles 
					Clear=(r-c1)/(b1-c1);
					Rain=(r-a2)/(b2-a2);
				}//end else if
				else if(r>c1  && r<=b2)			//going up second triangle
					Rain=(r-a2)/(b2-a2);
				else if(r>a3 && r<=c2) {		//intersection between second and third triangles
					Rain=(r-c2)/(b2-c2);
					Ice=(r-a3)/(b3-a3);
				}//end else if
				else if(r>c2 && r<=b3)			//going up third triangle
					Ice=(r-a3)/(b3-a3);
				else if(r>b3 && r<=a4)			//going down third triangle
					Ice=(r-c3)/(b3-c3);
				else if(r>a4 && r<=c3) {		//intersection between third and fourth triangles
					Ice=(r-c3)/(b3-c3);
					Snow=(r-a4)/(b4-a4);
				}//end else if
				else if(r>c3 && r<=b4)			//going up fourth triangle
					Snow=(r-a4)/(b4-a4);
				else if(r>b4 && r<=c4)			//going down fourth triangle
					Snow=(r-c4)/(b4-c4);

				//Check final road condition
				if(Clear>0.6)
					safety=0;
				else if(Rain<0.9 && Level>0.5)
					safety=0;
				else if(Rain>0.85 && Up>0.8)
					safety=10;
				else if(Rain>0.85 && Down>0.9)
					safety=10;
				else if(Snow>0.9 && Level>0.75)
					safety=10;
				else if(Snow>0.9 && Up>0.85)
					safety=20;
				else if(Snow>0.8 && Down>0.65)
					safety=30;
				else if(Ice>0.8)
					safety=30;
				else
					safety=0;


				//set road condition for all spots between nodes
				node1x=hmatx[i][0];
				node1y=hmatx[i][1];
				node2x=hmatx[j][0];
				node2y=hmatx[j][1];

				if(node1x==node2x) {
					for(int q=node1y; q<=node2y; q++) 
						world[q][node1x].roadcond=safety;
				}//end if

				else if(node1y==node2y) {
					for(int q=node1x; q<=node2x; q++) 
						world[node1y][q].roadcond=safety;
				}//end if
				

				Down=0.0;
				Level=0.0;
				Up=0.0;
			}//end if(adjmax)
		}//end for j
	}//end for i



}//end initalize
