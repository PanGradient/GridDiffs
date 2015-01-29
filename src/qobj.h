/*
 * File: qobj.h
 * Author(s): P Kuszaj
 * Last changed: 29.01.2015
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


struct QPoint
{
    double q1, q2, q3;

    QPoint(double Q1=0.0, double Q2=0.0, double Q3=0.0)
        : q1(Q1), q2(Q2), q3(Q3) { }

    QPoint& operator= (const QPoint& q)
    {
        if (this != &q){
            q1 = q.q1;
            q2 = q.q2;
            q3 = q.q3;
        }
        return *this;
    }

    bool operator== (const QPoint& q)
    {
        return (q1 == q.q1 &&
                q2 == q.q2 &&
                q3 == q.q3);
    }
};

typedef std::vector<double> QGrid;


} /* namespace GridDiff */

#endif /* GRIDDIFF_QOBJ_H */
