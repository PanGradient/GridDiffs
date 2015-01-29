/*
 * File: CylindricalGradient.cc
 * Author(s): P Kuszaj
 * Last changed: 29.01.2015
 *
 * A source file providing CylindricalGradient class methods implementation
 * (declared in CylindricalGradient.h header file).
 */

#include "CylindricalGradient.h"

namespace GridDiff
{

double CylindricalGradient::eval(const QGrid & rhoVals,
                                 const QGrid & phiVals,
                                 const QGrid &   zVals)
{
    /*                 [ df/d(rho)       ]
       Lf(rho,phi,z) = [ df/d(phi) / rho ]
                       [     df/dz       ] */
    QPoint grad;

    grad.q1 = fEvalQ1Diff(1, rhoVals);
    grad.q2 = fEvalQ2Diff(1, phiVals) / mQ0Point.q1 ;
    grad.q3 = fEvalQ3Diff(1,   zVals);

    return grad;
}

} /* namespace GridDiff */
