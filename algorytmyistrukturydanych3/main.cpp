#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

struct krawedz
{
	int poczatek;
	int koniec;
	int waga;
};

string zadanie1(string slowo1, string slowo2);
void zadanie5(int** wyjscie, int** wejscie, int n, int w);
vector<krawedz> zadanie3(int n, int m, const vector<krawedz>& listaKrawedzi);



int main()
{
	// ZADANIE 1
	fstream plikIn, plikOut;
	/*plikIn.open("In0301.txt");
	plikOut.open("Out0301.txt");
	int n = 0;
	plikIn >> n;

	string* tablicaGenetyczna = new string[n * 2];
	for (int i = 0; i < n * 2; ++i)
		plikIn >> tablicaGenetyczna[i];

	for (int i = 0; i < n; ++i)
		plikOut << zadanie1(tablicaGenetyczna[2 * i], tablicaGenetyczna[2 * i + 1]) << '\n';


	plikIn.close();
	plikOut.close();
	*/

	// ZADANIE 3
	plikIn.open("In0303.txt");
	plikOut.open("Out0303.txt");

	int n, m;
	plikIn >> n >> m;

	plikIn.ignore();

	vector<krawedz> krawedzie;

	for (int i = 1; i <= n; ++i)
	{
		string strIn;
		getline(plikIn, strIn);

		stringstream stringStream;
		stringStream << strIn;
		while (!stringStream.eof())
		{
			int koniec, waga;
			stringStream >> koniec >> waga;

			krawedz kr;
			kr.koniec = koniec;
			kr.poczatek = i;
			kr.waga = waga;
			krawedzie.push_back(kr);
		}		
	}

	sort(krawedzie.begin(), krawedzie.end(), [](const krawedz& a, const krawedz& b) -> bool {return a.waga < b.waga; });

	for (int i = 0; i < krawedzie.size(); ++i)
	{
		cout << krawedzie[i].poczatek << " -> " << krawedzie[i].koniec << " [ " << krawedzie[i].waga << " ]" << endl;
	}

	vector<krawedz> wynik = zadanie3(n, m, krawedzie);

	int suma = 0;
	cout << "WWYNIK " << endl;
	for (int i = 0; i < wynik.size(); ++i)
	{
		cout << wynik[i].poczatek << " -> " << wynik[i].koniec << " [ " << wynik[i].waga << " ]" << endl;
		suma += wynik[i].waga;
	}

	plikOut << suma << '\n';

	for (int i = 0; i < wynik.size(); ++i)
	{
		plikOut << wynik[i].poczatek << " - " << wynik[i].koniec << " [ " << wynik[i].waga << " ]" << '\n';
	}

	plikIn.close();
	plikOut.close();

	// ZADANIE 5
	/*plikIn.open("In0501.txt");
	plikOut.open("Out0501.txt");

	int wielkosc = 0;
	int w = -1;

	plikIn >> wielkosc >> w;
	int** tablica = new int* [wielkosc];
	for (int i = 0; i < wielkosc; ++i)
		tablica[i] = new int[wielkosc];

	for (int i = 0; i < wielkosc; ++i)
	{
		for (int j = 0; j < wielkosc; ++j)
			plikIn >> tablica[j][i];
	}

	int** wyjscie = new int* [wielkosc];
	for (int i = 0; i < wielkosc; ++i)
	{
		wyjscie[i] = new int[2];
		wyjscie[i][0] = 999;
	}

	zadanie5(wyjscie, tablica, wielkosc, w);

	//WYPISYWANIE
	cout << "      ";
	for (int i = 0; i < wielkosc; ++i)
		cout << i << " ";
	cout << endl;

	cout << "dist: ";
	for (int i = 0; i < wielkosc; ++i)
		cout << wyjscie[i][0] << " ";

	cout << endl;

	cout << "nast: ";
	for (int i = 0; i < wielkosc; ++i)
		cout << wyjscie[i][1] << " ";

	plikIn.close();
	plikOut.close();*/
	return 0;
}

string zadanie1(string slowo1, string slowo2)
{
	int dlugosc1 = slowo1.length(), dlugosc2 = slowo2.length();

	int** powtorzenia = new int*[dlugosc1 + 1];
	for (int i = 0; i < dlugosc1 + 1; ++i)
		powtorzenia[i] = new int[dlugosc2 + 1];

	// WYPE£NIANIE PIERWSZYCH LINII
	for (int i = 0; i < dlugosc1 + 1; ++i)
		powtorzenia[i][0] = 0;

	for (int i = 0; i < dlugosc2 + 1; ++i)
		powtorzenia[0][i] = 0;

	int najX = 1, najY = 0;
	// WYPE£NIANIE ŒRODKA
	for (int i = 1; i < dlugosc1; ++i)
	{
		for (int j = 1; j < dlugosc2; ++j)
		{
			if (slowo1[i] == slowo2[j])
			{
				powtorzenia[i][j] = powtorzenia[i - 1][j - 1] + 1;
			}
			else
			{
				powtorzenia[i][j] = powtorzenia[i - 1][j] >= powtorzenia[i][j - 1] ? powtorzenia[i - 1][j] : powtorzenia[i][j - 1];
			}
			if (powtorzenia[i][j] > powtorzenia[najX][najY])
			{
				najX = i;
				najY = j;
			}
		}
	}

	// WYSZUKIWANIE NAJDLUZSZEGO WSPOLNEGO PODCIAGU
	int x = najX;
	int y = najY;
	string wyjscie = "";

	while (x >= 0 && y >= 0)
	{
		if (slowo1[x] == slowo2[y])
		{
			wyjscie += slowo1[x];
			--x;
			--y;
		}
		else
		{
			if (powtorzenia[x - 1][y] >= powtorzenia[x][y - 1])
				--x;
			else
				--y;
		}
	}

	string wyjscieRev = "";
	for (int i = wyjscie.length() - 1; i >= 0; --i)
		wyjscieRev += wyjscie[i];

	return wyjscieRev;
}

void zadanie5(int** wyjscie, int** wejscie, int n, int w)
{
	vector<int> przerobione;
	queue<int> doPrzerobienia;
	
	doPrzerobienia.push(w);
	wyjscie[w][0] = 0;
	wyjscie[w][1] = -1;

	while (przerobione.size() < n)
	{
		int obecniePrzerabiany = doPrzerobienia.front();
		doPrzerobienia.pop();
		if (find(przerobione.begin(), przerobione.end(), obecniePrzerabiany) != przerobione.end())
			continue;

		for (int i = 0; i < n; ++i)
		{
			if (wejscie[obecniePrzerabiany][i] != 999 && wejscie[obecniePrzerabiany][i] != 0)
			{
				doPrzerobienia.push(i);

				if (wyjscie[i][0] > wejscie[obecniePrzerabiany][i])
				{
					wyjscie[i][0] = wejscie[obecniePrzerabiany][i] + wyjscie[obecniePrzerabiany][0];
					wyjscie[i][1] = obecniePrzerabiany;
				}
			}
		}
		przerobione.push_back(obecniePrzerabiany);
	}
}

int znajdzZbior(const vector<vector<int>>& zbiory, int wierzcholek)
{
	for (int i = 0; i < zbiory.size(); ++i)
	{
		for (int j = 0; j < zbiory[i].size(); ++j)
		{
			if (zbiory[i][j] == wierzcholek)
				return i;
		}
	}
	return -1;
}

bool czyWystepujeWZbiorze(const vector<vector<int>>& zbiory, int zbior, int wierzcholek)
{
	for (int i = 0; i < zbiory[zbior].size(); ++i)
	{
		if (zbiory[zbior][i] == wierzcholek)
			return true;
	}
	return false;
}

void polaczZbiory(vector<vector<int>>& zbiory, int zbior1, int zbior2)
{
	for (int i = 0; i < zbiory[zbior2].size(); ++i)
	{
		zbiory[zbior1].push_back(zbiory[zbior2].back());
		zbiory[zbior2].pop_back();
	}
}

bool czyUzytaKrawedz(const vector<krawedz> &uzyteKrawedzie, krawedz krawedz)
{
	for (int i = 0; i < uzyteKrawedzie.size(); ++i)
	{
		if ((uzyteKrawedzie[i].koniec == krawedz.poczatek && uzyteKrawedzie[i].poczatek == krawedz.koniec) || (uzyteKrawedzie[i].poczatek == krawedz.poczatek && uzyteKrawedzie[i].koniec == krawedz.koniec))
			return true;
	}
	return false;
}

vector<krawedz> zadanie3(int n, int m, const vector<krawedz>& listaKrawedzi)
{
	vector<krawedz> uzyteKrawedzie;

	vector<vector<int>> zbiory;

	for (int i = 1; i <= n; ++i)
	{
		zbiory.push_back(vector<int>());
		zbiory[i - 1].push_back(i);
	}
	   
	for (int i = 0; i < listaKrawedzi.size(); ++i)
	{
		if (znajdzZbior(zbiory, listaKrawedzi[i].poczatek) != -1 && znajdzZbior(zbiory, listaKrawedzi[i].koniec) != -1 && !czyWystepujeWZbiorze(zbiory, znajdzZbior(zbiory, listaKrawedzi[i].poczatek), listaKrawedzi[i].koniec) && !czyUzytaKrawedz(uzyteKrawedzie, listaKrawedzi[i]))
		{
			uzyteKrawedzie.push_back(listaKrawedzi[i]);

			polaczZbiory(zbiory, znajdzZbior(zbiory, listaKrawedzi[i].poczatek), znajdzZbior(zbiory, listaKrawedzi[i].koniec));
		}
		if (uzyteKrawedzie.size() == n - 1)
			break;
	}
	return uzyteKrawedzie;
}