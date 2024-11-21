#include "./HW2.h"
#include <iostream>
#include <String>

using namespace std;

Polynomial::Polynomial() {
    terms = 0;
    capacity = 1;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp){                                                              //double the size of array when the result is greater than current size
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];                            //define temp as new array
        copy(termArray, termArray + terms, temp);                   //copy old array into the new array
        delete[] termArray;                                         //deallocate old array memory location
        termArray = temp;                                           //point to new array location
    }

    termArray[terms].coef = theCoeff;                               //set coefficients
    termArray[terms].exp = theExp;                                  //move to next position (last time adding is greater) after copying to new array
    terms++;
    
}

Polynomial Polynomial::Add(Polynomial b){
    Polynomial c;                                                   //for short time process
    int aPos = 0, bPos = 0;                                         //position of processing point

    c.termArray = new Term[capacity];
    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {         //if exponent of a = b, add coefficients
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) {
                c.NewTerm(t, termArray[aPos].exp);
            }
            aPos++; bPos++;                                         //both move to next position in termArray
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) {     //b,exp is greater so add term of b
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }

        //add remaining terms of *this
    }
    for (; aPos < terms ; aPos++) {
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    }
    //add remaining terms of b
    for (; bPos < b.terms ; bPos++) {
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    }
    
    return c;
}

Polynomial Polynomial::Subtraction(Polynomial b) {
    Polynomial c;                                                   //for short time process
    int aPos = 0, bPos = 0;                                         //position of processing point

    c.termArray = new Term[capacity];
    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {         //if exponent of a = b, add coefficients
            float t = termArray[aPos].coef - b.termArray[bPos].coef;
            if (t) {
                c.NewTerm(t, termArray[aPos].exp);
            }
            aPos++; bPos++;                                         //both move to next position in termArray
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) {     //b,exp is greater so add term of b
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }

        //add remaining terms of *this
    }
    for (; aPos < terms; aPos++) {
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    }
    //add remaining terms of b
    for (; bPos < b.terms; bPos++) {
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    }

    return c;
}

Polynomial Polynomial::Mult(Polynomial b){
    Polynomial c;
    int aPos = 0;

    c.termArray = new Term[capacity];
    while ((aPos < terms)){
        for (int bPos = 0 ; bPos < b.terms ; bPos++){
            int ok = 0;
            float t = termArray[aPos].coef * b.termArray[bPos].coef;
            int y = termArray[aPos].exp + b.termArray[bPos].exp;
            for (int i = 0; i < c.terms; i++) {
                if (c.termArray[i].exp == y) {
                    c.termArray[i].exp = y;
                    c.termArray[i].coef += t;
                    ok = 1;
                }
            }
            if (ok == 0) {
                c.NewTerm(t, y);
            }
            
        }
        aPos++;
    }
    for (int i = 0; i < c.terms; i++) {                             //downgrade
        for (int j = (i + 1) ; j < c.terms ; j++){
            if (c.termArray[i].exp < c.termArray[j].exp){
                int tempExp = c.termArray[i].exp;
                c.termArray[i].exp = c.termArray[j].exp;
                c.termArray[j].exp = tempExp;

                float tempCoef = c.termArray[i].coef;
                c.termArray[i].coef = c.termArray[j].coef;
                c.termArray[j].coef = tempCoef;

            }
        }
    }

    return c;
}

//Polynomial Polynomial::Division(Polynomial b) {



std::ostream& operator<<(std::ostream& output, const Polynomial &P) {
    float coefficient;
    int exponent;
    std::string polyOperator;//polyOperator
    for (int i = 0; i < P.terms; i++) {
        coefficient = P.termArray[i].coef;
        exponent = P.termArray[i].exp;
        if (i > 0 && coefficient > 0) {
            polyOperator = " + ";
        }else if (coefficient == 0) {
            continue;
        }else {
            polyOperator = "";
        }
        std::cout << polyOperator << coefficient;
        if (coefficient != 0) {
            if (exponent > 1) {
                std::cout << "x^" << exponent;
            }
            else if (exponent == 1) {
                std::cout << "x";
            }
        }
        
    }
    std::cout << "\n";
    return output;
}

std::istream& operator>>(std::istream& input, Polynomial& P){
    int numTerms;   //how many terms in the polynomial
    float coefficient;
    int exponent;
    std::cout << "Please input the number of term of a polynomial:";
    std::cin >> numTerms;
    P.termArray = new Term[numTerms];
    P.terms = numTerms;
    for (int i = 0; i < numTerms; i++) {
        cout << i+1 << "th coefficient: ";
        std::cin >> coefficient;
        P.termArray[i].coef = coefficient;
        std::cout << i+1 << "th exponent: ";
        std::cin >> exponent;
        P.termArray[i].exp = exponent;
    }
    return input;
}

int main(){
    Polynomial A{}, B{};

    cout << "A(x): ";
    cin >> A;
    cout << "B(x): ";
    cin >> B;
    cout << endl;
    cout << "A(X)= " << A << endl;
    cout << "B(X)= " << B << endl;
    cout << "Add:" << A.Add(B) << endl;
    cout << "Subtraction:" << A.Subtraction(B) << endl;
    cout << "Mult:" << A.Mult(B);

    system("pause");
}