/*  SUDOKU puzzle, Author: Nikhil Kumar Mopidevi, Date: 4-09-2013*/

#include <iostream>  //for using iostream methods (cin,cout)
#include<ctime>      //for using time()
#include<cstdlib>    //for using srand() and rand()
#include<iomanip>    //for using setw()
#include<windows.h>  //for using gotoxy(int,int)
#include<algorithm>  //for using random::shuffle()
#include<cstdio>     //for using system()
#include<conio.h>    //for using getch()

using namespace std;

//This function sets the cursor at the
//column and row indexes passed,respectively.
void gotoxy(int x,int y)
 {
     static HANDLE h=NULL;
     if(!h)

           h=GetStdHandle(STD_OUTPUT_HANDLE);
     COORD c={x,y};

     SetConsoleCursorPosition(h,c);
 }

//This function sets the console window to
//almost fullscreen-maximum possible size
void fullscreen()
{
   HWND hWnd;
   SetConsoleTitle("SUDOKU");
   hWnd = FindWindow(NULL, "SUDOKU");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD NewSBSize = GetLargestConsoleWindowSize(hOut);
    SMALL_RECT DisplayArea = {0, 0, 0, 0};

    SetConsoleScreenBufferSize(hOut, NewSBSize);

    DisplayArea.Right = NewSBSize.X - 1;
    DisplayArea.Bottom = NewSBSize.Y - 1;

    SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);

    ShowWindow(hWnd, SW_MAXIMIZE);
}

#define N 3 // N is used in determining the size of the board.



//-------global variable declaration----------//

int board[N*N][N*N],p_board[9][9],game_board[9][9],reset_board[9][9];
/* 1)board[][] is the initial original array, which contains
   all numbers of the puzzle.
   2)p_board[][] stores either 1 or 0 only.
   3)game_board[][] stores values entered during game play
   4)reset_board[][] is the duplicate of "p_board[][] at the start of the game"
     which is used in resetting the board.
 */

char level;//for choosing level of difficulty of the game

//-------------ends here-----------------------//


//this function returns a random number within the range given
//excluding the upper limit
int randrange(int low,int high)
{
    return rand()%(high-low)+low;
}


//---this class looks after all the initialisation details of the board---//

class initialisation
{
private:
int random[3],i,j,k,l,temp[9];

public:
 void _initialisation();//this generates 1 to 9 numbers without repetation in
                        // both column and row
 void shuffle();
};


void  initialisation::_initialisation()
{

for (int i = 0; i < N*N; i++)
        for (int j = 0; j < N*N; j++)
                board[i][j] = (i*N + i/N + j) % (N*N) + 1;

}

void initialisation::shuffle()
{

  for(k=0;k<3;k++)
  {

   random[0]=randrange(0,3);
   random[1]=randrange(1,3);

   for(i=random[0]*3,l=0;l<3;l++)
   {
     for(j=0;j<9;j++)
     {
         temp[j]=board[j][i];
         board[j][i]=board[j][i+random[1]];
         board[j][i+random[1]]=temp[j];
     }

   }
   for(i=random[0]*3,l=0;l<3;l++)
   {
     for(j=0;j<9;j++)
     {
         temp[j]=board[i][j];
         board[i][j]=board[i+random[1]][j];
         board[i+random[1]][j]=temp[j];
     }
   }
}
}
//-----------------end of initialisation class--------------------//


//---this class looks after displaying aspects of the board------//

class display
{
private:
 int i,j,l;
 char ch[6]={179,196,220,221,222,223};
public:
 void _display();//displays just numbers
 void draw_box();//displays the board
 void mark_indices();//displays indices for the board
};

void display::draw_box()
  {

for(i=0;i<13;i++)
 cout<<endl;
gotoxy(65,13);

for(i=0;i<30;i++)
cout<<ch[2]; //to draw top outer line

for(i=0;i<19;i++)
{   cout<<endl;
    gotoxy(65,14+i);//to draw left outer line
    cout<<ch[3];
}
cout<<endl;
gotoxy(65,33);
for(i=0;i<30;i++)
cout<<ch[5];//to draw bottom outer line

for(l=14,i=0;i<19;i++,l++)//to draw right outer line
{ gotoxy(94,l);

    cout<<ch[4];
}
gotoxy(66,20);// inner lines from here
for(i=0;i<28;i++)
{
cout<<ch[1];//inner top vertical line
}
gotoxy(66,26);
for(i=0;i<28;i++)
{
cout<<ch[1];//inner bottom vertical line
}

for(i=0;i<19;i++)//inner right vertical line
{ gotoxy(84,i+14);
  cout<<ch[0];
}

for(i=0;i<19;i++)//inner left vertical line
{ gotoxy(74,i+14);
  cout<<ch[0];
}
}


void display::_display()
{
gotoxy(0,0);
 for(i=0;i<14;i++)
 cout<<endl;
 for(i=0;i<9;i++)
{   gotoxy(67,15+i*2);
  for(j=0;j<9;j++)
 {
    cout<<board[i][j];
   if(j!=2&&j!=5&&j!=8)
        cout<<"  ";
   else if (j==2)
    {
     cout<<ch[0];
     cout<<" ";

    }
    else if(j==5)
    {
      cout<<" ";
      cout<<ch[0];
      cout<<" ";
    }

 }

}
gotoxy(0,36);
}
void display::mark_indices()
{
gotoxy(67,12);
for(i=1;i<=9;i++)
{ if(i==7)
  cout<<" ";
    cout<<i<<"  ";

}
gotoxy(63,15);
for(i=1;i<=9;i++)
{
    cout<<i<<endl<<endl;
    gotoxy(63,15+i*2);
}
}

//-----------------end of display class--------------------------//


//-----this class is used in generating and displaying partial board------//

class partial_board
{
private:
  int i,j,k,l,num[9];
  char ch[6]={179,196,220,221,222,223};
public:
  void _generate();//generates numbers to be displayed randomly
  void display(); //displays them
  void display_game_board();//displays board for those numbers
};

void partial_board::_generate()
{
    int rnd[9];
  if(level==1)
     int rnd[9]={5,5,5,6,6,6,6,7,7};//53 cells are given
  else if(level==2)
     int rnd[9]={3,3,4,4,5,5,6,6,6};//42 cells are given
  else if (level==3)
     int rnd[9]={2,2,3,3,3,4,4,5,5};//31 cells are given

  random_shuffle(rnd,rnd+9);

  for(int p,q,k=0;k<9;k++)
  {  p=k/3;
     q=k%3;

    {
     for(l=0;l<rnd[k];l++)
      num[l]=1;
     for(l=rnd[k];l<9;l++)
      num[l]=0;
    }
  random_shuffle(num,num+9);


  for(i=0,l=0;i<3;i++)
   {
      for(j=0;j<3;j++,l++)
      {
        if(num[l]==1)
         p_board[i+(p*3)][j+(q*3)]=1;
       else
         p_board[i+(p*3)][j+(q*3)]=0;
      }
   }
  }

for(i=0;i<9;i++)
    for(j=0;j<9;j++)
    if(p_board[i][j]==1)
     game_board[i][j]=board[i][j];


}
void partial_board::display()
{
gotoxy(0,0);
 for(i=0;i<14;i++)
 cout<<endl;
 for(i=0;i<9;i++)
{   gotoxy(67,15+i*2);
  for(j=0;j<9;j++)
 {
    if(p_board[i][j]==1)
    cout<<board[i][j];
   else
     cout<<" ";


   if(j!=2&&j!=5&&j!=8)
        cout<<"  ";
   else if (j==2)
    {
     cout<<ch[0];
     cout<<" ";

    }
    else if(j==5)
    {
      cout<<" ";
      cout<<ch[0];
      cout<<" ";
    }

 }

}

}
void partial_board::display_game_board()
{
gotoxy(0,0);
 for(i=0;i<14;i++)
 cout<<endl;
 for(i=0;i<9;i++)
{   gotoxy(67,15+i*2);
  for(j=0;j<9;j++)
 {
    if(p_board[i][j]==1)
    cout<<game_board[i][j];
   else
     cout<<" ";


   if(j!=2&&j!=5&&j!=8)
        cout<<"  ";
   else if (j==2)
    {
     cout<<ch[0];
     cout<<" ";

    }
    else if(j==5)
    {
      cout<<" ";
      cout<<ch[0];
      cout<<" ";
    }

 }

}

}

//-------------end of partial_board class------------------------//


//-----this class checks the correctness of the entered values-----//
class Sudoku_check
{  private:
    int i,j,k,l;
   public:
    int  check();
    bool row_check();   //these three methods
    bool column_check();//are not used
    bool sub_check();   //in this program
};

int Sudoku_check::check()
{
 bool flag=false;
 for(i=0;i<9;i++)
 for(j=0;j<9;j++)
{
    if(reset_board[i][j]!=p_board[i][j])
    flag=true;
}

if(flag==false)
return 2;
else
{
 for(i=0;i<9;i++)
 for(j=0;j<9;j++)
 {
      if((game_board[i][j]!=0) )
       {
          if((game_board[i][j]!=board[i][j]))
         {
            return 0;
         }
        }
 }
    return 1;
}
}
//------not used section begins here--------//
bool Sudoku_check::row_check()
{
 for(i=0;i<9;i++)
{
for(j=0;j<9;j++)
for(k=0;k<9;k++)
 {
 if(board[i][j]==board[i][k])
 {
   return false;
 }
 }
}
return true;
}
bool Sudoku_check::column_check()
{
 for(i=0;i<9;i++)
{
for(j=0;j<9;j++)
for(k=0;k<9;k++)
 {
 if(board[j][i]==board[k][i])
 {
   return false;
 }
 }

}
return true;
}
bool Sudoku_check::sub_check()
{
    int sum=0;
	for(int p,q,k=0;k<9;k++)
  {  p=k/3;
     q=k%3;
 for(i=0;i<3;i++)
   {
      for(j=0;j<3;j++)
      {
          sum+=board[i+(p*3)][j+(q*3)];
      }
   }
  }
  if(sum!=45)
   return false;
   else return true;
}

//------not used section ends here--------//

//----------------end of sudoku_check class----------------------//


//-----------------------------------------------------------------------//
//this section contains definitions of some functions used in gameplay

void print_space(int n)// this clears the line till 'n'number of characters
{
    for(int i=0;i<n;i++)
        cout<<" ";
}


 bool check_if_full()//checks if the sudoku is filled completely
 {
    int i,j;
    for(i=0;i<9;i++)
     for(j=0;j<9;j++)
     if(p_board[i][j]==0)
       return false;
     return true;
 }


void clear_lines()// clears out an area on the screen
{

 for(int l=30;l<=47;l++)
 {
 gotoxy(0,l);
 print_space(25);
 }
gotoxy(0,36);
}


void options()//displays on screen options on the top-right of the screen
{
gotoxy(118,1);
cout<<" You can Press "<<endl;
gotoxy(118,3);
cout<<" h - for help "<<endl;
gotoxy(118,5);
cout<<" c - to check your progress  "<<endl;
gotoxy(118,7);
cout<<" s - to view solution  "<<endl;
gotoxy(118,9);
cout<<" r - to reset the board to the start of the game "<<endl;
gotoxy(118,11);
cout<<" n - for new game "<<endl;
gotoxy(118,13);
cout<<" q - to quit the game "<<endl;

}

//------------end of function definitions-------------------------------//


//--this class has methods to perform tasks displayed on welcome screen--//

class Menu
{
public:
int play_game();
void help();
void about_sudoku();
void credits();
};

int Menu::play_game()
{
while(1)
{
 system("cls");
 gotoxy(64,15);
 cout<<"CHOOSE DIFFICULTY LEVEL"<<endl;
 gotoxy(64,18);
 cout<<"1.EASY";
 gotoxy(64,20);
 cout<<"2.MEDIUM";
 gotoxy(64,22);
 cout<<"3.HARD"<<endl;

 cin>>level;

 if(level>48 && level<=51)
 {
  level=(int)level-48;
  break;
 }
}
system("cls");

srand(time(NULL));//sends current time as seed to srand
                  //to generate unique random numbers

initialisation obj_initialisation;
display d;
partial_board pb;

obj_initialisation._initialisation();
obj_initialisation.shuffle();

d.draw_box();
d.mark_indices();
options();

pb._generate();
pb.display();

for(int i=0;i<9;i++)
 for(int j=0;j<9;j++)
reset_board[i][j]= p_board[i][j];

{
// code for game play starts here

int r,c,l=0,num;
  char ch,opt;
  Sudoku_check ob_chk;
gotoxy(0,36);
fflush(stdin);
while(1)
{
 if(check_if_full()==true)
 {
   if(ob_chk.check()==1)
   {
       clear_lines();
       gotoxy(60,40);
       cout<<"Hurray!!You've made it!"<<endl;
       fflush(stdin);
       cin.get();
       system("cls");
   }
   else
    {
    cout<<"Something went wrong!!\n\n"<<"Keep Trying!!\n";
    fflush(stdin);
    cin.get();
    clear_lines();

     }
 }
fflush(stdin);
opt=cin.get();
if(!(opt>48 && opt<=57))
{
  switch (opt)
{ case 'H':
  case 'h':
    {
    system("cls");
    help();
    system("cls");
    pb.display_game_board();
    d.draw_box();
    d.mark_indices();
    options();

    gotoxy(0,36);
    }
   break;
  case 'C':
  case 'c':
    {
       l++;
      if( ob_chk.check()==1)
       {
         cout<<" good going!! "<<endl;

       }
      else if(ob_chk.check()==0)
       cout<<" wrong arrangement!"<<endl;

      else
        cout<<"no number entered yet!"<<endl;

   }
   break;
  case 'Q':
  case 'q':
          system("cls");
       gotoxy(65,14);
       cout<<"ARE YOU SURE, YOU WANT TO QUIT ?"<<endl;
       gotoxy(72,16);
       fflush(stdin);
       cout<<"YES (Y) OR NO (N)"<<endl;
       cin>>ch;
       if(ch=='y')
       {
        exit(2);
       }
       else
       {
         system("cls");
         pb.display_game_board();
         d.draw_box();
         d.mark_indices();
         options();
         gotoxy(0,36);
         l=0;
       }

    break;
  case 'R':
  case 'r':
      {
      system("cls");
       gotoxy(50,14);
       cout<<"ARE YOU SURE, YOU WANT TO RESET THE BOARD TO THE START OF THE GAME ?"<<endl;
       gotoxy(71,16);
       fflush(stdin);
       cout<<"YES (Y) OR NO (N)"<<endl;
       cin>>ch;
       system("cls");
       if(ch=='y')
       {
          for(int i=0;i<9;i++)
           for(int j=0;j<9;j++)
             p_board[i][j] = reset_board[i][j];

             pb.display_game_board();
             d.draw_box();
             d.mark_indices();
             options();

             gotoxy(0,36);
             l=0;
       }
       else
       {
           pb.display_game_board();
           d.draw_box();
           d.mark_indices();
           options();

           gotoxy(0,36);
           l=0;

       }
    }
    break;
  case 'N':
  case 'n':
      {
     system("cls");
       gotoxy(60,14);
       cout<<"ARE YOU SURE, YOU WANT TO START A NEW GAME ?"<<endl;
       gotoxy(72,16);
       fflush(stdin);
       cout<<"YES (Y) OR NO (N)"<<endl;
       cin>>ch;
       system("cls");

       if(ch=='y')
        return 1;
       else
        {
           pb.display_game_board();
           d.draw_box();
           d.mark_indices();
           options();

           gotoxy(0,36);
           l=0;

        }
   }
   break;
   case 'S':
   case 's':
     {
         system("cls");

         d.draw_box();
         d.mark_indices();
         d._display();

         gotoxy(57,40);
         cout<<"PRESS ANY KEY TO GET BACK TO THE PREVIOUS SCREEN"<<endl;
         fflush(stdin);
         getch();
         system("cls");
         pb.display_game_board();
         d.draw_box();
         d.mark_indices();
         options();

         gotoxy(0,36);
         l=3;

     }
        break;

    default:
    cout<<"Invalid entry\n";
    fflush(stdin);
    cin.get();
    clear_lines();
    break;

}
}


 else
 {
    r=(int)opt-48;
  cin>>c>>num;
 p_board[r-1][c-1]=1;
 game_board[r-1][c-1]=num;
 pb.display_game_board();
 gotoxy(0,36);

 if(l==0)
{
gotoxy(0,38);
cout<<"Number updated"<<endl<<endl;
fflush(stdin);
}
if(l==1)
{
gotoxy(0,42);
cout<<"Number updated"<<endl<<endl;
fflush(stdin);
}
if(l==2)
{
gotoxy(0,46);
cout<<"Number updated"<<endl<<endl;
}

l++;
 if(l==3)
   {

    clear_lines();
    l=0;
   }
}

}
}
}


//---------------------HELP implementation------------------//

void Menu::help()
{
char p=177,q=175;

gotoxy(75,2);
cout<<"HELP";
gotoxy(8,6);
cout<<q<<" "<<q<<" "<<q<<"  Sudoku Puzzle Rules ---"<<endl;
gotoxy(15,10);
cout<<p<<" Solving a sudoku puzzle can be rather tricky, but the rules of the game are quite simple."<<endl;
gotoxy(15,14);
cout<<p<<" A sudoku puzzle is a grid of nine by nine squares or cells, that has been subdivided into nine subgrids or \"regions\" of three by three cells."<<endl;
gotoxy(15,18);
cout<<p<<" The objective of sudoku is to enter a digit from 1 through 9 in each cell, in such a way that:"<<endl;
gotoxy(17,20);
cout<<"1)Each horizontal row contains each digit exactly once."<<endl<<endl;
gotoxy(17,22);
cout<<"2)Each vertical column contains each digit exactly once."<<endl<<endl;
gotoxy(17,24);
cout<<"3)Each subgrid or region contains each digit exactly once."<<endl<<endl;
gotoxy(15,28);
cout<<p<<" A sudoku puzzle typically has a unique solution."<<endl;
gotoxy(8,32);
cout<<q<<" "<<q<<" "<<q<<" Controls ---"<<endl;
gotoxy(15,36);
cout<<p<<" To put a number in a particular cell , enter <row index> <column index> <number> followed by enter."<<endl;
gotoxy(15,38);
cout<<"  For example, to put a number 6 in the 2nd row and 5th column , enter 2 5 6 followed by enter."<<endl;
gotoxy(15,42);
cout<<p<<" Options on the top-right corner of the screen can be accessed any time during the game."<<endl;
gotoxy(55,47);
cout<<"PRESS ANY KEY TO GET BACK TO THE PREVIOUS SCREEN"<<endl;
fflush(stdin);
getch();

}

//---------------------ABOUT SUDOKU implementation------------------//

void Menu::about_sudoku()
{
char p=219;
gotoxy(70,4);
  cout<<"ABOUT SUDOKU";
gotoxy(10,10);
cout<<p<<" Sudoku is a logical puzzle game, originally created in puzzle books and then made available in countless newspapers worldwide."<<endl;
gotoxy(10,14);
cout<<p<<" Sudoku originally called Number Place,is a logic-based combinatorial number-placement puzzle. "<<endl;
gotoxy(10,18);
cout<<p<<" The name Sudoku means \"single digits\", the word derives from the Japanese phrase \"Sūji wa dokushin ni kagiru,\" meaning \"the numbers must be single,"<<endl;
gotoxy(10,20);
cout<<"    \" or \"the numbers must occur only once."<<endl;
gotoxy(10,23);

cout<<p<<" Many people are put off by seeing a grid with numbers in it, but in fact the puzzle doesn't require any arithmetic at all - just deduction and logic. "<<endl;

gotoxy(55,28);
cout<<"PRESS ANY KEY TO GET BACK TO THE PREVIOUS SCREEN"<<endl<<endl<<endl;
fflush(stdin);
getch();

}


//---------------------CREDITS implementation------------------//

void Menu::credits()
{
system("cls");
gotoxy(58,20);
cout<<"This version of sudoku is created and developed by  ";
gotoxy(70,23);
cout<<"Nikhil Kumar Mopidevi";
gotoxy(39,30);
cout<<"If you have any queries or suggestions, send an email to nikhilkumarmopidevi@hotmail.com ";
gotoxy(58,45);
cout<<"PRESS ANY KEY TO GET BACK TO THE PREVIOUS SCREEN"<<endl<<endl<<endl;
fflush(stdin);
getch();


}


//------------------main function stars here------------------------------//

int main()
{
fullscreen();
char choice;
int returned_num;
bool flag=true;

do{ //displays the welcome screen
gotoxy(66,15);
cout<<"WELCOME TO SUDOKU"<<endl<<endl<<endl;

print_space(67);
cout<<left<<"1.PLAY GAME"<<endl<<endl;
print_space(67);
cout<<left<<"2.HELP"<<endl<<endl;
print_space(67);
cout<<left<<"3.ABOUT SUDOKU"<<endl<<endl;
print_space(67);
cout<<left<<"4.CREDITS"<<endl<<endl;
print_space(67);
cout<<left<<"5.QUIT"<<endl<<endl;

fflush(stdin);
cin>>choice;

if(choice>48 && choice<=53)
choice=(int)choice-48;

system("cls");

Menu game;


switch(choice)
{
case 1:
    flag=false;
    {

     returned_num=game.play_game();
     if(returned_num==1)
       flag=true;
     }

    break;
case 2:
    game.help();
    system("cls");
    break;
case 3:
    game.about_sudoku();
    system("cls");
    break;
case 4:
    game.credits();
    system("cls");
    break;
case 5:
    exit(1);
    break;
default:
    system("cls");
    break;
}
}while(flag==true);

return 0;
}
