#include <iostream>

using namespace std;

class adres {
	string miasto, kod_pocztowy, ulica;
	int numer;
public:
	adres() {
		miasto = "NA";
		kod_pocztowy = "NA";
		ulica = "NA";
		numer = 0;
	}
	adres(const string m, const string k, const string ul, const int n) {
		miasto = m;
		kod_pocztowy = k;
		ulica = ul;
		numer = n;
	}
	adres(const adres & ad) {
		miasto = ad.miasto;
		kod_pocztowy = ad.kod_pocztowy;
		ulica = ad.ulica;
		numer = ad.numer;
	}

	adres& operator=(const adres& adr) {
		if (this != &adr) {
			miasto = adr.miasto;
			kod_pocztowy = adr.kod_pocztowy;
			ulica = adr.ulica;
			numer = adr.numer;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, const adres& adres) {
		os << adres.miasto << ", " << adres.kod_pocztowy << ", " << adres.ulica << " " << adres.numer << endl;
		return os;
	}
};	

class osoba {
	string imie, nazwisko;
	int wiek;
	adres * _adres;
public:
	osoba() {
		imie = "";
		nazwisko = "";
		wiek = 0;
		_adres = new adres;
	}
	osoba(const string im, const string nazw, const int w, const adres & ad) {
		imie = im;
		nazwisko = nazw;
		wiek = w;
		_adres = new adres(ad);
	}
	osoba(const osoba& osb) {
		imie = osb.imie;
		nazwisko = osb.nazwisko;
		wiek = osb.wiek;
		_adres = new adres(*osb._adres);
	}
	osoba& operator=(const osoba& osb) {
		if (this != &osb) {
			imie = osb.imie;
			nazwisko = osb.nazwisko;
			wiek = osb.wiek;
			delete _adres;
			_adres = new adres(*osb._adres);
		}
		return *this;
	}
	~osoba() { delete _adres; }

	friend ostream& operator<<(ostream& os, const osoba& osb) {
		os << osb.imie << ", " << osb.nazwisko << ", " << osb.wiek << ", " << *osb._adres << endl;
		return os;
	}
};

int main()
{
	adres* wsk = new adres("Czestochowa", "42-200", "Dabrowskiego", 73);
	cout << *wsk << '\n';
	adres a1(*wsk);
	delete wsk;

	const adres* wsk1 = new adres("Warszawa", "00-950", "Mysliwiecka", 357);
	cout << a1 << '\n';
	cout << *wsk1 << '\n';

	adres a2;
	cout << a2 << '\n';
	a2 = a1;
	cout << a2 << '\n';

	osoba o("Jan", "Kos", 25, *wsk1);
	cout << o << '\n';
	osoba o1(o);
	cout << o1 << '\n';

	osoba o2;
	cout << o2 << '\n';
	o2 = o1;
	cout << o2 << '\n';
	delete wsk1;
	
	return 0;
}
