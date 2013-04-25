// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#include <cstdlib> // C++ standard definitions
#include <iostream> // I/O stream

// include files are in a slightly different location for MacOS
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "World.h" // world object definitions
#include "TopDownView.h"
#include "ThirdPerson.h"
#include "FirstPerson.h"