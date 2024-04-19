#include <iostream>
#include <ctime>

using namespace std;

int wartosc[7][7];
bool klik[7][7];
bool flaga[7][7];

void initialize() {
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++) {
            wartosc[i][j] = 0;
            klik[i][j] = false;
            flaga[i][j] = false;
        }
}

bool wpiszBombe(int x, int y) {
    if (wartosc[x][y] >= 9) return false;
    else {
        wartosc[x][y] = 9;
        return true;
    }
}

void dodajWokol(int x, int y) {
    for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
            if (i > 0 && i < 6 && j > 0 && j < 6 && wartosc[i][j] != 9) wartosc[i][j]++;
}

bool czyTrafilBombe(int x, int y, int z) {
    if (z == 0) {
        if (wartosc[x][y] == 9) {
            cout << "Niestety, trafiles na bombe!" << endl;
            return true;
        }
        klik[x][y] = true;
    }
    else {
        flaga[x][y] = !flaga[x][y];
        klik[x][y] = !klik[x][y];
        cout << (flaga[x][y] ? "Flaga ustawiona." : "Flaga zdjeta.") << endl;
    }
    return false;
}

void wyswietlPlansze() {
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            if (klik[i][j]) {
                if (flaga[i][j]) cout << "P ";
                else cout << wartosc[i][j] << " ";
            }
            else {
                cout << "_ ";
            }
        }
        cout << endl;
    }
}

bool calaPlansza() {
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++)
            if (!klik[i][j] && wartosc[i][j] != 9) return true;
    return false;
}

void zablokuj(int x, int y) {
    for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
            if (i > 0 && i < 6 && j > 0 && j < 6) wartosc[i][j] += 100;
}

void odblokuj(int x, int y) {
    for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
            if (i > 0 && i < 6 && j > 0 && j < 6) wartosc[i][j] -= 100;
}

void odkryjZera(int x, int y) {
    if (x < 1 || x > 5 || y < 1 || y > 5 || klik[x][y]) return;
    klik[x][y] = true;
    if (wartosc[x][y] == 0) {
        for (int i = x - 1; i <= x + 1; i++)
            for (int j = y - 1; j <= y + 1; j++)
                odkryjZera(i, j);
    }
}

int main() {
    srand(time(NULL));
    initialize();

    int x, y, z, licznik = 0, xx, yy;
    bool bomba = false;

    cout << "Podaj wspolrzedne poczatkowe, ktore zostana zablokowane (x y): ";
    cin >> yy >> xx;
    zablokuj(xx, yy);

    while (licznik < 5) {
        x = rand() % 5 + 1;
        y = rand() % 5 + 1;
        if (wpiszBombe(x, y)) {
            licznik++;
            dodajWokol(x, y);
        }
    }

    odblokuj(xx, yy);
    odkryjZera(xx, yy);

    wyswietlPlansze();

    while (calaPlansza() && !bomba) {
        cout << "Podaj wspolrzedne i akcje (y x z - 0 odkryj, 1 flaga): ";
        cin >> y >> x >> z;
        bomba = czyTrafilBombe(x, y, z);
        if (!bomba) {
            if (wartosc[x][y] == 0) odkryjZera(x, y);
            wyswietlPlansze();
        }
    }

    if (!bomba) {
        cout << "Gratulacje! Oczysciles pole minowe!" << endl;
    }

    return 0;
}
