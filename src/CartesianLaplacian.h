/*
 * File: CartesianLaplacian.h
 * Author(s): P Kuszaj
 * Last changed: 27.01.2015
 *
 * 
 * */

#ifndef GRIDDIFF_CARTESIANLAPLACIAN_H
#define GRIDDIFF_CARTESIANLAPLACIAN_H

#include "basic_3D_diffop.h"  /* Basic_3D_DiffOp */

namespace GridDiff
{

/*
 * CartesianLaplacian class
 *
 * 
 */
class CartesianLaplacian : public Basic_3D_DiffOp
{
    public:
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

        double eval(const QGrid & xVals,
                    const QGrid & yVals,
                    const QGrid & zVals);

}; /* class CartesianLaplacian */

} /* namespace GridDiff */

#endif /* GRIDDIFF_CARTESIANLAPLACIAN_H */
