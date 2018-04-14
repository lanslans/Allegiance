//////////////////////////////////////////////////////////////////////////////
//
// PCH.H
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _PCH_H_
#define _PCH_H_

// __MODULE__ is used by ZAssert
#define __MODULE__ "Cadet"

//////////////////////////////////////////////////////////////////////////////
//
// Disable some warnings
//
//////////////////////////////////////////////////////////////////////////////

// conversion from 'float' to 'int', possible loss of data
//#pragma warning(disable : 4244)

// 'this' : used in base member initializer list
#pragma warning(disable : 4355)

// identifier was truncated to '255' characters in the debug information
#pragma warning(disable : 4786)


//////////////////////////////////////////////////////////////////////////////
//
// The include files
//
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "windows.h"
#include "zlib.h"
#include "engine.h"
#include "effect.h"
#include "utility.h"
#include "igc.h"
#include "drones.h"

#include "sound.h"
#include "joystick.h"

#include "gamecore.h"
#include "mission.h"
#include "cadetplay.h"
#include "cadet.h"
#include "cadetradar.h"


#endif