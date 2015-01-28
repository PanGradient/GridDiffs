/*
 * File: CylindricalLaplacian.cc
 * Author(s): P Kuszaj
 * Last changed: 28.01.2015
 *
 * A source file providing CylindricalLaplacian class methods implementation
 * (declared in CylindricalLaplacian.h header file).
 */

#include "CylindricalLaplacian.h"

namespace GridDiff
{

double CylindricalLaplacian::eval(const QGrid & rhoVals,
                                  const QGrid & phiVals,
                                  const QGrid &   zVals)
{
    /* Lf(rho,phi,z) =   (1/rho) * df/d(rho)
                     + (1/rho^2) * d^2f/d(phi)^2
                     +             d^2f/d(rho)^2
                     +             d^2f/dz^2 */
    return ( fEvalQ1Diff(1, rhoVals)
           + fEvalQ2Diff(2, phiVals) / mQ0Point.q1 ) / mQ0Point.q1
           + fEvalQ1Diff(2, rhoVals)
           + fEvalQ3Diff(2, zVals);
}

} /* namespace GridDiff */
