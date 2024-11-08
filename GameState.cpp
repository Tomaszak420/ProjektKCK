#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "GameState.h"

void GameState::fillBoard()
{
    const char *dice[16][6] = {
        {"R", "I", "F", "O", "B", "X"}, {"I", "F", "E", "H", "E", "Y"},
        {"D", "E", "N", "O", "W", "S"}, {"U", "T", "O", "K", "N", "D"},
        {"H", "M", "S", "R", "A", "O"}, {"L", "U", "P", "E", "T", "S"},
        {"A", "C", "I", "T", "O", "A"}, {"Y", "L", "G", "K", "U", "E"},
        {"Qu", "B", "M", "J", "O", "A"}, {"E", "H", "I", "S", "P", "N"},
        {"V", "E", "T", "I", "G", "N"}, {"B", "A", "L", "I", "Y", "T"},
        {"E", "Z", "A", "V", "N", "D"}, {"R", "A", "L", "E", "S", "C"},
        {"U", "W", "I", "L", "R", "G"}, {"P", "A", "C", "E", "M", "D"}};

    for (int i = 0; i < RZEDY; ++i)
    {
        for (int j = 0; j < KOLUMNY; ++j)
        {
            int randomIndex = rand() % 6;
            board[i][j] = dice[i * 4 + j][randomIndex];
        }
    }
}

bool GameState::hasBeenSelected(struct coordinates cursor)
{
    for (struct coordinates coordinate : selected_coordinates)
    {
        if (coordinate == cursor) 
        {
            return true;
        }
    }

    return false;
}

bool GameState::isValidSelection(struct coordinates selected_letter)
{
    // Jesli nie zostala wybrana jeszcze zadna litera
    if (selected_coordinates.size() == 0)
    {
        return true;
    }

    // Jesli zostala wybrana wybrana ta sama litera, co poprzednio (to samo pole)
    if (selected_coordinates.back() == selected_letter)
    {
        return false;
    }

    int last_x = selected_coordinates.back().x;
    int last_y = selected_coordinates.back().y;

    return abs(last_x - selected_letter.x) <= 1 && abs(last_y - selected_letter.y) <= 1;
}

void GameState::tryAddLetter(struct coordinates cursor) 
{
    struct coordinates letter = {(cursor.x - 1) / 5, cursor.y - 1};

    if (isValidSelection(letter))
    {
        selected_coordinates.push_back(letter);

        selected_letters.push_back(board[letter.y][letter.x]);
    }
}

//TODO
bool GameState::tryAddSelectedWord()
{   
    string word = getSelectedWord();
    if (!isFoundWord(word)) 
    {
        found_words.push_back(word);
        return true;
    }
    return false;
}

void GameState::restartGame() {

    clearSelection();
    found_words.clear();

    fillBoard();
}

string GameState::getSelectedWord()
{
    string word = "";

    for (string letter : selected_letters)
    {
        word += letter;
    }

    return word;
}

int GameState::getSelectedLength() {
    return selected_coordinates.size();
}

bool GameState::isFoundWord(string word)
{
    for (string found_word : found_words)
    {
        if (word == found_word)
        {
            return true;
        }
    }
    return false;
}

void GameState::clearSelection() {
    selected_coordinates.clear();
    selected_letters.clear();
}

vector<struct coordinates> GameState::getSelectedCoordinates() {
    return selected_coordinates;
}