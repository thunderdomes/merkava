/*
 * ServerConnection.cpp
 *
 *  Created on: 11 août 2013
 *      Author: Eka Chan
 */

#include "ServerConnection.h"


static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	if(stream)
	{
		std::ostream& os = *static_cast<std::ostream*>(stream);
		std::streamsize len = size * nmemb;
		if(os.write(static_cast<char*>(ptr), len))
			return len;
	}

	return 0;
}

ServerConnection::ServerConnection()
	: m_curl_handle(NULL)
{
	// TODO Auto-generated constructor stub
//    curl_global_init(CURL_GLOBAL_ALL);
//    m_curl_handle = curl_easy_init();
}

ServerConnection::~ServerConnection() {
	// TODO Auto-generated destructor stub
//	if (m_curl_handle != NULL)
//	{
//		curl_easy_cleanup(m_curl_handle);
//		m_curl_handle = NULL;
//	}
}

bool ServerConnection::init(bool bInit)
{
	if (bInit)
	{
		if (m_curl_handle == NULL)
		{
		    curl_global_init(CURL_GLOBAL_ALL);
		    m_curl_handle = curl_easy_init();

		    if (m_curl_handle == NULL)
		    	return false;
		}
	}
	else
	{
		if (m_curl_handle != NULL)
		{
			curl_easy_cleanup(m_curl_handle);
		}
	}

	return true;
}

CURLcode ServerConnection::doHttpPost(const std::string& url, std::ostream& os, long timeout = 30)
{
	CURLcode code(CURLE_FAILED_INIT);

	if (m_curl_handle == NULL)
	{
		if (init(true) == false)
		{
			return code;
		}
	}


	return code;
}

CURLcode ServerConnection::doHttpGet(const char * url, std::ostream& os, long timeout = 30.0f)
{
	CURLcode code(CURLE_FAILED_INIT);

	if (m_curl_handle == NULL)
	{
		if (init(true) == false)
		{
			return code;
		}
	}

//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, &write_data)))
//			fprintf(stderr, "error at CURLOPT_WRITEFUNCTION.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, &stream)))
//			fprintf(stderr, "error at CURLOPT_WRITEDATA.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_NOPROGRESS, 1L)))
//			fprintf(stderr, "error at CURLOPT_NOPROGRESS.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_FOLLOWLOCATION, 1L)))
//			fprintf(stderr, "error at CURLOPT_FOLLOWLOCATION.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_FILE, &os)))
//			fprintf(stderr, "error at CURLOPT_FILE.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_TIMEOUT, timeout)))
//			fprintf(stderr, "error at CURLOPT_TIMEOUT.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_URL, url)))
//			fprintf(stderr, "error at CURLOPT_URL.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_COOKIEFILE, "")))
//			fprintf(stderr, "error at CURLOPT_COOKIEFILE.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_VERBOSE, 1L)))
//			fprintf(stderr, "error at CURLOPT_VERBOSE.\n");
//	code = curl_easy_perform(m_curl_handle);

	if(CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, &write_data))
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, &stream))
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_NOPROGRESS, 1L))
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_FOLLOWLOCATION, 1L))
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_FILE, &os))
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_TIMEOUT, timeout))
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_URL, url))
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_COOKIEFILE, ""))
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_VERBOSE, 1L))
	//&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEHEADER, headerfile))
	)
	{
		code = curl_easy_perform(m_curl_handle);
	}

	init(false);

	return code;
}

CURLcode ServerConnection::doHttpPut(const std::string& url, long timeout = 30)
{
	CURLcode code(CURLE_FAILED_INIT);

	if (m_curl_handle == NULL)
	{
		if (init(true) == false)
		{
			return code;
		}
	}


	return code;
}
