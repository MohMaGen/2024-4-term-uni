#include <stdio.h>
#define CALC_IMPLEMENT
#include "./calc.h"

void ex_29(void) {
    EX(29); 
    double p_x  = 1.5 * 98100;          // Pa
    double p_1  = p_x + 760 * 133.32;   // Pa 
    VALUE(p_1);

    double t_1 = 127.43; // C
    double r_1 = 2181.8 * 1000; // J / kg
    VALUE(t_1);
    VALUE(r_1);

    double m_dt2  = 8 * 1000.0 / 3600.0;  // kg / s
    double t_b    = 25.0, t_e = 75.0;     // C
    double t_avg  = (t_b + t_e) / 2.0;
    VALUE(m_dt2);
    VALUE(t_avg);

    double c_lb  = 904.0;
    double c_hb  = 1784.0;;
    double chi   = 0.2;
    double c_int = c_lb * chi + c_hb * (1 - chi);
    VALUE(c_lb);
    VALUE(c_hb);
    VALUE(c_int);

    double Q_2  = m_dt2 * c_int * (t_e - t_b);
    double loss = 0.07;
    double Q_1  = Q_2 / (1 - loss);
    double Q_l  = loss * Q_1;
    VALUE(Q_2);
    VALUE(Q_1);
    VALUE(Q_l);
    double m_dt1 = Q_1 / r_1;
    VALUE(m_dt1);
    VALUE(m_dt1*3600);
}

void ex_30(void) {
    EX(30); 

    double m_dt1 = 4.0 * 1000.0 / 3600.0;
    double r_lb  = 181.6 * 1000;
    double r_hb  = 370.5 * 1000;
    double chi   = 0.8;
    double r_1   = r_lb * chi + r_hb * (1 - chi); VALUE(r_1);

    double Q_1 = m_dt1 * r_1; VALUE(Q_1);

    double loss = 0.08;
    double Q_l = Q_1 * loss;
    VALUE(Q_l);

    double Q_2 = Q_1 - Q_l;
    VALUE(Q_2);

    double m_dt2 = 19.0 * 1000.0 / 3600.0;
    double t_s  = 18;
    double c_2s = 4183;
    double t_ef = t_s + Q_2 / m_dt2 / c_2s;
    VALUE(c_2s);

    double t_m  = (t_s + t_ef) / 2;
    VALUE(t_m);

    double c_2e = 4180;
    VALUE(c_2e);

    double t_e  = t_s + Q_2 / m_dt2 / c_2e;
    VALUE(t_e);
}

void ex_31(void) {
    EX(31);

    double p_1  = 9.9 * 98100; VALUE(p_1); 
    double loss = 0.14;
    double t_1  = lin(9.0e5, 175.36, 10.0e5, 179.88, p_1);
    VALUE(t_1);
    double r_1  = lin(9.0e5, 2030.4 * 1000, 10.0e5, 2014.4 * 1000, p_1);
    VALUE(r_1);

    double t_2 = 138.5; VALUE(t_2);
    double r_2 = lin(130, 344.6 * 1000, 140, 338.9 * 1000, 138.5); VALUE(r_2);

    double m_dt2 = 9.9;
    double Q_2   = m_dt2 * r_2; VALUE(Q_2);

    double Q_1   = Q_2 / (1 - loss); VALUE(Q_1);
    double m_dt1 = Q_1 / r_1; VALUE(m_dt1); VALUE(m_dt1 / 1000 * 3600);
}

int main(void) {
    VALUE(lin(20.0, 100.0, 40.0, 150.0, 30.0));

    ex_29();
    ex_30();
    ex_31();

    return 0;
}
