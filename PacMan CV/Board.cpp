#include "Board.h"
using std::filesystem::directory_iterator;
using namespace std;
void Board::printBoard(bool NoColor) const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!NoColor)
            {
                if (board[i][j] == '#')
                    setTextColor(c);
                else
                    setTextColor(Color::WHITE);
            }
            cout << board[i][j];
        }
        cout << endl;
    }
}

bool Board::ReadBoard()
{
    string path="./";
    string line, nextB;
    static queue<string> boardNames;
    int i = 0, len, ghoIndex = 0;
    bool invalid = false, first = true, FirstPac = true, firstScore = true;
    char c, level = NULL, pick = NULL;
    static int gameNum = 1;
    static bool firstGame = true;
    string fileName;
    ifstream TextBoard;
    clear_screen();
    while (!invalid)
    {
        if (firstGame)
        {
            firstGame = false;
            cout << "press 1 to play one of the built in board or 2 for a file of your pick" << endl;
            do {
                if (_kbhit())
                {
                    c = _getch();
                    if (c == '1' || c == '2')
                        pick = c;
                    else
                        cout << "You Entered an invalid Option please press 1 for build in or 2 for file of your pick" << endl;
                }
            } while (pick == NULL);
        }
        else
            pick = '1';
        if (pick == '1')
        {
            if(gameNum==1)
            {
                for (const auto& file : directory_iterator(path))
                {
                    path = file.path().filename().string();
                    if (file.path().extension().compare(".screen") == 0)
                        boardNames.push(file.path().string());
                }
                nextB = boardNames.front();
                boardNames.pop();
                TextBoard.open(nextB, ios::in);
            }
            else
            {
                if (!boardNames.empty())
                {
                    nextB = boardNames.front();
                    boardNames.pop();
                    TextBoard.open(nextB, ios::in);
                }
                else
                {
                    cout << "Congratulations!" << endl << "You won all the levels";
                    return false;
                }
            }
        }
        else
        {
            clear_screen();
            cout << "Please enter the file's name" << endl;
            getline(cin, fileName);
            TextBoard.open(fileName, ios::in);
        }
        if (!TextBoard)
        {
            cout << "File couldn't open!" << endl;
            pick = NULL;
            level = NULL;
            continue;
        }
        else
        {
            while (getline(TextBoard, line))
            {
                if (first)
                {
                    cols = (size_t)line.length();
                    first = false;
                }
                len = (size_t)line.length();
                for (int j = 0; j < len; j++)
                {
                    switch (line[j]) {
                    case '@':
                    {
                        if (FirstPac)
                        {
                            FirstPac = false;
                            pac.setPoint({ j, i });
                            IncreaseNumOfDots();
                            line[j] = '.';
                        }
                        else
                        {
                            invalid = true;
                            level = NULL;
                            pick = NULL;
                        }
                        break;
                    }
                    case '%':
                    {
                        line[j] = ' ';
                        break;
                    }
                    case '$':
                    {
                        gho[ghoIndex].setPoint({ j, i });
                        ghoIndex++;
                        IncreaseNumOfDots();
                        line[j] = '.';
                        break;
                    }
                    case '&':
                    {
                        if (firstScore)
                        {
                            firstScore = false;
                            score.setPoint({ j, i });
                        }
                        else
                        {
                            invalid = true;
                            level = NULL;
                            pick = NULL;
                        }
                        break;
                       
                    }
                    case ' ':
                    {
                        IncreaseNumOfDots();
                        line[j] = '.';
                        break;
                    }
                    default:
                        break;
                    }
                    if (invalid)
                        break;
                }
                board[i] = line;
                i++;
            }
            if (invalid)
            {
                invalid = false;
                level = NULL;
                pick = NULL;
                continue;
            }
        }
        invalid = true;
    }
    rows = i;
    GhostIndex = ghoIndex;
    if (gameNum == 1)
        TotalDots = numofdots;
    else
        AddToTotal(numofdots);
    gameNum++;
    return true;
}