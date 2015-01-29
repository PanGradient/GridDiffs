/*
 * File: CartesianGradient.cc
 * Author(s): P Kuszaj
 * Last changed: 29.01.2015
 *
 * A source file providing CartesianGradient class methods implementation
 * (declared in CartesianGradient.h header file).
 */

#include "CartesianGradient.h"

namespace GridDiff
{

QPoint CartesianGradient::eval(const QGrid & xVals,
                               const QGrid & yVals,
                               const QGrid & zVals)
{
    /*             [ df/dx ]
       Lf(x,y,z) = [ df/dy ]
                   [ df/dz ] */

    QPoint grad;

    grad.q1 = fEvalQ1Diff(1, xVals);
    grad.q2 = fEvalQ2Diff(1, yVals);
    grad.q3 = fEvalQ3Diff(1, zVals);

    return grad;
}

} /* namespace GridDiff */
