#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class sudoku {

public:

    int num_solutions;
    vector<vector<short>> board;
    vector<vector<bool>> row_contains;
    vector<vector<bool>> col_contains;
    vector<vector<vector<bool>>> box_contains;

    sudoku() {
        ifstream puzzle;
        string file;
        while(!puzzle.is_open()) {
            cout << "File Name: ";
            cin >> file;
            puzzle.open(file + ".txt");
            if (!puzzle.is_open()) {
                cout << "Invalid File Name\n";
            }
        }
        num_solutions = 0;
        board.resize(9, vector<short>(9, 0));
        row_contains.resize(9, vector<bool>(9, false));
        col_contains.resize(9, vector<bool>(9, false));
        box_contains.resize(3, vector<vector<bool>> (3, vector<bool>(9, false)));
        short num;
        for(short row = 0; row < 9; ++row) {
            for(short col = 0; col < 9; ++col) {
                puzzle >> num;
                if (num != 0) {
                    if (valid(row, col, num - 1)) {
                        board[row][col] = num;
                        row_contains[row][num - 1] = true;
                        col_contains[col][num - 1] = true;
                        box_contains[row / 3][col / 3][num - 1] = true;
                    }
                    else {
                        cout << "Invalid board\n";
                        exit(1);
                    }
                }
            }
        }
    }

    void print_board() {
        for(short row = 0; row < 9; ++row) {
            cout << "-------------------------------------\n| ";
            for(short col = 0; col < 9; ++col) {
                cout << board[row][col] << " | ";
            }
            cout << "\n";
        }
        cout << "-------------------------------------\n\n";
    }

    bool valid(short row, short col, short num) {
        return !row_contains[row][num] && !col_contains[col][num] && !box_contains[row / 3][col / 3][num];
    }

    void solve(short row, short col) {
        if (row == 9) {
            ++num_solutions;
            print_board();
            return;
        }
        else if (board[row][col] != 0) {
            if (col == 8) {
                ++row;
                col = 0;
            }
            else {
                ++col;
            }
            solve(row, col);
            return;
        }
        for (short num = 0; num < 9; ++num) {
            if(valid(row, col, num)) {
                board[row][col] = num + 1;
                row_contains[row][num] = true;
                col_contains[col][num] = true;
                box_contains[row / 3][col / 3][num] = true;
                if (col == 8) {
                    ++row;
                    col = 0;
                }
                else {
                    ++col;
                }
                solve(row, col);
                if (col == 0) {
                    --row;
                    col = 8;
                }
                else {
                    --col;
                }
                row_contains[row][num] = false;
                col_contains[col][num] = false;
                box_contains[row / 3][col / 3][num] = false;
                board[row][col] = 0;
            }
        }
        return;
    }

    void print_num_solutions() {
        cout << "Number of solutions: " << num_solutions << "\n";
    }
};

int main() {
    sudoku s;
    s.solve(0, 0);
    s.print_num_solutions();
    return 0;
}