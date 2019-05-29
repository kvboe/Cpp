//POP 2017-12-19 projekt 1 Polejowski Jakub EiT 3 171697 Dev-C++ 5.11 TDM-GCC 4.9.2 64-bit Release

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_L = 6; //maksymalna ilosc wierszy
const int MAX_C = 6; //maksymalna ilosc kolumn

const int MAX_R=3; //maksymalna ilosc punktow na rogach planszy
const int MAX_K=4; //maksymalna ilosc punktow na krawedziach
const int MAX_S=5; //maksymalna ilosc punktow dla srodka planszy
char L[]= {'F','E','D','C','B','A'};
char C[]= {'N', 'C', 'Z'};


struct tableGame
{
    int points;
    int color;
};

void printGame(tableGame[MAX_L][MAX_C]);
bool botChecked();
void turn(int a, int b,tableGame[MAX_L][MAX_C], bool botOption, int &currentPlayer);
int checkWinner(tableGame[MAX_L][MAX_C]);
void extraPools(int a, int b, tableGame[MAX_L][MAX_C], int currentPlayer);
void resetGame(tableGame[MAX_L][MAX_C]);

int main() {

    tableGame tbl[MAX_L][MAX_C];
    int a, b;
    bool botOption;
    int currentPlayer=1;

    resetGame(tbl);

    cout << "Witaj graczu!!" << endl;
    botOption = botChecked();

    printGame(tbl);

    int tmp=0;
    do
    {
        turn(a, b, tbl, botOption, currentPlayer);
        tmp = checkWinner(tbl);
    } while (tmp == 0);

    if (tmp == 1 or tmp == 2) cout << "Wygral gracz: " << tmp << ". Gratulacje!! " << endl;
    return tmp;
}

void resetGame(tableGame tbl[MAX_L][MAX_C])
{
    for (int i=0; i<MAX_L; i++)
    {
        for (int j=0; j<MAX_C; j++)
        {
            tbl[i][j].points = 1;
            tbl[i][j].color = 0;
        }
    }
}

void printGame(tableGame tbl[MAX_L][MAX_C])
{
    system("CLS");
    cout << endl << endl;
    cout << setw(22) << "|";
    for (int i=0; i<MAX_C; i++) cout << " " << i << " |";
    cout << endl;
    for (int i=0; i<MAX_L; i++)
    {
        cout << setw(20) << L[i] << " |";
        for (int k=0; k<MAX_C; k++)
        {
            cout << C[tbl[i][k].color] << ':' << tbl[i][k].points << "|";
        }
        cout << endl;
    }
}

bool botChecked()
{
    do
    {
        char bot;
        cout << endl << setw(50) << "Chcesz grac z botem ?? [Y/N]: ";
        cin >> bot;
        if (bot=='Y' or bot=='y') return true;
        if (bot=='N' or bot=='n') return false;
    } while (1);
}

void turn(int a, int b, tableGame tbl[MAX_L][MAX_C], bool botOption, int &currentPlayer)
{
    srand(time(NULL));
    char n;
    bool dane=false;
    cout << endl;
    cout << "Tura gracza: " << currentPlayer << endl;

    if (botOption==true and currentPlayer==2)
    {
        do
        {
            a = rand() % MAX_L;
            b = rand() % MAX_C;
        } while (tbl[a][b].color == 1);
    }
    else
    {
        do
        {
            do {
                cout << "Podaj wiersz i kolumne: ";
                cin >> n;

                for (int i = 0; i < MAX_L; i++) // zamiana liter na cyfry
                {
                    if (n == L[i]) {
                        a = i;
                        dane=true;
                        break;
                    }
                }
            } while (dane==false);

            dane=false;

            do
            {
                cout << "Podaj kolumne: ";
                cin >> b;
            }while (dane==true);

            if (tbl[a][b].color != currentPlayer and tbl[a][b].color!=0) cout << "Mozesz wybrac tylko swoje pole lub neutralne!! " << endl;
        } while (tbl[a][b].color != currentPlayer and tbl[a][b].color!=0);
    }

    tbl[a][b].color = currentPlayer;
    tbl[a][b].points++;
    if (checkWinner(tbl)==0)
        extraPools(a,b, tbl, currentPlayer);

    if(currentPlayer == 1) currentPlayer = 2;
    else if (currentPlayer == 2) currentPlayer = 1;

    printGame(tbl);
    cout << endl << endl << "Poprzedni gracz wybral pole: " << L[a] << b << endl;
}

int checkWinner(tableGame tbl[MAX_L][MAX_C])
{
    int firstWin=tbl[0][0].color;

    if(firstWin==0) return 0;

    for (int i = 0; i < MAX_L; ++i)
    {
        for (int k = 0; k < MAX_C; ++k)
        {
            if (firstWin == tbl[i][k].color) continue;
            else return 0;
        }
    }
    return firstWin;

}

void extraPools(int a, int b, tableGame tbl[MAX_L][MAX_C], int currentPlayer)
{
    if (checkWinner(tbl)==1 or checkWinner(tbl)==2) return;

    else if (a == MAX_L-1 and b == 0 and tbl[a][b].points>=MAX_R)
    {
        tbl[a][b].points=1;
        tbl[a-1][b].points++;
        tbl[a][b+1].points++;
        tbl[a][b+1].color=currentPlayer;
        tbl[a-1][b].color=currentPlayer;
        extraPools(a,b+1, tbl, currentPlayer);
        extraPools(a-1,b, tbl, currentPlayer);
    }

    else if (a == 0 and b == 0 and tbl[a][b].points>=MAX_R)
    {
        tbl[a][b].points=1;
        tbl[a][b+1].points++;
        tbl[a+1][b].points++;
        tbl[a][b+1].color=currentPlayer;
        tbl[a+1][b].color=currentPlayer;
        extraPools(a,b+1, tbl, currentPlayer);
        extraPools(a+1,b, tbl, currentPlayer);
    }


    else if (a == MAX_L-1 and b == MAX_C-1 and tbl[a][b].points>=MAX_R)
    {
        tbl[a][b].points=1;
        tbl[a][b-1].points++;
        tbl[a-1][b].points++;
        tbl[a][b-1].color=currentPlayer;
        tbl[a-1][b].color=currentPlayer;
        extraPools(a,b-1, tbl, currentPlayer);
        extraPools(a-1,b, tbl, currentPlayer);
    }

    else if (a == 0 and b == MAX_C-1 and tbl[a][b].points>=MAX_R)
    {
        tbl[a][b].points=1;
        tbl[a][b-1].points++;
        tbl[a+1][b].points++;
        tbl[a][b-1].color=currentPlayer;
        tbl[a+1][b].color=currentPlayer;
        extraPools(a,b-1, tbl, currentPlayer);
        extraPools(a+1,b, tbl, currentPlayer);
    }
    else if (tbl[a][b].points>=MAX_K and b==0)
    {
        tbl[a][b].points=1;
        tbl[a][b+1].points++;
        tbl[a+1][b].points++;
        tbl[a-1][b].points++;
        tbl[a][b+1].color=currentPlayer;
        tbl[a+1][b].color=currentPlayer;
        tbl[a-1][b].color=currentPlayer;
        extraPools(a,b+1, tbl, currentPlayer);
        extraPools(a+1,b, tbl, currentPlayer);
        extraPools(a-1,b, tbl, currentPlayer);
    }

    else if (tbl[a][b].points>=MAX_K and b==MAX_C-1)
    {
        tbl[a][b].points=1;
        tbl[a+1][b].points++;
        tbl[a-1][b].points++;
        tbl[a][b-1].points++;
        tbl[a+1][b].color=currentPlayer;
        tbl[a-1][b].color=currentPlayer;
        tbl[a][b-1].color=currentPlayer;
        extraPools(a+1,b, tbl, currentPlayer);
        extraPools(a-1,b, tbl, currentPlayer);
        extraPools(a,b-1, tbl, currentPlayer);
    }

    else if (tbl[a][b].points>=MAX_K and a==0)
    {
        tbl[a][b].points=1;
        tbl[a][b+1].points++;
        tbl[a][b-1].points++;
        tbl[a+1][b].points++;
        tbl[a][b+1].color=currentPlayer;
        tbl[a][b-1].color=currentPlayer;
        tbl[a+1][b].color=currentPlayer;
        extraPools(a,b+1, tbl, currentPlayer);
        extraPools(a,b-1, tbl, currentPlayer);
        extraPools(a+1,b, tbl, currentPlayer);
    }

    else if (tbl[a][b].points>=MAX_K and a>=MAX_L-1)
    {
        tbl[a][b].points=1;
        tbl[a][b-1].points++;
        tbl[a][b+1].points++;
        tbl[a-1][b].points++;
        tbl[a][b-1].color=currentPlayer;
        tbl[a][b+1].color=currentPlayer;
        tbl[a-1][b].color=currentPlayer;
        extraPools(a,b-1, tbl, currentPlayer);
        extraPools(a,b+1, tbl, currentPlayer);
        extraPools(a-1,b, tbl, currentPlayer);
    }

    else if (tbl[a][b].points>=MAX_S)
    {
        tbl[a][b].points=1;
        tbl[a][b-1].points++;
        tbl[a][b+1].points++;
        tbl[a-1][b].points++;
        tbl[a+1][b].points++;
        tbl[a][b-1].color=currentPlayer;
        tbl[a][b+1].color=currentPlayer;
        tbl[a-1][b].color=currentPlayer;
        tbl[a+1][b].color=currentPlayer;
        extraPools(a,b-1, tbl, currentPlayer);
        extraPools(a,b+1, tbl, currentPlayer);
        extraPools(a-1,b, tbl, currentPlayer);
        extraPools(a+1,b, tbl, currentPlayer);
    }
}