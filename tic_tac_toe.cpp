#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>

using namespace std;


struct tic_tac_toe
{
    char board[3][3];
    char player1;
    char cpu;
    char player2;
};

struct point
{
    int x;
    int y;
};

struct AImove
{
    AImove() {};
    AImove(int s) : score(s){};
    int x;
    int y;
    int score;
};


void initialise(char board[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            board[i][j]='.';
        }
    }
}

bool question_player(void)
{
    int player;
    cout<<"Would you like to play two player or a one player game"<<endl;
    cout<<"Press 1 for 1 player game and 2 for 2 player game"<<endl;
    cin>>player;
    if(player!=1 && player!=2)
    {
        cout<<"Please enter a valid number"<<endl;
        question_player();
    }
    else if(player==2)
        return true;
    else
        return false;
}

char determine_player_choice(string s)
{
    while(1)
    {
        string choice;
        cout<<s<<" What would you like your character to be: ";
        cin>>choice;
        if(choice.size()>1)
        {
            cout<<"Please enter one character only"<<endl;
            continue;
        }
        if(choice[0]!='X' && choice[0]!='x' && choice[0]!='O' && choice[0]!='o')
        {
            cout<<"Please select either X or O,since it's a tic tac toe game :)"<<endl;
            continue;
        }
        return choice[0];
    }
}

char determine_cpu_choice(char player)
{
    if(player=='X' || player=='x')
        return 'O';
    else
        return 'X';
}

void print_board(char board[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<board[i][j]<<' ';
        }
        cout<<endl;
    }
}

char determine_player2_choice(char player1)
{
    while(1)
    {
        string choice;
        cout<<"Player 2,Please enter your choice: ";
        cin>>choice;
        if(choice.size()>1)
        {
            cout<<"Please enter only one character"<<endl;
            continue;
        }
        else if(player1==choice[0])
        {
            cout<<"You have chosen the same character as that of player 1,Please choose different character"<<endl;
            continue;
        }
        return choice[0];
    }
}

void change_player(int *player)
{
    if(*player==1)
        *player=2;
    else
        *player=1;
}

bool check_point(point *p)
{
    if(p->x>2 || p->x<0)
    {
        cout<<"Please enter X co-ordinate in [0,2]"<<endl;
        return false;
    }
    if(p->y<0 || p->y>2)
    {
        cout<<"Please enter Y co-ordinate in [0,2]"<<endl;
        return false;
    }
    return true;
}

char check_winner(char board[3][3],char p1,char p2)
{
    char winner;
    int i,j;
    for(i=0;i<3;i++){
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2]){
            winner=board[i][0];
        }
    }
    for(j=0;j<3;j++){
        if(board[0][j]==board[1][j] && board[1][j]==board[2][j]){
            winner=board[0][j];
        }
    }
    if(board[1][1]==board[0][0] && board[0][0]==board[2][2]){
        winner=board[1][1];
    }
    if(board[2][0]==board[1][1] && board[1][1]==board[0][2])
        winner=board[1][1];
    if(winner!='.'){
        if(winner==p1)
            return p1;
        else if(winner==p2)
            return p2;
    }
    return 'n';
}

inline void place_point(tic_tac_toe *game,point p,int pl)
{
    if(pl==1)
    {
        game->board[p.x][p.y]=game->player1;
    }
    else
    {
        game->board[p.x][p.y]=game->player2;
    }
}

void play_game2_player(tic_tac_toe *game)
{
    int player_no=1;
    point p;
    int moves=0;
    while(moves<9)
    {
        print_board(game->board);
        cout<<"Player "<<player_no<<" Please enter the co-ordinates of the point you want to place: ";
        cin>>p.x>>p.y;
        if(!check_point(&p))
            continue;
        if(game->board[p.x][p.y]!='.')
        {
            cout<<"Position is already filled.Select different one"<<endl;
            continue;
        }
        place_point(game,p,player_no);
        if(check_winner(game->board,game->player1,game->player2)==game->player1)
        {
            print_board(game->board);
            cout<<"Player 1 won"<<endl;
            exit(1);
        }
        if(check_winner(game->board,game->player1,game->player2)==game->player2)
        {
            print_board(game->board);
            cout<<"Player 2 won"<<endl;
            exit(1);
        }
        change_player(&player_no);
        moves++;
    }
    print_board(game->board);
    cout<<"Game tied"<<endl;
}

int counter(char board[3][3]){
    int count=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]!='.')
                count++;
        }
    }
    return count;
}

AImove getBestmove(tic_tac_toe *game,char player)
{
    vector<AImove> moves;
    if(check_winner(game->board,game->player1,game->cpu)==game->cpu){
        return AImove(10);
    }else if(check_winner(game->board,game->player1,game->cpu)==game->player1){
        return AImove(-10);
    }else if(counter(game->board)==9 && check_winner(game->board,game->player1,game->cpu)=='n'){
        return AImove(0);
    }
    for(int j=0;j<3;j++){
        for(int i=0;i<3;i++){
            if(game->board[i][j]=='.'){
                AImove move; 
                move.x=i;
                move.y=j;
                game->board[i][j]=player;
                if(player==game->cpu){
                    move.score=getBestmove(game,game->player1).score;
                }else{
                    move.score=getBestmove(game,game->cpu).score;
                }
                moves.push_back(move);
                game->board[i][j]='.';
            }
        }
    }
    int bestMove=0;
    if(player==game->cpu){
        int bestScore=-100000;
        for(int i=0;i<moves.size();i++){
            if(moves[i].score>bestScore){
                bestScore=moves[i].score;
                bestMove=i;
            }
        }
    }else{
        int bestScore=100000;
        for(int i=0;i<moves.size();i++){
            if(moves[i].score<bestScore){
                bestScore=moves[i].score;
                bestMove=i;
            }
        }
    }
    return moves[bestMove];
} 

void play_game1_player(tic_tac_toe *game)
{
    int moves=0;
    AImove getMove;
    int curr_player=1;
    while(moves<9){
        if(curr_player==1){
            print_board(game->board);
            cout<<"Please enter the co-ordinate to place: ";
            point p;
            cin>>p.x>>p.y;
            if(!check_point(&p)){
                continue;
            }
            if(game->board[p.x][p.y]!='.'){
                cout<<"Position is already filled.Please choose another one"<<endl;
                continue;
            }
            game->board[p.x][p.y]=game->player1;
            curr_player=2;
        }
        else{
            getMove=getBestmove(game,game->cpu);
            game->board[getMove.x][getMove.y]=game->cpu;
            curr_player=1;
        }
        if(check_winner(game->board,game->player1,game->cpu)==game->player1){
            print_board(game->board);
            cout<<"Player 1 won"<<endl;
            exit(1);
        }else if(check_winner(game->board,game->player1,game->cpu)==game->cpu){
            print_board(game->board);
            cout<<"CPU won"<<endl;
            exit(2);
        }
        moves++;
    }
    print_board(game->board);
    cout<<"Game tied"<<endl;
}

int main()
{
    tic_tac_toe game;
    initialise(game.board);
    bool two_player=question_player();
    if(!two_player)
    {
        game.player1=determine_player_choice("Player 1");
        game.cpu=determine_cpu_choice(game.player1);
        play_game1_player(&game);    
    }
    else
    {
        game.player1=determine_player_choice("Player 1");
        game.player2=determine_player2_choice(game.player1);
        play_game2_player(&game);
    }
    return 0;
}