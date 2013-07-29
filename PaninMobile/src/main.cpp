/*
 * main.cpp
 *
 *  Created on: 28 juil. 2013
 *      Author: Eka Chan
 */


#include "platform.h"
#include "panin.h"

#include <stdlib.h>

using paninMobile::platform;
using paninMobile::panin;

int
main ()
{
	fprintf(stderr, "Mulai.\n");

	platform myPlatform;
	if (!myPlatform.init()) {
		fprintf(stderr, "Could not init platform\n");
		return EXIT_FAILURE;
	}

	fprintf(stderr, "eka tampan.\n");
	panin myPanin(myPlatform);
	//panin myPanin(myPlatform);
	myPanin.run();

	return EXIT_SUCCESS;
}
