#include <iostream>
using namespace std;

struct Position {
    int x;
    int y;
};

struct PositionList {
    Position* ptr;
    int size;
};

struct Board {
    int** ptr;
    int size;
};

void printBoard(Board board) {
    int size = board.size;

    cout << "  ";

    for(int i = 0; i < size; i++) {
        cout << i << " ";
    }

    for(int i = 0; i < size; i++)
    {
        cout << endl;
        cout << i << " ";
        for(int j = 0; j < size; j++)
        {
            if(board.ptr[i][j] == 0) {
                cout << "- ";
            }
            else if(board.ptr[i][j] == 1) {
                cout << "X ";
            }
            else if(board.ptr[i][j] == 2) {
                cout << "O ";
            }
        }
    }
    cout << endl;
}

Board initBoard(int size) {
    Board board;
    board.size = size;

    board.ptr = new int*[size];

    for (int i = 0; i < size; i++) {
        board.ptr[i] = new int[size];
    }

    int i = size / 2 - 1;
    board.ptr[i][i] = 1;
    board.ptr[i][i + 1] = 2;
    board.ptr[i + 1][i] = 2;
    board.ptr[i + 1][i + 1] = 1;

    return board;
}

void addPosition(PositionList& positionList, Position position) {
    // TODO
}

PositionList getPositionList(Board board, int player) {
    PositionList positionList;
    positionList.size = 0;

    // TODO
    
    return positionList;
}

void playMoves(Board& board, int player, Position position) {
    // TODO
}

int main() {
    Board board = initBoard(8);
    printBoard(board);

    PositionList positionList = getPositionList(board, 1);

    for (int i = 0; i < positionList.size; i++) {
        cout << "(" << positionList.ptr[i].x << ", " << positionList.ptr[i].y << ")" << endl;
    }

    // TODO: Free memory

    return 0;
}
