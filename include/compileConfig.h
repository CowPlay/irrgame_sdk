/*
 * compileConfig.h
 * Generic config for all platforms
 *  Created on: Sep 14, 2012
 *      Author: gregorytkach
 */

#ifndef COMPILECONFIG_H_
#define COMPILECONFIG_H_

#include "config/compileConfigMacOSX.h"
#include "config/compileConfigWin.h"

/*
 * Constants
 */

#define XML_TAG_CONFIG 					"config"
#define XML_TAG_APPLICATION 			"application"
#define XML_TAG_ATTRIBUTES				"attributes"

#define XML_ATTR_APP_FILE				"app_file"
#define XML_ATTR_APP_CREATOR			"app_creator"

//Use in collections
const s32 IrrNotFound = -1;

//! Maximum number of texture an SMaterial can have, up to 8 are supported by Irrlicht.
const u32 MaterialMaxTextures = 4;

/*
 * creates four CC codes used in Irrlicht for simple ids
 * some compilers can create those by directly writing the
 * code like 'code', but some generate warnings so we use this macro here
 */
#define MAKE_IRR_ID(c0, c1, c2, c3) \
		((u32)(u8)(c0) | ((u32)(u8)(c1) << 8) | \
		((u32)(u8)(c2) << 16) | ((u32)(u8)(c3) << 24 ))

//! threads
#define PRIORITY_LOW	-20
#define PRIORITY_NORMAL	0
#define PRIORITY_HIGH	20

#endif /* COMPILECONFIG_H_ */
