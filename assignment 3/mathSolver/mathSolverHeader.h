/*-------------------------------------------------------------------------*
 *---									---*
 *---		mathSolverHeader.h					---*
 *---									---*
 *---	    This file defines constants and includes other files 	---*
 *---	necessary for the math generator and solver program.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2019 May 6		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	<cstdlib>
#include	<cstdio>
#include	<cstring>
#include	<string>
#include	<iostream>
#include	<sstream>
#include	<pthread.h>
#include	<unistd.h>


//  PURPOSE:  To tell the maximum value that a tree can have.
const int	MAX_VALUE		= 64;


//  PURPOSE:  To tell how many problems to do.
const int	NUM_PROBLEMS		= 4096;


#include	"Node.h"
#include	"NodeBuffer.h"
