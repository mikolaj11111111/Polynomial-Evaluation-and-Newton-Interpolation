#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<cmath>
#include <chrono>

using namespace std;
using namespace chrono;

float wielomian_p_naturalnej(vector<float> a, vector<float> x, int n) {
    
    float sum = 0;

    for (int i = 0; i < x.size(); i++) {
        float result = 0;
        for (int j = 0; j <= n; j++) {
            result += a[j] * pow(x[i], j);
        }
        //cout << "result: " << result << " dla x = " << x[i] << endl;
        sum += result;
    }
    //Suma wieomianow w postaci naturalnej dla kazdego x'a
    cout << "SUMA WARTOSCI WIELOMIANU W POSTACI NATURALNEJ: " << sum << endl;
    return sum;
}

float wielomian_hornera(vector<float> a, vector<float> x, int n) {

    float sum = 0;

    for (int i = 0; i < x.size(); i++) {
        float result = 0;
        for (int j = n; j >= 0;j--) {
            if (j == n) {
                result += x[i] * a[j];
            }
            else if (j == 0) {
                result += a[j];
            }
            else{
                result += a[j];
                result *= x[i];
            }  
        }
        //cout << "result: " << result << " dla x = " << x[i] << endl;
        sum += result;
    }
    cout << "SUMA WARTOSCI WIELOMIANU W POSTACI HORNERA: " << sum << endl;
    return sum;
}
vector<float> oblicz_ilorazy_roznicowe(vector<float>& f, vector<float>& x, int n) {
    vector<vector<float>> ilorazy(n, vector<float>(n, 0));

    for (int i = 0; i < n; i++) {
        ilorazy[i][0] = f[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            ilorazy[i][j] = (ilorazy[i + 1][j - 1] - ilorazy[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    vector<float> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = ilorazy[0][i];
    }

    return a;
}

float wielomian_newtona(vector<float> a, float x, vector<float> x_wezlowy, int n) {
    
    if (a.size() <= n || x_wezlowy.size() <= n) {
        cerr << "B³¹d: Rozmiar wektora a lub x_wezlowy jest za ma³y!" << endl;
        return -1;
    }
    
    float sum = a[0];
    for (int i = 1; i <= n; i++) {
        float result = 1;
        for (int j = 0; j < i; j++) {
            if (j < x_wezlowy.size()) { 
                result *= (x - x_wezlowy[j]);
            }
            else {
                cerr << "B³¹d: Indeks przekracza zakres wektora x_wezlowy" << endl;
                return -1;
            }
        }
        sum += result * a[i];
    }
    return sum;
}



int main() {
    ifstream myfile("interpolacja_H_gr_01.txt");
    if (!myfile.is_open()) {
        cerr << "Nie mo¿na otworzyæ pliku!" << endl;
        return 1;
    }

    vector<float> xi_column;
    vector<float> a;

    string line;

    // Wczytywanie wspó³czynników a
    while (myfile >> line) {
        if (line == "xi:") break;  

        size_t pos = line.find("="); 
        if (pos != string::npos) {
            string numStr = line.substr(pos + 1); 
            try {
                a.push_back(stof(numStr)); 
            }
            catch (...) {
                continue;  
            }
        }
    }

    // Wczytywanie wartoœci xi
    float value;
    while (myfile >> value) {
        xi_column.push_back(value);
    }

    myfile.close();
    /*
    // Wyœwietlenie wyników
    cout << "xi:\n";
    for (size_t i = 0; i < xi_column.size(); i++) {
        cout << xi_column[i] << " ";
        if ((i + 1) % 5 == 0) cout << endl;
    }

    cout << "\n\nWspó³czynniki a:\n";
    for (size_t i = 0; i < a.size(); i++) {
        cout << "a" << i << " = " << a[i] << endl;
    }
    */

    //zadanie 1
    //wielomian_p_naturalnej(a, xi_column, 3);

    //zadanie 2
    auto start = high_resolution_clock::now();
    float w_p_n = wielomian_p_naturalnej(a, xi_column, 3);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    auto start1 = high_resolution_clock::now();
    float w_p_h = wielomian_hornera(a, xi_column, 3);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    float sum_difference = w_p_n - w_p_h;

    cout << "CZAS OBLICZENIA WIELOMIANU W POSTACI NATURALNEJ: " << duration.count() << " microseconds\n";
    cout << "CZAS OBLICZENIA WIELOMIANU W POSTACI HORNERA: " << duration1.count() << " microseconds\n";
    cout << "ROZNICA SUMY WIELOMIANU DLA N=3 POMIEDZY WIELOMIANEM W POSTACI NATURALNEJ I HORNERA: " << sum_difference << endl;


    //ZADANIE 5

    ifstream myfile1("interpolacja_N_gr_01.txt");
    if (!myfile1.is_open()) {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return 1;
    }

    vector<float> xi_column1, fxi_column;
    vector<float> xi_column_bez_w, fxi_column_bez_w;
    string tmp;
    bool is_fxi_column = false;

    while (myfile1 >> tmp) {
        if (tmp == "xi:") break;
    }
    int x = 0;
    int next = 0;
    float value1;
    while (myfile1 >> value1) {
        if (next == x) {
            xi_column1.push_back(value1);
            x += 5;
        }
        else {
            xi_column_bez_w.push_back(value1);
        }
        next += 1;
        if (myfile1.peek() == '\n') break;
    }
    x = 0;
    next = 0;

    while (myfile1 >> tmp) {
        if (tmp == "f(xi):") break;
    }

    while (myfile1 >> value1) {
        if (next == x) {
            fxi_column.push_back(value1);
            x += 5;
        }
        else {
            fxi_column_bez_w.push_back(value1);
        }
        next += 1;
        if (myfile1.peek() == '\n') break;
    }
    /*
    size_t n = min(xi_column1.size(), fxi_column.size());

    cout << "xi" << "         " << "f(xi)" << endl;
    for (size_t i = 0; i < n; i++) {
        cout << xi_column1[i] << "   " << fxi_column[i] << endl;
    }

    size_t n1 = min(xi_column_bez_w.size(), fxi_column_bez_w.size());

    cout << "xi co 5" << "         " << "f(xi) co 5" << endl;
    for (size_t i = 0; i < n1; i++) {
        cout << xi_column_bez_w[i] << "   " << fxi_column_bez_w[i] << endl;
    }
    myfile1.close();
    */
    //WYDRUK WARTOSCI A DLA NEWTONA
    vector<float> a_newton = oblicz_ilorazy_roznicowe(fxi_column, xi_column1, xi_column1.size());
    for (int i = 0; i < a_newton.size(); i++) {
        cout << "a[" << i << "] = " << a_newton[i] << endl;
    }
    float x_test;
    cout << "Podaj wartosc x: ";
    cin >> x_test;
    float wynik_newton = wielomian_newtona(a_newton, x_test, xi_column1, 3);
    cout << "Wartosc wielomianu Newtona dla x = " << x_test << ": " << wynik_newton << endl;

    //SPRAWDZENIE DLA ILU WEZLOW INTERPOLACJA JEST NAJLEPSZA
    //BIERZEMY X DLA PIERWSZEGO WEZLA
    
    float x_dla_newtona = xi_column1[4];
    float y_dla_newtona = fxi_column[4];
    float najmniejszy_blad = INT_MAX;
    int najlepsza_ilosc_wezlow;
    
    cout << "x testowy: " << x_dla_newtona << " y testowy: " << y_dla_newtona << endl;
    
    // Sprawdzanie b³êdu dla ró¿nych punktów wêz³owych
    for (int i = 1; i <= xi_column1.size(); i++) {
        vector<float> a_newton = oblicz_ilorazy_roznicowe(fxi_column, xi_column1, i); 
        float wynik = wielomian_newtona(a_newton, x_dla_newtona, xi_column1, i - 1);

        float blad = fabs(wynik - y_dla_newtona);  
        cout << "blad dla " << i << " wezlow to: " << blad << endl;
        if (blad < najmniejszy_blad) {
            najmniejszy_blad = blad;
            najlepsza_ilosc_wezlow = i;  
        }
    }

    cout << "Najdokladniejsze wyniki uzyskano dla " << najlepsza_ilosc_wezlow << " punktow wezlowych." << endl;
    cout << "Najmniejszy bla interpolacji: " << najmniejszy_blad << endl;


    
    return 0;
}
