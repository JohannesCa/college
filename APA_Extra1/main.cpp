/*
 * main.cpp
 *
 *  Created on: 29 de set de 2016
 *      Author: johannes
 */

#include <iostream>
#include "BinomialCoeficient.hpp"

using namespace std;

int main(void)
{
    int n = 5, p = 2;
    cout << "O valor do coeficiente binomial C(" << n << ", " << p << ")= " << BinomialCoeficient(n, p, true) << endl << endl;

    n = 4;
    p = 2;
    cout << "O valor do coeficiente binomial C(" << n << ", " << p << ")= " << BinomialCoeficient(n, p, true) << endl << endl;

    n = 0;
    p = 0;
    cout << "O valor do coeficiente binomial C(" << n << ", " << p << ")= " << BinomialCoeficient(n, p, true) << endl << endl;

    n = 5;
    p = 0;
    cout << "O valor do coeficiente binomial C(" << n << ", " << p << ")= " << BinomialCoeficient(n, p, true) << endl << endl;

    n = 0;
    p = 9;
    cout << "O valor do coeficiente binomial C(" << n << ", " << p << ")= " << BinomialCoeficient(n, p) << endl << endl;

    n = 7;
    p = 5;
    cout << "O valor do coeficiente binomial C(" << n << ", " << p << ")= " << BinomialCoeficient(n, p) << endl << endl;

    n = 6;
    p = 3;
    cout << "O valor do coeficiente binomial C(" << n << ", " << p << ")= " << BinomialCoeficient(n, p) << endl << endl;

    n = 11;
    p = 3;
    cout << "O valor do coeficiente binomial C(" << n << ", " << p << ")= " << BinomialCoeficient(n, p) << endl << endl;

    n = 5;
    p = 13;
    cout << "O valor do coeficiente binomial C(" << n << ", " << p << ")= " << BinomialCoeficient(n, p) << endl << endl;

    n = 16;
    p = 10;
    cout << "O valor do coeficiente binomial C(" << n << ", " << p << ")= " << BinomialCoeficient(n, p) << endl << endl;

    return 0;
}
