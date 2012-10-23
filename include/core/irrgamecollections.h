/*
 * collections.h
 *
 *  Created on: Aug 14, 2012
 *      Author: gregorytkach
 */

#ifndef COLLECTIONS_H_
#define COLLECTIONS_H_

//! Interfaces
#include "core/collections/ICollection.h"
#include "core/collections/ILeafNode.h"

#include "core/collections/array.h"
#include "core/collections/list/list.h"
#include "core/collections/map/map.h"
#include "core/collections/string.h"

//! array typedefs
typedef irrgame::core::array<s32> arrayi;
typedef irrgame::core::array<u32> arrayu;
typedef irrgame::core::array<f32> arrayf;
typedef irrgame::core::array<irrgame::core::string> arraystr;

//! list typedefs
typedef irrgame::core::list<s32> listi;
typedef irrgame::core::list<u32> listu;
typedef irrgame::core::list<f32> listf;
typedef irrgame::core::list<irrgame::core::string> liststr;

//! map typedefs
typedef irrgame::core::map<s32, s32> DictIntInt;

//! string typedef
typedef irrgame::core::string stringc;

#endif /* COLLECTIONS_H_ */
