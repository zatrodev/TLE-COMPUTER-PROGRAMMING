#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

struct Pipe
{
    int topHeight, botHeight;
    int pipeX, pipeY;
    int color;

    Pipe(int topHeight, int botHeight, int pipeX, int pipeY, int color)
        : topHeight(topHeight)
        , botHeight(botHeight)
        , pipeX(pipeX)
        , pipeY(pipeY)
        , color(color)
    {   
        draw();
    }

    void draw()
    {
        start_color();
        init_pair(color, COLOR_BLACK, color);
        attron(COLOR_PAIR(color));
        
        for (float i = 2; i < topHeight; ++i)
        {
            if (i == topHeight - 1)
            {
                mvaddstr(i, pipeX, "[_]");
            }
            else {
                mvaddch(i, pipeX, '[');
                mvaddch(i, pipeX + 2, ']');
            }
        }

        for (float i = 0; i < botHeight; ++i)
        {
            if (i == botHeight - 1)
            {
                mvaddstr(pipeY - i, pipeX, "[^]");
            }
            else
            {
                mvaddch(pipeY - i, pipeX, '[');
                mvaddch(pipeY - i, pipeX + 2, ']');
            }
        }
        attroff(COLOR_PAIR(2));
    }
};

void layout(int columns, int rows){
    for (int i = 0; i < columns - 1; ++i){
        mvaddch(1, i, '#');
        mvaddch(rows - 2, i, '#');
        mvaddch(rows - 1, i, '_');
    }

    for (int i = 1; i < rows; ++i){
        mvaddch(i, 0, '|');
        mvaddch(i, columns - 1, '|');
    }
}

void pipe_setup(int &topHeight, int &botHeight, int rows){
    srand(time(NULL));
    
    topHeight = rand() % (rows - 12) + 3;
    botHeight = (rows - 4) - topHeight - 4;

    mvprintw(0, 0, "%d %d", topHeight, botHeight);
}


int main()
{
    initscr();
    noecho();
    curs_set(0);
    resizeterm(22, 100);

    int columns, rows;
    getmaxyx(stdscr, rows, columns);

    layout(columns, rows);

    for (int i = 1; i <= 10; ++i){
        srand(i);

        int topHeight = rand() % (rows - 12) + 3;
        int botHeight = (rows - 4) - topHeight - 4;

        Pipe(topHeight, botHeight, i * 10, rows - 3, i);
    }

    refresh();
    while (getch() != 'q'){}
    
    endwin();

    return 0;
}
