/*
 * irrgameshapes.h
 *
 *  Created on: Aug 22, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMESHAPES_H_
#define IRRGAMESHAPES_H_

#include "core/shapes/aabbox3d.h"
#include "core/shapes/dimension2d.h"
#include "core/shapes/line2d.h"
#include "core/shapes/line3d.h"
#include "core/shapes/plane3d.h"
#include "core/shapes/rect.h"
#include "core/shapes/triangle3d.h"
#include "core/shapes/vector2d.h"
#include "core/shapes/vector3d.h"

//! Typedefs for aabbox3d
typedef irrgame::core::aabbox3d<f32> aabbox3df;
typedef irrgame::core::aabbox3d<s32> aabbox3di;

//! Typedefs for dimension2d
typedef irrgame::core::dimension2d<u32> dimension2du;
/** There are few cases where negative dimensions make sense. Please consider using
 dimension2du instead. */
typedef irrgame::core::dimension2d<s32> dimension2di;
typedef irrgame::core::dimension2d<f32> dimension2df;

//! Typedefs for line2d
typedef irrgame::core::line2d<f32> line2df;
typedef irrgame::core::line2d<s32> line2di;

//! Typedefs for line3d
typedef irrgame::core::line3d<f32> line3df;
typedef irrgame::core::line3d<s32> line3di;

//! Typedefs for plane3d
typedef irrgame::core::plane3d<f32> plane3df;
typedef irrgame::core::plane3d<s32> plane3di;

//! Typedefs for rect
typedef irrgame::core::rect<f32> rectf;
typedef irrgame::core::rect<s32> recti;

//! Typedefs for triangle3d
typedef irrgame::core::triangle3d<f32> triangle3df;
typedef irrgame::core::triangle3d<s32> triangle3di;

//! Typedefs for vector2d
typedef irrgame::core::vector2d<f32> vector2df;
typedef irrgame::core::vector2d<s32> vector2di;

//! Typedefs for vector3d
typedef irrgame::core::vector3d<f32> vector3df;
typedef irrgame::core::vector3d<s32> vector3di;

#endif /* IRRGAMESHAPES_H_ */
