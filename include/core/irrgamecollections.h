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
#include "core/collections/list/list.h"
#include "core/collections/map/map.h"
#include "core/collections/irrString.h"

//! Threadsafe collections
#include "core/collections/threadsafe/irrarraysafe.h"
#include "core/collections/threadsafe/irrlistsafe.h"
#include "core/collections/threadsafe/irrmapsafe.h"

//! array typedefs
typedef irrgame::core::array<s32> arrayi;
typedef irrgame::core::array<u32> arrayu;
typedef irrgame::core::array<f32> arrayf;
typedef irrgame::core::array<irrgame::core::string<c8> > arraystr;

//! threadsafe array typedefs
typedef irrgame::core::arraysafe<s32> arrsafei;
typedef irrgame::core::arraysafe<u32> arrsafeu;
typedef irrgame::core::arraysafe<f32> arrsafef;
typedef irrgame::core::arraysafe<irrgame::core::string<c8> > arrsafestr;

//! map typedefs
typedef irrgame::core::map<s32, s32> DictIntInt;

//! string typedefs
typedef irrgame::core::string<c8> stringc;

#endif /* COLLECTIONS_H_ */