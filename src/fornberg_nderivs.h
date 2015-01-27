/*
 * File: fornberg_nderivs.h
 * Author(s): P Kuszaj
 * Last changed: 27.01.2015
 *
 * A header file providing functions calculating numerical kth derivative at
 * a given point (for k==0: fast polynomial interpolation method) using an
 * arbitrarily spaced grid. Local implementation of Fornberg algorithm is
 * used (B. Fornberg "Generation of Finite Difference Formulas on Arbitrarily
 * Spaced Grids", Math. Comp. 51 (1988), 699-706, Free Access).
 * It is based on Fortran implementation provided by Bengt Fornberg himself
 * (B. Fornberg "A Practical Guide to Pseudospectral Methods", Cambridge
 * University Press, 1996).
 * The algorithm is based on Lagrange polynomial interpolation, thus is
 * susceptible to Runge's phenomenon. As Fornberg acknowledged, applying
 * it to higher derivatives evaluation might result in severe numerical
 * errors.
 */

#ifndef FORNBERG_NDERIVS_H
#define FORNBERG_NDERIVS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h> /* EXIT_SUCCESS, NULL, size_t */

/*
 * Enumerated type describing exit codes for FornbergNDerivsCoeffs() function
 * defined in this file.
 * If a fuction terminates successfully, it should return code equivalent to
 * EXIT_SUCCESS defined in stdlib.h. Otherwise, it should return appropriate
 * error code.
 */
enum
{
    FORNBERG_SUCCESS = EXIT_SUCCESS, /* successful termination */
    FORNBERG_NULLPTR_P,              /* pointer to the point position array
                                        is NULL */
    FORNBERG_NULLPTR_COEFFS,         /* pointer to the coefficients array
                                        is NULL */
    FORNBERG_SIZEERR                 /* number of points < highest derivative
                                        degree + 1 */
};


/*
 * FornbergNumDerivsCoeffs()
 *
 * Generates optimal coefficients for numerical derivatives with given point
 * and arbitrarly spaced one-dimensional grid:
 *
 *     d^k/dx^k ( f(x=x0) ) = c(k,0) * f(p[0]) + ... + c(k,n-1) * f(p[n-1])
 *
 * All coefficients c(k,i) for k=0,...,m-1 and i=0,..,n-1 are calculated and
 * saved in array (provided by user) of sized at least n*m. The special case
 * k==0 corresponds to polynomial interpolation at a given point. Coefficients
 * are invariant under translation transformation, therefore they can be used
 * for every (x0, p) set as long as relative differences are preserved (e.g.
 * equally spaced grid).
 *
 * All grid points have to be unique. Repetitions can (and will) cause errors
 * such as calculated coefficients being NaN or inf. Position of x0 can
 * coincide with one of grid points (in such case c(0,i) should be zero for
 * all p[i] except for p[j] == x0).
 *
 * Grid points order is also arbitrary, although the coefficient order
 * corresponds to it. Shuffling them before derivative evaluation might gives
 * false results. User has to take it into consideration.
 *
 * Number of grid points (n) has to be higher that the highest derivative
 * degree (equal to m or higher).
 *
 * -----------
 *  Arguments
 * -----------
 * double * coeffs
 *     An array of doubles. Its size has to be at least n*m. All
 *     coefficients are written in its first n*m*sizeof(double) bytes. Every
 *     c(k,i) coefficient is accesible as coeffs[k*n + i].
 *
 * const double x0
 *     A point at which derivatives will be evaluated. Can coindide with
 *     a grid point.
 *
 * const double * p
 *     An array with points from a one-dimensional grid (neighbourhood of x0).
 *     All values have to be unique.
 *
 * size_t n
 *     Number of grid points. Has to be at least equal to m.
 *
 * unsigned int m
 *     Derivative degree limit. The highest derivative for which approximation
 *     coefficients will be calculated will be of order m-1. For accurate
 *     results it is recommended to use relatively low values of m.
 *
 * ---------
 *  Returns
 * ---------
 * Integer value equal to proper exit code:
 *     FORNBERG_SUCCESS         function successfully terminates
 *     FORNBERG_NULLPTR_P       error code: p is a NULL pointer
 *     FORNBERG_NULLPTR_COEFFS  error code: coeffs is a NULL pointer
 *     FORNBERG_SIZEERR         error code: n < m
 */
int FornbergNumDerivsCoeffs (double * coeffs,
                             const double x0, const double * p,
                             size_t n, unsigned int m);


/*
 * FornbergGetCoeff()
 *
 * Returns c(k,i) coefficient value from a given array (assumed properly
 * formatted; ideally generated by FornbergNDerivsCoeffs function).
 *
 * -----------
 *  Arguments
 * -----------
 * double * coeffs
 *     Array of doubles, containing all coefficient used for evaluating
 *     n-point numerical derivatives up to the mth order (m being some
 *     non-negative number).
 *
 * size_t n
 *     Number of grid points used to calculate coefficients.
 *
 * size_t i
 *     Index of ith grid point/c(k,i) coefficient. Must be smaller than n.
 *
 * unsigned int k
 *     Index of kth derivative/c(k,i) coefficient.
 *
 * ---------
 *  Returns
 * ---------
 * Double value equal to the c(k,i) coefficient.
 */
double FornbergGetCoeff (double * coeffs,
                         size_t n, size_t i,
                         unsigned int k);

/*
 * FornbergGetCoeffList()
 *
 * Returns pointer to c(k,0) coefficient from a given array (assumed properly
 * formatted; ideally generated by FornbergNDerivsCoeffs function). This
 * allows to extract all coefficients for n-point numerical approximation of
 * kth derivative, assuming user knows total number of used points.
 *
 * -----------
 *  Arguments
 * -----------
 * double * coeffs
 *     Array of doubles, containing all coefficient used for evaluating
 *     n point numerical derivatives up to the mth order (m being some
 *     non-negative number).
 *
 * size_t n
 *     Number of grid points used to calculate coefficients.
 *
 * unsigned int k
 *     Index of kth derivative.
 *
 * ---------
 *  Returns
 * ---------
 * Pointer to c(k,0) coefficient.
 */
double * FornbergGetCoeffList (double * coeffs,
                               size_t n,
                               unsigned int k);

/*
 * FornbergKDerivEval()
 *
 * Evaluates kth derivative at some x0 point using n grid points and
 * coefficients for n-point numerical derivative (all calculated for
 * particular x0 and grid points or, more precisely, relative differences
 * between them).
 *
 * It is assumed coefficients (coeffs_k) and function values at grid points
 * (pvals) are ordered in such way that for all i coeffs_k[i] and pvals[i]
 * corresponds to the same ith grid point.
 *
 * -----------
 *  Arguments
 * -----------
 * const double * coeffs_k
 *     Array of doubles, containing all coefficient used for evaluating
 *     n-point numerical kth derivative. Can be obtained by generating
 *     coefficients up to some derivative of order m >= k with the
 *     FornbergNumDerivsCoeffs function and extracting proper pointer
 *     with the FornbergGetCoeffList function.
 *
 * const double * pvals
 *     Array of doubles, containing function values at grid points. Has to
 *     be ordered in a way corresponding to original grid points order. 
 *
 * size_t n
 *     Number of grid points used to calculate coefficients.
 *
 * ---------
 *  Returns
 * ---------
 * Double value equal to the n-point numerical approximation of kth
 * derivative at some point x0 (used to calculate all coefficients).
 */
double FornbergKDerivEval (const double * coeffs_k,
                           const double * pvals, size_t n);


#ifdef __cplusplus
}
#endif

#endif /* FORNBERG_NDERIVS_H */
