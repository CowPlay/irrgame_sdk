/*
 * constants.h
 *
 *  Created on: Sep 14, 2012
 *      Author: gregorytkach
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "core/base/baseTypes.h"

//! Player config

#define XML_TAG_CONFIG 					"config"
#define XML_TAG_APPLICATION 			"application"
#define XML_TAG_ATTRIBUTES				"attributes"

#define XML_ATTR_APP_FILE				"app_file"
#define XML_ATTR_APP_CREATOR			"app_creator"

//Use in collections
const s32 IrrNotFound = -1;

//! Maximum number of texture an SMaterial can have, up to 8 are supported by Irrlicht.
const  u32 MaterialMaxTextures = 4;

#endif /* CONSTANTS_H_ */
