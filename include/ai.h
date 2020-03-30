#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

int expectimax(board, int, bool);
int best_move(board, int);
int cal_eval(board);
int cal_weight(board);
int cal_cluster(board);
int cal_mono(board);
int cal_free(board);


#endif // AI_H_INCLUDED
