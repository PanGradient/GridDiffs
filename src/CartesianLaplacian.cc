/*
 * File: CartesianLaplacian.cc
 * Author(s): P Kuszaj
 * Last changed: 28.01.2015
 *
 * A source file providing CartesianLaplacian class methods implementation
 * (declared in CartesianLaplacian.h header file).
 */

#include "CartesianLaplacian.h"

namespace GridDiff
{

double CartesianLaplacian::eval(const QGrid & xVals,
                                const QGrid & yVals,
                                const QGrid & zVals)
{
    /* Lf(x,y,z) = d^2f/dx^2 + d^2f/dy^2 +  d^2f/dz^2 */
    return   fEvalQ1Diff(2, xVals)
           + fEvalQ2Diff(2, yVals)
           + fEvalQ3Diff(2, zVals);
}

} /* namespace GridDiff */
