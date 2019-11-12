#include <iostream>
#include <stack>
#include"LT.h"
#include"IT.h"
#include "PolishNotation.h"

using namespace std;

bool PolishNotation( LT::LexTable& lextable)
{
	stack<LT::Entry> stack1;
	stack<LT::Entry> stack2;
	stack<LT::Entry> stack3;
	
	char PolMass[5];
	bool ostalsa = true;
	
	int	k=0,saveravno=0,konec=0;	

	for (int i = 0; i < lextable.size; i++)
	{

		if (lextable.table[i].lexema[0] == '=')
		{
			k = 0;
			LT::Entry*mass = new LT::Entry [50];
			saveravno = i;
			stack1.push(lextable.table[i]);
			i++;


			while (lextable.table[i - 1].lexema[0] != ';')
			{

				if (lextable.table[i].lexema[0] == 'i' || lextable.table[i].lexema[0] == 'l')
				{
					stack2.push(lextable.table[i]);
				}
				else
				{
					while (ostalsa == true)
					{

						LT::Entry temp = stack1.top();
						switch (lextable.table[i].znak[0])
						{
						case '+': case '-':
						{
							if (temp.lexema[0] == '=')
							{
								stack1.push(lextable.table[i]);
								ostalsa = false;
							}
							else if (stack1.top().znak[0] == '+' || stack1.top().znak[0] == '-' || stack1.top().znak[0] == '*' || stack1.top().znak[0] == '/')
							{
								stack2.push(lextable.table[i]);
								stack1.pop();
								ostalsa = true;
							}
							else if (temp.lexema[0] == '(')
							{
								stack1.push(lextable.table[i]);
								ostalsa = false;
							}


						}break;
						case '*': case '/':
						{
							if (temp.lexema[0] == '=')
							{
								stack1.push(lextable.table[i]);
								ostalsa = false;

							}
							else if (stack1.top().znak[0] == '+' || stack1.top().znak[0] == '-' || stack1.top().znak[0] == '(')
							{
								stack1.push(lextable.table[i]);
								ostalsa = false;
							}
							else if (stack1.top().znak[0] == '*' || stack1.top().znak[0] == '/')
							{
								stack2.push(stack1.top());
								stack1.pop();
								ostalsa = true;
							}
						}break;
						case '(':
						{
							if (temp.lexema[0] == '=')
							{
								stack1.push(lextable.table[i]);
								ostalsa = false;
							}
							else if (stack1.top().znak[0] == '+' || stack1.top().znak[0] == '-' || stack1.top().znak[0] == '*' || stack1.top().znak[0] == '/')
							{
								stack1.push(lextable.table[i]);
								ostalsa = false;
							}
							else if (temp.lexema[0] == '(')
							{
								stack1.push(lextable.table[i]);
								ostalsa = false;
							}
						}break;
						case ')':
						{
							if (stack1.top().znak[0] == '=')
								return false;
							if (stack1.top().znak[0] == '+' || stack1.top().znak[0] == '-' || stack1.top().znak[0] == '*' || stack1.top().znak[0] == '/')
							{
								stack2.push(stack1.top());
								stack1.pop();
								ostalsa = true;
							}
							else if (stack1.top().znak[0] == '(')
							{
								stack1.pop();
								ostalsa = false;

							}

						}break;
						case ';':
						{
							if (temp.lexema[0] == '=')
							{
								stack1.pop();
								ostalsa = false;
							}
							else if (stack1.top().znak[0] == '+' || stack1.top().znak[0] == '-' || stack1.top().znak[0] == '*' || stack1.top().znak[0] == '/')
							{
								stack2.push(stack1.top());
								stack1.pop();
								ostalsa = true;
							}
							else if (temp.lexema[0] == '(')
							{
								return false;
								ostalsa = false;
							}
							konec = i;
						}break;
						}
					}
				}
				i++;
				ostalsa = true;
			}
			int chet = 0;
			
			while (!stack2.empty())
			{
				mass[k] = stack2.top();
				stack2.pop();
				chet++;
				k++;

			}
			// !!!!!!
			for (int j = saveravno+1,m=chet-1; j < konec;j++,m--)
			{
				lextable.table[j] = mass[m];
				
			}
			delete mass;
		}
		
		
		/*while (!stack2.empty())
		{
			stack3.push(stack2.top());
			stack2.pop();

		}
		while (!stack3.empty())
		{
			cout << stack3.top().lexema[0];
			stack3.pop();

		}*/
		
		
	}
				
	/*while (!stack3.empty())
	{
		lextable.table[i].lexema[0] = stack3.top().lexema;
		stack3.pop();
		i++;

	}*/
			
			
			
			
			
			

	
		
	
	

}