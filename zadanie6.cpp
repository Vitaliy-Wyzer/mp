#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

class Point {
public:
  float x,y;
};

class Wielokat {
public:
  Point * p;
  int * ids;
  int size;
};

float distance(float x1, float y1, float x2, float y2) {
  return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

float Pole(const Point * p, const Wielokat& wielokat) {
  float pole = 0.0f;
  for (int i = 0; i<wielokat.size; ++i) {
    const Point& current = p[wielokat.ids[i] - 1];
    const Point& next = p[wielokat.ids[(i+1) % wielokat.size] - 1];
    pole += current.x * next.y - next.x * current.y;
  }
  return abs(pole) / 2.0f;
}

float Obwod(const Point * p, const Wielokat& wielokat) {
  float obwod = 0.0f;
  for (int i = 0; i<wielokat.size; ++i) {
    const Point& current = p[wielokat.ids[i] - 1];
    const Point& next = p[wielokat.ids[(i+1) % wielokat.size] - 1];
    obwod += distance(current.x, current.y, next.x, next.y);
  }
  return fabs(obwod);
}

// ids table
// getline
// >>
// while do konca pliku
// getline sprawdzenie
// f >> id >> x >> y; n razy




int main() {
  ifstream fin("ok.txt");
  if (!fin.good()) {
    cerr << "Blad pliku";
    fin.clear();
    fin.ignore();
    fin.close();
    return -1;
  }

  Wielokat wielokat;
  wielokat.p = nullptr;
  wielokat.ids = nullptr;
  wielokat.size = 0;

  string line;
  while (getline(fin, line)) {
    if (line.find("[NUMBER OF NODES]") != string::npos) {
      fin >> wielokat.size;
      wielokat.p = new Point[wielokat.size];
      getline(fin, line);
    } else if (line.find("[NODES]") != string::npos) {
      for (int i = 0; i<wielokat.size; ++i) {
        int id;
        fin >> id;
        fin >> wielokat.p[id-1].x >> wielokat.p[id-1].y;
      }
    } else if (line.find("[POLYGON]") != string::npos) {
      wielokat.ids = new int[wielokat.size];
      for (int i = 0; i<wielokat.size; ++i) {
        fin >> wielokat.ids[i];
      }
    }
  }
  fin.clear();
  fin.close();

  float obwod = Obwod(wielokat.p, wielokat);
  float pole = Pole(wielokat.p, wielokat);

  cout << "Obwod: " << obwod << endl;
  cout << "Pole: " << pole << endl;

  delete [] wielokat.p;
  delete [] wielokat.ids;

  return 0;
}
