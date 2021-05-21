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
        init_color(COLOR_BLACK, 0, 0, 0);
        init_pair(color, COLOR_BLACK, color);
        attron(COLOR_PAIR(color));
        
        for (float i = 2; i < topHeight; ++i)
        {
            if (i == topHeight - 1)
            {
                mvaddstr(i, pipeX, "[_]"); // moves the cursor and prints characters simulatenously
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
    for (int i = 2; i < columns - 1; ++i){
        mvaddch(1, i, '#');
        mvaddch(rows - 2, i, '#');
    }

    for (int i = 1; i < rows - 1; ++i){
        mvaddch(i, 2, '#');
        mvaddch(i, columns - 1, '#');
    }
}

int main()
{
    initscr();
    noecho();
    curs_set(0);
    resizeterm(22, 100);

    int columns, rows;
    int topHeight, botHeight;
    getmaxyx(stdscr, rows, columns);

    layout(columns, rows);

    for (int i = 1, j = 17, k = 32; i <= (columns - 3) / 3; ++i, ++j){
        srand(i);

        topHeight = rand() % (rows - 4) + 2;
        botHeight = (rows - 4) - topHeight + 2;

        if (i > ((columns - 3) / 3) / 2){
            Pipe(topHeight, botHeight, i * 3, rows - 3, k);
            --k;
        }
        else
            Pipe(topHeight, botHeight, i * 3, rows - 3, j);
    }

    refresh();
    while (getch() != 'q'){}
    
    endwin();

    return 0;
}
