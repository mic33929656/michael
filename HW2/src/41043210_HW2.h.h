#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
using namespace std;

// �e�m�ŧi
class Polynomial;

// �涵�����O
class Term {
    friend class Polynomial;

private:
    float coef; // �Y��
    int exp;    // ����
};

// �h�������O
class Polynomial {
public:
    Polynomial(); // �w�]�غc�l
    Polynomial Add(const Polynomial& poly); // �h�����ۥ[
    Polynomial Mult(const Polynomial& poly); // �h�����ۭ�
    float Eval(float f); // �p��h������

    // ��J�P��X�B��l�h��
    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

private:
    Term* termArray; // �x�s�h����������
    int capacity;    // termArray ���e�q
    int terms;       // termArray �������Ķ��ؼ�

    void NewTerm(const float coef, const int exp); // �s�W�@�ӳ涵��
};

#endif // POLYNOMIAL_H



