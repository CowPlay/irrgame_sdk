/*
 * collections.h
 *
 *  Created on: Aug 14, 2012
 *      Author: gregorytkach
 */

#ifndef COLLECTIONS_H_
#define COLLECTIONS_H_

#include "core/base/irrgameTypes.h"
#include "core/collections/irrArray.h"
#include "core/collections/irrList.h"
#include "core/collections/irrMap.h"
#include "core/collections/irrString.h"

//! array typedefs
typedef irrgame::core::array<s32> arrayi;
typedef irrgame::core::array<u32> arrayu;
typedef irrgame::core::array<f32> arrayf;
typedef irrgame::core::array< irrgame::core::string<c8> > arraystr;

//! map typedefs
typedef irrgame::core::map<s32, s32> DictIntInt;

//! string typedefs
typedef irrgame::core::string<c8> stringc;

#endif /* COLLECTIONS_H_ */
