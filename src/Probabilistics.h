/*
 * Probabilistics.h
 *
 *  Created on: 22 Sep 2011
 *      Author: thomas, B-Human codebase
 */

#ifndef PROBABILISTICS_H_
#define PROBABILISTICS_H_

#include "Common.h"
#include <math.h>
#include <algorithm>

/** constant for triangular distribution*/
const float sqrt6dividedBy2 = sqrt(6.0f)/2.0f;

/**
 * Returns the probability of a value in a gaussian distribution
 * @param x The value
 * @param s The standard deviation
 * @return The probability density at x
 */
inline float gaussianProbability(float x, float s)
{
    return std::max(1.0f / (s * sqrt2pi) * expf(-0.5f * pow(x / s, 2)), 0.000001f);
}

/**
 * Sampling from a triangular distribution with zero mean and
 * standard deviation b. C.f. "Probabilistic Robotics", Table 5.4
 * @param b The standard deviation
 * @return The sampled value
 */
inline float sampleTriangularDistribution(float b)
{
    float randResult = 2.0f * ((randomFloat() - 0.5f) * b) + 2.0f * ((randomFloat() - 0.5f) * b);
    return sqrt6dividedBy2 * randResult;
}

#endif /* PROBABILISTICS_H_ */
