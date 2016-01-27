#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

typedef struct POLYNOMIAL {
    int deg;
    double* coeffs;
} Polynomial;

Polynomial* mk_poly(int deg);        // Create a polynomial of deg degree
void del_poly(Polynomial* poly_ptr); // Free a polynomial's heap memory

Polynomial* cpy_poly(Polynomial* source); // Clone a polynomial, return the clone's pointer

void scan_poly(Polynomial* poly_ptr);  // Fill a polynomial with coefficients
void print_poly(Polynomial* poly_ptr); // Spit out a polynomial's equation

/* NOTE: The division function returns a two-element 
 * array that needs to be freed after use.
 *
 * First element - the quotient
 * Second element - the remainder
 */
Polynomial** div_poly(Polynomial* poly1, Polynomial* poly2);
Polynomial* multiply_poly(Polynomial* poly1, Polynomial* poly2); // Multiply two polynomials

Polynomial* add_poly(Polynomial* poly1, Polynomial* poly2);
Polynomial* subtract_poly(Polynomial* poly1, Polynomial* poly2);

#endif
