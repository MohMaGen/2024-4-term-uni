#include <stdio.h>

int main(void)
{
    FILE *output;

    float U_AB, U_AC, U_BC,
          I_AB, I_AC, I_BC,
          I_A,  I_B,  I_C;

    float P_AB, P_AC, P_BC, P_E;
    output = fopen("result2.csv", "w");

    // first line:
    U_AB = 381.1;
    U_AC = 381.1;
    U_BC = 381.1;

    I_AB = 3.46;
    I_AC = 3.46;
    I_BC = 3.46;

    I_A  = 6.0;
    I_B  = 6.0;
    I_C  = 6.0;

    P_AB = U_AB * I_AB;
    P_AC = U_AC * I_AC;
    P_BC = U_BC * I_BC;
    P_E  = P_AB + P_AC + P_BC;

    fprintf(output, "%f, %f, %f, ",
            U_AB, U_AC, U_BC);

    fprintf(output, "%f, %f, %f, ",
            I_AB, I_AC, I_BC);

    fprintf(output, "%f, %f, %f, ",
            I_A, I_B, I_C);

    fprintf(output, "%f, %f, %f, %f\n",
            P_AB, P_AC, P_BC, P_E);

    // second line:
    U_AB = 381.1;
    U_AC = 381.1;
    U_BC = 381.1;

    I_AC = 3.46;
    I_BC = 2.54;

    I_A  = 2.54;
    I_B  = 3.46;
    I_C  = 5.22;

    P_AB = U_AB * I_AB;
    P_AC = U_AC * I_AC;
    P_BC = U_BC * I_BC;
    P_E  = P_AB + P_AC + P_BC;

    fprintf(output, "%f, %f, %f, ",
            U_AB, U_AC, U_BC);

    fprintf(output, "- , %f, %f, ",
            I_AC, I_BC);

    fprintf(output, "%f, %f, %f, ",
            I_A, I_B, I_C);

    fprintf(output, "%f, %f, %f, %f\n",
            P_AB, P_AC, P_BC, P_E);

    // third line:
    U_AB = 95.27;
    U_AC = 285.8;
    U_BC = 381.1;

    I_AB = 1.9;
    I_AC = 1.9;
    I_BC = 3.46;

    I_A  = 0;
    I_B  = 1.9;
    I_C  = 5.369;

    P_AB = U_AB * I_AB;
    P_AC = U_AC * I_AC;
    P_BC = U_BC * I_BC;
    P_E  = P_AB + P_AC + P_BC;

    fprintf(output, "%f, %f, %f, ",
            U_AB, U_AC, U_BC);

    fprintf(output, "%f , %f, %f, ",
            I_AB, I_AC, I_BC);

    fprintf(output, "%f, %f, %f, ",
            I_A, I_B, I_C);

    fprintf(output, "%f, %f, %f, %f\n",
            P_AB, P_AC, P_BC, P_E);

    fclose(output);
    return 0;
}
