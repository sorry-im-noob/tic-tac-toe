#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>

using std::cout;
using std::cin;
using std::string;

// function to ignore line
void ignore ()
{
    cin.ignore (std::numeric_limits<std::streamsize>::max(),'\n');
}

// make a class for player
class Player {
private:
    // temporary var
    int input1{};
    int input2{};
    string warning{};
    int numOfPos{0};

    // long time  var
    std::array<int,9> m_board{0};
    char player1{'X'};
    char player2{'O'};
    int currentPlayer{-1};
public:

    void board()
    {
    for (int i=0;i<9;++i)
    {   
        switch (m_board[i])
        {
            case 0: cout << "_";break;
            case 1: cout << player1;break;
            case 2: cout << player2;break;
            default: cout << "?";break;
        }
        cout << "  ";
        if ((i+1)%3==0) cout << "\n";
    }
    }

    void whoFirst ()
    {
        cout << "who is going to be first?\n";
        cout << "(01) player1 [" << player1 << "]\n";
        cout << "(02) player2 [" << player2 << "]\n";
        cout << "(03) choose random\n";
        cout << "choose: ";
        cin>>input1;
        ignore ();
        switch (input1)
        {
            case 01: currentPlayer = 1;break;
            case 02: currentPlayer = 2;break;
            default: currentPlayer = 1+(rand()%2);
        }
        cout << "first is " << currentPlayer << "\n";
    }

    void enterPos()
    {
        cout << warning << "\n";
        warning = "";
        cout << "player" << currentPlayer << "'s turn [" << ((currentPlayer==1) ? player1 : player2) << "]: ";
        cin>>input2;
        ignore();
        if (input2-1<9 && m_board[input2-1]==0)
        {
            m_board[input2-1]=currentPlayer;
            ++numOfPos;
            currentPlayer = (currentPlayer==1) ? 2 : 1;
        }else if (input2>9)
        {
            warning = "the position you entered is out of scope";
        }
        else
        {
            std::stringstream ss;
            ss << "that place already filled with player" << m_board[input2-1] << "'s turn";
            warning = ss.str ();
        }
    }
    inline bool check (int a,int b,int c)
    {
        return (m_board[a-1]==m_board[b-1] && m_board[a-1]==m_board[c-1]) && (m_board[a-1]!=0);
    }
    
    bool isWin ()
    {
        if (check (1,2,3) || check(4,5,6) || check(7,8,9) || check(1,4,7) || check(2,5,8) || check(3,6,9) || check(1,5,9) || check(3,5,7))
        {
            currentPlayer = (currentPlayer==1) ? 2 : 1;
            cout << "congratulation for player" << currentPlayer << " [" << ((currentPlayer==1) ? player1 : player2) << "] you have won\n";
            return true;
        }else if (numOfPos==m_board.size())
        {
            cout << "TIE\n";
            return true;
        }
        return false;
    }
};

int main ()
{
    std::srand (std::time (0));
    Player player1;
    player1.whoFirst();
    bool play{false};
    while (!play)
    {
        player1.board ();
        play = player1.isWin();
        if (!play)
            player1.enterPos ();
    }
    return 0;
}