#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
using namespace std;

// 前置宣告
class Polynomial;

// 單項式類別
class Term {
    friend class Polynomial;

private:
    float coef; // 係數
    int exp;    // 指數
};

// 多項式類別
class Polynomial {
public:
    Polynomial(); // 預設建構子
    Polynomial Add(const Polynomial& poly); // 多項式相加
    Polynomial Mult(const Polynomial& poly); // 多項式相乘
    float Eval(float f); // 計算多項式值

    // 輸入與輸出運算子多載
    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

private:
    Term* termArray; // 儲存多項式的項目
    int capacity;    // termArray 的容量
    int terms;       // termArray 中的有效項目數

    void NewTerm(const float coef, const int exp); // 新增一個單項式
};

#endif // POLYNOMIAL_H



