/*
 * File: basic_3D_diffop.h
 * Author(s): P Kuszaj
 * Last changed: 28.01.2015
 *
 * A header file providing Basic_3D_DiffOp class. It can be used as
 * a parent class for defining partial differential operators classes
 * of arbitrary order in 3-dimensional space parametrized by some general
 * coordinates q1, q2, q3. Numerical partial derivatives are provided
 * as private function members and are based on discrete differentiation
 * (evaluation of optimal coefficients is handled by the class).
 */

#ifndef GRIDDIFF_BASIC_3D_DIFFOP_H
#define GRIDDIFF_BASIC_3D_DIFFOP_H

#include "qobj.h"  /* QPoint, QGrid */

namespace GridDiff
{

/*
 * Basic_3D_DiffOp class
 *
 * Provides basic framework for calculating numerical partial differential
 * operators of given order at a particular point using arbitrary grid points
 * expressed in any orthonormal parametrization of R^3 acting on some scalar
 * function with known values at grid nodes.
 *
 * Class holds position, at which calculations will be performed (mQ0Point),
 * grid points coordinates along a paricular axis (it is assumed, that grid
 * points differs from mQ0Point in at most one coordinate value),
 * coefficients used in discrete dervatives calculation (automatically
 * optimized) and maximal derivative order.
 *
 * Basic_3D_DiffOp class has no public function member for evaluating any
 * differential operator for given point set. User has to implement appropriate
 * method on his/her own in child class inheriting from this one.
 *
 * Given grid point coordinates can be given in any order, but they have to
 * be unique. mQ0Point coordinates can coincide with those in mQiCoords
 * (i=1,2,3). Although them class holds their absolute value, translated
 * values of mQ0Point and mQiCoords are equivalent, since coefficients
 * pQiCoeffs depends only on relative value between coordinates. This means
 * that all values can be, for instance, expressed in relation to mQ0Point
 * and used for different grid points, as long as position differences are
 * invariant under transformation between both grid sets. This is
 * particularly useful for equally spaced grids, for which user can define
 * a local subgrid and loop over all grid points using the same Basic_3D_DiffOp
 * instance, without redefining mQ0Point and/or mQiCoords and recalculating
 * values stored in pQiCoeffs.
 *
 * This class also provides three protected function members fEvalQiDiff
 * (i=1,2,3) evaluating kth partial derivatives d^k/dqi^k at mQ0Point. User
 * should use them for defining differential operators in his/her child
 * classes parented by Basic_3D_DiffOp. For instance: a differential operator:
 *     Lf(q1,q2,q3) = 3/2*d^2f/dq1^2 + 2*df/dq2 - 1/4*df/dq3
 * should be implemented as:
 *     L(q1Vals,q2Vals,q3Vals) = 1.50 * fEvalQ1Diff(2, q1Vals)
 *                             + 2.00 * fEvalQ2Diff(1, q2Vals)
 *                             - 0.25 * fEvalQ3Diff(3, q3Vals)
 * with qiVals being function values for grid points on qi axis.
 */
class Basic_3D_DiffOp
{
    protected:
        /* Points coordinates as which operator is evaluated. */
        QPoint     mQ0Point;
        /* Grid point coordinates at qi axis (i=1,2,3). */
        QGrid      mQ1Coords,
                   mQ2Coords,
                   mQ3Coords;
        /* Coefficient used in calculating kth partial derivative along qi
         * axis (i=1,2,3). */
        double   * pQ1Coeffs,
                 * pQ2Coeffs,
                 * pQ3Coeffs;
        /* Highest derivative order, which class can use. */
        unsigned   mMaxOrder;

        /*
         * fEvalQiDiff() (i=1,2,3)
         *
         * Returns kth numerical partial derivative along qi axis using given
         * function values at grid points. Given order has to be at most equal
         * to mMaxOrder.
         *
         * -----------
         *  Arguments
         * -----------
         * const unsigned & order
         *     Derivative order. If zero, performs polynomial interpolation.
         *     Cannot be larger than mMaxOrder.
         *
         * const QGrid & qiVals
         *     Function values at grid points on qi axis. Order has to
         *     corresponds to grid points order. Has to be the same size
         *     as mQiCoords.
         *
         * ---------
         *  Returns
         * ---------
         * Double value equal to numerical partial derivative d^k/dqi^k at
         * mQ0Point. If order is 0, returns polynomially interpolated function
         * value at this point.
         * 
         * ------------
         *  Exceptions
         * ------------
         * std::invalid_argument if:
         *     * Given order larger than allowed (order > mMaxOrder)
         *     * qiVals size not equal to number of grid points along qi axis
         */
        double fEvalQ1Diff (const unsigned &  order,
                            const QGrid    & q1Vals);
        double fEvalQ2Diff (const unsigned &  order,
                            const QGrid    & q2Vals);
        double fEvalQ3Diff (const unsigned &  order,
                            const QGrid    & q3Vals);

    public:
        /*************
         * LIFECYCLE *
         ************/

        /*
         * Constructor
         *
         * -----------
         *  Arguments
         * -----------
         * const QPoint & q0Point
         *     Point at which evaluations will be performed.
         *
         * const QGrid & q1Coords
         * const QGrid & q2Coords
         * const QGrid & q3Coords
         *     Grid point positions along axes q1, q2 and q3. For each axis
         *     those positions have to be unique, otherwise dire numerical
         *     errors occur.
         *
         * const unsigned & MaxOrder
         *     Highest derivative used in the differential operator.
         *
         * ------------
         *  Exceptions
         * ------------
         * std::invalid_argument if:
         *     * Any of qiCoords is of size < 2
         *     * Any of qiCoords is of size < MaxOrder
         */
        Basic_3D_DiffOp (const QPoint   &  q0Point,
                         const QGrid    & q1Coords,
                         const QGrid    & q2Coords,
                         const QGrid    & q3Coords,
                         const unsigned & MaxOrder);

        /*
         * Copy constructor
         *
         * -----------
         *  Arguments
         * -----------
         * const Basic_3D_DiffOp & other
         *     Other instance of Basic_3D_DiffOp class.
         *
         * ------------
         *  Exceptions
         * ------------
         * None.
         */
        Basic_3D_DiffOp (const Basic_3D_DiffOp & other);

        /*
         * Virtual destructor
         *
         * ------------
         *  Exceptions
         * ------------
         * None.
         */
        virtual ~Basic_3D_DiffOp ();


        /*************
         * OPERATORS *
         ************/

        /*
         * Copy operator
         *
         * Does nothing in case of self-assignment attempt.
         *
         * ------------
         *  Exceptions
         * ------------
         * None.
         */
        Basic_3D_DiffOp & operator= (const Basic_3D_DiffOp & other);

}; /* class Basic_3D_DiffOp */

} /* namespace GridDiff */

#endif /* GRIDDIFF_BASIC_DIFFOP_H */
