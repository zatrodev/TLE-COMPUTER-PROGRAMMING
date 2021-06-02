#include <ncurses.h>
#include <vector>
#include <string>
using namespace std;

int columns, rows;
bool END = false;

const string WHITESPACE = " \n\r\t\f\v";

void layout(){
    for (int i = 0; i < columns - 1; ++i){
        mvaddch(0, i, '#');
        for (int j = 1; j < rows - 3; ++j)
            mvaddch(j, i, ' ');

        mvaddch(rows - 3, i, '#');
    }

    for (int i = 0; i < rows - 2; ++i){
        mvaddch(i, 0, '|');
        mvaddch(i, columns - 1, '|');
    }
}

void track(){
    static bool isMoving = true;

    if (isMoving){
        for (int i = 0; i < 2; ++i){
            for (int j = 1; j < columns - 1; ++j){
                mvaddch(((rows - 3) / 3) * (i + 1), j, '=');
                ++j;
            }
        }

        isMoving = false;
    }
    else {
        for (int i = 0; i < 2; ++i){
            for (int j = 1; j < columns - 1; ++j){
                ++j;
                mvaddch(((rows - 3) / 3) * (i + 1), j, '=');
            }
        }

        isMoving = true;
    }
}

string ltrim(string s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

int getMaxLength(vector <string> fig){
    int max = 0;
    
    for (int i = 0; i < fig.size(); ++i)
        max = (max < fig[i].length()) ? fig[i].length() : max;
        
    return max;
}

void draw(vector <string> fig, int figX, int figY){
    int spaceCount;

    for (int i = 0; i < fig.size(); ++i){
        spaceCount = 0;
        for (char i : fig[i]){
            if (i == ' ')
                ++spaceCount;
            else
                break;
        }

        mvaddstr(figY + i, figX + spaceCount, ltrim(fig[i]).c_str());
    }
}

void controller(int &botX, int &botY){
    switch (getch()){
        case 'w':
            botY -= 7;
            break;
        case 'a':
            botX -= 6;
            break;
        case 's':
            botY += 7;
            break;
        case 'd':
            botX += 6;
            break;
        case 'q':
            END = true;
            break;
    }
}

int main(){
    initscr();
    noecho();
    curs_set(0);
    scrollok (stdscr, TRUE);
    nodelay (stdscr, TRUE);
    
    getmaxyx(stdscr, rows, columns);

    vector <string> bot = {
        "    ____",
        "\\  i | o|",
        "|>#######",
        "/(_______)"
    };
    
    vector <string> bus = {
        "   _____________",
        " _/_|[][][][][] | - -",
        "(               | - -",
        "=--OO-------OO--="
    };
    
    int botX = 2;
    int botY = ((rows - 1) / 2) - (bot.size() / 2);

    int busX = columns - 2 - getMaxLength(bus);
    int busY = 2;
    
    while (!END){
        layout();
        track();
        draw(bot, botX, botY);
        draw(bus, busX, busY);         
        controller(botX, botY);
        
        napms(100);
        refresh();
    }
    
    endwin();
    
    return 0;
}
