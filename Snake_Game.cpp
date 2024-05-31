#include "graphics.h"
#include <climits>
#include <queue>

using namespace std;

const int EMPTY=0;
const int BODY=1;
const int APPLE=2;
const int WALL=3;
int score = 0;

enum Directions{UP,DOWN,LEFT,RIGHT};
Directions snakeDirection = DOWN;
bool isGameOver = false ;

struct Location{
   int r;
   int c;
 };
 
 bool isFireStarted;
Location fireLocation;
Directions fireDirection;
 
 queue<Location> snakeBody;

int board[35][35]={
{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
};

void drawWelcomeScreen() {
    cleardevice(); 
    setcolor(WHITE);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    char buffer1[] = "Welcome to Snake Game!";
    outtextxy(getmaxx() / 2, getmaxy() / 2 - 50,buffer1);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    char buffer2[] = "Press any key to start...";
    outtextxy(getmaxx() / 2, getmaxy() / 2 +50, buffer2);
    getch();
}

void clearWelcomeScreen() 
{
    cleardevice();
}

void drawGate(int row,int col)
{
    int x = col*18 ,y = row*18;
    setfillstyle(SOLID_FILL , BLACK);
    bar(x , y , x+18 , y+18);
}

void drawFire(int r,int c)
{
    int x = c*18 ,y = r*18;

    setfillstyle(SOLID_FILL , YELLOW);
    if(board[r][c] == APPLE || board[r][c] == BODY)
    return;
    if(board[r][c]==WALL)
    {
        board[r][c]=EMPTY , drawGate(r,c);
        if(r==34)
        board[0][c]=EMPTY , drawGate(0,c);
        else if(r==0)
        board[34][c]=EMPTY  , drawGate(34,c);
        
        else if(c==34)
        board[r][0]=EMPTY , drawGate(r,0);
        else if(c==0)
        board[r][34]=EMPTY  , drawGate(r,34);
        return;
    }
    else
    bar(x+2 , y+2 , x+15 , y+15);
}


void eraseFire(int r,int c)
{
    int x = c*18 ,y = r*18;
    setfillstyle(SOLID_FILL , BLACK);
    if(board[r][c] == APPLE || board[r][c] == BODY)
    return;
    bar(x , y , x+18 , y+18);
}


void eraseSnakeBody(int r,int c)
{
    int x = c*18 ,y = r*18;

    setfillstyle(SOLID_FILL , BLACK);
    bar(x , y , x+18 , y+18);

}

void drawSnakeBody(int r,int c)
{
    int x = c*18 ,y = r*18;

    setfillstyle(SOLID_FILL , LIGHTBLUE);
    bar(x+1 , y+1 , x+17 , y+17);

}

void drawApple(int r,int c)
{
    int x = c*18 ,y = r*18;

    readimagefile( "anapple.ico" , x+1 ,y+1 ,x+16 ,y+16);

}

void drawWall(int r,int c)
{
    int x = c*18 ,y = r*18;
    setfillstyle(SOLID_FILL , LIGHTRED);
    bar(x , y , x+18 , y+18);

    setcolor(BLACK);
    setlinestyle(SOLID_LINE,1,NORM_WIDTH);
    line(x+0 , y+0 , x+18 ,y+0);
    line(x+0 , y+9 , x+18 ,y+9);
    line(x+0 , y+18 , x+18 ,y+18);

    line(x+12 , y+0 , x+12 ,y+9);
    line(x+6 , y+9 , x+6 ,y+18);

}

void drawBoard()
{
    for(int r=0 ;r<35 ;r++)
    for(int c=0;c<35;c++)
    {
        switch(board[r][c])
        {
            case EMPTY:
            break;
            case BODY:
            drawSnakeBody(r,c);
            break;
            case APPLE:
            drawApple(r,c);
            break;
            case WALL:
            drawWall(r,c);
            break;
        }
    }

}

void initSnake(){
    Location loc;
    loc.r = 2;
    loc.c = 10;
    
    for(int i=0;i<=4;i++)
    {
       snakeBody.push(loc);
       board[loc.r][loc.c] = 1;
       loc.r +=1;
    }

}
Location getNextFireLocation(){
     Location nextFireLoc= fireLocation;
     switch(fireDirection){  
         case UP:
          nextFireLoc.r -= 1;
            break;
         case DOWN:
           nextFireLoc.r += 1;
            break;
         case LEFT:
          nextFireLoc.c -= 1;
            break;
         case RIGHT:
          nextFireLoc.c += 1;
            break; 
            }
            return nextFireLoc;
     
}
Location getNextHead()
{
    Location head = snakeBody.back();
    switch(snakeDirection)
    {
        case UP:
        head.r -=1;
        if(head.r <0) head.r = 34; 
        break;
        case DOWN:
        head.r +=1;
        if(head.r >34) head.r = 0;
        break;
        case LEFT:
        head.c -=1;
        if(head.c <0) head.c = 34;
        break;
        case RIGHT:
        head.c +=1;
        if(head.c >34) head.c = 0;
        break;
    }
    return head;
}

void generateNextAplle(){
    int r,c;
    do{
         r = rand()%35;
         c = rand()%35;
    }while(board [r][c] != EMPTY);
    board[r][c] = APPLE;
    drawApple(r,c);


}
void moveSnakeToNextLocation(Location nextHead){
    snakeBody.push(nextHead);
     drawSnakeBody(nextHead.r,nextHead.c);
     board[nextHead.r][nextHead.c] = 1;
     
     Location tail = snakeBody.front();
     snakeBody.pop();
     eraseSnakeBody(tail.r,tail.c);
     board[tail.r][tail.c] = 0;

}

void moveAndGrowSnake(Location nextHead){
    snakeBody.push(nextHead);
     drawSnakeBody(nextHead.r,nextHead.c);
     board[nextHead.r][nextHead.c] = 1;
     
     

}
void gameOver()
{
    isGameOver = true;
    PlaySound(TEXT("game_over.wav"), NULL, SND_ASYNC);
    setcolor(WHITE);
    settextjustify(CENTER_TEXT , CENTER_TEXT);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR ,4);
    char buffer[] = "Game Over";
    outtextxy(getmaxx()/2 , getmaxy()/2 , buffer);

    settextstyle(TRIPLEX_FONT,HORIZ_DIR ,2);
    char scoreBuffer[20];
    sprintf(scoreBuffer, "Your Score: %d", score);
    outtextxy(getmaxx()/2 , getmaxy()/2 + 50 , scoreBuffer);
}

void moveSnake (){
         Location nextHead = getNextHead();
         switch (board[nextHead.r][nextHead.c]){
        case EMPTY:
        moveSnakeToNextLocation(nextHead);
        break;
        case APPLE:
        PlaySound(TEXT("eat_apple.wav"), NULL, SND_ASYNC);   
        moveAndGrowSnake(nextHead);
        generateNextAplle();
        score+=10;
        break;
        case WALL:
        case BODY:
        gameOver();
        break;       
        }   
     
     
}

void changeSnakeDirection(char ch)
{
    switch(ch)
    {
        case KEY_UP:
        if(snakeDirection == DOWN)
        return;
        else
        {
            snakeDirection = UP;
            break;
        }
        
        case KEY_DOWN:
        if(snakeDirection == UP)
        return;
        else
        {
            snakeDirection = DOWN;
            break;
        }
        
        case KEY_LEFT:
        if(snakeDirection == RIGHT)
        return;
        else
        {
            snakeDirection = LEFT;
            break;
        }
        
        case KEY_RIGHT:
        if(snakeDirection == LEFT)
        return;
        else
        {
            snakeDirection = RIGHT;
            break;
        }
    }
}



void startFire(){ 
    isFireStarted = true;
    fireLocation = getNextHead();
    fireDirection = snakeDirection;
    drawFire(fireLocation. r,fireLocation. c);
    
    PlaySound(TEXT("fire_sound.wav"), NULL, SND_ASYNC);    
}
void stopFire(){
    isFireStarted = false;
    eraseFire(fireLocation.r,fireLocation.c);
}

void moveFire(){
   if(isFireStarted){
     Location nextFireLoc = getNextFireLocation();
     
     if(nextFireLoc.r >35 || nextFireLoc.r <0 || nextFireLoc.c >35 || nextFireLoc.c <0){
        stopFire();
        return;     
     }
     
     
     drawFire(nextFireLoc.r,nextFireLoc.c);
     eraseFire(fireLocation.r,fireLocation.c);
     fireLocation = nextFireLoc;
   }
}

void checkKeykInput(){
    char ch;
    if(kbhit()){
    ch = getch();
    if(ch ==0){
        ch = getch();
        changeSnakeDirection(ch);       
    }else if (ch ==32) //spaceman is pressed
    { 
    if(!isFireStarted)
     startFire();
    }
  }
}
void drawScore()
{
    setcolor(WHITE);
    settextjustify(LEFT_TEXT , TOP_TEXT);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR ,2);
    char scoreBuffer[20];
    sprintf(scoreBuffer, "Score: %d", score);
    outtextxy(10, 10, scoreBuffer);
}


int main()
{
    isGameOver = false;
    initwindow(630,630, "Snake Game");
    drawWelcomeScreen();
    clearWelcomeScreen();
    initSnake(),
    drawBoard();
    
    int gameTimer = 0;
    while(! isGameOver)
    {
     if(gameTimer == INT_MAX)
        gameTimer = 0;
    if(gameTimer % 1000000 ==0)
    moveFire();
    if(gameTimer % 6000000 ==0){
        
        moveSnake();
        drawScore();
    }
      gameTimer++;
      
      checkKeykInput();      
    }
    while(!kbhit());
    return 0;

}