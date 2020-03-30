#include "board.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cmath>

using namespace std;

board::board()
{
    init();
}

void board::init()
{
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            grid[i][j] = 0;

    grid[rand()%4][rand()%4] = number();
    add();
}

void board::display()
{
    system("cls");
    cout << setw(52) << endl << endl << "AI Application -- 2048 Game" << endl << endl;
    cout << setw(50) << " |-----------------------|" << endl;

    for (int i = 0; i <= 3; i++)
    {
        cout << setw(24) << "";
        for (int j = 0; j <= 3; j ++)
        {
            if (grid[i][j] == 0)
                cout << setw(2) << "|" << setw(4) << " ";
            else
                cout << setw(2) << "|" << setw(4) <<grid[i][j];

            if (j==3)
                {
                    cout << setw(2) << "|" << endl;
                    cout << setw(50) << " |-----------------------|" << endl;
                }
        }
    }
}

int board::number()
{
    if (rand() % 100 < 90)
        return 2;
    else
        return 4;
}

void board::add()
{
    if (!isFull())
    {
        int i = rand()%4;
        int j = rand()%4;
        while(grid[i][j])
            i = rand()%4, j = rand()%4;
        grid[i][j] = number();
    }
}

void board::add(int n)
{
    if (!isFull())
    {
        int i = rand()%4;
        int j = rand()%4;
        while(grid[i][j])
            i = rand()%4, j = rand()%4;
        grid[i][j] = n;
    }
}

int board::max()
{
    int m = 0;
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            if (grid[i][j] > m)
                m = grid[i][j];
    return m;
}

void board::move(int act)
{
    switch(act)
    {
        case 1:
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                if (!grid[j][i])
                    for (int k = j + 1; k <= 3; k++)
                        if (grid[k][i])
                        {
                            grid[j][i] = grid[k][i];
                            grid[k][i] = 0;
                            break;
                        }
        break;

        case 2:
        for (int i = 0; i <= 3; i++)
            for (int j = 3; j >= 0; j--)
                if (!grid[j][i])
                    for (int k = j - 1; k >= 0; k--)
                        if (grid[k][i])
                        {
                            grid[j][i] = grid[k][i];
                            grid[k][i] = 0;
                            break;
                        }
        break;

        case 3:
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                if (!grid[i][j])
                    for (int k = j + 1; k <= 3; k++)
                        if (grid[i][k])
                        {
                            grid[i][j] = grid[i][k];
                            grid[i][k] = 0;
                            break;
                        }
        break;

        case 4:
        for (int i = 0; i <= 3; i++)
            for (int j = 3; j >= 0; j--)
                if (!grid[i][j])
                    for (int k = j - 1; k >= 0; k--)
                        if (grid[i][k])
                        {
                            grid[i][j] = grid[i][k];
                            grid[i][k] = 0;
                            break;
                        }
        break;
    }
}

void board::merge(int act)
{
    switch(act)
    {
        case 1:
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[j][i] && grid[j][i] == grid[j+1][i])
                {
                    grid[j][i] *= 2;
                    score += grid[j][i];
                    grid[j+1][i] = 0;
                }
        break;

        case 2:
        for (int i = 0; i <= 3; i++)
            for (int j = 3; j > 0; j--)
                if (grid[j][i] && grid[j][i] == grid[j-1][i])
                {
                    grid[j][i] *= 2;
                    score += grid[j][i];
                    grid[j-1][i] = 0;
                }
        break;

        case 3:
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] && grid[i][j] == grid[i][j+1])
                {
                    grid[i][j] *= 2;
                    score += grid[i][j];
                    grid[i][j+1] = 0;
                }
        break;

        case 4:
        for (int i = 0; i <= 3; i++)
            for (int j = 3; j > 0; j--)
                if (grid[i][j] && grid[i][j] == grid[i][j-1])
                {
                    grid[i][j] *= 2;
                    score += grid[i][j];
                    grid[i][j-1] = 0;
                }
        break;
    }
}

bool board::moveTo(int act)
{
    backup();
    move(act);
    merge(act);
    move(act);
    return test_move();
}

void board::backup()
{
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            backup_grid[i][j] = grid[i][j];
}

void board::restore()
{
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            grid[i][j] = backup_grid[i][j];
}

bool board::test_move()
{
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            if (backup_grid[i][j] != grid[i][j])
                return 1;

    return 0;
}

bool board::isFull()
{
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            if (!grid[i][j])
                return 0;
    return 1;
}

int board::isOver()
{
    if (isFull())
    {
        backup();
        for (int i = 1; i <= 4; i++)
            merge(i);
        bool flag = test_move();
        restore();
        if (!flag)
            return 1;
    }
    return 0;
}

bool board::isWin()
{
    if (max() == 2048)
        return 1;
    else
        return 0;
}
