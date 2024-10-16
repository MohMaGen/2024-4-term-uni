#include <stdio.h>
#define  IML_CALC
#include "./calc.h"

int main() {
    double R_15 = 14, R_2 = 6, R_34 = 16;
    double E_2 = 23.0, E_3 = 43.0;



    double data[] = {
        1.0,   1.0, 1.0,  0.0,
        R_15, -R_2, 0.0,  0.0,
        0,    -R_2, R_34, E_2 - E_3,
    };
    Matrix sle = mk_matrix(4, 3, data);
    display_matrix(sle); 
    Matrix Is = solve_sle(sle); 
    display_matrix(sle); 
    M_FOREACH(Is, curr, { printf("I_%ld = %lf\n", y, *curr); }) 

    double I_1 = Is.data[0], I_2 = Is.data[1], I_3 = Is.data[2];
    double l = I_3 * (E_2 - E_3);
    double r = I_1*I_1*R_15 + I_2*I_2*R_2 + I_3*I_3*R_34;
    printf("%lf == %lf\n", l, r);

    double phi_0 = 0;
    double phi_1 = phi_0 - I_1 * R_15;
    double phi_2 = phi_1 - E_2;
    double phi_3 = phi_2 + I_3 * R_34;
    double phi_4 = phi_3 + E_3;
    printf("phi_1, phi_2, phi_3, phi_4 = %lf, %lf, %lf, %lf\n", phi_1, phi_2, phi_3, phi_4);

    return 0;
}
