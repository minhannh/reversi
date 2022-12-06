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

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board.ptr[i][j] = 0;
        }
    }

    int i = size / 2 - 1;
    // board.ptr[i][i] = 1;
    // board.ptr[i][i + 1] = 2;
    // board.ptr[i + 1][i] = 2;
    // board.ptr[i + 1][i + 1] = 1;
    board.ptr[2][3] = 2;
    board.ptr[3][4] = 2;
    board.ptr[4][5] = 1;

    // board.ptr[6][4] = 2;

    return board;
}

void addPosition(PositionList& positionList, Position position) {
    // Step 1: Allocate array and assign to new ptr
    Position* newptr;
    newptr = new Position[positionList.size + 1];

    // Step 2: Copy data from old ptr to new ptr
    for (int i = 0; i < positionList.size; i++) {
        newptr[i].x = positionList.ptr[i].x;
        newptr[i].y = positionList.ptr[i].y;
    }

    // Step 3: Add element to array of new ptr
    newptr[positionList.size].x = position.x;
    newptr[positionList.size].y = position.y;

    // Step 4: Free array of old ptr
    if (positionList.ptr != nullptr) {
        delete[] positionList.ptr;
    }

    // Step 5: Direct old ptr to array which new ptr holds
    positionList.ptr = newptr;

    // Step 6: Increase size of positionList
    positionList.size++;
}

PositionList getPositionList(Board board, int player) {
    PositionList positionList;
    positionList.size = 0;
    positionList.ptr = nullptr;

    // TODO
    int size = board.size;
    // PLAYER 1
    // Horizontal
    if (player == 1) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                // Case 1: 001200
                if ((board.ptr[i][j] == 2) && (board.ptr[i][j - 1] == 1) && (board.ptr[i][j + 1] == 0)) {
                    Position position;
                    position.x = i;
                    position.y = j + 1;
                    addPosition(positionList, position);
                }
                // Case 2: 002100
                if ((board.ptr[i][j] == 2) && (board.ptr[i][j - 1] == 0) && (board.ptr[i][j + 1] == 1)) {
                        Position position;
                        position.x = i;
                        position.y = j - 1;
                        addPosition(positionList, position);
                }
                // Case 3: 0022210
                if ((board.ptr[i][j] == 2) && (board.ptr[i][j - 1] == 0) && (board.ptr[i][j + 1] == 2)) {
                    int iPosition = i;
                    int jPosition = j;
                    int pos = 1;
                        for (int y = jPosition; y < size; y++) {
                            if (board.ptr[iPosition][y] == 0) {
                                break;
                            }
                            else if (board.ptr[iPosition][y] == 1) {
                                Position position;
                                position.x = i;
                                position.y = j - 1;
                                addPosition(positionList, position);
                                break;
                            }
                        }
                }
                // Case 4: 0122000
                if ((board.ptr[i][j] == 2) && (board.ptr[i][j - 1] == 1) && (board.ptr[i][j + 1] == 2)) {
                    int iPosition = i;
                    int jPosition = j;
                        for (int y = jPosition; y < size; y++) {
                            if (board.ptr[iPosition][y] == 1) {
                                break;
                            }
                            else if (board.ptr[iPosition][y] == 0) {
                                Position position;
                                position.x = i;
                                position.y = y;
                                addPosition(positionList, position);
                                break;
                            }
                        }
                }
            
            }
        }
    }
    // Vertical
    if (player == 1) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                // Case 1: 001200
                if ((board.ptr[i][j] == 2) && (board.ptr[i - 1][j] == 1) && (board.ptr[i + 1][j] == 0)) {
                    Position position;
                    position.x = i + 1;
                    position.y = j;
                    addPosition(positionList, position);
                }

                // Case 2: 002100
                if ((board.ptr[i][j] == 2) && (board.ptr[i - 1][j] == 0) && (board.ptr[i + 1][j] == 1)) {
                    Position position;
                    position.x = i - 1;
                    position.y = j;
                    addPosition(positionList, position);
                }

                // Case 3: 022100
                if ((board.ptr[i][j] == 2) && (board.ptr[i - 1][j] == 2) && (board.ptr[i + 1][j] == 1)) {
                    int iPosition = i - 1;
                    int jPosition = j;
                    int pos = 1;
                    for (int x = iPosition; x > 0; x--) {
                            if (board.ptr[iPosition - pos][jPosition] == 1) {
                                break;
                            }
                            else if (board.ptr[iPosition - pos][jPosition] == 0) {
                                Position position;
                                position.x = iPosition - pos;
                                position.y = jPosition;
                                addPosition(positionList, position);
                                break;
                            }
                            pos++;
                    }
                }

                // Case 4: 012200
                if ((board.ptr[i][j] == 2) && (board.ptr[i - 1][j] == 1) && (board.ptr[i + 1][j] == 2)) {
                    int iPosition = i + 1;
                    int jPosition = j;
                    int pos = 1;
                    for (int x = iPosition; x < size; x++) {
                        if (board.ptr[x][jPosition] == 1) {
                            break;
                        }
                        else if (board.ptr[x][jPosition] == 0) {
                            Position position;
                            position.x = x;
                            position.y = jPosition;
                            addPosition(positionList, position);
                            break;
                        }
                    }
                }

            }
        }
    }

    //Left Diagonal
    if (player == 1) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                // Case 1: 001200
                if ((board.ptr[i][j] == 2) && (board.ptr[i - 1][j - 1] == 1) && (board.ptr[i + 1][j + 1] == 0)) {
                    Position position;
                    position.x = i + 1;
                    position.y = j + 1;
                    addPosition(positionList, position);
                }

                // Case 2: 002100
                if ((board.ptr[i][j] == 2) && (board.ptr[i - 1][j - 1] == 0) && (board.ptr[i + 1][j + 1] == 1)) {
                    Position position;
                    position.x = i - 1;
                    position.y = j - 1;
                    addPosition(positionList, position);
                }

                // Case 3:022100
                if ((board.ptr[i][j] == 2) && (board.ptr[i - 1][j - 1] == 2) && (board.ptr[i + 1][j + 1] == 1)) {
                    int y = j;
                    for (int x = i; x >= 0; x--) {
                        if (board.ptr[x][y] == 1) {
                            break;
                        }
                        else if (board.ptr[x][y] == 0) {
                            Position position;
                            position.x = x;
                            position.y = y;
                            addPosition(positionList, position);
                        }
                            y--;
                    }
                }
            }
        }
    } 

    // Position position;
    // position.x = 9;
    // position.y = 2;
    // addPosition(positionList, position);

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

    // Free memory
    for (int i = 0; i < board.size; i++) {
        delete[] board.ptr[i];
    }

    delete[] board.ptr;
    delete[] positionList.ptr;

    return 0;
}
