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

    tmp = p1;
    while (tmp) {
        free(tmp);
        tmp = p1->next;
    }
}



// This function adds two polynomials p1 and p2 to form a new polynomial and return the new polynomial
POLY *add(POLY *p1, POLY *p2)
{
    POLY *new_head, *tmp;

    if (!p1) {
        dbg_print(p2, __LINE__);
        return p2;
    }
    else if (!p2) {
        dbg_print(p1, __LINE__);
        return p1;
    }


    if (p1->degree > p2->degree) {
        dbg_print(p1, __LINE__);
        dbg_print(p2, __LINE__);
        new_head = p1;
        new_head->next = add(p1->next, p2);

        print(new_head);
    } else if (p1->degree < p2->degree) {
        dbg_print(p1, __LINE__);
        dbg_print(p2, __LINE__);
        new_head = p2;
        new_head->next = add(p1, p2->next);

        print(new_head);
    } else {
#if 1
        dbg_print(p1, __LINE__);
        dbg_print(p2, __LINE__);
        new_head = p1;
        new_head->coef += p2->coef;
        tmp = p2->next;
        if (p1 != p2)
            free(p2);
        new_head->next = add(new_head->next, tmp);
#else
        dbg_print(p1, __LINE__);
        dbg_print(p2, __LINE__);
        new_head = oneTerm(p1->degree, p1->coef + p2->coef);
        new_head->next = add(p1->next, p2->next);
        free(p1);
        free(p2);
#endif
        print(new_head);
    }
    return new_head;
}



void dbg_print(POLY *p1, int line)
{
    if (p1)
        printf("%d:  %f x^%d\n", line, p1->coef, p1->degree);
}


// This function subtract polynomial p2 from p1 to form a new polynomial and return the new polynomial.
POLY *sub(POLY *p1, POLY *p2)
{


}


// This function multiplies two polynomials p1 and p2 to form a new polynomial and return the new polynomial.
POLY *mply(POLY *p1, POLY *p2)
{
    POLY *new_head;

    new_head = p1;

    while (p1) {
        new_head->next;
    }

}

// This function prints out the polynomial p1 in human readable form. See the example output given below for more details.
void print(POLY *p1)
{

    while (p1) {
         //printf("enter..\n");
        if (p1->coef > 0) {
            printf("+%f", p1->coef);
        } else if (p1->coef < 0) {
            printf("%f", p1->coef);
        }

        if (p1->degree) {
            printf("x");
            if (p1->degree > 1)
                printf("^%d",p1->degree );
        }

        p1 = p1->next;

    }
    printf("\n\n");

}




int main()
{
    POLY *A, *B, *C, *A2;

    printf("Hello World\n");

    A = add(oneTerm(1, 1), oneTerm(0, 1));
    //printf("%p\n", A);
    if (A) {
        printf("A=");
        print(A);
        printf("\n\n");
      //  release(A);
    }

#if 0
    B = add(oneTerm(1, 1), oneTerm(0, -1));
    if (B) {
        printf("B=");
        print(B);
        printf("\n\n");
      //  release(B);
    }

    C = add(A, B);
    printf("C=");
    print(C);
    printf("\n\n");
#endif

    A2 = add(A, A);
    printf("A2=");
    print(A2);
    printf("\n\n");


    return 0;
}

