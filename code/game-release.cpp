//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<string>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>
#include<cstring>
#include<sstream>
#include<fstream>
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}

void start();

/*
 * Main Canvas drawing function.
 * */
double startx=320,starty=400;

const int rows = 65;
const int col = 65;
int food_count = 0;
int score = 0;
string str, str_key = "";
int num_tails = 2;
int gamestate = 1;
	
int board[rows][col];

void gameOver()
{
	for (int x = 0; x < rows; x += 1)
	{
		for (int y = 0; y < col; y += 1)
		{
			board[x][y] = 0;
		}
	}
	
	gamestate = 3;
}

void food()
{
	int x = 7 + rand() % 45;
	int y = 7 + rand() % 45;
	
	while (board[x][y] > 0 && board[x][y] < 9)
	{
		x = 7 + rand() % 45;
		y = 7 + rand() % 45;
	}
	
	board[x][y] = 3;
	
	food_count += 1;
}

void move_up()
{
	int check = 0;
			
	for (int x = 0; x < rows; x += 1)
	{
		for (int y = 0; y < col; y += 1)
		{
			if (board[x][y] == 1 && check == 0)
			{
				if (board[x][y+1] == 2)
					gameOver();
					
				if (board[x][y+1] == 3) //food collision
				{
					score += 5; //update score
					num_tails++;
					food_count = 4;
							
					if (food_count == 4) //add more food to replace eaten one
						food();
				}
						
				if (board[x][y+1] == 4) //powerfood collision
					score += 20;
							
				if (board[x][y+1] == 5)
					gameOver();
							
				if (board[x][y+1] == 6) //boundary collision
					gameOver();
							
				if (board[x][y+1] == 7)
					gameOver();
					
				if (board[x][y+1] == 8)
					gameOver();
					
				board[x][y+1] = 1;
				board[x][y] = 0;
				
				//board[x][y+1] = board[x][y];
				
				//for (int i = 0; i <= num_tails; i += 1)
				//{
				//	board[x][y-i] = board[x][y-i-1];
				//}
				//board[x][y+1] = board[x][y];
				//board[x][y] = board[x][y-1];
				//board[x][y-1] = board[x][y-2];
				//board[x][y-2] = board[x][y-3];
				
				check = 1;
					
			}
			
		}
	}	
}

void move_down()
{
	int check = 0;
		
	for (int x = 0; x < rows; x += 1)
	{
		for (int y = 0; y < col; y += 1)
		{
			if (board[x][y] == 1 && check == 0)
			{
				if (board[x][y-1] == 2)
					gameOver();
					
				if (board[x][y-1] == 3)
				{
					score += 5;
					num_tails++; //updates block count of tail when food is eaten
					food_count = 4; 
							
					if (food_count == 4) //if food is eaten
						food(); //generate another food
				}
						
				if (board[x][y-1] == 4)
					score += 20;
							
				if (board[x][y-1] == 5)
					gameOver();
							
				if (board[x][y-1] == 6)
					gameOver();
						
				if (board[x][y-1] == 7)
					gameOver();
					
				if (board[x][y-1] == 8)
					gameOver();
					
				board[x][y-1] = 1;
				board[x][y] = 0;
				
				/*board[x][y-1] = board[x][y];
				
				for (int i = 0; i <= num_tails; i += 1)
				{
					board[x][y+i] = board[x][y+i+1];
				}*/
				
				check = 1;
			}
		}
	}
}

void move_left()
{
	int check = 0;

	for (int x = 0; x < rows; x += 1)
	{
		for (int y = 0; y < col; y += 1)
		 {
			if (board[x][y] == 1 && check == 0)
			{
				if (board[x-1][y] == 2)
					gameOver();
						
				if (board[x-1][y] == 3)
				{
					score += 5;
					num_tails++;
					food_count = 4;
							
					if (food_count == 4)
						food();
				}
						
				if (board[x-1][y] == 4)
					score += 20;
							
				if (board[x-1][y] == 5)
					gameOver();
							
				if (board[x-1][y] == 6)
					gameOver();
							
				if (board[x-1][y] == 7)
					gameOver();
					
				if (board[x-1][y] == 8)
					gameOver();
						
				board[x-1][y] = 1;
				board[x][y] = 0;
				
				/*board[x-1][y] = board[x][y];
				
				for (int i = 0; i <= num_tails; i += 1)
				{
					board[x+i][y] = board[x+i+1][y];
				}*/
				
				check = 1;
			}
		}
	}
}

void move_right()
{
	int check = 0;
			
	for (int x = 0; x < rows; x += 1)
	{
		for (int y = 0; y < col; y += 1)
		{
			if (board[x][y] == 1 && check == 0)
			{
				if (board[x+1][y] == 2) //collides with tail
					gameOver();
					
				if (board[x+1][y] == 3) //eats food
				{
					score += 5;
					num_tails++;
					food_count = 4;
							
					if (food_count == 4)
						food();
				}
						
				if (board[x+1][y] == 4) //eats powerfood
					score += 20;
							
				if (board[x+1][y] == 5) //collides with hurdle1
					gameOver();
							
				if (board[x+1][y] == 6) //collides with boundary
					gameOver();
							
				if (board[x+1][y] == 7) //collides with hurdle2
					gameOver();
					
				if (board[x+1][y] == 8) //collides with hurdle3
					gameOver();
					
				board[x+1][y] = 1;
				board[x][y] = 0;
				check = 1;
			}
		}
	}
}	

void Display() {
    	
    	// set the background color using function glClearColotgr.
    	// to change the background play with the red, green and blue values below.
    	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

    	glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
            	0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    	glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    	
    	stringstream ss;
    	
	int score2;
	
	fstream dataFile;
	dataFile.open("scores.txt", ios::in); //high score file
	dataFile >> score2;
    	
    	if (gamestate == 1) //opening menu
    	{
    		DrawString( 200, 380, "START GAME (PRESS SPACE)", colors[MISTY_ROSE]);
    		DrawString( 200, 340, "HIGH SCORE (PRESS H)", colors[MISTY_ROSE]);
    		DrawString( 200, 300, "EXIT (PRESS ESC)", colors[MISTY_ROSE]);
    			
    	}
    	
    	else if (gamestate == 2)
    	{
	    	for (int x = 0; x < rows; x += 1)
	    	{
		    	for (int y = 0; y < col; y += 1)
		    	{
		    		if (board[x][y] == 1) //head
		    			DrawCircle(x*10, y*10, 7, colors[5]);
		    	
		    		if (board[x][y] == 2) //tail
		    			DrawSquare(x*10, y*10, 10, colors[0]);
		    
		    		if (board[x][y] == 3) //food
		    			DrawSquare(x*10, y*10, 8, colors[11]);
		    		
		    		if (board[x][y] == 4) //powerfood
		    			DrawSquare(x*10, y*10, 11, colors[28]);
		    			
		    		if (board[x][y] == 5) //hurdle
		    			DrawSquare(x*10, y*10, 10, colors[80]);
		    		
		    		if (board[x][y] == 6) //boundary
		    			DrawSquare(x*10, y*10, 8, colors[118]);
		    		
		    		if (board[x][y] == 7) //hurdle 2
		    			DrawSquare(x*10, y*10, 10, colors[69]);
		    			
		    		if (board[x][y] == 8) //hurdle 3
		    			DrawSquare(x*10, y*10, 10, colors[49]);
		    	}
	    	}
		
		if (str_key == "left")
			move_left();
		
		if (str_key == "right")
			move_right();
		
		if (str_key == "down")
			move_down();
		
		if (str_key == "up")
			move_up();
									
	    	//snake progress bas
	    	DrawString( 15, 620, "Snake", colors[MISTY_ROSE]);
	    	DrawLine( 90 , 630 , 530 , 630 , 3 , colors[119] );
	    	
	    	if (score <= 45)
	    		DrawLine( 90 , 630 , 90 + (score*10), 630, 3, colors[5] );
	    	
	    	else if (score > 45 && score <= 90)
	    		DrawLine( 90 , 630 , 90 + ((score-45)*10), 630, 3, colors[18] );
	    		
	    	else
	    		DrawLine( 90 , 630 , 90 + ((score-90)*10), 630, 3, colors[24] );
	    
	    	//displaying score - int to string
	    	ss<<score;
	   	str = "Score = " + ss.str();
	    	DrawString( 540, 620, str, colors[MISTY_ROSE]);
	}
	
	else if (gamestate == 3) //gameOver display
	{
		DrawString( 200, 440, "GAME OVER", colors[13]);
		//DrawString( 200, 400, str, colors[12]);
		
		if (score > score2)
		{	
			dataFile.open("scores.txt", ios::out);
			dataFile << score;
    	
			ss<<score;
	   		str = "Score = " + ss.str();	
			DrawString( 200, 400, str, colors[12]);
			
	   		str = "You have broken all previous records! New high score is: " + ss.str();
	   		DrawString( 50, 360, str, colors[MISTY_ROSE]);
	   		
	   		DrawString( 200, 320, "PLAY AGAIN (PRESS SPACE)", colors[MISTY_ROSE]);
	   		DrawString( 200, 280, "RETURN TO MENU (PRESS R)", colors[MISTY_ROSE]);
			DrawString( 200, 240, "PRESS ESCAPE TO EXIT", colors[MISTY_ROSE]);
		}
			
		else
		{
			DrawString( 200, 400, str, colors[12]);
    			DrawString( 200, 380, "PLAY AGAIN (PRESS SPACE)", colors[MISTY_ROSE]);
    			DrawString( 200, 340, "RETURN TO MENU (PRESS R)", colors[MISTY_ROSE]);
    			DrawString( 200, 300, "EXIT (PRESS ESC)", colors[MISTY_ROSE]);
    		}
    	}
    	
    	else if (gamestate == 4) //high score display
    	{
    		if (score > score2)
    		{
    			dataFile.open("scores.txt", ios::out);
			dataFile << score;
		}
    	
    		dataFile.open("scores.txt", ios::in);
		dataFile >> score2;
    	
    		ss<<score2;
	   	str = "High Score: " + ss.str();
	   	
    		DrawString( 200, 440, str, colors[3]);
    		DrawString( 200, 400, "PRESS R TO RETURN TO MENU", colors[MISTY_ROSE]);
    	}
     
   	glutSwapBuffers(); // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
    	if (key == GLUT_KEY_LEFT   /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
    		str_key = "left";
										// what to do when left key is pressed...
      
    	} else if (key == GLUT_KEY_RIGHT  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
    		str_key = "right";	
		
    	} else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
    		str_key = "up";
    
    	} else if (key == GLUT_KEY_DOWN)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
    		str_key = "down";		
    	}
    
   	 /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     	* this function*/
     	glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    	
    	if (key == KEY_ESC/* Escape key ASCII*/) {
        	exit(1); // exit the program when escape key is pressed.
    	}
    	
    	if (key == 'H' || key=='h' /* Escape key ASCII*/) {
       	 	//exit(1); // exit the program when escape key is pressed.
    		//aswangle+=90;
    		gamestate = 4; //displays high score
    	}
    	
    	if (key == 'R' || key == 'r')
    		gamestate = 1; //displays start menu
    
    	else if (int(key) == 13 || int(key) == 32) //32 is ASCII for space
    	{
    		gamestate = 2; //starts game again
    		start();
    	}
    
    	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {
	// implement your functionality here
	glutPostRedisplay();
	// once again we tell the library to call our Timer function after next 1000/FPS
    	glutTimerFunc(800.0 / FPS, Timer, 0);
}


void all_food() { //five new foods, at random locations
	
	for (int i = 0; i < rows; i += 1)
	{
		for (int j = 0; j < col; j += 1)
		{
			if (board[i][j] == 3)
				board[i][j] = 0;  //removing all food before generating it again
		}
	}
	
	for (int i = 0; i < 5; i += 1)
		food();
}

void powerfood() {
	
	for (int x = 0; x < rows; x += 1)
	{
		for (int y = 0; y < col; y += 1)
		{
			if (board[x][y] == 4)
				board[x][y] = 0; //removing powerfood before generating it again
		}
	}

	int x = 7 + rand() % 45;
	int y = 7 + rand() % 45;
	
	while (board[x][y] > 0 && board[x][y] < 9) //checking that board[x][y] is empty
	{
		x = 7 + rand() % 45;
		y = 7 + rand() % 45;
	}
	
	board[x][y] = 4;
}

void hurdle1()
{
	for (int x = 0; x < rows; x += 1)
	{
		for (int y = 0; y < col; y += 1)
		{
			if (board[x][y] == 5)
				board[x][y] = 0; //removing previous hurdle1
		}
	}

	int x = 7 + rand() % 45;
	int y = 7 + rand() % 45;
	
	while (board[x][y] > 0 && board[x][y] < 9) //checking that board[x][y] is empty
	{
		x = 7 + rand() % 45;
		y = 7 + rand() % 45;
	}
	
	board[x][y] = 5;
	board[x][y-1] = 5;
	board[x][y-2] = 5;
	board[x][y-3] = 5;
	board[x+1][y-3] = 5;
	board[x+2][y-3] = 5;
	board[x+3][y-3] = 5;
}

void hurdle2()
{
	for (int x = 0; x < rows; x += 1)
	{
		for (int y = 0; y < col; y += 1)
		{
			if (board[x][y] == 7)
				board[x][y] = 0; //removing previous hurdle2
		}
	}
	
	int x = 7 + rand() % 45;
	int y = 7 + rand() % 45;
	
	while (board[x][y] > 0 && board[x][y] < 9) //checking that board[x][y] is empty
	{
		x = 7 + rand() % 45;
		y = 7 + rand() % 45;
	}
	
	board[x][y] = 7;
	board[x][y-1] = 7;
	board[x][y-2] = 7;
	board[x][y-3] = 7;
	board[x][y-4] = 7;
	board[x][y-5] = 7;
	board[x][y-6] = 7;
}

void hurdle3()
{
	for (int x = 0; x < rows; x += 1)
	{
		for (int y = 0; y < col; y += 1)
		{
			if (board[x][y] == 8) 
				board[x][y] = 0; //removing previous hurdle3
		}
	}

	int x = 7 + rand() % 45;
	int y = 7 + rand() % 45;
	
	while (board[x][y] > 0 && board[x][y] < 9) //checking that board[x][y] is empty
	{
		x = 7 + rand() % 45;
		y = 7 + rand() % 45;
	}
	
	board[x][y] = 8;
	board[x][y-1] = 8;
	board[x][y-2] = 8;
	board[x][y-3] = 8;
	board[x+1][y-3] = 8;
	board[x+2][y-3] = 8;
	board[x+3][y-3] = 8;
	board[x+3][y-3] = 8;
	board[x+4][y-3] = 8;
	board[x+5][y-3] = 8;
	board[x+6][y-3] = 8;
	board[x+6][y-2] = 8;
	board[x+6][y-1] = 8;
	board[x+6][y] = 8;
}

void timer6 (int m) {
	hurdle3();
	glutPostRedisplay();
	glutTimerFunc(30000, timer6, 0);
}	


void timer5 (int m) {
	hurdle2();
	glutPostRedisplay();
	glutTimerFunc(30000, timer5, 0);
}	

void timer4 (int m) {
	hurdle1();
	glutPostRedisplay();
	glutTimerFunc(30000, timer4, 0);
}

void timer3 (int m) {
	powerfood();
	glutPostRedisplay();
        glutTimerFunc(60000, timer3, 0);
}
/*
 * our gateway main function
 * */
 
void timer2 (int m) {
	all_food();
	glutPostRedisplay();
    	glutTimerFunc(15000, timer2, 0);
}

void start()
{
	//initializing all variables
	food_count = 0;
	score = 0;
	num_tails = 2;
	str_key = "";

 	for (int i=0; i<rows; i++) //initializing board as 'empty'
	{
		for (int j=0; j<col; j++)
			board[i][j]=0;
	}
	
	for (int y = 1; y < 60; y += 1) //boundary start
	{
		int x = 1;
		board[x][y] = 6;
		
		x = 64;
		board[x][y] = 6;
	}
	
	for (int x = 1; x < 65; x += 1)
	{
		int y = 1;
		board[x][y] = 6;
		
		y = 60;
		board[x][y] = 6;
	} //boundary end
	
	int x = 5 + rand() % (rows-15);
	int y = 5 + rand() % (col-15);
	
	board[x][y] = 1; //head
	board[x][y-1] = 2; //tail
	board[x][y-2] = 2; //tail
	
	for (unsigned int i = 0; i < 5; i += 1)
		food();
	
	powerfood();
	hurdle1();
	hurdle2();
	hurdle3();
}

int main(int argc, char*argv[]) {

	srand(time(NULL));

	//start();

    	int width = 650, height = 650; // i have set my window size to be 800 x 600
    	InitRandomizer(); // seed the random number generator...
    	glutInit(&argc, argv); // initialize the graphics library...

    	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    	glutInitWindowPosition(50, 50); // set the initial position of our window
    	glutInitWindowSize(width, height); // set the size of our window
    	glutCreateWindow("Sana Ali's Snake Game"); // set the title of our game window
   	SetCanvasSize(width, height); // set the number of pixels...
	
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    	
    	glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
    	
    	glutTimerFunc(5.0 / FPS, Timer, 0);
	glutTimerFunc(15000, timer2, 0);
	glutTimerFunc(60000, timer3, 0);
	glutTimerFunc(10000, timer4, 0);
	glutTimerFunc(20000, timer5, 0);
	glutTimerFunc(30000, timer6, 0);
	
    	glutMainLoop();
    	return 1;
}
#endif /* Snake Game */

