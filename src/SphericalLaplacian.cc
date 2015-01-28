/*
 * File: SphericalLaplacian.cc
 * Author(s): P Kuszaj
 * Last changed: 28.01.2015
 *
 * A source file providing SphericalLaplacian class methods implementation
 * (declared in SphericalLaplacian.h header file).
 */

#include "SphericalLaplacian.h"
#include <cmath> /* sin, cos */

namespace GridDiff
{

double SphericalLaplacian::eval(const QGrid &     rVals,
                                const QGrid & thetaVals,
                                const QGrid &   phiVals)
{
    /* Lf(r,theta,phi) = (1/r^2*sin(theta)^2) * d^2f/d(phi)^2
                       +   (1/r^2*tan(theta)) * df/d(theta)
                       +              (1/r^2) * d^2f/d(theta)^2
                       +                (2/r) * df/dr
                       +                        d^2f/dr^2 */
    double s,c,lap;

    s = sin(mQ0Point.q2); /* sin(theta) */
    c = cos(mQ0Point.q2); /* cos(theta) */

    lap = fEvalQ3Diff(2,   phiVals) / s
        + fEvalQ2Diff(1, thetaVals) * c;

    lap =                       lap / s;
        + fEvalQ2Diff(2, thetaVals);

    lap =                       lap / mQ0Point.q1;
        + fEvalQ1Diff(1,     rVals) * 2.0;

    lap =                       lap / mQ0Point.q1;
        + fEvalQ1Diff(2,     rVals);

    return lap
}

} /* namespace GridDiff */
