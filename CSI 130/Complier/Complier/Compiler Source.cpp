//Madelaine Zinser
//Lab 13
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct SymTab
{
	string identifier;
	int address;
};

void SymbolTable(string id, int act)
{
	static SymTab st[15];
	static int addr = 255, i = 0;
	int j = 0;


	if (act == 1)
	{
		st[i].identifier = id;
		st[i].address = addr;
		i = i + 1;
		addr = addr - 1;
	}


	if (act == 2)
	{
		for (j = 0; j<i; j = j + 1)
		if (id == st[j].identifier)
			cout << st[j].identifier << endl << st[j].address << endl << j << endl;

	}

}

//parser function
//input: ifp-input file of source code: prog[]-array for target code
//output: returns prog[] as a reference parameter
//purpose: main parser functuon calls statementList()

void parser( ifstream & ifp, string prog[])
{
	statementList (ifp, prog);
}

void statementList (ifstream &ifp, string prog[])
{
	string token;
	char lexeme[5];
	int safe=1;
	scanner (ifp, token, lexeme);
	while (token != "eofToken" && token !="errorToken" && safe==1)
	{
		safe = statement(ifp, prog, token, lexeme);
		scanner(ifp, token, lexeme);

	}
	if (token=="eofToken")
		CodeGenerator (prog, "HALT", lexeme);

}

int statement (ifstream & ifp, string prog[], string token, char lexeme[])
{
	int safe;
	if (token =="intToken")
		safe==varDec(ifp, prog,token);

	else if(token=="varToken")
		safe== addAssignOP(ifp, prog, token, lexeme);

	else if (token=="ifToken")
		safe= ifStatemetn(ifp, prog, token);
	else 
	{
		cout<<"Syntax Error in Statement!"<<endl;
		safe=0;
	}
	return safe;
}

int varDec (ifstream & ifp, string prog[], string token)
{
	char lexeme[20]={' '};
		int safe=1;
	safe= match (token, "decToken");
	scanner (ifp, token, lexeme);
	safe = match (token, "varToken");
	if (safe)
		SymbolTable (lexeme, 1);
	scanner(ifp, token, lexeme);
	safe= match(token, "eolToken");
	return safe;
}

int relExpr (ifstream &ifp, string prog[], string token, char lex[])
{
	int safe=0; 
	CodeGenerator (prog, "LDID", lex);
	safe= //ENDED HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
int main()															//Scanner Function
{
	string  Token;
	string program[512];
	ifstream ifp;
	ofstream ofp;
		ofp.open ("C:\\Users\\mrzinser\\Desktop\\text.txt");
		ifp.open ("C:\\Users\\mrzinser\\Desktop\\SCRAP.txt");
		if (!ifp)
		cout << "File Opening Error.";
	parser (ifp, program);
	for(int i=0; i<50; ++i)
		ofp<<program[i]<<endl;
	return 0;
}

void scanner(ifstream & ifp, string &Token, char lexem[])
{
	char c = ' ';
	int i = 0;
	Token = "errorToken";

	while(c != '#')
	{
		
										cout << " c: " << c << endl; //Debug
		while (!isprint(c) || isspace(c))
		{
			c = ifp.get();				
		}
		lexem[i++] = c;


		if (c >= 'A' && c <= 'Z')
		{
			while (c >= 'A' && c <= 'Z')
			{
				lexem[i++] = c;
				c = ifp.get();		
			}
			Token = "varToken"; 		cout << Token << endl; //Debug
			ifp.putback(c);
		}

		else if (c == '+')
		{
			Token = "addToken"; 		cout << Token << endl; //Debug
		}

		else if (c == '#')
		{
			Token = "endofToken"; 		cout << Token << endl; //Debug
		}

		else if (c == '=')
		{
			Token = "assignToken"; 		cout << Token << endl; //Debug
			
		}

		else if (c == '==')
		{
			Token = "equalityToken"; 		cout << Token << endl; //Debug
		}

		else if (c == '(')
		{
			Token = "LparenToken"; 		cout << Token << endl; //Debug
		}

		else if (c == ')')
		{
			Token = "RparenToken"; 		cout << Token << endl; //Debug
		}

		else if (c == '.')
		{
			Token = "eolToken"; 		cout << Token << endl; //Debug
		}

		else if (c == '&')
		{
			Token = "andToken"; 		cout << Token << endl; //Debug
		}

		else if (c == '|')
		{
			Token = "orToken"; 		cout << Token << endl; //Debug
		}

		else if (c == 'i')
		{
			c = ifp.get();
			if (c == 'f')
			{
				lexem[i++] = c;
				Token = "ifToken";
				cout << Token << endl; //Debug
			}
			else if (c == 'n')
			{
				lexem[i++] = c;
				c = ifp.get();
				if (c == 't')
				{
					lexem[i++] = c;
					c = ifp.get();
				}
				if (c == 'e')
				{
					lexem[i++] = c;
					c = ifp.get();
				}
				if (c == 'g')
				{
					lexem[i++] = c;
					c = ifp.get();
				}
				if (c == 'e')
				{
					lexem[i++] = c;
					c = ifp.get();
				}
				if (c == 'r')
				{
					lexem[i++] = c;
					Token = "integerToken";
					cout << Token << endl; //Debug
				}
			}
			
		}
		else if (c >= '0' && c <= '9')
		{
			while (c >= 48 && c <= 57)
			{
				c = ifp.get();
				lexem[i++] = c;
			}
			Token = "intToken";		cout << Token << endl; //Debug
			--i;
			ifp.putback(c);
		}

		else if (c == 's')
		{
			lexem[i++] = c;
			c = ifp.get();
			if (c == 't')
			{
				lexem[i++] = c;
				c = ifp.get();
				if (c == 'o')
				{
					lexem[i++] = c;
					c = ifp.get();
					if (c == 'p')
					{
						lexem[i++] = c;
						Token = "stopToken"; 		cout << Token << endl; //Debug
					}
				}
				else if (c == 'a')
				{
					lexem[i++] = c;
					c = ifp.get();
					if (c == 'r')
					{
						lexem[i++] = c;
						c = ifp.get();
						if (c == 't')
						{
							lexem[i++] = c;
							Token = "beginToken"; 		cout << Token << endl; //Debug
						}
					}
				}
			}

			else
			{
				Token = "varToken"; 		cout << Token << endl; //Debug
				ifp.putback(c);
			}
		}

		else
		{
			cout << "Unknown Character \n" << c << endl;
			Token = "errorToken"; 		cout << Token << endl; //Debug
		}
		lexem[i] = '\0';
		
	c = ifp.get();	
	}
}
