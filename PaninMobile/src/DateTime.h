/*
 * DateTime.h
 *
 *  Created on: 4 août 2013
 *      Author: Eka Chan
 */

#ifndef DATETIME_H_
#define DATETIME_H_

#include <time.h>

class DateTime {
public:
	DateTime();
	virtual ~DateTime();
	char* getDate();
	char* getTime();
	char* ambilBulan(int bulanke);
	char* getDateTime();
};

#endif /* DATETIME_H_ */
