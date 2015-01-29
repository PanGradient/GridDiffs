/*
 * File: SphericalGradient.cc
 * Author(s): P Kuszaj
 * Last changed: 29.01.2015
 *
 * A source file providing SphericalGradient class methods implementation
 * (declared in SphericalGradient.h header file).
 */

#include "SphericalGradient.h"
#include <cmath > /* sin */

namespace GridDiff
{

double SphericalGradient::eval(const QGrid &     rVals,
                               const QGrid & thetaVals,
                               const QGrid &   phiVals)
{
    /*                 [       df/dr                 ]
       Lf(rho,phi,z) = [ df/d(theta) / r             ]
                       [   df/d(phi) / (r*sin(theta))] */
    QPoint grad;

    grad.q1 = fEvalQ1Diff(1,     rVals);
    grad.q2 = fEvalQ2Diff(1, thetaVals) / mQ0Point.q1;
    grad.q3 = fEvalQ3Diff(1,   phiVals) / (mQ0Point.q1 * sin(mQ0Point.q2));

    return grad;
}

} /* namespace GridDiff */
