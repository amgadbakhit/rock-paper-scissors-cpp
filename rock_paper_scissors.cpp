#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;
enum engamechoice{stone=1,paper=2,scissor=3};
enum enwinner{player1=1,computer=2,draw=3};
struct stroundinfo{
    int roundnumber;
    engamechoice player1choice;
    engamechoice computerchoice;
    enwinner roundwinner;
    string namewinner;
};
struct stgameresult{
    int game_rounds;
    int player1wintimes;
    int computer2wintimes;
    int drawtimes;
    enwinner gamewinner;
    string winername;
};
int random_number(int from,int to){
    return rand()%(to-from+1)+from;
}
int how_many_rounds(){
    int round;
    do{
        cout<<"inter rounds from 1 to 10 ?\n";
        cin>>round;
    }while(round<1||round>10);
    return round;
}
engamechoice read_player1_choice(){
   int choice;
   do{
    cout<<"your choice stone [1]:paper [2]:sciscor[3]\n";
    cin>>choice;
   }while(choice <1||choice>3);
   return (engamechoice)choice;
}
engamechoice computer_choice(){
    return (engamechoice)random_number(1,3);
}
enwinner who_win_round(stroundinfo roundinfo){
    if(roundinfo.computerchoice==roundinfo.player1choice){
        return enwinner::draw;
    }
    switch(roundinfo.player1choice){
        case engamechoice::stone:
        if(roundinfo.computerchoice==engamechoice::scissor){
            return enwinner::player1;
        }
        case engamechoice::paper:
        if(roundinfo.computerchoice==engamechoice::stone){
           return enwinner::player1; 
        }
        case engamechoice::scissor:
        if(roundinfo.computerchoice==engamechoice::paper){
          return enwinner::player1;  
        }
    }
    return enwinner::computer;
}
string winer_name(enwinner winner){
    string arrwinner_name[3]={"player1","computer","draw"};
    return arrwinner_name[winner-1];
}
string choice_name(engamechoice choice){
    string arrchoice_name[3]={"stone","paper","scissor"};
    return arrchoice_name[choice-1];
}
void setwinner_screen(enwinner winner){
    switch(winner){
        case enwinner::computer:
        system("color 4F");
        cout << "\a";// explain
        break;
        case enwinner::player1:
        system("color 2F");
        break;
        default:
        system("color 6F");
        break;
    }
}
void print_round_result(stroundinfo roundinfo){
    cout<<"______________________ROUND["<<roundinfo.roundnumber<<"]______________________\n";
    cout<<"player1 choice "<<choice_name(roundinfo.player1choice)<<endl;
    cout<<"computer choice "<<choice_name(roundinfo.computerchoice)<<endl;
    cout<<"round winner["<<roundinfo.namewinner<<"]\n"<<endl;
    cout<<"____________________________________\n";
    setwinner_screen(roundinfo.roundwinner);
}
enwinner who_win_the_game(int player1winstime,int computer2winstime){
    if(player1winstime>computer2winstime){
        return enwinner::player1;
    }
    else if(player1winstime<computer2winstime){
        return enwinner::computer;
    }
    else{
        return enwinner::draw;
    }
}
stgameresult fill_game_result(int gamerounds,int player1wins,int computerwines,int drawtimes){
    stgameresult gameresult;
    gameresult.player1wintimes=player1wins;
    gameresult.computer2wintimes=computerwines;
    gameresult.drawtimes=drawtimes;
    gameresult.game_rounds=gamerounds;
    gameresult.gamewinner=who_win_the_game(player1wins,computerwines);
    gameresult.winername=winer_name(gameresult.gamewinner);
    return gameresult;
}
stgameresult play_game(int number_of_rounds){
    stroundinfo roundinfo;
    int play1winstime=0;
    int computerwinstime=0;
    int drawtimes=0;
    for(int i=1;i<=number_of_rounds;i++){
        cout<<"Round ["<<i<<"] begins"<<endl;
        roundinfo.player1choice=read_player1_choice();
        roundinfo.computerchoice=computer_choice();
        roundinfo.roundnumber=i;
        roundinfo.roundwinner=who_win_round(roundinfo);
        roundinfo.namewinner=winer_name(roundinfo.roundwinner);
        if(roundinfo.roundwinner==enwinner::computer){
            computerwinstime++;
        }
        else if(roundinfo.roundwinner==enwinner::player1){
            play1winstime++;
        }
        else{
            drawtimes++;
        }
        print_round_result(roundinfo);
    }
    return fill_game_result(number_of_rounds,play1winstime,computerwinstime,drawtimes);
}
string taps(int number_of_taps){
    string t="";
    for(int i=0;i<number_of_taps;i++){
        t+="\t";
    }
    return t;
}
void ShowGameOverScreen()
{
    cout << taps(2) << "------------------------------------------------\n\n";
    cout << taps(2) << "            +++ G a m e  O v e r +++\n";
    cout << taps(2) << "------------------------------------------------\n\n";
}
void show_final_game_result(stgameresult gameresult){
 cout << taps(2) << "----------------- [Game Results] -----------------\n\n";
    cout << taps(2) << "Game Rounds        : " << gameresult.game_rounds<< endl;
    cout << taps(2) << "Player1 Win Times  : " <<gameresult.player1wintimes<< endl;
    cout << taps(2) << "Computer Win Times : " <<gameresult.computer2wintimes<< endl;
    cout << taps(2) << "Draw Times         : " <<gameresult.drawtimes<< endl;
    cout << taps(2) << "Final Winner       : " <<gameresult.winername<< endl;
    cout << taps(2) << "-----------------------------------------------------\n";
    setwinner_screen(gameresult.gamewinner);
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void start_game(){
    char playagain='y';
    do{
        ResetScreen();
        stgameresult gameresult=play_game(how_many_rounds());
        ShowGameOverScreen();
        show_final_game_result(gameresult);
        cout << endl << taps(3) << "Do you want to play again? Y/N? ";
        cin>>playagain;
    }while(playagain=='y'||playagain=='Y');
}

int main(){
    srand((unsigned)time(NULL));
start_game();
}