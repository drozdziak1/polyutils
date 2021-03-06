#include <stdio.h>  // printf()
#include <stdlib.h> // malloc(), calloc(), free()
#include <assert.h> // assert()

#include "polynomial.h"

Polynomial* mk_poly(int deg)
{
    Polynomial* ret_poly = calloc(1, sizeof(Polynomial));

    ret_poly->deg = deg;
    ret_poly->coeffs = calloc(++deg, sizeof(double));

    return ret_poly;
}

void del_poly(Polynomial* poly_ptr)
{
    free(poly_ptr->coeffs);
    free(poly_ptr);
}

Polynomial* cpy_poly(Polynomial* source)
{
    Polynomial* target = mk_poly(source->deg);

    for (int i = 0; i <= source->deg; i++)
        target->coeffs[i] = source->coeffs[i];

    return target;
}

void scan_poly(Polynomial* poly_ptr)
{
    /*Don't let the user define a faulty coefficient*/
    while (
        !poly_ptr->coeffs[poly_ptr->deg]
        && poly_ptr->deg > 1) {

        printf("x^%d: ", poly_ptr->deg);
        scanf("%lf", poly_ptr->coeffs + poly_ptr->deg);
    }

    for (int i = poly_ptr->deg - 1; i > 1; i--) {

        printf("x^%d: ", i);
        scanf("%lf", poly_ptr->coeffs + i);
    }

    if (poly_ptr->deg) {
        printf("x: ");
        scanf("%lf", poly_ptr->coeffs + 1);
    }

    printf("Intercept: ");
    scanf("%lf", poly_ptr->coeffs);
}

void print_poly(Polynomial* poly_ptr)
{
    for (int i = poly_ptr->deg; i > 1; i--) {

        printf("(%.2lf*x^%d)", poly_ptr->coeffs[i], i);
        printf(" + ");
    }

    if (poly_ptr->deg)
        printf("(%.2lf*x) + ", poly_ptr->coeffs[1]);

    printf("(%.2lf)", poly_ptr->coeffs[0]);
}

Polynomial** div_poly(Polynomial* poly1, Polynomial* poly2)
{
    /* NOTE:
     * The remainder is used temporarily for handling the intermediate
     * polynomials and becomes the actual thing only when the
     * quotient is resolved. Then, it requires
     * truncation of its intercept.
     */
    Polynomial *q, *r, *r_trunc; // q - quotient, r - remainder, r_trunc - to help truncate r's intercept

    Polynomial** ret = malloc(2 * sizeof(Polynomial*)); // The array to be returned

    int deg1 = poly1->deg, deg2 = poly2->deg; // For decluttering the statements below
    int qdeg;                                 // qdeg - quotient's degree

    assert(poly1->coeffs[deg1] != 0); // Make sure we're not dividing by 0

    if (deg1 >= deg2) {

        qdeg = deg1 - deg2;

        q = mk_poly(qdeg);
        r = mk_poly(deg2);

        // First coefficient
        q->coeffs[qdeg] = poly1->coeffs[deg1] / poly2->coeffs[deg2];

        // Prepare the first intermediate polynomial
        for (int i = 0; i < deg2; i++) {

            r->coeffs[deg2 - i] = poly1->coeffs[deg1 - i - 1];
            r->coeffs[deg2 - i] -= q->coeffs[qdeg] * poly2->coeffs[deg2 - i - 1];
        }

        for (int i = qdeg - 1; i >= 0; i--) {

            r->coeffs[0] = poly1->coeffs[i];

            // Calculate another coefficient for the quotient
            q->coeffs[i] = r->coeffs[deg2] / poly2->coeffs[deg2];

            // Calculate next temporary polynomial
            for (int j = deg2; j > 0; j--) {

                r->coeffs[j] = r->coeffs[j - 1];
                r->coeffs[j] -= (q->coeffs[i] * poly2->coeffs[j - 1]);
            }
        }

        // Truncate r's redundant intercept
        r_trunc = mk_poly(deg2 - 1);

        for (int i = 0; i < deg2; i++)
            r_trunc->coeffs[i] = r->coeffs[i + 1];

        del_poly(r);
        r = r_trunc;
    }
    else {
        q = mk_poly(0); // (0.00)
        r = cpy_poly(poly1);
    }

    ret[0] = q;
    ret[1] = r;
    return ret;
}

Polynomial* multiply_poly(Polynomial* poly1, Polynomial* poly2)
{
    int deg1 = poly1->deg;
    int deg2 = poly2->deg;

    Polynomial* product = mk_poly(deg1 + deg2);

    for (int i = 0; i <= deg1; i++)
        for (int j = 0; j <= deg2; j++) {
            product->coeffs[i + j] += poly1->coeffs[i] * poly2->coeffs[j];
        }

    return product;
}

Polynomial* add_poly(Polynomial* poly1, Polynomial* poly2)
{
    Polynomial* sum;

    // Make sure the first pointer has higher degree than the second
    if (poly1->deg < poly2->deg) {

        sum = poly1;
        poly1 = poly2;
        poly2 = sum;
    }

    /* Coefficients higher than deg2 won't change anyway,
     * so it's safe to copy them from poly1 already.
     */
    sum = cpy_poly(poly1);

    for (int i = 0; i <= poly2->deg; i++)
        sum->coeffs[i] = poly1->coeffs[i] + poly2->coeffs[i];

    return sum;
}

Polynomial* subtract_poly(Polynomial* poly1, Polynomial* poly2)
{
    Polynomial* diff = cpy_poly(poly2);

    // Negate poly2's coefficients...
    for (int i = 0; i <= poly2->deg; i++)
        diff->coeffs[i] = -poly2->coeffs[i];

    // ...to reuse add_poly()
    diff = add_poly(poly1, diff);

    return diff;
}
