#include <iostream>

using namespace std;

class osoba {
protected:
	string _nazwisko;
	int _liczba_lat;
public:
	osoba(): _nazwisko(""), _liczba_lat(0) {}
	osoba(string last_name, int age): _nazwisko(last_name), _liczba_lat(age) {}

	void pokaz() {
		cout << _nazwisko << " " << _liczba_lat << endl;
	}

	string nazwisko() const { return _nazwisko; }
	int liczba_lat() const { return _liczba_lat; }
};

class pracownik: public osoba {
	string _stanowisko;
	double _placa;
public:
	pracownik(string last_name, int age, string job_type, double salary): osoba(last_name, age), _stanowisko(job_type), _placa(salary) {}

	pracownik(const pracownik &pr) {
		_nazwisko = pr.nazwisko();
		_liczba_lat = pr.liczba_lat();
		_stanowisko = pr.stanowisko();
		_placa = pr.placa();
	}

	string stanowisko() const { return _stanowisko; }
	double placa() const { return _placa; }
	
	void pokaz() {
		osoba::pokaz();
		cout << _stanowisko << " " << _placa << endl;
	}

	pracownik& operator=(const pracownik & pr) {
		_nazwisko = pr.nazwisko();
		_liczba_lat = pr.liczba_lat();
		_stanowisko = pr.stanowisko();
		_placa = pr.placa();

		return (*this);
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
