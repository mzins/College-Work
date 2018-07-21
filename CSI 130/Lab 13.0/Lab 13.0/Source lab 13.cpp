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





int main()
{
	ifstream ifp;
	string  Token;
	char lexem[200];
	ifp.open("C:\\Users\\mrzinser\\Desktop\\text.txt");
	if (!ifp)
		cout << "File Opening Error.";
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

	return 0;
}
