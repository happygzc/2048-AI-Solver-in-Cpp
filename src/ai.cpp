#include "board.h"
#include "ai.h"
#include <cmath>
#include <stdlib.h>

int expectimax(board now, int depth, bool flag)
{
    if (depth == 0)
    {
        if (now.isOver())
            return -1;
        else
            return cal_eval(now);
    }

    if (flag)
    {
        int best = -1;
        for (int i = 0; i < 4; i++)
        {
            board next = now;
            if (!next.moveTo(i + 1))
                continue;

            int eval = expectimax(next, depth - 1, 0);
            if (eval > best)
                best = eval;
        }
        return best;
    }

    else
    {
        int sum_eval = 0, count = 0;
        for (int p = 0; p < 4; p++)
            for (int q = 0; q < 4; q++)
            {
                board next = now;
                if (next.grid[p][q] != 0)
                    continue;

                next.grid[p][q] = 2;
                sum_eval += expectimax(next, depth - 1, 1);
                //sum_eval += expectimax(next, depth - 1, 1) * 0.9;

                //next.grid[p][q] = 4;
                //sum_eval += expectimax(next, depth - 1, 1) * 0.1;
                count ++;
            }
        if (!count)
            return expectimax(now, depth - 1, 1);

        return sum_eval / count;
    }
}

int best_move(board now, int depth)
{
    int best = -1, action = 0;

    for (int i = 0; i < 4; i++)
    {
        board next = now;
        if (!next.moveTo(i + 1))
            continue;

        int eval = expectimax(next, depth - 1, 0);
        if (eval > best)
        {
            best = eval;
            action = i + 1;
        }
    }

    return action;
}

int cal_eval(board now)
{
    return cal_weight(now) - cal_cluster(now) + now.score + cal_free(now) * cal_free(now);
}

int cal_weight(board now)
{
    int w = 0;
    int weight[4][4] = {0, 0, 1, 3, 0, 1, 3, 5, 1, 3, 5, 15, 3, 5, 15, 30};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j ++)
            w += now.grid[i][j] * weight[i][j];
    return w / 16;
}

int cal_cluster(board now)
{
    int p = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int h = -1; h <= 1; h++)
                for (int k = -1; k <=1; k++)
                {
                    if (i + h > 3 || i + h < 0 || j + k > 3 || j + k < 0)
                        continue;
                    p += abs(now.grid[i + h][j + k] - now.grid[i][j]);
                }
    return p / 2;
}

int cal_mono(board now)
{
    int m = 0;
    for (int i = 1; i < 4; i++)
    {
        if (now.grid[3][i - 1] == 0)
            continue;
        m += (now.grid[3][i] / now.grid [3][i - 1] == 2);
    }

    for (int i = 1; i < 4; i++)
    {
        if (now.grid[i - 1][3] == 0)
            continue;
        m += (now.grid[i][3] / now.grid [i - 1][3] == 2);
    }

    return m * 20;
}

int cal_free(board now)
{
    int f = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (!now.grid[i][j])
                f ++;
    return f;
}
