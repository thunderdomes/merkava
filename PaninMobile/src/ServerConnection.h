/*
 * ServerConnection.h
 *
 *  Created on: 11 ao�t 2013
 *      Author: Eka Chan
 */

#ifndef SERVERCONNECTION_H_
#define SERVERCONNECTION_H_

#include <curl/curl.h>
#include <bps/netstatus.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

class ServerConnection {
public:
	ServerConnection();
	virtual ~ServerConnection();

	bool init(bool bInit);
	CURLcode doLogin(const char * url, std::ostream& os, long timeout);
	CURLcode doHttpGet2 (const char * url, std::ostream& os, long timeout);
//	CURLcode doRTStart(const char * url, std::ostream& os, long timeout);
	CURLcode doHttpPost(const std::string& url, std::ostream& os, long timeout);
	CURLcode doHttpGet (const char * url, std::ostream& os, long timeout);
	CURLcode doHttpPut (const std::string& url, long timeout);

private:
	CURL * m_curl_handle;

	std::ostringstream stream;
	std::ostringstream stream_login;
	std::ostringstream stream_RT;

	std::vector<std::string> vCookies;

	struct curl_slist *cookies;
	char * sCookies;

};

#endif /* SERVERCONNECTION_H_ */
