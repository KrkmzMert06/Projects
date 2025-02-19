#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Polynomial {
private:
    vector<int> coefficients;
    int degree;

public:
    Polynomial() : degree(0) {
        coefficients.push_back(0);
    }

    Polynomial(vector<int> coeffs) {
        coefficients = coeffs;
        degree = coeffs.size() - 1;
    }

    int getDegree() const {
        return degree;
    }

    void setDegree(int a) {
        degree = a;
    }

    int getVector(int index) const {
        if (index < coefficients.size()) {
            return coefficients[index];
        }
        return 0;
    }

    void setVector(int index, int a) {
        if (index >= coefficients.size()) {
            coefficients.resize(index + 1, 0);
        }
        coefficients[index] = a;
    }

    vector<int>& getCoefficients() {
        return coefficients;
    }

    Polynomial operator+(const Polynomial& x) const {
        Polynomial sum;
        makeEqual(x, sum);
        sum.setDegree(max(degree, x.getDegree()));
        for (int i = 0; i <= sum.getDegree(); i++) {
            sum.setVector(i, getVector(i) + x.getVector(i));
        }
        return sum;
    }

    Polynomial operator-(const Polynomial& x) const {
        Polynomial subs;
        makeEqual(x, subs);
        subs.setDegree(max(degree, x.getDegree()));
        for (int i = 0; i <= subs.getDegree(); i++) {
            subs.setVector(i, getVector(i) - x.getVector(i));
        }
        return subs;
    }

    Polynomial operator*(const Polynomial& x) const {
        Polynomial multiply;
        int newDegree = degree + x.getDegree();
        multiply.setDegree(newDegree);
        multiply.getCoefficients().resize(newDegree + 1, 0);

        for (int i = 0; i <= degree; i++) {
            for (int j = 0; j <= x.getDegree(); j++) {
                multiply.setVector(i + j, multiply.getVector(i + j) + getVector(i) * x.getVector(j));
            }
        }
        return multiply;
    }

    double operator()(double x) const {
        double sum = 0;
        for (int i = 0; i <= degree; i++) {
            sum += getVector(i) * pow(x, i);
        }
        return sum;
    }

    void displayPolynomial() const {
        for (int i = degree; i >= 0; i--) {
            if (i != degree && coefficients[i] >= 0) cout << "+";
            cout << coefficients[i] << "x^" << i << " ";
        }
        cout << endl;
    }

    void makeEqual(const Polynomial& a, Polynomial& b) const {
        if (a.getDegree() > b.getDegree()) {
            b.getCoefficients().resize(a.getDegree() + 1, 0);
        }
        else {
            a.getCoefficients().resize(b.getDegree() + 1, 0);
        }
    }
};

Polynomial add(Polynomial& a, Polynomial& b) {
    return a + b;
}

Polynomial subtract(Polynomial& a, Polynomial& b) {
    return a - b;
}

Polynomial multiply(Polynomial& a, Polynomial& b) {
    return a * b;
}

int main() {
    Polynomial p1({ 7, -2, 5, 3 });
    Polynomial p2({ 4, 0, 1 });

    cout << "P1: ";
    p1.displayPolynomial();
    cout << "P2: ";
    p2.displayPolynomial();

    Polynomial sum = add(p1, p2);
    cout << "Sum: ";
    sum.displayPolynomial();

    Polynomial diff = subtract(p1, p2);
    cout << "Difference: ";
    diff.displayPolynomial();

    Polynomial product = multiply(p1, p2);
    cout << "Product: ";
    product.displayPolynomial();

    double value = p1(2);
    cout << "P1(2): " << value << endl;

    return 0;
}
