#include <ncurses.h>
#include <vector>
#include <string>
using namespace std;

struct COORD {
    int x;
    int y;
} WOLF, MOON, CLOUD1, CLOUD2, STARS;

int columns, rows;

void setup(vector <string> &wolf, vector <string> &moon, vector <string> &cloud){
    int moonMax = 0;
    int cloudMax = 0;

    resizeterm(30, 50);
    getmaxyx(stdscr, rows, columns);

    WOLF.x = 1;
    WOLF.y = rows - 1 - wolf.size();
    
    for (int i = 0; i < moon.size(); ++i)
        moonMax = (moonMax < moon[i].length()) ? moon[i].length() : moonMax;

    for (int i = 0; i < cloud.size(); ++i)
        cloudMax = (cloudMax < cloud[i].length()) ? cloud[i].length() : cloudMax;
    
    MOON.x = columns - cloudMax - moonMax;
    MOON.y = 2;

    CLOUD1.x = MOON.x - 10;
    CLOUD1.y = 4;

    CLOUD2.x = columns - cloudMax - 5;
    CLOUD2.y = 6;

    STARS.x = 1;
    STARS.y = 1;
}

void layout(){
    for (int i = 0; i < columns - 1; ++i){
        mvaddch(0, i, '#');
        mvaddch(rows - 1, i, '#');
    }

    for (int i = 0, k = 1; i < rows; ++i, ++k){
        mvaddch(i, 0, '|');
        mvaddch(i, columns - 1, '|');
    }

    mvaddstr(rows / 2, (columns / 2) - 9, "B L O O D  M O O N");
}

void draw(vector <string> fig, COORD coord){
    if (coord.x == WOLF.x && coord.y == WOLF.y){
        for (int i = 0; i < fig.size(); ++i){
            for (int j = 0; j < fig[i].length(); ++j){
                switch(fig[i][j]){
                    case '.':
                        attron(COLOR_PAIR(2));
                        break;
                }

                mvaddch(coord.y + i, coord.x + j, fig[i][j]);
                attroff(COLOR_PAIR(2));
            }
        }
    }

    else {
        for (int i = 0; i < fig.size(); ++i)
            mvaddstr(coord.y + i, coord.x, fig[i].c_str());
    }
}

int main(){
    initscr();
    curs_set(0);

    vector <string> wolf = {
        "  .   .      .    .      .      .       .  .    ",
        ".  .    .     .      .    .  .    .     .   .",
        "  .   .      .    .      .      .       .  .    ",
        ".  .    .     .      .    .  .    .     .   .",
        "  .    .       .    / V\\  .    .       .     .",
        "    .      .      / `  /    .      .      .",
        " .      .    .   <<   |    .  .    .     .     .",
        "  .     .    .   /    |  .    .       .      .  ",
        "    .     .    /      |   .  .    .     .",
        "  .      .   /        |     .     .      .    . ",
        "      .    /    \\  \\ /   .     .    .        .",
        "  .   .   (      ) | | .      .    .      .    .",
        "  ________|   _/_  | |  .    .    .      .   .",
        "<__________\\______)\\__)    .      .    .     ."
    };

    vector <string> moon = {
        "   _.-'''-._",
        "  .'   .-'``|'.",
        " /    /    -*- \\",
        ";    /      |   ;",
        "|    | |       |", 
        ";    \\ -*- |    ;",
        " \\    \\  | -*-  /",
        "  '._ '.__ |_.'",
        "     '-----'"
    };

    vector <string> cloud = {
        "     .-.",
        "  .-(   )-.",
        " (     __) )-.",
        "  `-(       __)",
        "    `(____)-'"
    };
    
    vector <string> stars = {
        "     .     .  .      .     .      .     .    .",
        "  .       .      .     .       .   .       .",
    };
    
    setup(wolf, moon, cloud);

    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    for (int i = 0; i < 7; ++i){
        draw(stars, STARS);
        STARS.y += 2;
    }
    attroff(COLOR_PAIR(1));

    init_pair(2, 8, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    draw(cloud, CLOUD1);
    draw(cloud, CLOUD2);
    attroff(COLOR_PAIR(2));

    init_pair(3, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(3));
    draw(moon, MOON);
    attroff(COLOR_PAIR(3));

    draw(wolf, WOLF);

    layout();
    
    refresh();
    while (getch() != 'q'){}

    endwin();
    
    return 0;
}
