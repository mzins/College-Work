//Madelaine Zinser
//Traveler's Guide- create world Xela with cheese, traps, gold, and monster named FUZZ. AI agent will win the game by dodging traps, avoiding or killing FUZZ, eating cheese, and finding the gold. 
//					Agent creates a knowledge base by collecting percepts in a blind environment
//4/7/2016

#include <iostream>
#include <ctime>
#include <iomanip>
#include <stack>
using namespace std;

struct node {
	bool danger, cheese, fuzz, stench, wall, trap, gold, open;
};//end struct
struct cord {
	int x,y;
};
struct spot {
	bool stench;
	int prob;
	bool wall;
	bool dead;
	int visited;
	spot(){
		stench=false;
		prob=0;
		wall=false;
		dead=false;
		visited=0;
	}
};

unsigned char wall=219, w='x', o=32;
char maze[33][37]={w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,o,o,o,w,w,w,w,w,w,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,o,o,o,o,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,o,w,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,o,o,o,w,o,w,w,o,w,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,o,o,o,o,o,o,o,o,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,o,o,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w};
spot knob[33][37];

node world[33][37];

bool getprob(int, int);
void printworld();
void initalize();
void nextstep(int y, int x, stack <cord> &p);

int main() {
	stack <cord> path;
	cord next;
	initalize();
	int x=3, y=1, nextx=0, nexty=0;
	do {
		nextstep(y, x, path);
		next=path.top();
		cout<<"Next location is ("<<y<<","<<x<<") \n\n";
		y=next.y;
		x=next.x;
		if(world[y][x].danger) {
			cout<<"Danger\n\n";
			knob[y][x].prob=1;
		}
		if(world[y][x].wall){
			cout<<"In a wall\n\n";
			knob[y][x].wall=true;
		}


		system("pause");
	}while(x>0);

	

	return 0;
}//end main

void nextstep(int y, int x, stack <cord> &p) {
	cord nxt;
	if(!knob[y][x+1].visited && !world[y][x+1].wall && !knob[y][x+1].dead && x<35) {
		nxt.y=y;
		nxt.x=x+1;
		p.push(nxt);
		cout<<"Went right\n";
	}
	else if(!knob[y+1][x].visited && !world[y+1][x].wall && !knob[y+1][x].dead && y<31) {
		nxt.y=y+1;
		nxt.x=x;
		p.push(nxt);
		cout<<"Went down\n";

	}
	else if(!knob[y][x-1].visited && !world[y][x-1].wall && !knob[y][x-1].dead && x>0) {
		nxt.y=y;
		nxt.x=x-1;
		p.push(nxt);
		cout<<"Went left\n";
	}
	else if(!knob[y-1][x].visited && !world[y-1][x].wall && !knob[y-1][x].dead && y>0) {
		nxt.y=y-1;
		nxt.x=x;
		p.push(nxt);
		cout<<"Went up\n";
	}
	else {
		if(world[y][x+1].wall || world[y+1][x].wall || world[y][x-1].wall || world[y-1][x].wall)
			cout<<"Hit a wall\n";
		p.pop();
		cout<<"*********************have to backtrack*********************\n";
	}//end else
}//end nextstep

void initalize() {
//INPUT: none
//OUTPUT: none
//PURPOSE: create node world from existing maze matrix. set all variables in accordance to an open spot or a wall. use probability to 
//		   put cheese, traps, FUZZ, and gold in locations. set danger and stench in adjacent locations
	srand(time(NULL));
	const bool DEBUG=false;
	int randx, randy;
	bool set=false;
	
	for(int i=0; i<33; i++) {
		for(int j=0; j<37; j++) {
			if(maze[i][j]==w) {
				world[i][j].danger=false;
				world[i][j].cheese=false;
				world[i][j].fuzz=false;
				world[i][j].stench=false;
				world[i][j].wall=true;
				world[i][j].trap=false;
				world[i][j].gold=false;
				world[i][j].open=false;
			}//end if
			else if(maze[i][j]==o) {
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
			if(getprob(10, 100)) {		//if 10% chance of cheese in location
				if(world[i][j].open==true) { 
					world[i][j].cheese=true;
					world[i][j].open=false;
					if(getprob(50, 100)) {	//if 50% chance of trap with cheese
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
	set=false;
	do{
		randy=rand()%33;
		randx=rand()%37;
		if(world[randy][randx].open) {
			world[randy][randx].gold=true;
			world[randy][randx].open=false;
			set=true;
		}//end if
	}while(!set);
	
	
	cout<<endl;
	printworld();
	
}//end initalize

void printworld(){
//INPUT: none
//OUTPUT: none
//PURPOSE: print characters in world matrix accordingly
	unsigned char w=219;
	cout<<'X';
	for(int k=0; k<37; k++)
		cout<<k%10;
	cout<<endl;
	for(int i=0; i<33; i++) {
		cout<<i%10;
		for(int j=0; j<37; j++) {
			if(world[i][j].danger==true) 
				cout<<"d";
			else if(world[i][j].cheese==true) {
				if(world[i][j].trap==true)
					cout<<"t";
				else
					cout<<"c";
			}//end if
			else if(world[i][j].fuzz==true)
				cout<<"F";
			else if(world[i][j].stench==true)
				cout<<"s";
			else if(world[i][j].wall==true)
				cout<<w;
			else if(world[i][j].gold==true)
				cout<<'G';
			else				//if(world[i][j].open==true)
				cout<<o;
		}//end for
		cout<<endl;
	}//end for
	system("pause");
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