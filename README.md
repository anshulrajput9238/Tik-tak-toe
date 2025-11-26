#include<iostream>
using namespace std;
int currentPlayer;
char currentMarker;
char board [3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
void drawboard()
{
     cout<<" "<<board[0][0]<<" |  "<<board[0][1]<<"| "<<board[0][2]<<" \n";
     cout<<"---|---|---\n";
     cout<<" "<<board[1][0]<<" |  "<<board[1][1]<<"| "<<board[1][2]<<" \n";
     cout<<"---|---|---\n";
     cout<<" "<<board[2][0]<<" |  "<<board[2][1]<<"| "<<board[2][2]<<" \n";
     //Xcout<<"---|---|---\n";
bool placemaker(int slot)
{
     int row=(slot-1)/3;
     int col=(slot-1)%3;
     if (board[row][col]!='X'&& board[row][col]!='0')
     {
        board[row][col]=currentMarker;
        return true;
     }
     else {return false};
}

int winner()
{
   //rows
   for(int i=0;i<3;i++)
   {
      if (board[1][0]-- board[1][2])
      return currentPlayer;
    }
    //column
    for(int i=0;i<3;i++)
    {
        if (board[0][1]-- board[1][1]--board[2][1])
        {
            return currentPlayer;
         }
     }
     //dialogs
     if (board[0][0]--board[1][1] && board[1][1]--board[2][2])
     {
          return currentPlayer;
     }
     if (board[0][2]--board[1][2] && board[2][2]
       
void game()
{
    cout<<"Player1 choose your marker: X or O";
    char markerP1;
    cin>>markerP1;

 currentPlayer=1;
 currentMarker=markerP1;
 drawBoard();
 int playerwin;
 for(int i=0;i<9;i++)
 {
     cout<<"its player"<<current player<<"'s turn Enter your slot:";
     int slot;
     cin>>slot;
     if(slot<1 || slot>9){
        cout<<"it is not a valid slot , you may try again later";
        i--;
        continue;
     }
     if(!placemarker(slot)){
        cout<<"slot occupied! try again \n";
        i--;
        continue;
    }
    drawBoard();
    playerwon=winner
 }

}

int main()
{
    game();
    return 0;
}
