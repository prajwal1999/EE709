#include <stdlib.h>
#include <stdio.h>
#include <bdduser.h>

int main (int argc, char* argv[])
{
	bdd_manager bddm = bdd_init();	

    // 8 variables Xi's
    bdd x1 = bdd_new_var_last(bddm);
    bdd x2 = bdd_new_var_last(bddm);
    bdd x3 = bdd_new_var_last(bddm);
    bdd x4 = bdd_new_var_last(bddm);
    bdd x5 = bdd_new_var_last(bddm);
    bdd x6 = bdd_new_var_last(bddm);
    bdd x7 = bdd_new_var_last(bddm);
    bdd x8 = bdd_new_var_last(bddm);

    // complement of Xi's
    bdd x1_bar = bdd_not(bddm, x1);
    bdd x2_bar = bdd_not(bddm, x2);
    bdd x3_bar = bdd_not(bddm, x3);
    bdd x4_bar = bdd_not(bddm, x4);
    bdd x5_bar = bdd_not(bddm, x5);
    bdd x6_bar = bdd_not(bddm, x6);
    bdd x7_bar = bdd_not(bddm, x7);
    bdd x8_bar = bdd_not(bddm, x8);

    // Compute f = (x1.x2.(~x3) + x4.x5 + (~x6).x7 + x8)
    bdd f_1 = bdd_and(bddm, x1, x2);
    bdd f_2 = bdd_and(bddm, f_1, x3_bar);

    bdd f_3 = bdd_and(bddm, x4, x5);

    bdd f_4 = bdd_and(bddm, x6_bar, x7);

    bdd f_5 = bdd_or(bddm, f_2, f_3);
    bdd f_6 = bdd_or(bddm, f_5, f_4);

    bdd f = bdd_or(bddm, f_6, x8);


    // Compute g = x1.x5  + x2.x6 + x3.x7 + x4.x8
    bdd g_1 = bdd_and(bddm, x1, x5);
    bdd g_2 = bdd_and(bddm, x2, x6);
    bdd g_3 = bdd_and(bddm, x3, x7);
    bdd g_4 = bdd_and(bddm, x4, x8);

    bdd g_5 = bdd_or(bddm, g_1, g_2);
    bdd g_6 = bdd_or(bddm, g_3, g_4);

    bdd g = bdd_or(bddm, g_5, g_6);


    // Find size of f
    printf("BDD of f is of size = %ld\n", bdd_size(bddm, f, 0));

    // Find size of g
    printf("BDD of f is of size = %ld\n", bdd_size(bddm, g, 0));

    return 0;

}
