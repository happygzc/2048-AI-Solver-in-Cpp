#ifndef BOARD_H
#define BOARD_H


class board
{
    public:
        board();
        void init();
        void display();
        int number();
        void add();
        void add(int);
        int max();
        void move(int);
        void merge(int);
        bool moveTo(int);
        void backup();
        void restore();
        bool test_move();
        bool isFull();
        bool isWin();
        int isOver();


//    private:
        int score = 0;
        int grid[4][4];
        int backup_grid[4][4];

};

#endif // BOARD_H
