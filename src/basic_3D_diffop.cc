/*
 * File: basic_3D_diffop.cc
 * Author(s): P Kuszaj
 * Last changed: 28.01.2015
 *
 * A source file providing Basic_3D_DiffOp class methods implementation
 * (declared in basic_3D_diffop.h header file).
 */

#include "basic_3D_diffop.h"
#include "fornberg_nderivs.h" /* FornbergNumDerivsCoeffs */

#include <cstring>            /* memcpy */
#include <stdexcept>          /* std::invalid_argument */

namespace GridDiff
{

Basic_3D_DiffOp::Basic_3D_DiffOp (const QPoint   &  q0Point,
                                  const QGrid    & q1Coords,
                                  const QGrid    & q2Coords,
                                  const QGrid    & q3Coords,
                                  const unsigned & MaxOrder)
{
    /* Initializing members (in case of exception accurence). */
    mQ0Point.q1 = 0.0; mQ0Point.q2 = 0.0; mQ0Point.q3 = 0.0; 

    mQ1Coords = QGrid();
    mQ2Coords = QGrid();
    mQ3Coords = QGrid();

    pQ1Coeffs = NULL;
    pQ2Coeffs = NULL;
    pQ3Coeffs = NULL;

    mMaxOrder = 0;

    /* If one of arguments is invalid, throw exception. */
    if (q1Coords.size() <= 2){
        throw std::invalid_argument("q1 grid size < 2");
    }
    if (q2Coords.size() <= 2){
        throw std::invalid_argument("q2 grid size < 2");
    }
    if (q3Coords.size() <= 2){
        throw std::invalid_argument("q3 grid size < 2");
    }

    if (q1Coords.size() <= MaxOrder){
        throw std::invalid_argument("q1 grid size < max deriv. order");
    }
    if (q2Coords.size() <= MaxOrder){
        throw std::invalid_argument("q2 grid size < max deriv. order");
    }
    if (q3Coords.size() <= MaxOrder){
        throw std::invalid_argument("q3 grid size < max deriv. order");
    }

    /* Setting members to argument values. */
    mQ0Point.q1 = q0Point.q1;
    mQ0Point.q2 = q0Point.q2;
    mQ0Point.q3 = q0Point.q3;

    mQ1Coords = q1Coords;
    mQ2Coords = q2Coords;
    mQ3Coords = q3Coords;

    /* Allocating coefficient arrays. */
    pQ1Coeffs = new double [ q1Coords.size() * (MaxOrder+1) ];
    pQ2Coeffs = new double [ q2Coords.size() * (MaxOrder+1) ];
    pQ3Coeffs = new double [ q3Coords.size() * (MaxOrder+1) ];

    /* Calculating coefficient values up to the derivative of order
     * MaxOrder. */
    FornbergNumDerivsCoeffs(pQ1Coeffs,
                            q0Point.q1, &q1Coords[0],
                            q1Coords.size(), MaxOrder+1);

    FornbergNumDerivsCoeffs(pQ2Coeffs,
                            q0Point.q2, &q2Coords[0],
                            q2Coords.size(), MaxOrder+1);

    FornbergNumDerivsCoeffs(pQ3Coeffs,
                            q0Point.q3, &q3Coords[0],
                            q3Coords.size(), MaxOrder+1);

    /* Setting mMaxOrder. */
    mMaxOrder = MaxOrder;
}


Basic_3D_DiffOp::Basic_3D_DiffOp (const Basic_3D_DiffOp & other)
{
    /* Copy members. */
    mQ0Point.q1 = other.mQ0Point.q1;
    mQ0Point.q2 = other.mQ0Point.q2;
    mQ0Point.q3 = other.mQ0Point.q3;

    mQ1Coords = other.mQ1Coords;
    mQ2Coords = other.mQ2Coords;
    mQ3Coords = other.mQ3Coords;

    /* Initialize coefficient pointers to NULL. */
    pQ1Coeffs = NULL;
    pQ2Coeffs = NULL;
    pQ3Coeffs = NULL;

    /* If other has non-null pointers to coefficients, allocate memory. */
    if (other.pQ1Coeffs != NULL){
        pQ1Coeffs = new double [ other.mQ1Coords.size() *
                                    (other.mMaxOrder+1) ];
    }
    if (other.pQ2Coeffs != NULL){
        pQ2Coeffs = new double [ other.mQ2Coords.size() *
                                    (other.mMaxOrder+1) ];
    }
    if (other.pQ3Coeffs != NULL){
        pQ3Coeffs = new double [ other.mQ3Coords.size() *
                                    (other.mMaxOrder+1) ];
    }

    /* If other has non-null pointers to coefficients, copy them. */
    if (other.pQ1Coeffs != NULL){
        std::memcpy( pQ1Coeffs, other.pQ1Coeffs,
                            other.mQ1Coords.size() *
                            (other.mMaxOrder+1) *
                                    sizeof(double) );
    }
    if (other.pQ2Coeffs != NULL){
        std::memcpy( pQ2Coeffs, other.pQ2Coeffs,
                            other.mQ2Coords.size() *
                            (other.mMaxOrder+1) *
                                    sizeof(double) );
    }
    if (other.pQ3Coeffs != NULL){
        std::memcpy( pQ3Coeffs, other.pQ3Coeffs,
                            other.mQ3Coords.size() *
                            (other.mMaxOrder+1) *
                                    sizeof(double) );
    }

    /* Copy mMaxOrder. */
    mMaxOrder = other.mMaxOrder;
}


Basic_3D_DiffOp::~Basic_3D_DiffOp ()
{
    /* Free memory only if coefficient pointer aren't NULL. */
    if (pQ1Coeffs != NULL) { delete [] pQ1Coeffs; }
    if (pQ2Coeffs != NULL) { delete [] pQ2Coeffs; }
    if (pQ3Coeffs != NULL) { delete [] pQ3Coeffs; }
}


Basic_3D_DiffOp & Basic_3D_DiffOp::operator= (const Basic_3D_DiffOp & other)
{
    /* Avoid self-assignment */
    if (this != &other){
        /* Copy members. */
        mQ0Point.q1 = other.mQ0Point.q1;
        mQ0Point.q2 = other.mQ0Point.q2;
        mQ0Point.q3 = other.mQ0Point.q3;

        mQ1Coords = other.mQ1Coords;
        mQ2Coords = other.mQ2Coords;
        mQ3Coords = other.mQ3Coords;

        /* If coefficient pointers aren't NULL, free memory. */
        if (pQ1Coeffs != NULL) { delete [] pQ1Coeffs; }
        if (pQ2Coeffs != NULL) { delete [] pQ2Coeffs; }
        if (pQ3Coeffs != NULL) { delete [] pQ3Coeffs; }

        /* If other has non-null pointers to coefficients, allocate
         * memory. */
        if (other.pQ1Coeffs != NULL){
            pQ1Coeffs = new double [ other.mQ1Coords.size() *
                                        (other.mMaxOrder+1) ];
        }
        if (other.pQ2Coeffs != NULL){
            pQ2Coeffs = new double [ other.mQ2Coords.size() *
                                        (other.mMaxOrder+1) ];
        }
        if (other.pQ3Coeffs != NULL){
            pQ3Coeffs = new double [ other.mQ3Coords.size() *
                                        (other.mMaxOrder+1) ];
        }

        /* If other has non-null pointers to coefficients, copy them. */
        if (other.pQ1Coeffs != NULL){
            std::memcpy( pQ1Coeffs, other.pQ1Coeffs,
                             other.mQ1Coords.size() *
                                (other.mMaxOrder+1) *
                                     sizeof(double) );
        }
        if (other.pQ2Coeffs != NULL){
            std::memcpy( pQ2Coeffs, other.pQ2Coeffs,
                             other.mQ2Coords.size() *
                                (other.mMaxOrder+1) *
                                     sizeof(double) );
        }
        if (other.pQ3Coeffs != NULL){
            std::memcpy( pQ3Coeffs, other.pQ3Coeffs,
                             other.mQ3Coords.size() *
                                (other.mMaxOrder+1) *
                                     sizeof(double) );
        }

        /* Copy mMaxOrder. */
        mMaxOrder = other.mMaxOrder;
    }

    return *this;
}


double Basic_3D_DiffOp::fEvalQ1Diff (const unsigned &  order,
                                     const QGrid    & q1Vals)
{
    /* If arguments invalid, throw exception. */
    if (order > mMaxOrder){
        throw std::invalid_argument("given order higher than max");
    }

    if (q1Vals.size() < mQ1Coords.size()){
        throw std::invalid_argument("too little values at grid points given");
    }

    if (q1Vals.size() > mQ1Coords.size()){
        throw std::invalid_argument("too much values at grid points given");
    }

    /* Extract proper coefficients. */
    double * q1_k_coeffs = FornbergGetCoeffList(pQ1Coeffs,
                                                mQ1Coords.size(),
                                                order);
    
    /* Return partial derivative of given order. */
    return FornbergKDerivEval(q1_k_coeffs,
                              &q1Vals[0], q1Vals.size());
}


double Basic_3D_DiffOp::fEvalQ2Diff (const unsigned &  order,
                                     const QGrid    & q2Vals)
{
    /* If arguments invalid, throw exception. */
    if (order > mMaxOrder){
        throw std::invalid_argument("given order higher than max");
    }

    if (q2Vals.size() < mQ2Coords.size()){
        throw std::invalid_argument("too little values at grid points given");
    }

    if (q2Vals.size() > mQ2Coords.size()){
        throw std::invalid_argument("too much values at grid points given");
    }

    /* Extract proper coefficients. */
    double * q2_k_coeffs = FornbergGetCoeffList(pQ2Coeffs,
                                                mQ2Coords.size(),
                                                order);
    
    /* Return partial derivative of given order. */
    return FornbergKDerivEval(q2_k_coeffs,
                              &q2Vals[0], q2Vals.size());
}


double Basic_3D_DiffOp::fEvalQ3Diff (const unsigned &  order,
                                     const QGrid    & q3Vals)
{
    /* If arguments invalid, throw exception. */
    if (order > mMaxOrder){
        throw std::invalid_argument("given order higher than max");
    }

    if (q3Vals.size() < mQ3Coords.size()){
        throw std::invalid_argument("too little values at grid points given");
    }

    if (q3Vals.size() > mQ3Coords.size()){
        throw std::invalid_argument("too much values at grid points given");
    }

    /* Extract proper coefficients. */
    double * q3_k_coeffs = FornbergGetCoeffList(pQ3Coeffs,
                                                mQ3Coords.size(),
                                                order);
    
    /* Return partial derivative of given order. */
    return FornbergKDerivEval(q3_k_coeffs,
                              &q3Vals[0], q3Vals.size());
}

} /* namespace GridDiff */
