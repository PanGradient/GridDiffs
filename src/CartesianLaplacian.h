/*
 * File: CartesianLaplacian.h
 * Author(s): P Kuszaj
 * Last changed: 28.01.2015
 *
 * A header file prividing with CartesianLaplacian class used for evaluating
 * Laplace operator at a given point in cartesian coordinate system using
 * given grid points along x, y and z axes. For further information please
 * see basic_3D_diffop.h header file.
 */

#ifndef GRIDDIFF_CARTESIANLAPLACIAN_H
#define GRIDDIFF_CARTESIANLAPLACIAN_H

#include "basic_3D_diffop.h"  /* Basic_3D_DiffOp */

namespace GridDiff
{

/*
 * CartesianLaplacian class
 *
 * Allows evaluation of Laplace operator at a given point in cartesian
 * coordinate system using given grid points along x, y and z axes.
 */
class CartesianLaplacian : public Basic_3D_DiffOp
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
        CartesianLaplacian (const QPoint   & r0Point,
                            const QGrid    & xCoords,
                            const QGrid    & yCoords,
                            const QGrid    & zCoords) :

                            Basic_3D_DiffOp (r0Point,
                                             xCoords,
                                             yCoords,
                                             zCoords,
                                                   2) { }

        CartesianLaplacian (const Basic_3D_DiffOp & other) :

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
         * x, y and z. Their order has to correspond to the grid points
         * order.
         *
         * -----------
         *  Arguments
         * -----------
         * const QGrid & xVals
         * const QGrid & yVals
         * const QGrid & zVals
         *     Function values at grid points at axes x, y and z.
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
        double eval(const QGrid & xVals,
                    const QGrid & yVals,
                    const QGrid & zVals);

}; /* class CartesianLaplacian */

} /* namespace GridDiff */

#endif /* GRIDDIFF_CARTESIANLAPLACIAN_H */
