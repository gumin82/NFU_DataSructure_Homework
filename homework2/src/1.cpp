#include <iostream>
#include <algorithm>
using namespace std;

class Polynomial;

class Term {
    friend Polynomial;
    friend ostream& operator<<(ostream& output, const Polynomial& Poly);
private:
    int exp;
    float coef;
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;
public:
    Polynomial() : capacity(2), terms(0) {
        termArray = new Term[capacity];
    }
    ~Polynomial() { delete[] termArray; }
    Polynomial Add(const Polynomial& b) const;
    Polynomial Mult(const Polynomial& b) const;
    float Eval(float x) const;
    void newTerm(const float newcoef, const int newexp);
    friend istream& operator>>(istream& input, Polynomial& Poly);
    friend ostream& operator<<(ostream& output, const Polynomial& Poly);
};

istream& operator>>(istream& is, Polynomial& poly) {
    float coef;
    int exp, n;
    is >> n;
    while (n--) {
        is >> coef >> exp;
        poly.newTerm(coef, exp);
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; ++i) {
        if (i > 0 && poly.termArray[i].coef > 0) os << "+";
        os << poly.termArray[i].coef;
        if (poly.termArray[i].exp > 0) {
            os << "X";
            if (poly.termArray[i].exp > 1) os << "^" << poly.termArray[i].exp;
        }
    }
    return os;
}

void Polynomial::newTerm(const float theCoef, const int theExp) {
    if (theCoef == 0) return;
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    for (int i = 0; i < terms; i++) {
        if (termArray[i].exp == theExp) {
            termArray[i].coef += theCoef;
            return;
        }
    }
    termArray[terms].coef = theCoef;
    termArray[terms].exp = theExp;
    terms++;
}

Polynomial Polynomial::Add(const Polynomial& b) const {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while (aPos < terms && bPos < b.terms) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) c.newTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if (termArray[aPos].exp > b.termArray[bPos].exp) {
            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
        else {
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
    }
    for (; aPos < terms; aPos++)
        c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    return c;
}

Polynomial Polynomial::Mult(const Polynomial& b) const {
    Polynomial c;
    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < b.terms; j++) {
            float newCoef = termArray[i].coef * b.termArray[j].coef;
            int newExp = termArray[i].exp + b.termArray[j].exp;
            c.newTerm(newCoef, newExp);
        }
    }
    return c;
}

float Polynomial::Eval(float x) const {
    float sum = 0;
    for (int i = 0; i < terms; i++) {
        float termValue = termArray[i].coef;
        for (int j = 0; j < termArray[i].exp; j++)
            termValue *= x;
        sum += termValue;
    }
    return sum;
}

int main() {
    Polynomial A, B;
    cin >> A;
    cin >> B;
    Polynomial C = A.Add(B);
    Polynomial D = A.Mult(B);
    float x;
    cin >> x;
    cout << C << endl;
    cout << D << endl;
    cout << A.Eval(x) << endl;
    cout << B.Eval(x) << endl;
    return 0;
}
