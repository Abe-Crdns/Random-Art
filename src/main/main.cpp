/*
 * Author: Abraham Cardenas
 * Assignment: PA6
 */

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <cstdlib>
#include "../expression/expression.h"
#include "../lpc_lib/grid.h"
#include "../lpc_lib/lpclib.h"
using namespace std;

const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 700;
GraphicsWindow window(WINDOW_WIDTH, WINDOW_HEIGHT, "Random Art");

void clearcin(void);
char mainMenu(void);
string GenerateExpression(int depth);

int main(){
	int minDepth = 0, maxDepth = 0;
	bool isDepthSet = false;
	Grid<int> pixelX, pixelY;
	char prevSelection;

	int row = WINDOW_HEIGHT/2, col = WINDOW_WIDTH/2;

	pixelX.resize(row, col);
	pixelY.resize(row, col);

	int tempX = 0, tempY = 0;
	for(int r = 0; r < row; r++){
		for(int c = 0; c < col; c++){
			pixelX[r][c] = tempX;
			pixelY[r][c] = tempY;
			tempX += 2;
		}
		tempY += 2;
		tempX = 0;
	}

	while(true){
		char menuChoice;

		menuChoice = mainMenu();
		if(menuChoice != '\n'){
			prevSelection = menuChoice;
		}
		else if(prevSelection != '\0' && menuChoice == '\n'){
			menuChoice = prevSelection;
		}

		switch(menuChoice){
			case('E'):{
				while(true){
					double x = 0, y = 0, result = 0;
					string userInput;

					cout << "Please enter an expression: ";
					getline(cin, userInput);

					Expression *expr = new Expression(userInput);

					if(expr->SyntaxIsValid()){
						for(int r = 0; r < row; r++){
							for(int c = 0; c < col; c++){
								x = (pixelX[r][c]/(WINDOW_WIDTH/2.0)) - 1.0;
								y = (pixelY[r][c]/(WINDOW_WIDTH/2.0)) - 1.0;
								result = ((expr->Evaluate(x, y))+1.0) * (255/2.0);
								Color color(result, result, result);
								window.DrawRectangle(pixelX[r][c], pixelY[r][c], 2, 2, color, true);
							}
						}
						window.Refresh();
						delete expr;
						break;
					}
					else{
						delete expr;
						continue;
					}
				}
				cout << endl;
				break;
			}
			case('S'):{
				while(true){
					int input;

					if(isDepthSet){
						cout << "Current minimum depth: " << minDepth << endl;
						cout << "Current maximum depth: " << maxDepth << endl;
						cout << endl;
 					}
					cout << "Please enter the minimum depth (Enter -999 for Main Menu) : ";
					if(cin >> input){
						if(input >= 0){
							minDepth = input;
							while(true){
								cout << "Please enter the maximum depth: ";
								if(cin >> maxDepth){
									if(maxDepth > minDepth && maxDepth >= 0){
										isDepthSet = true;
										break;
									}
									else{
										clearcin();
										cout << "Error, max depth must be bigger than the the minimum depth.\n";
										continue;
									}
								}
								clearcin();
								cout << "Error, please enter positive integers only.\n";
							}
							break;
						}
						else if(input == -999){
							break;
						}
					}
					if(input != -999){
						cout << "Error, please enter positive integers only.\n";
					}
					clearcin();
				}
				clearcin();
				cout << endl;
				break;
			}
			case('G'):{
				if(isDepthSet){
					int depth;
					while(true){
						depth = rand()%maxDepth;
						if(depth >= minDepth){
							break;
						}
					}

					string genExpr = GenerateExpression(depth);
					Expression *expr = new Expression(genExpr);

					cout << "Expression generated\n";
					cout << "------------------------------------------------------\n";
					cout << genExpr << endl;

					double x, y, greyScale;
					for(int r = 0; r < row; r++){
						for(int c = 0; c < col; c++){
							x = (pixelX[r][c]/(WINDOW_WIDTH/2.0)) - 1.0;
							y = (pixelY[r][c]/(WINDOW_WIDTH/2.0)) - 1.0;
							greyScale = ((expr->Evaluate(x, y))+1.0) * (255/2.0);
							Color color(greyScale, greyScale, greyScale);
							window.DrawRectangle(pixelX[r][c], pixelY[r][c], 2, 2, color, true);
						}
					}
					window.Refresh();
					delete expr;
				}
				else{
					cout << "Minimum and maximum depth must be initialized before printing an image.\n";
				}
				cout << endl;
				break;
			}
			case('C'):{
				if(isDepthSet){
					int depth;
					Expression *expr1, *expr2, *expr3;
					string genExpr1, genExpr2, genExpr3;

					for(unsigned int i = 0; i < 3; i++){
						while(true){
							depth = rand()%maxDepth;
							if(depth >= minDepth){
								break;
							}
						}
						if(i == 0){
							genExpr1 = GenerateExpression(depth);
							expr1 = new Expression(genExpr1);
						}
						else if(i == 1){
							genExpr2 = GenerateExpression(depth);
							expr2 = new Expression(genExpr2);
						}
						else if (i == 2){
							genExpr3 = GenerateExpression(depth);
							expr3 = new Expression(genExpr3);
						}
					}

					cout << "Expressions generated\n";
					cout << "------------------------------------------------------\n";
					cout << "Red: "<< genExpr1 << endl;
					cout << endl;
					cout << "Green: "<< genExpr2 << endl;
					cout << endl;
					cout << "Blue: "<< genExpr3 << endl;

					double x, y, red, green, blue;
					for(int r = 0; r < row; r++){
						for(int c = 0; c < col; c++){
							x = (pixelX[r][c]/(WINDOW_WIDTH/2.0)) - 1.0;
							y = (pixelY[r][c]/(WINDOW_WIDTH/2.0)) - 1.0;
							red = ((expr1->Evaluate(x, y))+1.0) * (255/2.0);
							green = ((expr2->Evaluate(x, y))+1.0) * (255/2.0);
							blue = ((expr3->Evaluate(x, y))+1.0) * (255/2.0);
							Color color(red, green, blue);
							window.DrawRectangle(pixelX[r][c], pixelY[r][c], 2, 2, color, true);
						}
					}
					window.Refresh();
					delete expr1;
					delete expr2;
					delete expr3;
				}
				else{
					cout << "Minimum and maximum depth must be initialized before printing an image.\n";
				}
				cout << endl;
				break;
			}
		   	default:{
		   		cout << "Invalid entry of [" << menuChoice << "], please try again." << endl;
		   		cout << endl;
		   	}
			case('Q'):{
				break;
			}
		}
		if(menuChoice == 'Q'){
			break;
		}
	}

}

void clearcin(void){
    cin.clear();
    cin.ignore(32768, '\n');
}

char mainMenu(void){
	 char menuChoice;
	 string checkStr;
	 while(true){
	 		 cout << "Main Menu" << endl;
	 		 cout << "===============================" << endl;
	 		 cout << "E - Enter an expression        |" << endl;
	 		 cout << "S - Set min. and max. depth    |" << endl;
	 		 cout << "G - Random greyscale image     |" << endl;
	 		 cout << "C - Random color image         |" << endl;
	 		 cout << "Q - Quit                       |" << endl;
	 		 cout << "-------------------------------" << endl;
	 		 getline(cin, checkStr);
	 		 if(checkStr.size() == 1){
	 			 menuChoice = checkStr[0];
		 		 break;
	 		 }
	 		 else if(checkStr.empty()){
	 			 return '\n';
		 		 break;
	 		 }
	 		 else{
	 			 cout << endl;
	 			 cout << "Invalid selection.\n";
	 			 cout << endl;
	 		 }
	 }
	 cout << endl;

	 return toupper(menuChoice);
}

string GenerateExpression(int depth){
	if(depth == 0){
		int r = rand()%2;
		return (r == 0 ? "x" : "y");
	}
	else{
		int r = rand()%4;
		if(r == 0)
			return "avg(" + GenerateExpression(depth-1) + ", " + GenerateExpression(depth-1) + ")";
		else if(r == 1)
			return GenerateExpression(depth-1) + " * " + GenerateExpression(depth-1);
		else if(r == 2)
			return "sin(pi * " + GenerateExpression(depth-1) + ")";
		else
			return "cos(pi * " + GenerateExpression(depth-1) + ")";
	}

}
