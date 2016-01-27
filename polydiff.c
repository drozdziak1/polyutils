#include <stdio.h>

#include "polynomial.h"

int main(void)
{
    int deg1, deg2;
    Polynomial *poly1, *poly2, *diff;

    printf("Give me the degrees of your polynomials (separate with space): ");
    scanf("%d %d", &deg1, &deg2);

    // Prepare the structures
    poly1 = mk_poly(deg1);
    poly2 = mk_poly(deg2);

    // Fill the first polynomial
    puts("Define the first polynomial:");
    scan_poly(poly1);

    // ...and present it to the user
    puts("The first polynomial: ");
    print_poly(poly1);

    puts("\n");

    // Fill the second polynomial
    puts("Define the second polynomial:");
    scan_poly(poly2);

    // ...and spit it out, too.
    puts("The second polynomial: ");
    print_poly(poly2);

    puts("\n");

    diff = subtract_poly(poly1, poly2);

    puts("Difference:");
    print_poly(diff);

    del_poly(poly1);
    del_poly(poly2);
    del_poly(diff);

    return 0;
}
