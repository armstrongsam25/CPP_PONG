#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;

enum eDirection { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

//---------------------------------
//			Ball Class
//---------------------------------
class Ball {
private: 
	int x, y;
	int originalX, originalY;
	eDirection direction;
public:
	//contructor
	Ball(int posX, int posY) {
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}

	//Reset - resets ball to middle
	void reset() {
		x = originalX;
		y = originalY;
		direction = STOP; //not moving
	}
	
	//Changes direction after hitting paddle/wall
	void changeDirection(eDirection d) {
		direction = d;
	}

	//picks random direction for ball
	void randomDirection() {
		direction = (eDirection)((rand() % 6) + 1);
	}

	//Gets X-coord
	int getX() {
		return x;
	}

	//Gets Y-coord
	int getY() {
		return y;
	}

	//Gets current direction
	eDirection getDirection() {
		return direction;
	}

	//telling the ball which way
	//move for each direction
	void Move() {
		switch (direction) {
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case DOWNLEFT:
			x--;
			y++;
			break;
		case UPRIGHT:
			x++;
			y--;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		default:
			break;
		}
	}

	//for testing, returns position of ball [x,y]
	friend ostream &operator<<(ostream &o, Ball c) {
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
		return o;
	}
};

//---------------------------------
//		  Paddle Class
//---------------------------------
class Paddle {
private:
	int x, y;
	int originalX, originalY;
public:
	//constructors
	Paddle() {
		x = y = 0;
	}

	Paddle(int posX, int posY) : Paddle() {
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}

	//Resets Paddle to middle of screen
	void Reset() {
		x = originalX;
		y = originalY;
	}

	//Gets X-coord
	int getX() {
		return x;
	}

	//Gets Y-coord
	int getY() {
		return y;
	}

	//Moves paddle up screen
	void moveUp() {
		y--;
	}

	//Moves paddle down on the screen
	void moveDown() {
		y++;
	}

	//For testing. Outputs the current position [x,y]
	//x shouldn't change
	friend ostream &operator<<(ostream &o, Paddle c) {
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}
};

//---------------------------------
//		  Game Manager
//---------------------------------
class GameManager {
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	Ball *ball;
	Paddle *player1;
	Paddle *player2;
public:
	//contructor
	GameManager(int w, int h) {
		srand(time(NULL));
		quit = false;
		up1 = 'w';
		down1 = 's';
		up2 = 'o';	 //will figure out how to change to up arrow
		down2 = 'l'; //will figure out how to change to down arrow
		score1 = score2 = 0;
		width = w;
		height = h;
		ball = new Ball(w / 2, h / 2);			//middle of screen
		player1 = new Paddle(1, h / 2 - 3);		//left side of screen
		player2 = new Paddle(w-2, h / 2 - 3);	//right side of screen
	}

	//destructor
	~GameManager() {
		delete ball, player1, player2;
	}

	//increases score of player. resets ball/paddles
	void scoreUp(Paddle *player) {
		if (player == player1) 
			score1++;
		if (player == player2) 
			score2++;

		ball->reset();
		player1->Reset();
		player2->Reset();
	}

	//Draws everything
	void Draw() {
		system("cls");
		for (int i = 0; i < width + 2; i++) {
			cout << "\xB2";
		}
		cout << '\n';

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player1y = player1->getY();
				int player2x = player2->getX();
				int player2y = player2->getY();

				if (j == 0) 
					cout << "\xB2";

				if (ballx == j && bally == i)
					cout << "\xFE";
				else if (player1x == j && player1y == i)
					cout << "\xB3";
				else if (player2x == j && player2y == i)
					cout << "\xB3";

				//making paddle bigger
				else if (player1x == j && player1y +1 == i)
					cout << "\xB3";
				else if (player1x == j && player1y +2 == i)
					cout << "\xB3";
				else if (player1x == j && player1y +3 == i)
					cout << "\xB3";
				else if (player2x == j && player2y + 1 == i)
					cout << "\xB3";
				else if (player2x == j && player2y + 2 == i)
					cout << "\xB3";
				else if (player2x == j && player2y + 3 == i)
					cout << "\xB3";
				// ~making paddle bigger

				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";
			}
			cout << '\n';
		}

		for (int i = 0; i < width + 2; i++) {
			cout << "\xB2";
		}
		cout << "\n\n";

		cout << "\t\t\t\t" << score1 << " <-- Score --> " << score2 << '\n';
	}

	void Input() {
		ball->Move();
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		if (_kbhit()) {
			char current = _getch();
			if (current == up1)
				if (player1y > 0)
					player1->moveUp();
			if (current == up2)
				if (player2y > 0)
					player2->moveUp();
			if (current == down1)
				if (player1y+4 < height)
					player1->moveDown();
			if (current == down2)
				if (player2y+4 < height)
					player2->moveDown();

			if (ball->getDirection() == STOP)
				ball->randomDirection();

			if (current == 'q')
				quit = true;
		}
	}

	//Interprets input from keyboards and moves ball and paddles
	void Logic() {
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		//left paddle
		for (int i = 0; i < 4; i++) {
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->changeDirection((eDirection)((rand() %3) +4));
		}
		//right paddle
		for (int i = 0; i < 4; i++) {
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->changeDirection((eDirection)((rand() % 3) + 1));
		}

		//bottom ball redir
		if (bally == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		//top ball redir
		if (bally == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		//right wall
		if (ballx == width - 1)
			scoreUp(player1);
		//left wall
		if (ballx == 0)
			scoreUp(player2);
	}

	//runs the program
	void Run() {
		cout << "\n\n\n\n\n\n";
		cout << "\t\t\t\tTO QUIT PRESS 'q'";
		Sleep(3000);
		while (!quit) {
			Draw();
			Input();
			Logic();
		}
	}
};

//---------------------------------
//			  Main
//---------------------------------
int main() {
	GameManager g(80, 24);
	g.Run();
	return 0;
}
