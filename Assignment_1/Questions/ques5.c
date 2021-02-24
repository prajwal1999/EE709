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


    //Existentially quantifying out h(x5, x6, x7,x8)
	bdd Q[5];
	Q[0] = x1; Q[1] = x2; Q[2] = x3; Q[3] = x4; Q[4] = NULL; 
	int assoc = bdd_new_assoc(bddm,Q,0);
	bdd_assoc(bddm,assoc);
	bdd r0 = bdd_exists(bddm, f);
	
	printf("BDD of f after existentially quantifying out h(x5, x6, x7,x8) is:\n-----------------------------------------\n" );
	bdd_print_bdd(bddm, r0, NULL, NULL,NULL, stdout);

    //Existentially quantifying out h(x5, x6, x7,x8)
	bdd r1 = bdd_forall(bddm, f);	

	printf("-----------------------------------------\nBDD of f after universally quantifying out h(x5, x6, x7,x8) is: \n-----------------------------------------\n" );
	bdd_print_bdd(bddm, r1, NULL, NULL,NULL, stdout);
	printf("-----------------------------------------\n");

    return 0;

}
