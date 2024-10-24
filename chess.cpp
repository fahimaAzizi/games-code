#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Piece {
public:
    char type; // 'P' for pawn, 'R' for rook, etc.
    bool isWhite;

    Piece(char t, bool color) : type(t), isWhite(color) {}
};

class Board {
public:
    vector<vector<Piece*>> squares;

    Board() {
        squares.resize(8, vector<Piece*>(8, nullptr));
        setup();
    }

    ~Board() {
        for (auto row : squares) {
            for (auto piece : row) {
                delete piece;
            }
        }
    }

    void setup() {
        // Setup white pieces
        squares[0][0] = new Piece('R', true);
        squares[0][1] = new Piece('N', true);
        squares[0][2] = new Piece('B', true);
        squares[0][3] = new Piece('Q', true);
        squares[0][4] = new Piece('K', true);
        squares[0][5] = new Piece('B', true);
        squares[0][6] = new Piece('N', true);
        squares[0][7] = new Piece('R', true);
        for (int i = 0; i < 8; ++i) {
            squares[1][i] = new Piece('P', true);
        }

        // Setup black pieces
        squares[7][0] = new Piece('R', false);
        squares[7][1] = new Piece('N', false);
        squares[7][2] = new Piece('B', false);
        squares[7][3] = new Piece('Q', false);
        squares[7][4] = new Piece('K', false);
        squares[7][5] = new Piece('B', false);
        squares[7][6] = new Piece('N', false);
        squares[7][7] = new Piece('R', false);
        for (int i = 0; i < 8; ++i) {
            squares[6][i] = new Piece('P', false);
        }
    }

    void display() {
        for (int i = 7; i >= 0; --i) {
            cout << i + 1 << " ";
            for (int j = 0; j < 8; ++j) {
                if (squares[i][j]) {
                    cout << squares[i][j]->type << (squares[i][j]->isWhite ? 'W' : 'B') << " ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
        cout << "  a b c d e f g h" << endl;
    }

    bool movePiece(const string& from, const string& to) {
        // Simplified move logic
        int fromRow = from[1] - '1';
        int fromCol = from[0] - 'a';
        int toRow = to[1] - '1';
        int toCol = to[0] - 'a';

        if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
            toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
            return false; // Invalid move
        }

        if (squares[fromRow][fromCol] == nullptr) {
            return false; // No piece to move
        }

        // Move piece to the new position
        delete squares[toRow][toCol]; // Capture any existing piece
        squares[toRow][toCol] = squares[fromRow][fromCol];
        squares[fromRow][fromCol] = nullptr;

        return true; // Move successful
    }
};

int main() {
    Board board;
    string from, to;

    while (true) {
        board.display();
        cout << "Enter your move (e.g., e2 e4) or 'exit' to quit: ";
        cin >> from;
        if (from == "exit") break;
        cin >> to;

        if (!board.movePiece(from, to)) {
            cout << "Invalid move. Try again." << endl;
        }
    }

    return 0;
}
