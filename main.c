/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>  // malloc/free


typedef struct sPoly {
    int degree; // the degree of the node
    double coef; // the coefficient of the node
    struct sPoly *next; // pointer to the next node
} POLY;


void dbg_print(POLY *p1, int line);
void print(POLY *p1);

/*
 * This function creates a 1-term polynomial of the form coef * x^degree
 * and returns the new polynomial
 */
POLY *oneTerm(int degree, double coef)
{
    POLY *new = NULL;

    if (degree == 0 && coef == 0)
        return NULL;

    new = (POLY *)malloc(sizeof(POLY));
    if (new) {
        new->degree = degree;
        new->coef = coef;
        new->next = NULL;
    }

    return new;
}


// This function releases all nodes of the polynomial p1 and returns them to the heap space.
void release(POLY *p1)
{
    POLY *tmp;
    while (p1) {
        tmp = p1;
        p1 = p1->next;
        free(tmp);
    }
}



// This function adds two polynomials p1 and p2 to form a new polynomial and return the new polynomial
POLY *add(POLY *p1, POLY *p2)
{
    POLY np;
    POLY *np_head = &np;

    while (p1 && p2) {
        if (p1->degree > p2->degree) {
            np_head->next = oneTerm(p1->degree, p1->coef);
            p1 = p1->next;
        } else if (p1->degree < p2->degree) {
            np_head->next = oneTerm(p2->degree, p2->coef);
            p2 = p2->next;
        } else {
            np_head->next = oneTerm(p1->degree,  p1->coef + p2->coef);
            p1 = p1->next;
            p2 = p2->next;
        }
        np_head = np_head->next;
    }

    while (p1) {
        np_head->next = oneTerm(p1->degree, p1->coef);
        p1 = p1->next;
        np_head = np_head->next;
    }

    while (p2) {
        np_head->next = oneTerm(p2->degree, p2->coef);
        p2 = p2->next;
        np_head = np_head->next;
    }

    return np.next;
}



void dbg_print(POLY *p1, int line)
{
    if (p1)
        printf("%d:  %f x^%d\n", line, p1->coef, p1->degree);
}


// This function subtract polynomial p2 from p1 to form a new polynomial and return the new polynomial.
POLY *sub(POLY *p1, POLY *p2)
{
    POLY np;
    POLY *np_head = &np;

    while (p1 && p2) {
        if (p1->degree > p2->degree) {
            np_head->next = oneTerm(p1->degree, p1->coef);
            p1 = p1->next;
        } else if (p1->degree < p2->degree) {
            np_head->next = oneTerm(p2->degree, -p2->coef);
            p2 = p2->next;
        } else {
            np_head->next = oneTerm(p1->degree,  p1->coef - p2->coef);
            p1 = p1->next;
            p2 = p2->next;
        }
        np_head = np_head->next;
    }

    while (p1) {
        np_head->next = oneTerm(p1->degree, p1->coef);
        p1 = p1->next;
        np_head = np_head->next;
    }

    while (p2) {
        np_head->next = oneTerm(p2->degree, -p2->coef);
        p2 = p2->next;
        np_head = np_head->next;
    }

    return np.next;
}


// This function multiplies two polynomials p1 and p2 to form a new polynomial and return the new polynomial.
POLY *mply(POLY *p1, POLY *p2)
{
    POLY *new_head, *tmp = p2, *n, *n2;
    POLY np;
    np.coef = 0;
    np.degree = 0;

    new_head = &np;

    for (; p1; p1 = p1->next) {
        for (p2 = tmp; p2; p2 = p2->next) {
            new_head->next = oneTerm(p1->degree + p2->degree, p1->coef * p2->coef);
            new_head = new_head->next;
        }
    }

    for (n = np.next; n; n = n->next) {
        for (n2 = n->next; n2; n2 = n2->next) {
            if (n->degree == n2->degree) {
                n->coef += n2->coef;
                // FIXME: should release term, not just set coef = zero;
                n2->coef = 0;
            }
        }
    }

    // remove term with coef "0"
    n = np.next;
    while (n) {
        POLY *to_remove;
        if (n->next && n->next->coef == 0) {
            if (n->next->next) {
                to_remove = n->next;
                n->next = n->next->next;
                to_remove->next = NULL;
                release(to_remove);
                continue;  // do not move to next here, becuase we need to check the coef of current "next" is zero or not.
            } else {
                release(n->next);
                n->next = NULL;
            }
        }
        n = n->next;
    }

    return np.next;
}

// This function prints out the polynomial p1 in human readable form. See the example output given below for more details.
void print(POLY *p1)
{
    int first = 1;

    for (; p1; p1 = p1->next) {
        /*if (p1->coef == 0)*/
            /*continue;*/

        if (first && p1->coef == 1) {
                // nothing;
        } else if (p1->coef > 0) {
            if (!first)
                printf("+%g", p1->coef);
            else
                printf("%g", p1->coef);
        } else if (p1->coef < 0) {
            printf("%g", p1->coef);
        } else// debug..
            printf("**%g", p1->coef);


        if (p1->degree) {
            printf("x");
            if (p1->degree > 1)
                printf("^%d",p1->degree);
        }

        first = 0;
    }
    printf("\n\n");
}


void test_case1(void)
{
    POLY *A, *B, *C, *A2;

    printf("Hello World\n");

    A = add(oneTerm(1, 1), oneTerm(0, 1));
    printf("A=");
    print(A);
    printf("\n\n");

    B = sub(oneTerm(1, 1), oneTerm(0, 1));
    printf("B=");
    print(B);
    printf("\n\n");

    C = add(A, B);
    printf("C=");
    print(C);
    printf("\n\n");

    A2 = mply(A, A);
    printf("A2=");
    print(A2);
    printf("\n\n");

    printf("A=");
    print(A);
    printf("\n\n");


    release(A);
    release(B);
    release(C);
    release(A2);
}


void test_case2(void)
{
    POLY *A, *A2, *A3, *A4, *A5;
    POLY *B, *B2, *B3, *B4, *B5;
    POLY *C, *C2, *C3, *C4, *C5;
#if 0
Polynomial A =X+One,
Polynomial A2 = A x A,
Polynomial A3 = A2 x A,
Polynomial A4 = A3 x A,
Polynomial A5 = A4 x A,
printf("A = ");
print(A),
printf("A2 = ");
print(A2),
#endif
    A = add(oneTerm(1, 1), oneTerm(0, 1));
    A2 = mply(A, A);
    A3 = mply(A2, A);
    A4 = mply(A3, A);
    A5 = mply(A4, A);

    printf("A = ");
    print(A);
    printf("A2 = ");
    print(A2);
#if 0
Polynomial B =X - One,
Polynomial B2 = B x  B,
Polynomial B3 = B2 x B,
Polynomial B4 = B3 x B,
Polynomial B5 = B4 x B,
Polynomial C = A + B,
Polynomial C2 = A2 x B2,
Polynomial C3 = A3 x B3,
Polynomial C4 = A4 x B4,
Polynomial C5 = A5 x B5,
printf("C = ");
print(C),
printf("C2 = ");
print(C2),
printf("C3 = ");
print(C3),
printf("C4 = ");
print(C4),
printf("C5 = ");
print(C5
#endif

    /*B = add(oneTerm(1, 1), oneTerm(0, -1));*/
    B = sub(oneTerm(1, 1), oneTerm(0, 1));
    B2 = mply(B, B);
    B3 = mply(B2, B);
    B4 = mply(B3, B);
    B5 = mply(B4, B);

    printf("A2 = ");
    print(A2);
    printf("B2 = ");
    print(B2);

    C = add(A, B);
    C2 = mply(A2, B2);
    C3 = mply(A3, B3);
    C4 = mply(A4, B4);
    C5 = mply(A5, B5);

    printf("C = ");
    print(C);
    printf("C2 = ");
    print(C2);
    printf("C3 = ");
    print(C3);
    printf("C4 = ");
    print(C4);

    printf("A5 = ");
    print(A5);
    printf("B5 = ");
    print(B5);

    printf("C5 = ");
    print(C5);

    release(A);
    release(A2);
    release(A3);
    release(A4);
    release(A5);
    release(B);
    release(B2);
    release(B3);
    release(B4);
    release(B5);
    release(C);
    release(C2);
    release(C3);
    release(C4);
    release(C5);

}


void test_case3(void)
{
    POLY *A, *B, *C;

    A = add(oneTerm(1, 1), oneTerm(0, 1));
    B = add(oneTerm(1, 1), oneTerm(0, -1));

    printf("A = ");
    print(A);
    printf("B = ");
    print(B);

    C = add(A, B);
    printf("C = ");
    print(C);

    printf("%d: C:(%p)\n", __LINE__, C);
}


int main()
{
    /*test_case1();*/
    test_case2();
    /*test_case3();*/

    return 0;
}
