/*
 * File: qobj.h
 * Author(s): P Kuszaj
 * Last changed: 27.01.2015
 *
 * A header file providing a QPoint struct and QGrid typedef.
 * QPoint should be used to hold position of a 3-dimensional
 * point. QGrid should be used to hold multiple double values
 * (like particular coordinate values for multiple points
 * belonging to the same axis).
 */

#ifndef GRIDDIFF_QOBJ_H
#define GRIDDIFF_QOBJ_H

#include <vector>  /* std::vector */

namespace GridDiff
{


typedef struct
{
    double q1, q2, q3;
} QPoint;

typedef std::vector<double> QGrid;


} /* namespace GridDiff */

#endif /* GRIDDIFF_QOBJ_H */
