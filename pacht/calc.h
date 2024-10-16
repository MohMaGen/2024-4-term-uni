#ifndef _CALC_H_GUARD_
#define _CALC_H_GUARD_

#define EX(number)   printf("Solution for " #number ":\n")
#define VALUE(value) printf("%20s = %e.\n", #value, value)

double lin(double l_k, double l_v, double u_k, double u_v, double k);


// v ^
//lv | |\
//   | | \
// v | L__\
//uv | L___\
//   |---------------> k
//     l k u
//
// lv-v = (l-u / l-k) lv-uv

#endif


#ifdef CALC_IMPLEMENT
double lin(double l_k, double l_v, double u_k, double u_v, double k) {
    return l_v - (k-l_k)/(u_k-l_k) * (l_v - u_v);
}
#endif


