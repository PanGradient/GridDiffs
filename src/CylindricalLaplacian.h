/*
 * File: CylindricalLaplacian.h
 * Author(s): P Kuszaj
 * Last changed: 28.01.2015
 *
 * A header file providing CylindricalLaplacian class used for evaluating
 * Laplace operator at a given point in cylindrical coordinate system using
 * given grid points along rho, phi and z axes. For further information please
 * see basic_3D_diffop.h header file.
 */

#ifndef GRIDDIFF_CYLINDRICALLAPLACIAN_H
#define GRIDDIFF_CYLINDRICALLAPLACIAN_H

#include "basic_3D_diffop.h"  /* Basic_3D_DiffOp */

namespace GridDiff
{

/*
 * CartesianLaplacian class
 *
 * Allows evaluation of Laplace operator at a given point in cylindrical
 * coordinate system using given grid points along rho, phi and z axes.
 */
class CylindricalLaplacian : public Basic_3D_DiffOp
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
        CylindricalLaplacian (const QPoint   &   r0Point,
                              const QGrid    & rhoCoords,
                              const QGrid    & phiCoords,
                              const QGrid    &   zCoords) :

                              Basic_3D_DiffOp (  r0Point,
                                               rhoCoords,
                                               phiCoords,
                                                 zCoords,
                                                       2) { }

        CylindricalLaplacian (const Basic_3D_DiffOp & other) :

                                     Basic_3D_DiffOp (other) { }

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
         * Double value equal to numerical Laplace operator at given point.
         *
         * ------------
         *  Exceptions
         * ------------
         * None.
         */
        double eval(const QGrid & rhoVals,
                    const QGrid & phiVals,
                    const QGrid &   zVals);

}; /* class CylindricalLaplacian */

} /* namespace GridDiff */

#endif /* GRIDDIFF_CYLINDRICALLAPLACIAN_H */
