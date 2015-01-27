/*
 * File: fornberg_nderivs.c
 * Author(s): P Kuszaj
 * Last changed: 27.01.2015
 *
 * A source file with implementations of functions declared in
 * fornberg_nderivs.h header file. */

#include "fornberg_nderivs.h"

int FornbergNumDerivsCoeffs (double * coeffs,
                           const double x0, const double * p,
                           size_t n, unsigned int m)
{
    /*******************************
     * Pre-calculation input check *
     *******************************/

    /* Ensure none of input pointers are NULL. Otherwise, exit with
     * an appropriate error code. */
    if (p == NULL){
        return FORNBERG_NULLPTR_P;
    }

    if (coeffs == NULL){
        return FORNBERG_NULLPTR_COEFFS;
    }

    /* If number of points < highest derivative + 1, exit with error
     * code. */
    if (n < m){
        return FORNBERG_SIZEERR;
    }

    /*************************
     * Main code begins here *
     *************************/

    /* Variables holding some temporary values */
    double a, b;
    size_t min_im;

    /* Variables holding point position differences */
    double p_ij,       /* p[i]   - p[j] */
           p_ix0,      /* p[i]   - x0 */
           p_ix0_prev; /* p[i-1] - x0 */

    /* Indices used in loops */
    size_t i, j, k;

    /* Initializing all coefficients to zero */
    for (k = 0; k < m; ++k){
        for (j = 0; j < n; ++j){
            coeffs[k*n+j] = 0.0;
        }
    }

    a = 1.0;
    p_ix0  = p[0] - x0;

    coeffs[0] = 1.0;

    /* Main loop over all accuracies up to n (all points used) */
    for (i = 1; i < n; ++i){
        b = 1.0;
        p_ix0_prev = p_ix0;
        p_ix0      = p[i] - x0;

        /* Compare i and m and choose the smaller one */
        min_im = (i < m-1) ? i : m-1;

        /* Looping over all grid points before p[i] */
        for (j = 0; j < i; ++j){
            p_ij  = p[i] - p[j];
            b    *= p_ij;

            /* The last coefficient for i grid points and kth derivative
             * has to be calculated before any operations done on (i-1)th
             * coefficient (since it depends on its value in from previous
             * iteration). */
            if (j == i-1){
                for (k = min_im; k > 0; --k){
                    coeffs[k*n+i]  = a;
                    coeffs[k*n+i] *=          k * coeffs[(k-1)*n+(i-1)]
                                   - p_ix0_prev * coeffs[k*n+(i-1)];
                    coeffs[k*n+i] /= b;
                }
                /* Since there is no c(-1,i-1) coefficient, it is assumed
                 * to be zero. */
                coeffs[i]  =   a;
                coeffs[i] *= - p_ix0_prev * coeffs[i-1];
                coeffs[i] /=   b;
            }

            /* Coefficient calculation */
            for (k = min_im; k > 0; --k){
                coeffs[k*n+j]  = p_ix0 * coeffs[k*n+j]
                                   - k * coeffs[(k-1)*n+j];
                coeffs[k*n+j] /= p_ij;
            }
            /* Since there is no c(-1,j) coefficient, it is assumed to be
             * zero. */
            coeffs[j]  = p_ix0 * coeffs[j];
            coeffs[j] /= p_ij;
        }

        a = b;
    }

    /* Successful termination */
    return FORNBERG_SUCCESS;
}


double FornbergGetCoeff (double * coeffs,
                         size_t n, size_t i,
                         unsigned int k)
{
    return coeffs[k*n + i];
}


double * FornbergGetCoeffList (double * coeffs,
                               size_t n,
                               unsigned int k)
{
    return &coeffs[k*n];
}


double FornbergKDerivEval (const double * coeffs_n,
                           const double * pvals, size_t n)
{
    double eval = 0.0;
    size_t i;

    for (i = 0; i < n; ++i){
        eval += coeffs_n[i] * pvals[i];
    }

    return eval;
}

