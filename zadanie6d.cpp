#include <iostream>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

class Point {
public:
    float x, y;
};

class Wielokat {
public:
    Point* p;
    int* ids;
    int size;

    Wielokat() : p(nullptr), ids(nullptr), size(0) {}

    ~Wielokat() {
        delete[] p;
        delete[] ids;
    }

    void wczytajZPliku(const string& nazwaPliku) {
        ifstream fin(nazwaPliku);
        if (!fin.is_open()) {
            throw runtime_error("Nie można otworzyć pliku: " + nazwaPliku);
        }

        string line;
        bool numberOfNodesRead = false;
        bool nodesRead = false;
        bool polygonRead = false;

        while (getline(fin, line)) {
            if (line.find("[NUMBER OF NODES]") != string::npos) {
                fin >> size;
                if (size <= 0) {
                    throw runtime_error("Nieprawidłowa liczba węzłów w pliku.");
                }
                p = new Point[size];
                getline(fin, line); // Przejdź do następnej linii
                numberOfNodesRead = true;
            } else if (line.find("[NODES]") != string::npos) {
                if (!numberOfNodesRead) {
                    throw runtime_error("Sekcja [NUMBER OF NODES] musi być przed sekcją [NODES].");
                }
                for (int i = 0; i < size; ++i) {
                    int id;
                    if (!(fin >> id >> p[id - 1].x >> p[id - 1].y)) {
                        throw runtime_error("Nieprawidłowe dane w sekcji [NODES].");
                    }
                }
                nodesRead = true;
            } else if (line.find("[POLYGON]") != string::npos) {
                if (!nodesRead) {
                    throw runtime_error("Sekcja [NODES] musi być przed sekcją [POLYGON].");
                }
                ids = new int[size];
                for (int i = 0; i < size; ++i) {
                    if (!(fin >> ids[i])) {
                        throw runtime_error("Nieprawidłowe dane w sekcji [POLYGON].");
                    }
                }
                polygonRead = true;
            }
        }

        if (!numberOfNodesRead || !nodesRead || !polygonRead) {
            throw runtime_error("Brak wymaganych sekcji w pliku.");
        }

        fin.close();
    }
};

float distance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float Pole(const Point* p, const Wielokat& wielokat) {
    float pole = 0.0f;
    for (int i = 0; i < wielokat.size; ++i) {
        const Point& current = p[wielokat.ids[i] - 1];
        const Point& next = p[wielokat.ids[(i + 1) % wielokat.size] - 1];
        pole += current.x * next.y - next.x * current.y;
    }
    return abs(pole) / 2.0f;
}

float Obwod(const Point* p, const Wielokat& wielokat) {
    float obwod = 0.0f;
    for (int i = 0; i < wielokat.size; ++i) {
        const Point& current = p[wielokat.ids[i] - 1];
        const Point& next = p[wielokat.ids[(i + 1) % wielokat.size] - 1];
        obwod += distance(current.x, current.y, next.x, next.y);
    }
    return fabs(obwod);
}

int main() {
    try {
        Wielokat wielokat;
        wielokat.wczytajZPliku("bad.txt");

        float obwod = Obwod(wielokat.p, wielokat);
        float pole = Pole(wielokat.p, wielokat);

        cout << "Obwod: " << obwod << endl;
        cout << "Pole: " << pole << endl;
    } catch (const exception& e) {
        cerr << "Wystąpił błąd: " << e.what() << endl;
        return -1;
    }

    return 0;
}
