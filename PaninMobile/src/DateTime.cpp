/*
 * DateTime.cpp
 *
 *  Created on: 4 août 2013
 *      Author: Eka Chan
 */

#include "DateTime.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

DateTime::DateTime() {
	// TODO Auto-generated constructor stub

}

DateTime::~DateTime() {
	// TODO Auto-generated destructor stub
}

char* DateTime::getDate()
{
	char * hari = new char[3];
	const char* bulan;
	char * tahun = new char[5];

	char * tanggal = new char[20];
	char * hasil ;

	tm *lokal;
	const time_t k_time = time(NULL);
	lokal = localtime(&k_time);

	itoa(lokal->tm_mday, hari, 10);
	bulan = ambilBulan(lokal->tm_mon);
	itoa(lokal->tm_year + 1900, tahun, 10);

	strcpy(tanggal, hari);
	strcat(tanggal, " ");
	strcat(tanggal, bulan);
	strcat(tanggal, " ");
	strcat(tanggal, tahun);

	hasil = tanggal;

	delete(hari);
	delete(tahun);
	delete(tanggal);

	return hasil;
}

char* DateTime::getTime()
{
	char * detik = new char[3];
	char * menit = new char[3];
	char * jam = new char[3];
	char * wkt = new char[10];
	char * waktu;

	tm *lokal;
	const time_t k_time = time(NULL);
	lokal = localtime(&k_time);

	itoa(lokal->tm_sec, detik, 10);
	itoa(lokal->tm_min, menit, 10);
	itoa(lokal->tm_hour, jam, 10);

	strcpy(wkt, jam);
	strcat(wkt, ":");
	if (strlen(menit) == 1)
	{
		strcat(wkt, "0");
	}
	strcat(wkt, menit);
	strcat(wkt, ":");
	if (strlen(detik) == 1)
	{
		strcat(wkt, "0");
	}
	strcat(wkt, detik);

	waktu = wkt;

	delete(detik);
	delete(menit);
	delete(jam);
	delete(wkt);

	return waktu;
}

char* DateTime::ambilBulan(int bulanke)
{
	char* namaBulan;
	switch(bulanke)
	{
		case 0: namaBulan = "January"; break;
		case 1: namaBulan = "February"; break;
		case 2: namaBulan = "March"; break;
		case 3: namaBulan = "April"; break;
		case 4: namaBulan = "May"; break;
		case 5: namaBulan = "June"; break;
		case 6: namaBulan = "July"; break;
		case 7: namaBulan = "August"; break;
		case 8: namaBulan = "September"; break;
		case 9: namaBulan = "October"; break;
		case 10: namaBulan = "November"; break;
		case 11: namaBulan = "December"; break;
	}
	return namaBulan;
}

char* DateTime::getDateTime()
{
	char* tgl = getDate();
	char* wkt = getTime();

	char* hsl = new char[30];

	char * hasil;

	strcpy(hsl, tgl);
	strcat(hsl, " ");
	strcat(hsl, wkt);

	hasil = hsl;

	delete (hsl);

	return hasil;
}

