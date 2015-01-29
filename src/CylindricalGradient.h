/*
 * File: CylindricalGradient.h
 * Author(s): P Kuszaj
 * Last changed: 29.01.2015
 *
 * A header file providing CylindricalGradient class used for evaluating
 * gradient at a given point in cylindrical coordinate system using given
 * grid points along rho, phi and z axes. For further information please see
 * basic_3D_diffop.h header file.
 */

#ifndef GRIDDIFF_CYLINDRICALGRADIENT_H
#define GRIDDIFF_CYLINDRICALGRADIENT_H

#include "basic_3D_diffop.h"  /* Basic_3D_DiffOp */

namespace GridDiff
{

/*
 * CylindricalGradient class
 *
 * Allows evaluation of gradient at a given point in cylindrical
 * coordinate system using given grid points along rho, rhi and z axes.
 */
class CylindricalGradient : public Basic_3D_DiffOp
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
        CylindricalGradient (const QPoint   &   r0Point,
                             const QGrid    & rhoCoords,
                             const QGrid    & phiCoords,
                             const QGrid    &   zCoords)

                           : Basic_3D_DiffOp (  r0Point,
                                              rhoCoords,
                                              phiCoords,
                                                zCoords,
                                                      1) { }

        CylindricalGradient (const Basic_3D_DiffOp & other)

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
         * rho, phi and z. Their order has to correspond to the grid points
         * order.
         *
         * Operator diverges for rho_0 := mQ0Point.q1 == 0 (or very close to
         * this value). Is is advised to exlude such points for calculations.
         *
         * -----------
         *  Arguments
         * -----------
         * const QGrid & rhoVals
         * const QGrid & phiVals
         * const QGrid &   zVals
         *     Function values at grid points at axes rho, phi and z.
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
        QPoint eval(const QGrid & rhoVals,
                    const QGrid & phiVals,
                    const QGrid &   zVals);

}; /* class CylindricalGradient */

} /* namespace GridDiff */

#endif /* GRIDDIFF_CYLINDRICALGRADIENT_H */
