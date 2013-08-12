/*
 * ServerConnection.h
 *
 *  Created on: 11 août 2013
 *      Author: Eka Chan
 */

#ifndef SERVERCONNECTION_H_
#define SERVERCONNECTION_H_

#include <curl/curl.h>
#include <bps/netstatus.h>
#include <fstream>
#include <sstream>
#include <iostream>

class ServerConnection {
public:
	ServerConnection();
	virtual ~ServerConnection();

	bool init(bool bInit);
	CURLcode doHttpPost(const std::string& url, std::ostream& os, long timeout);
	CURLcode doHttpGet (const char * url, std::ostream& os, long timeout);
	CURLcode doHttpPut (const std::string& url, long timeout);

private:
	CURL * m_curl_handle;
};

#endif /* SERVERCONNECTION_H_ */
