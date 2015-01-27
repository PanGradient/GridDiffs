/*
 * File: basic_3D_diffop.h
 * Author(s): P Kuszaj
 * Last changed: 27.01.2015
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
 * expressed in any orthonormal parametrization of R^3.
 *
 * Class holds position, at which calculations will be performed (mQ0Point),
 * grid points coordinates along a paricular axis (it is assumed, that grid
 * points differs from mQ0Point in at most one coordinate value),
 * coefficients used in discrete dervatives calculation (automatically
 * optimized) and maximal derivative order.
 *
 * Basic_3D_DiffOp class has no public function member for calculating
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
 */
class Basic_3D_DiffOp
{
    private:
        QPoint     mQ0Point;
        QGrid      mQ1Coords,
                   mQ2Coords,
                   mQ3Coords;
        double   * pQ1Coeffs,
                 * pQ2Coeffs,
                 * pQ3Coeffs;
        unsigned   mMaxOrder;

    protected:
        double fEvalQ1Diff (const unsigned &  order,
                            const QGrid    & q1Vals);
        double fEvalQ2Diff (const unsigned &  order,
                            const QGrid    & q2Vals);
        double fEvalQ3Diff (const unsigned &  order,
                            const QGrid    & q3Vals);

    public:
        Basic_3D_DiffOp (const QPoint   &  q0Point,
                         const QGrid    & q1Coords,
                         const QGrid    & q2Coords,
                         const QGrid    & q3Coords,
                         const unsigned & MaxOrder);

        Basic_3D_DiffOp (const Basic_3D_DiffOp & other);

        virtual ~Basic_3D_DiffOp ();


        Basic_3D_DiffOp & operator= (const Basic_3D_DiffOp & other);

}; /* class Basic_3D_DiffOp */

} /* namespace GridDiff */

#endif /* GRIDDIFF_BASIC_DIFFOP_H */
