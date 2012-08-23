/*
 * irrgame.h
 *
 *  Created on: Jul 24, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAME_H_
#define IRRGAME_H_

#include "irrgameApp.h"
#include "irrgamePlayer.h"

//actions
#include "actions/IActionScheduler.h"

//core
#include "core/irrgamebase.h"
#include "core/irrgamecollections.h"
#include "core/irrgamemath.h"
#include "core/irrgameshapes.h"

//io
#include "io/ioutil.h"
#include "io/IFileSystem.h"
#include "io/IReadFile.h"
#include "io/IWriteFile.h"
#include "io/SPath.h"

#include "io/xml/IXMLReader.h"
#include "io/xml/IXMLWriter.h"

#include "io/config/IConfigReader.h"
#include "io/config/IPlayerConfigReader.h"

//logic
//#include "IGameObject.h"

//threads

#include "threads/irrgameMonitor.h"
#include "threads/irrgameThread.h"

//video

#endif /* IRRGAME_H_ */
