#include "41043210_HW2.h.h"
#include <iostream>
#include <String>
#include <cmath>

Polynomial::Polynomial() {
    capacity = 1;
    terms = 0;
    termArray = new Term[capacity];
}

void Polynomial::NewTerm(const float coef, const int exp) {
    if (terms == capacity) {
        capacity *= 2;
        Term* newArray = new Term[capacity];
        for (int i = 0; i < terms; ++i) {
            newArray[i] = termArray[i];
        }
        delete[] termArray;
        termArray = newArray;
    }
    termArray[terms].coef = coef;
    termArray[terms].exp = exp;
    terms++;
}

Polynomial Polynomial::Add(const Polynomial& poly) {
    Polynomial result;
    int i = 0, j = 0;

    while (i < terms && j < poly.terms) {
        if (termArray[i].exp == poly.termArray[j].exp) {
            float sum = termArray[i].coef + poly.termArray[j].coef;
            if (sum != 0) {
                result.NewTerm(sum, termArray[i].exp);
            }
            i++;
            j++;
        } else if (termArray[i].exp > poly.termArray[j].exp) {
            result.NewTerm(termArray[i].coef, termArray[i].exp);
            i++;
        } else {
            result.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp);
            j++;
        }
    }

    for (; i < terms; i++) {
        result.NewTerm(termArray[i].coef, termArray[i].exp);
    }
    for (; j < poly.terms; j++) {
        result.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp);
    }

    return result;
}

Polynomial Polynomial::Mult(const Polynomial& poly) {
    Polynomial result;

    for (int i = 0; i < terms; ++i) {
        for (int j = 0; j < poly.terms; ++j) {
            float coef = termArray[i].coef * poly.termArray[j].coef;
            int exp = termArray[i].exp + poly.termArray[j].exp;
            result.NewTerm(coef, exp);
        }
    }

    // �X�֬ۦP���ƪ���
    Polynomial temp;
    for (int i = 0; i < result.terms; ++i) {
        bool combined = false;
        for (int j = 0; j < temp.terms; ++j) {
            if (temp.termArray[j].exp == result.termArray[i].exp) {
                temp.termArray[j].coef += result.termArray[i].coef;
                combined = true;
                break;
            }
        }
        if (!combined) {
            temp.NewTerm(result.termArray[i].coef, result.termArray[i].exp);
        }
    }
    return temp;
}

float Polynomial::Eval(float f) {
    float result = 0.0;
    for (int i = 0; i < terms; ++i) {
        result += termArray[i].coef * std::pow(f, termArray[i].exp);
    }
    return result;
}

istream& operator>>(istream& in, Polynomial& poly) {
    int numTerms;
    cout << "�п�J�h����������: ";
    in >> numTerms;

    for (int i = 0; i < numTerms; ++i) {
        float coef;
        int exp;
        cout << "�п�J�Y�ƻP����: ";
        in >> coef >> exp;
        poly.NewTerm(coef, exp);
    }

    return in;
}

ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; ++i) {
        if (i > 0 && poly.termArray[i].coef > 0) {
            out << " + ";
        }
        out << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
    }
    return out;
}

int main() {
    Polynomial p1, p2;

    cout << "�п�J�Ĥ@�Ӧh����:\n";
    cin >> p1;

    cout << "�п�J�ĤG�Ӧh����:\n";
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "�Ĥ@�Ӧh����: " << p1 << endl;
    cout << "�ĤG�Ӧh����: " << p2 << endl;
    cout << "��Ӧh�������M: " << sum << endl;
    cout << "��Ӧh�������n: " << product << endl;

    float x;
    cout << "�п�J x ���ȥH�p��Ĥ@�Ӧh��������: ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Eval(x) << endl;

    return 0;
}
