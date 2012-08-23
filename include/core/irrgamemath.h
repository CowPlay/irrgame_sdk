/*
 * irrgamemath.h
 *
 *  Created on: Aug 22, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMEMATH_H_
#define IRRGAMEMATH_H_

#include "core/math/fast_atof.h"
#include "core/math/heapsort.h"
#include "core/math/irrMath.h"
#include "core/math/matrix4.h"
#include "core/math/quaternion.h"

//! Typedef for matrix
typedef irrgame::core::CMatrix4<f32> matrix4;
//! global const identity matrix
extern const matrix4 IdentityMatrix;

#endif /* IRRGAMEMATH_H_ */
