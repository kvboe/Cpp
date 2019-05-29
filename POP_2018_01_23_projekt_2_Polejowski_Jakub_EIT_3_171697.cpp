//POP 2017-12-19 projekt 1 Polejowski Jakub EiT 3 171697 Dev-C++ 5.11 TDM-GCC 4.9.2 64-bit Release

#include <iostream>
#include <fstream>

using namespace std;

void makeFile(fstream &config, string linia);

int main() {

    fstream config;
    string linia;

    cout << "Witaj, przetworze twoj plik!" << endl;

    config.open("config.txt", ios::in);

    if(config.good() == true)
    {
        cout << "Udalo mi sie otworzyc twoj plik" << endl;
        makeFile(config, linia);
    }

    else
    {
        cout << "Nie udalo mi sie otworzyc pliku!!! " << endl;
        return 0;
    }
    return 0;
}

void makeFile(fstream &config, string linia)
{
    fstream kod;
    fstream modul;

    kod.open("kod_jadra.txt", ios::out);
    modul.open("modul_jadra.txt", ios::out);


    int nr_linii=0;
    string dane;

    while(getline(config, linia))
    {
        if (linia[0]=='#' and linia[1]== '\0') nr_linii++;
        else if (linia[0]=='#')
        {
            nr_linii++;
            dane = linia;
        }
        else if (linia[0]=='#' and linia[1]=='\0') nr_linii++;
        if (linia[0]=='#' and linia[2]=='C' and linia[3]=='O' or linia[0]=='C') nr_linii=0;
        if (nr_linii==3)
        {
            kod << endl;
            modul << endl;
            nr_linii=0;
            for (int k=2; k<dane.length(); k++)
            {
                kod << dane[k];
                modul << dane[k];
            }
            kod << endl;
            modul << endl;
        }

        if (linia[linia.length() - 1] == 'y' and linia[linia.length() - 2] == '=')
        {
            dane = linia;
            if (dane[0]=='#')
            {
                for (int i=0; i<dane.length()-11; i++) kod << dane[i+9];
                kod << endl;
            }
            else
            {
                for (int i=0; i<dane.length()-9; i++) kod << dane[i+7];
                kod << endl;
            }
        }

        if (linia[linia.length() - 1] == 'm' and linia[linia.length() - 2] == '=')
        {
            dane = linia;
            if (dane[0]=='#')
            {
                for (int i=0; i<dane.length()-11; i++) modul << dane[i+9];
                modul << endl;
            }
            else
            {
                for (int i=0; i<dane.length()-9; i++) modul << dane[i+7];
                modul << endl;
            }
        }
    }

    kod << endl << endl;
    modul << endl << endl;

    config.close();
    kod.close();
    modul.close();
    cout << "Twoje pliki sa gotowe";

}