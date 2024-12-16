#include <iostream>
using namespace std;

class Paczka{
  string _adres;
  float _cena;
public:
  Paczka(): _adres(""), _cena(0.0f) {}
  Paczka(string adres, float cena) {
    _adres = adres;
    _cena = cena;
  }
  friend ostream& operator<<(ostream& os, const Paczka& paczka) {
    os << paczka._adres << " " << paczka._cena << "\n";
    return os;
  }
  string& adres() {return _adres; }
  float cena() {return _cena; }
};

class Osoba {
  string _imie, _nazwisko;
public:
  Osoba(): _imie(""), _nazwisko("") {}
  Osoba(string imie, string nazwisko) {
    _imie = imie;
    _nazwisko = nazwisko;
  }
  bool operator==(const Osoba& os) {
    return _imie == os._imie && _nazwisko == os._nazwisko;
  } 
  friend ostream& operator<<(ostream& os, const Osoba& osb) {
    os << osb._imie << " " << osb._nazwisko << "\n";
    return os;
  }
  string& imie() {return _imie;}
  string& nazwisko() {return _nazwisko;}
};

class Kurier: public Osoba {
  Paczka * p;
  int rozmiar;
public:
  Kurier(): p(nullptr), rozmiar(0) {}
  Kurier(const Paczka * p1, const Paczka *p2) {
    rozmiar = p2-p1;
    p = new Paczka[rozmiar];
    for (int i=0; i<rozmiar; ++i) {
      p[i] = p1[i];
    }
  }
  Kurier(const Kurier& k) {
    rozmiar = k.rozmiar;
    p = new Paczka[rozmiar];
    for (int i=0; i<rozmiar; ++i) {
      p[i] = k.p[i];
    }
  }
  Kurier operator=(const Kurier& k) {
    rozmiar = k.rozmiar;
    if (p) { delete [] p; }
    p = new Paczka[rozmiar];
    for (int i=0; i<rozmiar; ++i) {
      p[i] = k.p[i];
    }
    return (*this);
  }
  Kurier operator+(const Paczka& paczka) {
    Kurier k;
    k.rozmiar = rozmiar + 1;
    k.p = new Paczka[k.rozmiar];
    for (int i = 0; i<k.rozmiar-1; ++i) {
      k.p[i] = p[i];
    }
    k.p[k.rozmiar-1] = paczka;
    return k;
  }
  Paczka operator[](const int i) {
    if (i < rozmiar && i >=0) {
      return p[i];
    } else {
      throw i;
    }
  }
  string wartosc() {
    for (int i =0; i<rozmiar; ++i) {
      cout << p[i].adres() << " " << p[i].cena() << "\n";
    }
    return "";
  }

  ~Kurier() {
    if (p) {
      delete [] p;
      p = nullptr;
    }
  }
 
};

int main()
{
  Paczka p[] = {
    Paczka("Dabrowskiego 33", 123.00), 
    Paczka("NMP 12", 40.00),
    Paczka("Armii Krakowej 4", 30.00), 
    Paczka("Andersa 6", 51.00),
    Paczka("Kukuczki 13", 12.00), 
    Paczka("Skrzyneckiego 5", 40.00), 
  };

  Osoba o1("Jan", "Kowalski");
  cout << "---- 1 ----" << endl;
  cout << o1 << endl;
  
  {
      Osoba o2(o1);
      cout << "---- 2 ----" << endl;
      cout << o2 << endl;
      
      cout << "---- 3 ----" << endl;
      cout << boolalpha << (o1 == o2) << endl;
      
      Osoba o3;
      cout << "---- 4 ----" << endl;
      cout << o3 << endl;

      o3 = o2;
      cout << "---- 5 ----" << endl;
      cout << o3 << endl;
      
  }   

  cout << "---- 6 ----" << endl;
  cout << o1 << endl;
      
  Kurier k1(p, p+3);
  cout << "---- 7 ----" << endl;
  cout << k1.wartosc() << endl;

  Kurier k2;
  cout << "---- 8 ----" << endl;
  cout << k2.wartosc() << endl;

  {
    Kurier k3(k1);
    cout << "---- 9 ----" << endl;
    cout << k3.wartosc() << endl;

    k2 = k3;
    cout << "---- 10 ----" << endl;
    cout << k2.wartosc() << endl;

    k1 = k1 + p[4]; 
    k1 = k1 + p[5];

    cout << "---- 11 ----" << endl;
    cout << k1.wartosc() << endl;

  }

  cout << "---- 12 ----" << endl;
  cout << k2.wartosc() << endl;

  try{
    Kurier k4(p, p+3);
    cout << "---- 13 ----" << endl;
    for(int i=0; i<10; ++i){
      cout << k4[i] << ",";
    }
    cout << endl;
  }
  catch(...){
    cout << "---- 14 ----" << endl;
    cout << "Wyjatek" << endl;
  }

  return 0;
}
