#include "CartesianLaplacian.h"

namespace GridDiff
{

double CartesianLaplacian::eval(const QGrid & xVals,
                                const QGrid & yVals,
                                const QGrid & zVals)
{
    return   fEvalQ1Diff(2, xVals)
           + fEvalQ2Diff(2, yVals)
           + fEvalQ3Diff(2, zVals);
}

} /* namespace GridDiff */
