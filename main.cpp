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

    board.ptr[3][3] = 1;
    board.ptr[4][3] = 1;
    board.ptr[5][3] = 1;
    board.ptr[6][3] = 1;
    board.ptr[4][2] = 1;
    board.ptr[6][2] = 1;
    board.ptr[6][4] = 1;

    board.ptr[5][1] = 2;
    board.ptr[5][2] = 2;
    board.ptr[5][4] = 2;

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
    int play;
    int rival;

    if (player == 1) {
        play = 1;
        rival = 2;
    } else if (player == 2) {
        play = 2;
        rival = 1;
    }

    // Horizontal
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Case 1: 001200
            if ((board.ptr[i][j] == rival) && (board.ptr[i][j - 1] == play) && (board.ptr[i][j + 1] == 0)) {
                Position position;
                position.x = i;
                position.y = j + 1;
                addPosition(positionList, position);
                
            }

            // Case 2: 002100
                if ((board.ptr[i][j] == rival) && (board.ptr[i][j - 1] == 0) && (board.ptr[i][j + 1] == play)) {
                    Position position;
                    position.x = i;
                    position.y = j - 1;
                    addPosition(positionList, position);
                    
                }

            // Case 3: 002210
            if ((board.ptr[i][j] == rival) && (board.ptr[i][j - 1] == 0) && (board.ptr[i][j + 1] == rival) && (board.ptr[i][j + 2] == play)) {
                int jPosition = j;
                    for (int y = jPosition; y < size; y++) {
                        if (board.ptr[i][y] == 0) {
                            break;
                        }
                        else if (board.ptr[i][y] == play) {
                            Position position;
                            position.x = i;
                            position.y = j - 1;
                            addPosition(positionList, position);
                            break;
                        }
                    }
            }
            // Case 4: 0122000
            if ((board.ptr[i][j] == rival) && (board.ptr[i][j - 1] == play) && (board.ptr[i][j + 1] == rival)) {
                int iPosition = i;
                int jPosition = j;
                    for (int y = jPosition; y < size; y++) {
                        if (board.ptr[iPosition][y] == play) {
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
    
    // Vertical
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Case 1: 001200
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j] == play) && (board.ptr[i + 1][j] == 0)) {
                Position position;
                position.x = i + 1;
                position.y = j;
                addPosition(positionList, position);
                
            }

            // Case 2: 002100
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j] == 0) && (board.ptr[i + 1][j] == play)) {
                Position position;
                position.x = i - 1;
                position.y = j;
                addPosition(positionList, position);
                
            }

            // Case 3: 022100
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j] == rival) && (board.ptr[i + 1][j] == play)) {
                int iPosition = i - 1;
                int jPosition = j;
                int pos = 1;
                for (int x = iPosition; x >= 0; x--) {
                    if (board.ptr[iPosition - pos][jPosition] == play) {
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
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j] == play) && (board.ptr[i + 1][j] == rival)) {
                int iPosition = i + 1;
                int jPosition = j;
                int pos = 1;
                for (int x = iPosition; x < size; x++) {
                    if (board.ptr[x][jPosition] == play) {
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

    //Left Diagonal
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Case 1: 001200
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j - 1] == play) && (board.ptr[i + 1][j + 1] == 0)) {
                Position position;
                position.x = i + 1;
                position.y = j + 1;
                addPosition(positionList, position);
                
            }

            // Case 2: 002100
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j - 1] == 0) && (board.ptr[i + 1][j + 1] == play)) {
                Position position;
                position.x = i - 1;
                position.y = j - 1;
                addPosition(positionList, position);
                
            }

            // Case 3:022100
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j - 1] == rival) && (board.ptr[i + 1][j + 1] == play)) {
                int y = j;
                for (int x = i; x >= 0; x--) {
                    if (board.ptr[x][y] == play) {
                        break;
                    }
                    else if (board.ptr[x][y] == 0) {
                        Position position;
                        position.x = x;
                        position.y = y;
                        addPosition(positionList, position);
                        break;
                    }
                    y--;
                }
            }

            // Case 4:012200
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j - 1] == play) && (board.ptr[i + 1][j + 1] == rival)) {
                int y = j;
                for (int x = i; x < size; x++) {
                    if (board.ptr[x][y] == play) {
                        break;
                    }
                    else if (board.ptr[x][y] == 0) {
                        Position position;
                        position.x = x;
                        position.y = y;
                        addPosition(positionList, position);
                        break;
                    }
                    y++;
                }
            }
                
        }
    }

    //Right Diagonal
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Case 1: 001200
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j + 1] == play) && (board.ptr[i + 1][j - 1] == 0)) {
                Position position;
                position.x = i + 1;
                position.y = j - 1;
                addPosition(positionList, position);
                
            }

            // Case 2: 002100
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j + 1] == 0) && (board.ptr[i + 1][j - 1] == play)) {
                Position position;
                position.x = i - 1;
                position.y = j + 1;
                addPosition(positionList, position);
                
            }

            // Case 3:022100
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j + 1] == rival) && (board.ptr[i + 1][j - 1] == play)) {
                int jPosition = j + 1;
                for (int x = i - 1; x >= 0; x--) {
                    if (board.ptr[x][jPosition] == play) {
                        break;
                    }
                    else if (board.ptr[x][jPosition] == 0) {
                        Position position;
                        position.x = x;
                        position.y = jPosition;
                        addPosition(positionList, position);
                        break;
                    }
                    jPosition++;
                }
            }

            // Case 4:012200
            if ((board.ptr[i][j] == rival) && (board.ptr[i - 1][j + 1] == play) && (board.ptr[i + 1][j - 1] == 2)) {
                int jPosition = j - 1;
                for (int x = i + 1; x < size; x++) {
                    if (board.ptr[x][jPosition] == play) {
                        break;
                    }
                    else if (board.ptr[x][jPosition] == 0) {
                        Position position;
                        position.x = x;
                        position.y = jPosition;
                        addPosition(positionList, position);
                        break;
                    }
                    jPosition--;
                }
            }
        }
    }
    return positionList;
}

PositionList deleteDuplicate (PositionList &positionList) {
    for (int i = 0; i < positionList.size; i++) {
        for (int j = i + 1; j < positionList.size; j++) {
            if ((positionList.ptr[i].x == positionList.ptr[j].x) && (positionList.ptr[i].y == positionList.ptr[j].y)) {
                for (int k = j; k < positionList.size; k++) {
                    positionList.ptr[k].x = positionList.ptr[k + 1].x;
                    positionList.ptr[k].y = positionList.ptr[k + 1].y;
                }
                positionList.size--;
                j--;
            }
        }
    }
    return positionList;

}

void findBlock(Board& board, int player, Position position, int idirect, int jdirect) {
    int size = board.size;
    int i = position.x + idirect;
    int j = position.y + jdirect;
    Position block;
    while ((0 <= i) && (i < size) && (0 <= j) && (j < size)) {
        if (board.ptr[i][j] == player) {
            block.x = i;
            block.y = j;
            int starti = position.x;
            int startj = position.y;
            while (board.ptr[starti][startj] != board.ptr[block.x][block.y]) {
                board.ptr[starti][startj] = player;
                starti += idirect;
                startj += jdirect;
            }
            break;
        }
        i += idirect;
        j += jdirect;
    }

}

void playMoves(Board& board, int player, Position position) {
    findBlock(board, player, position, 0, 1);
    findBlock(board, player, position, 0, -1);
    findBlock(board, player, position, 1, 0);
    findBlock(board, player, position, 1, -1);
    findBlock(board, player, position, 1, 1);
    findBlock(board, player, position, -1, -1);
    findBlock(board, player, position, -1, 0);
    findBlock(board, player, position, -1, 1);
}

int main() {
    Board board = initBoard(8);

    PositionList positionList = getPositionList(board, 2);
    deleteDuplicate(positionList);

    for (int i = 0; i < positionList.size; i++) {
        cout << "(" << positionList.ptr[i].x << ", " << positionList.ptr[i].y << ")" << endl;
    }

    Position position = {7, 2};
    playMoves(board, 2, position);
    printBoard(board);

    // Free memory
    for (int i = 0; i < board.size; i++) {
        delete[] board.ptr[i];
    }

    delete[] board.ptr;
    delete[] positionList.ptr;

    return 0;
}