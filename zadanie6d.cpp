#include <iostream>
#include <cmath>
#include <fstream>
#include <stdexcept>

using namespace std;

class InvalidFileStructure : public runtime_error {
public:
  InvalidFileStructure(const string& message) : runtime_error(message) {}
};

class Point {
public:
  float x, y;
};

class Wielokat {
public:
  Point * p;
  int * ids;
  int size;

  Wielokat() : p(nullptr), ids(nullptr), size(0) {}

  void wczytajZPliku(const string& nazwaPliku) {
    ifstream fin(nazwaPliku);
    if (!fin.good()) {
      throw InvalidFileStructure("Blad pliku: Nie udalo sie otworzyc pliku.");
    }

    string line;
    while (getline(fin, line)) {
      if (line.find("[NUMBER OF NODES]") != string::npos) {
        if (!(fin >> size) || size <= 0) {
          throw InvalidFileStructure("Blad pliku: Nieprawidlowy rozmiar w [NUMBER OF NODES].");
        }
        p = new Point[size];
        getline(fin, line);
      } else if (line.find("[NODES]") != string::npos) {
        for (int i = 0; i < size; ++i) {
          int id;
          if (!(fin >> id) || id <= 0) {
            throw InvalidFileStructure("Blad pliku: Nieprawidlowe ID punktu w [NODES].");
          }
          fin >> p[id - 1].x >> p[id - 1].y;
        }
      } else if (line.find("[POLYGON]") != string::npos) {
        if (ids) {
          delete[] ids;
        }
        ids = new int[size];
        for (int i = 0; i < size; ++i) {
          if (!(fin >> ids[i]) || ids[i] <= 0 || ids[i] > size) {
            throw InvalidFileStructure("Blad pliku: Nieprawidlowe ID w [POLYGON].");
          }
        }
      }
    }

    fin.clear();
    fin.close();
  }
};

float distance(float x1, float y1, float x2, float y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float Pole(const Point * p, const Wielokat& wielokat) {
  float pole = 0.0f;
  for (int i = 0; i < wielokat.size; ++i) {
    const Point& current = p[wielokat.ids[i] - 1];
    const Point& next = p[wielokat.ids[(i + 1) % wielokat.size] - 1];
    pole += current.x * next.y - next.x * current.y;
  }
  return abs(pole) / 2.0f;
}

float Obwod(const Point * p, const Wielokat& wielokat) {
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

    delete[] wielokat.p;
    delete[] wielokat.ids;
  } catch (const InvalidFileStructure& e) {
    cerr << "Wystapil blad: " << e.what() << endl;
    return -1;
  }

  return 0;
}
