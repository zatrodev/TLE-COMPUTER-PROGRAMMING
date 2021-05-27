#include <ncurses.h>
#include <vector>
#include <string>
using namespace std;

int columns = 40, rows = 15;

void layout(){
    for (int i = 0; i < rows - 1; ++i){
        mvaddch(i, 0, 'o');
        mvaddch(i, columns - 1, 'o');
    }
    
    for (int i = 0; i < columns; ++i){
        mvaddch(0, i, '#');
        mvaddch(rows - 2, i, '#');
    }
}


void apple(){
    vector <string> apple = {
        " ,--./,-.",
        "/ #      \\",
       "|         |",
        "\\        /",
        " `._,._,'"
    };
    
    int appleX = 2, appleY = (rows / 2) - apple.size();
    
    for (int i = 0; i < apple.size(); ++i){
        mvaddstr(appleY + i, appleX, apple[i].c_str());
    }
}

void drink(){
    vector <string> drink = {
       "  ...",
      " \\~~~~~/",
      "  \\   /",
       "   \\ /",
       "    V",
       "    |",
       "    |",
      "   ---"
    };
    
    int drinkX = (columns / 2) - 2, drinkY = (rows / 2) - 5;
    
    for (int i = 0; i < drink.size(); ++i){
        mvaddstr(drinkY + i, drinkX, drink[i].c_str());
    }
}

void beer(){
    vector <string> beer = {
        ".~~~~.",
        "i====i_",
        "|cccc|_)",
        "|cccc|",
        "`-==-'"
    };
    
    int beerX = columns - 2 - beer[1].length(), beerY = (rows / 2);
    
    for (int i = 0; i < beer.size(); ++i){
        mvaddstr(beerY + i, beerX, beer[i].c_str());
    }
}

int main(){
    initscr();
    curs_set(0);
    
    layout();
    apple();
    drink();
    beer();
    
    refresh();
    getch();
    
    return 0;
}
