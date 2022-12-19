#include<bits/stdc++.h>
#include<ctime>
#include<cstdlib>
#include<iomanip>

using namespace std;

int board[4][4];
// to change the directions along Y axis
int delrow[] = {1,0,-1,0};
// to change the directions along X axis
int delcol[] = {0,1,0,-1};
// to generate a random positon for putting the values each time a line is empty and after a move is made
pair<int,int> generate_unoccupied_pos(){
    int occupied = 1,row,col;
    while(occupied){
        row = rand()%4;
        col = rand()%4;
        if(board[row][col] == 0){
            occupied = 0;

        }
    }
    return make_pair(row,col);
}
void add_piece(){
    pair<int,int>pos = generate_unoccupied_pos();
    board[pos.first][pos.second] = 2;
}
void new_game(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            board[i][j]=0;
        }
    }
    add_piece();
}

// to print the UI and display the functions
void printUI(){
    cout<<"the goal is to make 2048"<<endl;
    system("cls");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j] == 0){
                cout<<setw(4)<<'.';
            }
            else{
                cout<<setw(4)<<board[i][j];
            }
            
        }
        cout<<endl;
    }
    cout<<"n: new game, w: up, s: down, d: right, a: left, q: quit"<<endl;
}

bool is_move_possible(int row,int col,int nr,int nc){
    if(nr<0 || nr>=4  || nc<0 || nc>=4 || board[row][col]!=board[nr][nc] && board[nr][nc]!=0){
        return false;
    }
    return true;
}
// applying the moves in the game
int flag = 0;
void apply_move(int direction){
    int startrow = 0,startcol = 0,row_step=1,col_step=1;
    if(direction == 0){
        startrow = 3;
        row_step=-1;
    }
    if(direction == 1){
        startcol = 3;
        col_step = -1;
    }
    
    int movePossible,canAddpeice=0;
    do{
    movePossible = 0;
    for(int i=startrow;i>=0 && i<4;i+=row_step){
        for(int j=startcol;j>=0  && j<4;j+=col_step){
            int nr = i+delrow[direction];
            int nc = j+delcol[direction];
            // cout<<i<<' '<<j<<" "<<nr<<' '<<nc<<' '<<endl;
            // we are facing segmentation fault here because the program also makes the move to add two zeros(0's)
            // but we only need to add the non zero values hence we can check if its zero or not then apply our move
            if( board[i][j] && is_move_possible(i,j,nr,nc)){
                board[nr][nc]+=board[i][j];
                if(board[nr][nc] == 2048){
                    cout<<"You won"<<endl;
                    flag = 1;
                    return;
                }
                
                board[i][j]=0;
                movePossible = 1;
                canAddpeice=1;  
                // add_piece();
            }
        }
    }
    }while(movePossible);
    if(canAddpeice){
        add_piece();
    }
    
}


int main(){   
    srand(time(0));
    
    new_game();
    
    // mapping the directions to the digits
    char command_to_dir[128];
    command_to_dir['s'] = 0; 
    command_to_dir['d'] = 1;
    command_to_dir['w'] = 2;
    command_to_dir['a'] = 3;
    // the player can play as long as they want that is the reason we're using while true
    while(true){
        printUI();
        char command;
        cin>>command;
        if(command == 'n'){
            new_game();
        }
        else if(command == 'q'){
            break;
        }
        else{
            int direction = command_to_dir[command];
            apply_move(direction);
            // add_piece();
            if(flag == 1){
                break;
            }
        }

    }
   
    cout<<"Created By: sdakshya23"<<endl<<endl;
    return 0;
}