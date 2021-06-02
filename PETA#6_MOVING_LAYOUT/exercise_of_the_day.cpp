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

void controller(int &carX, int &carY){
    switch (getch()){
        case 'w':
            carY -= 7;
            break;
        case 'a':
            carX -= 6;
            break;
        case 's':
            carY += 7;
            break;
        case 'd':
            carX += 6;
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
    
    vector <string> car = {
        "  ______",
        " /|_||_\\`.__",
        "(   _    _ _\\",
        "=`-(_)--(_)-'"
    };

    vector <string> train = {
        "      ___",
        " _][__| |",
        "<_______|-1",
        "  O-O-O"
    };
    
    int carX = 2;
    int carY = ((rows - 1) / 2) - (car.size() / 2);

    int trainX = columns - 2 - getMaxLength(train);
    int trainY = 2;
    
    while (!END){
        layout();
        track();
        draw(car, carX, carY);
        draw(train, trainX, trainY);         
        controller(carX, carY);
        
        napms(100);
        refresh();
    }
    
    endwin();
    
    return 0;
}
