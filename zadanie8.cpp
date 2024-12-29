#include <iostream>

using namespace std;

class osoba {
	string _nazwisko;
	int _liczba_lat;
public:
	osoba() {
		_nazwisko = "";
		_liczba_lat = 0;
	}
	osoba(string nazwisko, int liczba_lat) {
		_nazwisko = nazwisko;
		_liczba_lat = liczba_lat;
	}
	void pokaz() {
		cout << "\n" << _nazwisko << " " << _liczba_lat << " ";
	}

	string nazwisko() const {
		return _nazwisko;
	}
	int liczba_lat() const {
		return _liczba_lat;
	}
};

class pracownik : public osoba {
	string _stanowisko;
	double _placa;
public:
	pracownik() {
		_stanowisko = "";
		_placa = 0.0;
	}
	pracownik(string nazwisko, int liczba_lat, string stanowisko, double placa): osoba(nazwisko, liczba_lat) {
		_stanowisko = stanowisko;
		_placa = placa;
	}
	string stanowisko() const {
		return _stanowisko;
	}
	double placa() const {
		return _placa;
	}
	void pokaz() {
		osoba::pokaz();
		cout << " " << _stanowisko << " " << _placa << endl;
	}
};

int main()
{
	osoba os("Dolas", 26);
	os.pokaz();
	const pracownik pr1("Dyzma", 35, "mistrz", 1250.0);
	cout << pr1.nazwisko() << pr1.liczba_lat();
	cout << pr1.stanowisko() << pr1.placa();
	pracownik pr2(pr1);
	pr2.pokaz();
	pracownik pr3("Kos", 45, "kierownik", 2260.0);
	pr3.pokaz();
	pr3 = pr2;
	pr3.pokaz();
	osoba* w = &os;
	w->pokaz();
	w = &pr3;
	w->pokaz();
	static_cast<pracownik*>(w)->pokaz();

	return 0;
}
