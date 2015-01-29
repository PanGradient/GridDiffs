/*
 * File: SphericalGradient.h
 * Author(s): P Kuszaj
 * Last changed: 29.01.2015
 *
 * A header file providing SphericalGradient class used for evaluating
 * gradient at a given point in spherical coordinate system using
 * given grid points along r, theta and phi axes. For further information
 * please see basic_3D_diffop.h header file.
 */

#ifndef GRIDDIFF_SPHERICALGRADIENT_H
#define GRIDDIFF_SPHERICALGRADIENT_H

#include "basic_3D_diffop.h"  /* Basic_3D_DiffOp */

namespace GridDiff
{

/*
 * SphericalGradient class
 *
 * Allows evaluation of gradient at a given point in spherical
 * coordinate system using given grid points along r, theta and phi axes.
 */
class SphericalGradient : public Basic_3D_DiffOp
{
    public:
        /*************
         * LIFECYCLE *
         ************/

        /*
         * Since the only new class member is evaluation method,
         * constructors simply call the parent class constructors.
         * For further information please see basic_3D_diffop.h header file.
         */
        SphericalGradient (const QPoint &     r0Point,
                           const QGrid  &     rCoords,
                           const QGrid  & thetaCoords,
                           const QGrid  &   phiCoords)

                       : Basic_3D_DiffOp (    r0Point,
                                              rCoords,
                                          thetaCoords,
                                            phiCoords,
                                                    1) { }

        SphericalGradient (const Basic_3D_DiffOp & other)

                                : Basic_3D_DiffOp (other) { }

        /*************
         * OPERATORS *
         ************/

        /*
         * Inherited: 
         * Basic_3D_DiffOp & operator= (const Basic_3D_DiffOp & other);
         */

        /**************
         * OPERATIONS *
         **************/

        /*
         * eval()
         *
         * Evaluation method. Takes function values at grid points at axes
         * r, theta and phi. Their order has to correspond to the grid points
         * order.
         *
         * Operator diverges for r_0 := mQ0Point.q1 == 0 and/or
         * theta_0 := mQ0Point.q2 == 0 or pi (or very close to those values).
         * Is is advised to exlude such points for calculations.
         *
         * -----------
         *  Arguments
         * -----------
         * const QGrid &     rVals
         * const QGrid & thetaVals
         * const QGrid &   phiVals
         *     Function values at grid points at axes r, theta and phi.
         *
         * ---------
         *  Returns
         * ---------
         * QPoint structure equal to numerical gradient at given point.
         *
         * ------------
         *  Exceptions
         * ------------
         * None.
         */
        double eval(const QGrid &     rVals,
                    const QGrid & thetaVals,
                    const QGrid &   phiVals);

}; /* class SphericalGradient */

} /* namespace GridDiff */

#endif /* GRIDDIFF_SPHERICALGRADIENT_H */
