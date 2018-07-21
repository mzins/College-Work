//Madelaine Zinser
//Traveler's Guide- create world Xela with cheese, traps, gold, and monster named FUZZ. Logical AI agent will win the game by dodging traps, avoiding or killing FUZZ, eating cheese, and finding the gold. 
//					Agent creates a knowledge base by collecting percepts in a blind environment
//4/7/2016

#include <iostream>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

struct node {
	bool danger, cheese, fuzz, stench, wall, trap, gold, open;
	node() {
		danger=0;
	}
};//end struct

struct spot {
	bool stench;
	int prob;
	bool wall;
	bool dead;
	int visited;
	bool glitter;
	spot(){
		stench=false;
		prob=0;
		wall=false;
		dead=false;
		visited=0;
		glitter=false;
	}
};


bool getprob(int, int);
void printworld(int y, int x, node world[][37], int size);
void printkb(int y, int x, spot knob[][37], node world[][37], int size, bool &sre, bool bmp, bool cheese, bool dang);
void initalize(char maze[][37], spot knob[][37], node world[][37], int size);
void nextstep(int y, int x, int &nx, int &ny, int &sc, spot knob[][37], node world[][37], int size, bool &sre);

int main() {
	const int sz=33;
	int y=1, x=3, nx, ny, SCORE=10000;
	const bool DEBUG=false;
	bool scream=false, bump=false, cheese=false, danger=false;
	unsigned char wall=219, w='x', o=32;
	char maze[33][37]={w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,o,o,o,w,w,w,w,w,w,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,o,o,o,o,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,w,w,o,w,o,w,w,o,w,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,o,o,o,o,w,o,w,w,o,w,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,o,w,w,o,w,w,w,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,o,o,o,o,o,o,o,o,o,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,w,w,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,o,o,o,o,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w};
	spot knob[33][37];
	node world[33][37];
	cout<<"##################################\n########  WELCOME TO THE #########\n########                 #########\n####### T R A P H O U S E ########\n##################################\n";
	initalize(maze, knob, world, sz);
	do {
		nextstep(y, x, nx, ny, SCORE, knob, world, sz, scream);
		SCORE--;

		DEBUG && cout<<"Current location is ("<<y<<","<<x<<") \n";		

		//printworld(y,x, world, sz);
		DEBUG && cout<<"Next location is ("<<ny<<","<<nx<<") \n";

		//if you hit a wall
		if(world[ny][nx].wall) {
			knob[ny][nx].wall=true;
			bump=true;
		}//end if
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

		printkb(y,x, knob, world, sz, scream, bump, cheese, danger);
		system("pause");
		bump=false;
		cheese=false;
		danger=false;
	}while(SCORE>0  && SCORE <15000);

	
	return 0;
}//end main

void nextstep(int y, int x, int & nx, int & ny, int &sc, spot knob[][37], node world[][37], int size, bool &sre) {
	const bool DBG=true;
	static bool stick=true, arrow=true;
	int right=0, down=0, left=0, up=0;
	
	//find risk of going right 
	(knob[y][x+1].wall)? right+=1000 : right+=0;
	(knob[y][x+1].dead)? right+=1000 : right+=0;
	(knob[y][x+1].stench)? right+=1050 : right+=0;
	right=right+knob[y][x+1].visited+(knob[y][x+1].prob);

	//find risk of going down 
	(knob[y+1][x].wall)? down+=1000 : down+=0;
	(knob[y+1][x].dead)? down+=1000 : down+=0;
	(knob[y+1][x].stench)? down+=1050 : down +=0;
	down=down+knob[y+1][x].visited+(knob[y+1][x].prob);

	//find risk of going left 
	(knob[y][x-1].wall)? left+=1000 : left+=0;
	(knob[y][x-1].dead)? left+=1000 : left+=0;
	(knob[y][x-1].stench)? left +=1050 : left+=0;
	left=left+knob[y][x-1].visited+(knob[y][x-1].prob);

	//find risk of going up 
	(knob[y-1][x].wall)? up+=1000 : up+=0;
	(knob[y-1][x].dead)? up+=1000 : up+=0;
	(knob[y-1][x].stench)? up+=1050 : up+=0;
	up=up+knob[y-1][x].visited+(knob[y-1][x].prob);
	
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

void printkb(int y, int x, spot knob[][37], node world[][37], int size, bool &sre, bool bmp, bool cheese, bool dang) {
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
			}//end if
		}//end for
		cout<<endl;
	}//end for

	
}//end printkb 

void printworld(int y, int x, node world[][37], int size){
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
			if(i==y && j==x)
				cout<<'X';
			else if(world[i][j].danger==true) 
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

void initalize(char maze[][37], spot knob[][37], node world[][37], int size) {
//INPUT: none
//OUTPUT: none
//PURPOSE: create node world from existing maze matrix. set all variables in accordance to an open spot or a wall. use probability to 
//		   put cheese, traps, FUZZ, and gold in locations. set danger and stench in adjacent locations
	srand(time(NULL));
	const bool DEBUG=false;
	int randx, randy;
	bool set=false;
	unsigned char w=219;
	
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


}//end initalize
