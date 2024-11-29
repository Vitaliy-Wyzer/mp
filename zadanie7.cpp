#include <iostream>
#include <fstream>
using namespace std;

class Osoba {
  string imie, nazwisko;
  long long int pesel;
public:
  Osoba(): imie(""), nazwisko(""), pesel(0) {}
  Osoba(string im, string nz, long long int psl) {
    imie = im;
    nazwisko = nz;
    pesel = psl;
  }
  friend bool operator==(const Osoba& os1, const Osoba& os2) {
    return os1.pesel == os2.pesel;
  }
  friend ostream& operator<<(ostream& os, const Osoba& osoba) {
    os << osoba.imie << " " << osoba.nazwisko << " " << osoba.pesel << endl;
    return os;
  }
  friend ifstream& operator>>(ifstream& fin, Osoba& osoba) {
    fin >> osoba.imie >> osoba.nazwisko >> osoba.pesel;
    return fin;
  }
  string& get_imie(){
    return imie;
  }
  string& get_nazwisko(){
    return nazwisko;
  }
  long long int& get_pesel() {
    return pesel;
  }


};

class BazaDanych {
  Osoba * baza;
  int rozmiar;
public:
  BazaDanych(): baza(nullptr), rozmiar(0) {}

  BazaDanych(BazaDanych& bd) {
    rozmiar = bd.rozmiar;
    if (rozmiar > 0) {
      baza = new Osoba[rozmiar];
      for (int i = 0; i<rozmiar; ++i) {
        baza[i] = bd.baza[i];

      }
    } else {
      baza = nullptr;
    }
  }

  int liczbaOsob() {
    return rozmiar;
  }

  friend ostream& operator<<(ostream& os, const BazaDanych& bd) {
    if (bd.rozmiar > 0) {
      for (int i = 0; i<bd.rozmiar; ++i) {
        os << bd.baza[i].get_imie() << " " << bd.baza[i].get_nazwisko() << " " << bd.baza[i].get_pesel() << endl; 
      }
    }
    return os;
  }

  BazaDanych operator+(Osoba& os) {
    BazaDanych new_bd;
    new_bd.rozmiar = rozmiar + 1;
    new_bd.baza = new Osoba[new_bd.rozmiar];
    for (int i = 0; i<rozmiar; ++i) {
      new_bd.baza[i] = baza[i];
    }
    new_bd.baza[new_bd.rozmiar-1] = os;
    return new_bd;
  }
  
  Osoba operator[](const int i) {
    return baza[i];
  }
  BazaDanych& operator=(const BazaDanych& bd) {
    if (this != &bd) {
      if (baza) {
        delete [] baza;
        baza = nullptr;
      }
      rozmiar = bd.rozmiar;
      baza = new Osoba[rozmiar];
      for (int i = 0; i<rozmiar; ++i) {
        baza[i].get_imie() = bd.baza[i].get_imie();
        baza[i].get_nazwisko() = bd.baza[i].get_nazwisko();
        baza[i].get_pesel() = bd.baza[i].get_pesel();
      }
      }
    return *this;
  }
  friend BazaDanych operator+(BazaDanych& bd1, BazaDanych& bd2) {
    BazaDanych bd;
    bd.rozmiar = bd1.rozmiar + bd2.rozmiar;
    bd.baza = new Osoba[bd.rozmiar];
    for (int i = 0; i<bd1.rozmiar; ++i) {
      bd.baza[i] = bd1.baza[i];
    }
    for (int i = 0; i<bd2.rozmiar; ++i) {
      bd.baza[i+bd1.rozmiar] = bd2.baza[i];
    }
    return bd;
  }

  friend BazaDanych operator-(BazaDanych& bd, Osoba& os) {
    int new_size = 0;
    for (int i = 0; i<bd.rozmiar; ++i) {
      if (!(bd.baza[i] == os)) {
        new_size++;
      }
    }

    if (new_size == bd.rozmiar) {
      return bd;
    }

    BazaDanych d;
    d.rozmiar = new_size;
    d.baza = new Osoba[new_size];
    int index = 0;
    for (int i = 0; i<bd.rozmiar; ++i) {
      if (!(bd.baza[i] == os)) {
        d.baza[index++] = bd.baza[i];
      }
    }
    return d;
  }

  ~BazaDanych() {
    if (baza) {
      delete [] baza;
      baza = nullptr;
    }
  }
};

int main()
{
  Osoba o1;
  cout << "---- 1 ----" << endl;
  cout << o1 << endl;

  Osoba o2("Jan", "Kowalski", 11111111111);
  cout << "---- 2 ----" << endl;
  cout << o2 << endl;
      
  cout << "---- 3 ----" << endl;
  cout << boolalpha << (o1 == o2) << endl;

  BazaDanych db1;
  cout << "---- 4 ----" << endl;
  cout << db1;
  
  db1 = db1 + o1;
  cout << "---- 5 ----" << endl;
  cout << db1;
  
  ifstream plik_we("zadanie7.txt");
  if(!plik_we)
  {
    cout << "---- 6 ----" << endl;
    return 1;
  }
  
  while(plik_we >> o2)
  {
      db1 = db1 + o2;
  }
  cout << "---- 7 ----" << endl;
  cout << db1;
  
  {
    BazaDanych db2(db1);
    cout << "---- 8 ----" << endl;
    cout << db2;
  }

  cout << "---- 9 ----" << endl;
  cout << db1;
  
  BazaDanych db3;
  db3 = db1 + db1;
  cout << "---- 10 ----" << endl;
  cout << db3;
  
  for(int i=0; i<db3.liczbaOsob(); ++i)
  {
      cout << db3[i] << endl; 
  }
  cout << "---- 11 ----" << endl;  
  
  db1 = db1 - o1;
  cout << "---- 12 ----" << endl;
  cout << db1;
  
  cout << "---- 13 ----" << endl;
  cout << db3;
  cout << "---- 14 ----" << endl;
  
  return 0;
}
