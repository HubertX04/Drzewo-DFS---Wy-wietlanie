#include <iostream>

using namespace std;

int const dla_kresek = 400; // 2 razy wiecej niz dla_wierzcholkow
int const dla_wierzcholkow = 200; //z zapasem

struct drzewo
{
    int czy_jest = 0;
    int nazwa = 0;
    int tab[dla_wierzcholkow] = {};
    int odwiedzone=0;
    int ilosc_podkorzeni = 0;
}*w;

void wypisywanie_numeru(int zaglebienie, int wierzcholek)
{
    if (zaglebienie != 0)
    {
        cout << "-";
    }

    if (w[wierzcholek].nazwa < 10)
    {
        cout << "0";
    }
    cout << w[wierzcholek].nazwa << endl;
}

void ustawianie_I (int zaglebienie, int kreski[dla_kresek], int &pozycja)
{
    for (int k = 0; k < zaglebienie; k++)
    {
        if (kreski[pozycja] == 195 || kreski[pozycja] == 179) // sprawdza czy znak jest ├ lub │
        {
            kreski[pozycja] = 179; // jesli tak to ustawia na I
            pozycja++;
        }
        else
        {
            kreski[pozycja] = 32; // jesli nie ustawia na spacje
            pozycja++;
        }

        kreski[pozycja] = 32;
        pozycja++;
    }
}

void ustawianie_znakow(int &ktory, int wierzcholek, int kreski[dla_kresek], int &pozycja)
{
    ktory++; //ktory wierzcholek zostal juz sprawdzony
    if (ktory == w[wierzcholek].ilosc_podkorzeni)
    {
        kreski[pozycja] = 192; //znak - └
        pozycja++;
    }
    else
    {
        kreski[pozycja] = 195; //znak - ├
        pozycja++;
    }

}

void dfs(int wierzcholek, int zaglebienie, int kreski[dla_kresek])
{
    int ktory = 0; // jest to zmienna, ktora zapisuje, w ktorym podkorzeniu obecnie sie znajdujemy, czy w pierwszym,drugim itp.
    int pozycja = 0; // jest to numer elementu dla tablicy kreski

    wypisywanie_numeru(zaglebienie, wierzcholek);

    w[wierzcholek].odwiedzone = 1;

    for (int i = 0; i < dla_wierzcholkow; i++)
    {
        if (w[wierzcholek].tab[i] == 1)
        {
            if (w[i].odwiedzone == 0)
            {
                pozycja = 0;

                ustawianie_I(zaglebienie, kreski, pozycja); //sprawdza kiedy ma wypisac I
                ustawianie_znakow(ktory, wierzcholek, kreski, pozycja);//wypisuje albo ├ albo └

                for (int k = 0; k < pozycja; k++)
                {
                    cout << char(kreski[k]); // wypisywanie kresek
                }

                dfs(i, zaglebienie+1, kreski);
            }
        }
    }
}

void zlicz_potomkow(int wierzcholek)
{
    w[wierzcholek].odwiedzone = 1;

    for (int i = 0; i < dla_wierzcholkow; i++)
    {
        if (w[wierzcholek].tab[i] == 1)
        {
            if (w[i].odwiedzone == 0)
            {
                w[wierzcholek].ilosc_podkorzeni++;
                zlicz_potomkow(i);
            }
        }
    }
}

int main()
{
    int wierz, k, kreski[dla_kresek] = {}, zaglebienie=0;

    w = new drzewo[dla_wierzcholkow]; // tworzy 200 struktur w

    cout << "Podaj ile jest wierzcholkow:" << endl;
    cin >> wierz;

    k = wierz - 1; // w drzewie musi byc o jedno mniejsze

    cout << "Podaj polaczenia:" << endl;

    int a, b, korzen;

    for (int i = 0; i < k; i++)
    {
        cin >> a >> b;
        w[a].tab[b] = 1;
        w[b].tab[a] = 1; //tworzy polaczenia miedzy a, b

        w[a].czy_jest = 1;
        w[b].czy_jest = 1; // dla nazewnictwa -> przydaje sie podczas wpisywania nazw w ponizszym forze
    }

    cout << "Podaj numer korzenia:" << endl;

    cin >> korzen;
    cout << endl;

    for (int i = 0; i < dla_wierzcholkow; i++)
    {
        if (w[i].czy_jest == 1) //wpisywanie nazw dla danych wierzcholkow
        {
            cout << "Podaj nazwe (numer), dla wierzcholka o indeksie " << i << ": ";
            cin >> w[i].nazwa;
        }
    }

    zlicz_potomkow(korzen); //zlicza podkorzenie

    for (int i = 0; i < dla_wierzcholkow; i++) //odwiedzone ustawia znowu na 0
    {
        w[i].odwiedzone = 0;
    }

    dfs(korzen, zaglebienie, kreski); // dfs

    delete[]w;

    return 0;
}

/*
Przykładowy plik wejściowy:
24
1 2
1 8
1 10
2 7
7 9
7 45
8 11
8 12
11 15
11 14
11 16
11 17
12 25
12 22
22 18
22 19
10 13
10 5
13 31
13 32
13 33
5 34
5 35

1

20
1
12
24
37
10
45
24
5
48
21
15
39
25
77
22
25
14
13
11
6
2
20
7

*/
