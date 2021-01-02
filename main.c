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

POLY *oneTerm(int degree, double coef);
void release(POLY *p1);
POLY *add(POLY *p1, POLY *p2);
POLY *sub(POLY *p1, POLY *p2);
POLY *mply(POLY *p1, POLY *p2);
void print(POLY *p1);


int main()
{
    POLY *A, *A2, *A3, *A4, *A5;
    POLY *B, *B2, *B3, *B4, *B5;
    POLY *C, *C2, *C3, *C4, *C5;

    A = add(oneTerm(1, 1), oneTerm(0, 1));
    A2 = mply(A, A);
    A3 = mply(A2, A);
    A4 = mply(A3, A);
    A5 = mply(A4, A);

    printf("A = ");
    print(A);
    printf("A2 = ");
    print(A2);

    /*B = add(oneTerm(1, 1), oneTerm(0, -1));*/
    B = sub(oneTerm(1, 1), oneTerm(0, 1));
    B2 = mply(B, B);
    B3 = mply(B2, B);
    B4 = mply(B3, B);
    B5 = mply(B4, B);

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

    return 0;
}



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


/*
 * This function releases all nodes of the polynomial p1
 * and returns them to the heap space.
 */
void release(POLY *p1)
{
    POLY *tmp;
    while (p1) {
        tmp = p1;
        p1 = p1->next;
        free(tmp);
    }
}



/*
 * This function adds two polynomials p1 and p2
 * to form a new polynomial and return the new polynomial
 */
POLY *add(POLY *p1, POLY *p2)
{
    POLY np;
    POLY *np_head = &np;

    while (p1 && p2) {
        if (p1->degree > p2->degree) {  // if degrees are not equal, use the bigger one.
            np_head->next = oneTerm(p1->degree, p1->coef);
            p1 = p1->next;
        } else if (p1->degree < p2->degree) {   // if degrees are not equal, use the bigger one.
            np_head->next = oneTerm(p2->degree, p2->coef);
            p2 = p2->next;
        } else {  // degrees are same, creat term with new coef.
            np_head->next = oneTerm(p1->degree,  p1->coef + p2->coef);
            p1 = p1->next;
            p2 = p2->next;
        }
        np_head = np_head->next;
    }

    /* no more term in p2 list, so just create terms with the value of term of p1 */
    while (p1) {
        np_head->next = oneTerm(p1->degree, p1->coef);
        p1 = p1->next;
        np_head = np_head->next;
    }

    /* no more term in p1 list, so just create terms with the value of term of p2 */
    while (p2) {
        np_head->next = oneTerm(p2->degree, p2->coef);
        p2 = p2->next;
        np_head = np_head->next;
    }

    return np.next;
}



/*
 * This function subtract polynomial p2 from p1
 * to form a new polynomial and return the new polynomial.
 */
// the flow of "sub" is almost as same as "add"
POLY *sub(POLY *p1, POLY *p2)
{
    POLY np;
    POLY *np_head = &np;

    while (p1 && p2) {
        if (p1->degree > p2->degree) {
            np_head->next = oneTerm(p1->degree, p1->coef);
            p1 = p1->next;
        } else if (p1->degree < p2->degree) {
            np_head->next = oneTerm(p2->degree, -p2->coef); // this is "sub" case, so inverse the coef.
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
        np_head->next = oneTerm(p2->degree, -p2->coef);  // this is "sub" case, so inverse the coef.
        p2 = p2->next;
        np_head = np_head->next;
    }

    return np.next;
}


/*
 * This function multiplies two polynomials p1 and p2
 * to form a new polynomial and return the new polynomial.
 */
POLY *mply(POLY *p1, POLY *p2)
{
    POLY *np_head, *term;
    POLY np; // this is just as "HEAD" of new polynomial

    np.coef = 0;
    np.degree = 0;
    np.next = NULL;
    np_head = &np;

    // create Term for each (a x b)
    for (; p1; p1 = p1->next) {
        for (term = p2; term; term = term->next) {
            np_head->next = oneTerm(p1->degree + term->degree, p1->coef * term->coef);
            np_head = np_head->next;
        }
    }

    // merge term with same degree, and mark being merged term with coef "zero" which will be removed later.
    for (np_head = np.next; np_head; np_head = np_head->next) {
        for (term = np_head->next; term; term = term->next) {
            if (np_head->degree == term->degree) {
                np_head->coef += term->coef;
                term->coef = 0;
            }
        }
    }

    // remove term with coef "zero" in the list that will be returned finally.
    np_head = np.next;
    while (np_head) {
        POLY *to_remove;

        if (np_head->next && np_head->next->coef == 0) {
            if (np_head->next->next) {
                to_remove = np_head->next;
                np_head->next = np_head->next->next;
                to_remove->next = NULL;  // prevent from releasing more terms.
                release(to_remove);      // we don't need this term anymore, reclaim memory to heap.
                continue;  // do not move to next here, becuase we need to check the coef of current "next" is zero or not.
            } else {
                release(np_head->next);  // this term is the last one in the this, so just release it.
                np_head->next = NULL;
            }
        }
        np_head = np_head->next;
    }

    return np.next;
}


/*
 * This function prints out the polynomial p1 in human readable form.
 * See the example output given below for more details.
 */
void print(POLY *p1)
{
    int first = 1;

    for (; p1; p1 = p1->next) {
        if (first && p1->coef == 1) {  // first term and coef == 1, we should ignroe printing the coef.
            // nothing;
        } else if (p1->coef > 0 && !first) {
            printf("+%g", p1->coef);  // print "+" only if it is not first term.
        } else {
            printf("%g", p1->coef);
        }

        if (p1->degree) {
            printf("x");
            if (p1->degree > 1)
                printf("^%d", p1->degree);
        }

        first = 0;
    }
    printf("\n\n");
}
