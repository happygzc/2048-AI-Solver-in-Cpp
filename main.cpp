#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "board.h"
#include "ai.h"

using namespace std;

int main()
{
    srand(time(NULL));
    board bd;

    while (true)
    {
        bd.display();
        int depth;
        if (cal_free(bd) <= 4)
            depth = 6;
        else
            depth = 5;
        int action = best_move(bd, depth);
        if (action == 0)
            action = rand() % 4 + 1;
        if (bd.moveTo(action))
            bd.add();
        if (bd.isOver())
        {
            bd.display();
            cout << "Final Score: " << bd.score << endl;
            cout << "Game Over!" << endl;
            return 0;
        }
        if (bd.isWin())
        {
            bd.display();
            cout << "Final Score: " << bd.score << endl;
            cout << "Win!" << endl;
            return 1;
        }
    }
    return -1;
}
