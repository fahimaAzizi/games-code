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

    ~Board() {
        for (auto row : squares) {
            for (auto piece : row) {
                delete piece;
            }
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
        int fromRow = from[1] - '1';
        int fromCol = from[0] - 'a';
        int toRow = to[1] - '1';
        int toCol = to[0] - 'a';

        // Validate input positions
        if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
            toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
            cout << "Invalid move: Position out of bounds." << endl;
            return false;
        }

        if (squares[fromRow][fromCol] == nullptr) {
            cout << "Invalid move: No piece at the source." << endl;
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
