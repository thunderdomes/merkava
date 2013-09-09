/*
 * ServerConnection.cpp
 *
 *  Created on: 11 ao�t 2013
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

static size_t write_login(void *ptr, size_t size, size_t nmemb, void *stream)
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

static void
print_cookies(CURL *curl)
{
  CURLcode res;
  struct curl_slist *cookies;
  struct curl_slist *nc;
  int i;

  printf("Cookies, curl knows:\n");
  res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
  if (res != CURLE_OK) {
    fprintf(stderr, "Curl curl_easy_getinfo failed: %s\n", curl_easy_strerror(res));
    //exit(1);
  }
  nc = cookies, i = 1;
  while (nc) {
    printf("[%d]: %s\n", i, nc->data);
    nc = nc->next;
    i++;
  }
  if (i == 1) {
    printf("(none)\n");
  }
  curl_slist_free_all(cookies);
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

CURLcode ServerConnection::doLogin(const char * url, std::ostream& os, long timeout = 30.0f)
{
	fprintf(stderr, "coba login.\n");
	CURLcode code(CURLE_FAILED_INIT);

	if (m_curl_handle == NULL)
	{
		if (init(true) == false)
		{
			return code;
		}
	}

	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, &write_data)))
			fprintf(stderr, "error at CURLOPT_WRITEFUNCTION.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, &stream)))
//			fprintf(stderr, "error at CURLOPT_WRITEDATA.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_NOPROGRESS, 1L)))
			fprintf(stderr, "error at CURLOPT_NOPROGRESS.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_FOLLOWLOCATION, 1L)))
//			fprintf(stderr, "error at CURLOPT_FOLLOWLOCATION.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_FILE, &os)))
			fprintf(stderr, "error at CURLOPT_FILE.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_TIMEOUT, timeout)))
			fprintf(stderr, "error at CURLOPT_TIMEOUT.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_URL, url)))
			fprintf(stderr, "error at CURLOPT_URL.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_COOKIEFILE, "")))
			fprintf(stderr, "error at CURLOPT_COOKIEFILE.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_VERBOSE, 1L)))
			fprintf(stderr, "error at CURLOPT_VERBOSE.\n");

	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_SSL_VERIFYPEER, 0L)))
			fprintf(stderr, "error at CURLOPT_VERBOSE.\n");

	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_SSL_VERIFYHOST, 0L)))
			fprintf(stderr, "error at CURLOPT_VERBOSE.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_CERTINFO, 1L)))
			fprintf(stderr, "error at CURLOPT_VERBOSE.\n");


	code = curl_easy_perform(m_curl_handle);

	print_cookies(m_curl_handle);

//	if(CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, &write_login))
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, &stream_login))
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_NOPROGRESS, 1L))
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_FOLLOWLOCATION, 1L))
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_FILE, &os))
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_TIMEOUT, timeout))
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_URL, url))
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_COOKIEFILE, ""))
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_VERBOSE, 1L))
//
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_SSL_VERIFYPEER, 1L))
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_SSL_VERIFYHOST, 1L))
//	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_CERTINFO, 1L))
//	//&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEHEADER, headerfile))
//	)
//	{
//		code = curl_easy_perform(m_curl_handle);
//	}

	init(false);

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
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_SSL_VERIFYPEER, 1L))
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_SSL_VERIFYHOST, 1L))
	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_CERTINFO, 1L))
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
