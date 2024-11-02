#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

void printMessage(string message, bool printTop = true, bool printBottom = true) {
    if (printTop) {
        cout << "+---------------------------------+" << endl;
    }

    cout << "|";
    bool front = true;
    while (message.length() < 33) {
        if (front) {
            message = " " + message;
        } else {
            message = message + " ";
        }
        front = !front;
    }

    cout << message.c_str() << "|" << endl;

    if (printBottom) {
        cout << "+---------------------------------+" << endl;
    }
}

void DrawHangman(int guessCount = 0) {
    if (guessCount >= 1) printMessage("|", false, false);
    else printMessage(" ", false, false);

    if (guessCount >= 2) printMessage("|", false, false);
    else printMessage(" ", false, false);

    if (guessCount >= 3) printMessage("O", false, false);
    else printMessage(" ", false, false);

    if (guessCount == 4) printMessage("/", false, false);
    else if (guessCount == 5) printMessage("/|", false, false);
    else if (guessCount >= 6) printMessage("/|\\", false, false);
    else printMessage(" ", false, false);

    if (guessCount >= 7) printMessage("|", false, false);
    else printMessage(" ", false, false);

    if (guessCount == 8) printMessage("/", false, false);
    else if (guessCount >= 9) printMessage("/ \\", false, false);
    else printMessage(" ", false, false);
}

void printLetters(string input, char from, char to) {
    string s;
    for (char i = from; i <= to; i++) {
        if (input.find(i) == string::npos) {
            s += i;
            s += " ";
        } else {
            s += "  ";
        }
    }
    printMessage(s, false, false);
}

void printAvailableLetters(string taken) {
    printLetters(taken, 'A', 'M');
    printLetters(taken, 'N', 'Z');
}

bool printWordAndCheckWin(string word, string guessed) {
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++) {
        if (guessed.find(word[i]) == string::npos) {
            won = false;
            s += "_ ";
        } else {
            s += word[i];
            s += " ";
        }
    }
    printMessage(s, false);
    return won;
}

string LoadRandomWord(string path) {
    vector<string> words;
    ifstream reader(path);
    string word;
    if (reader.is_open()) {
        while (getline(reader, word)) {
            words.push_back(word);
        }
        reader.close();
    }
    if (!words.empty()) {
        int randomIndex = rand() % words.size();
        return words[randomIndex];
    }
    return "";
}

int TriesLeft(string word, string guessed) {
    int errors = 0;
    for (int i = 0; i < guessed.length(); i++) {
        if (word.find(guessed[i]) == string::npos) {
            errors++;
        }
    }
    return errors;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    string guesses;
    string wordToGuess = LoadRandomWord("path.txt");
    if (wordToGuess.empty()) {
        cout << "Error loading word list!" << endl;
        return 1;
    }

    int tries = 0;
    bool win = false;

    do {
        system("clear"); // Use "cls" if on Windows
        printMessage("HANGMAN GAME");
        DrawHangman(tries);
        printAvailableLetters(guesses);
        printMessage("Guess the word:");
        win = printWordAndCheckWin(wordToGuess, guesses);

        if (win) break;

        char x;
        cout << "> ";
        cin >> x;

        if (guesses.find(x) == string::npos) {
            guesses += x;
        }

        tries = TriesLeft(wordToGuess, guesses);

    } while (tries < 9);

    if (win) {
        printMessage("Congratulations! You won!");
    } else {
        printMessage("Game Over! The word was: " + wordToGuess);
    }

    return 0;
}
