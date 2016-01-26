#include <stdio.h>
#include <stdlib.h>

#include "polynomial.h"

int main(int argc, char const* argv[])
{
    int deg1, deg2;
    Polynomial *poly1, *poly2, **qr; // qr - quotient and remainder array

    printf("Give me the degrees of your polynomials (separate with space): ");
    scanf("%d %d", &deg1, &deg2);

    // Prepare the structures
    poly1 = mk_poly(deg1);
    poly2 = mk_poly(deg2);

    // Fill the first polynomial
    puts("Define the first polynomial:");
    scan_poly(poly1);

    // ...and show it to the user
    puts("The first polynomial: ");
    print_poly(poly1);

    puts("\n");

    // Fill the second polynomial
    puts("Define the second polynomial:");
    scan_poly(poly2);

    // ...and spit it out, too.
    puts("The second polynomial: ");
    print_poly(poly2);

    qr = div_poly(poly1, poly2); // Do the math

    puts("\n");

    puts("Quotient:");
    print_poly(qr[0]);

    putchar('\n');

    puts("Remainder:");
    print_poly(qr[1]);

    del_poly(poly1);
    del_poly(poly2);
    del_poly(qr[0]);
    del_poly(qr[1]);
    free(qr);

    return 0;
}
