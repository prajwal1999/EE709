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

    // Compute f = (x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8)
    bdd f_1 = bdd_or(bddm, x1, x2);
    bdd f_2 = bdd_or(bddm, f_1, x3);
    bdd f_3 = bdd_or(bddm, f_2, x4);
    bdd f_4 = bdd_or(bddm, f_3, x5);
    bdd f_5 = bdd_or(bddm, f_4, x6);
    bdd f_6 = bdd_or(bddm, f_5, x7);
    bdd f = bdd_or(bddm, f_6, x8);


    // Compute g = (x1 ^ x2 ^ x3 ^ x4 ^ x5 ^ x6 ^ x7 ^ x8)
    bdd g_1 = bdd_xor(bddm, x1, x2);
    bdd g_2 = bdd_xor(bddm, g_1, x3);
    bdd g_3 = bdd_xor(bddm, g_2, x4);
    bdd g_4 = bdd_xor(bddm, g_3, x5);
    bdd g_5 = bdd_xor(bddm, g_4, x6);
    bdd g_6 = bdd_xor(bddm, g_5, x7);
    bdd g = bdd_xor(bddm, g_6, x8);

    // check if f_xnor_g = (f=g)
    bdd f_xnor_g = bdd_xnor(bddm, f, g);
  
    // check if f_xor_g = (f!=g)
    bdd f_xor_g = bdd_xor(bddm, f, g);

    // check if f==g
    if(f == g) {
        printf("Success! Two expressions are equal\n");
    } else {
        printf("Failure! Two expressions are not equal\n");
    }

    // Find Xi's for which f=g
    printf("Variable assignment for which the two functions evaluate to the same value.");
    bdd_print_bdd(bddm, bdd_satisfy(bddm, f_xnor_g), NULL, NULL, NULL, stdout);

    // Find Xi's for which f!=g
    printf("Variable assignment for which the two functions evaluate to different value.");
    bdd_print_bdd(bddm, bdd_satisfy(bddm, f_xor_g), NULL, NULL, NULL, stdout);

    return 0;

}
