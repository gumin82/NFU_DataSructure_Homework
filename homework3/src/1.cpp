#include <iostream>
#include <cmath>
using namespace std;

template <class T> class Chain;
template <class T> class ChainIterator;
template <class T> class AvailableList;

template <class T>
class ChainNode {
    friend class Chain<T>;
    friend class ChainIterator<T>;
    friend class AvailableList<T>;
private:
    T element;
    ChainNode<T>* next;
public:
    ChainNode() : next(nullptr) {}
    ChainNode(const T& e) : element(e), next(nullptr) {}
    ChainNode(const T& e, ChainNode<T>* n) : element(e), next(n) {}
};

template <class T>
class ChainIterator {
private:
    ChainNode<T>* current;
public:
    ChainIterator(ChainNode<T>* p = nullptr) : current(p) {}
    T& operator*() const { return current->element; }
    T* operator->() const { return &current->element; }
    ChainIterator& operator++() {
        current = current->next;
        return *this;
    }
    bool operator!=(const ChainIterator& rhs) const {
        return current != rhs.current;
    }
};

template <class T>
class Chain {
    friend class AvailableList<T>;
private:
    ChainNode<T>* head;
public:
    Chain() : head(nullptr) {}
    ~Chain() {
        while (head) {
            ChainNode<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    ChainIterator<T> begin() const { return ChainIterator<T>(head); }
    ChainIterator<T> end() const { return ChainIterator<T>(nullptr); }

    void insertFront(const T& e) {
        head = new ChainNode<T>(e, head);
    }

    ChainNode<T>* release() {
        ChainNode<T>* tmp = head;
        head = nullptr;
        return tmp;
    }
};

template <class T>
class AvailableList {
private:
    static ChainNode<T>* available;
public:
    static ChainNode<T>* getNode() {
        if (!available) return nullptr;
        ChainNode<T>* node = available;
        available = available->next;
        node->next = nullptr;
        return node;
    }

    static void getBack(ChainNode<T>* first) {
        if (!first) return;
        ChainNode<T>* p = first;
        while (p->next) p = p->next;
        p->next = available;
        available = first;
    }
};

template <class T>
ChainNode<T>* AvailableList<T>::available = nullptr;

struct Term {
    double coef;
    int exp;
    Term(double c = 0, int e = 0) : coef(c), exp(e) {}
};

class Polynomial {
    friend istream& operator>>(istream&, Polynomial&);
    friend ostream& operator<<(ostream&, const Polynomial&);
private:
    Chain<Term> terms;
public:
    void newTerm(double c, int e) {
        if (c == 0) return;

        for (auto it = terms.begin(); it != terms.end(); ++it) {
            if (it->exp == e) {
                it->coef += c;
                return;
            }
        }
        terms.insertFront(Term(c, e));
    }

    double Evaluate(double x) const {
        double sum = 0;
        for (auto it = terms.begin(); it != terms.end(); ++it)
            sum += it->coef * pow(x, it->exp);
        return sum;
    }

    Polynomial operator+(const Polynomial& b) const {
        Polynomial r;
        for (auto it = terms.begin(); it != terms.end(); ++it)
            r.newTerm(it->coef, it->exp);
        for (auto it = b.terms.begin(); it != b.terms.end(); ++it)
            r.newTerm(it->coef, it->exp);
        return r;
    }

    Polynomial operator-(const Polynomial& b) const {
        Polynomial r;
        for (auto it = terms.begin(); it != terms.end(); ++it)
            r.newTerm(it->coef, it->exp);
        for (auto it = b.terms.begin(); it != b.terms.end(); ++it)
            r.newTerm(-it->coef, it->exp);
        return r;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial r;
        for (auto it1 = terms.begin(); it1 != terms.end(); ++it1)
            for (auto it2 = b.terms.begin(); it2 != b.terms.end(); ++it2)
                r.newTerm(it1->coef * it2->coef,
                    it1->exp + it2->exp);
        return r;
    }
};

istream& operator>>(istream& is, Polynomial& p) {
    int n;
    is >> n;
    for (int i = 0; i < n; i++) {
        double c;
        int e;
        is >> c >> e;
        p.newTerm(c, e);
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& p) {
    bool first = true;
    for (auto it = p.terms.begin(); it != p.terms.end(); ++it) {
        if (!first && it->coef > 0) os << "+";
        os << it->coef << "x^" << it->exp;
        first = false;
    }
    return os;
}

int main() {
    Polynomial A, B;
    cout << "A:";
    cin >> A;
    cout << "B:";
    cin >> B;
    //cout << "A=" << A << endl;
    //cout << "B=" << B << endl;
    cout << "A+B=" << A + B << endl;
    cout << "A-B=" << A - B << endl;
    cout << "A*B=" << A * B << endl;
    cout << "A(2)=" << A.Evaluate(2) << endl;
    return 0;
}
