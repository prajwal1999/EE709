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

    // Compute f = (x1.x4 + (~x1).x2.x5 + (~x1).(~x2).x3.x6 + (~x1).(~x2).(~x3).x4.x8)
    bdd f_1 = bdd_and(bddm, x1, x4);

    bdd f_2 = bdd_and(bddm, x1_bar, x2);
    bdd f_3 = bdd_and(bddm, f_2, x5);

    bdd f_4 = bdd_and(bddm, x1_bar, x2_bar);
    bdd f_5 = bdd_and(bddm, f_4, x3);
    bdd f_6 = bdd_and(bddm, f_5, x6);

    bdd f_7 = bdd_and(bddm, x1_bar, x2_bar);
    bdd f_8 = bdd_and(bddm, f_7, x3_bar);
    bdd f_9 = bdd_and(bddm, f_8, x4);
    bdd f_10 = bdd_and(bddm, f_9, x8);

    bdd f_11 = bdd_or(bddm, f_1, f_3);
    bdd f_12 = bdd_or(bddm, f_11, f_6);
    bdd f = bdd_or(bddm, f_12, f_10);

    // Compute h = (x1.(~x3) + (~x1).x3)
    bdd h_1 = bdd_and(bddm, x1, x3_bar);
    bdd h_2 = bdd_and(bddm, x1_bar, x3);
    bdd h = bdd_or(bddm, h_1, h_2);

    // Compute g = (x1.x4 + (~x1).((~x2).x6 + x2.x5))
    bdd g_1 = bdd_and(bddm, x1, x4);
    bdd g_2 = bdd_and(bddm, x2_bar, x6);
    bdd g_3 = bdd_and(bddm, x2, x5);
    bdd g_4 = bdd_or(bddm, g_2, g_3);
    bdd g_5 = bdd_and(bddm, g_4, x1_bar);
    bdd g = bdd_or(bddm, g_5, g_1);

    //  Define W = h => (f = g)
    // W = (~h) + (f xnor g)
    bdd W_1 = bdd_xnor(bddm, f, g);
    bdd h_bar = bdd_not(bddm, h);
    bdd W = bdd_or(bddm, h_bar, W_1);

    if(W == bdd_one(bddm)) {
        printf("Success! f=g on h=1\n");
    } else {
        printf("Failure! f=g on h=1\n");
    }

    return 0;

}

