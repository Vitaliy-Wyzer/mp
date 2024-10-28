#include <iostream>
#include <cmath>

using namespace std;

class punkt {
    float _x, _y;
public:
    punkt() {
        _x = 0;
        _y = 0;
    }
    punkt(float x, float y) {
        _x = x;
        _y = y;
    }
    float &x() {
        return _x;
    }
    float &y() {
        return _y;
    }
    float odleglosc(punkt p) {
        return sqrt(pow(p.x() - _x, 2) + pow(p.y()-_y, 2));
    }
};

class wielobok {
    punkt *_t, *_f;
public:
    wielobok() {
        _t = nullptr;
        _f = nullptr;
    }
    wielobok(punkt *t, punkt *f) {
        _t = t;
        _f = f;
    }
    float obwod() {
        float sum = 0.0f;
        punkt * tmp = _t;
        while (tmp < (_f-1)) {
            sum += tmp->odleglosc(*(tmp+1));
            tmp++;
        }
        return sum;
    }
    punkt &Punkt(int i) {
        return _t[i];
    }
    void Punkty(punkt *t, punkt *f) {
        _t = t;
        _f = f;
    }

    int ilosc() {
        return _f - _t;
    }

};

int main()
{
    punkt p(2, 3); 
    cout << p.x() << ' ' << p.y() << '\n'; 
    
    p.x() = 1; 
    p.y() = 1; 
    cout << p.x() << ' ' << p.y() << '\n'; 
    cout << p.odleglosc(punkt()) << '\n'; 
    
    punkt t[] = { punkt(0, 1), punkt(0, 0), punkt(1, 0), punkt(1, 1) }; 
    wielobok w1(t, t+4); 
    cout << w1.obwod() << '\n'; 
    
    w1.Punkt(1) = punkt(0.5, 0.5); 
    cout << w1.obwod() << '\n'; 
    
    wielobok w2; 
    w2.Punkty(t, t+3); 
    cout << w2.obwod() << '\n'; 
    for (int i = 0; i < w2.ilosc(); ++i) 
        cout << w2.Punkt(i).x() << ' ' << w2.Punkt(i).y() << '\n'; 

     return 0;
}
