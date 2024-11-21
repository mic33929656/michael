#include <iostream>

using namespace std;

class Polynomial;
class Term;

class Polynomial{

    
    private:
        Term *termArray;
        int capacity;
        int terms;

    public:
        Polynomial();

        Polynomial Add(Polynomial poly);

        Polynomial Subtraction(Polynomial poly);

        Polynomial Mult(Polynomial poly);

        //Polynomial Division(Polynomial poly);

        void NewTerm(const float theCoeff, const int theExp);

        //float Eval(float f);
      
        friend std::ostream& operator <<(std::ostream& output, const Polynomial& P);
        friend std::istream& operator >>(std::istream& input, Polynomial& P);

};

class Term{

    friend Polynomial;

    public:
        float coef;
        int exp;
};





