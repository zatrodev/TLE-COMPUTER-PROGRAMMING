#include <ncurses.h>
#include <vector>
#include <string>
using namespace std;

void layout(vector <string> tree){
    int rows = tree.size() + 2, columns;
    int max = 0;

    for (int i = 0; i < tree.size(); ++i){
        if (tree[i].length() > max)
            max = tree[i].length();
    }

    columns = max + 2;

    resizeterm(rows, columns);

    for (int i = 0; i < columns; ++i){
        mvaddch(0, i, '#');
        mvaddch(rows - 1, i, '#');
    }

    for (int i = 0; i < rows; ++i){
        mvaddch(i, 0, '|');
        mvaddch(i, columns - 1, '|');
    }
}

void draw(vector <string> tree){
    int color;

    start_color();

    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_RED, 165, 116, 73);
    init_color(COLOR_YELLOW, 255, 255, 0);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    for (int i = 0; i < tree.size(); ++i){
        for (int j = 0; j < tree[i].length(); ++j){
            start_color();
            switch(tree[i][j]){
                case '"':
                case '+':
                    color = 1;
                    attron(COLOR_PAIR(color));  
                    break;
                case '0':
                case'O':
                    color = 2;
                    attron(COLOR_PAIR(color));
                    attron(A_BOLD);
                    break;
                case '.':
                    color = 3;
                    attron(COLOR_PAIR(color));
                    break;
                case '#':
                    color = 4;
                    attron(COLOR_PAIR(color));
                    break;
            }

            mvaddch(i + 1, j + 1, tree[i][j]);
            attroff(COLOR_PAIR(color));
        }
        // mvaddstr(i + 1, 1, tree[i].c_str());
    }
}

int main(){
    initscr();
    curs_set(0);

    int columns, rows;
    getmaxyx(stdscr, rows, columns);

    vector <string> tree = {
        "          .     .  .      +     .      .          .",
        "     .       .      .     #       .           .",
        "        .      .         ###            .      .      .",
        "      .      .   \"#:. .:##\"##:. .:#\"  .      .",
        "          .      . \"####\"###\"####\"  .",
        "       .     \"#:.    .:#\"###\"#:.    .:#\"  .        .       .",
        "  .             \"#########\"#########\"        .        .",
        "        .    \"#:.  \"####\"###\"####\"  .:#\"   .       .",
        "     .     .  \"#######\"\"##\"##\"\"#######\"                  .",
        "                .\"##\"#####\"#####\"##\"           .      .",
        "    .   \"#:. ...  .:##\"###\"###\"##:.  ... .:#\"     .",
        "      .     \"#######\"##\"#####\"##\"#######\"      .     .",
        "    .    .     \"#####\"\"#######\"\"#####\"    .      .",
        "            .     \"      000      \"    .     .",
        "       .         .   .   000     .        .       .",
        ".. .. ..................O000O........................ ......"
    };

    layout(tree);
    draw(tree);

    refresh();
    while(getch() != 'q'){}

    endwin();

    return 0;
}
