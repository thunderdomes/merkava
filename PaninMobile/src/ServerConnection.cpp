/*
 * ServerConnection.cpp
 *
 *  Created on: 11 août 2013
 *      Author: Eka Chan
 */

#include "ServerConnection.h"



typedef int size_type;

//template<typename T>
//
//std::vector<T> split(const T & str, const T & delimiters) {
//    std::vector<T> v;
//    int start = 0;
//    int pos = str.find_first_of(delimiters, start);
//    while(pos != T::npos) {
//        if(pos != start) // ignore empty tokens
//            v.emplace_back(str, start, pos - start);
//        start = pos + 1;
//        pos = str.find_first_of(delimiters, start);
//    }
//    if(start < str.length()) // ignore trailing delimiter
//        v.emplace_back(str, start, str.length() - start); // add what's left of the string
//    return v;
//}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	if(stream)
	{
		std::ostream& os = *static_cast<std::ostream*>(stream);
		std::ostringstream& os1 = *static_cast<std::ostringstream*>(stream);
		std::streamsize len = size * nmemb;
		if(os.write(static_cast<char*>(ptr), len))
			return len;
	}

	return 0;
}

//static size_t write_login(void *ptr, size_t size, size_t nmemb, void *stream)
//{
//	if(stream)
//	{
//		std::ostream& os = *static_cast<std::ostream*>(stream);
//		std::streamsize len = size * nmemb;
//		if(os.write(static_cast<char*>(ptr), len))
//			return len;
//	}
//
//	return 0;
//}

//static size_t write_dataRT(void *ptr, size_t size, size_t nmemb, void *stream)
//{
//	if(stream)
//	{
//		std::ostream& os = *static_cast<std::ostream*>(stream);
//		std::streamsize len = size * nmemb;
//		if(os.write(static_cast<char*>(ptr), len))
//			return len;
//	}
//
//	return 0;
//}

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
    fprintf(stderr, "eka [%d]: %s\n", i, nc->data);
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
	sCookies = new char[1024];
	init(true);
}

ServerConnection::~ServerConnection() {
	// TODO Auto-generated destructor stub
//	if (m_curl_handle != NULL)
//	{
//		curl_easy_cleanup(m_curl_handle);
//		m_curl_handle = NULL;
//	}

	delete sCookies;
	init(false);
}

bool ServerConnection::init(bool bInit)
{
	if (bInit)
	{
		curl_global_init(CURL_GLOBAL_ALL);
		m_curl_handle = curl_easy_init();

		if (m_curl_handle == NULL)
			return false;
	}
	else
	{
		curl_easy_cleanup(m_curl_handle);
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
		fprintf(stderr, "m_curl_handle == NULL -- login.\n");
		if (init(true) == false)
		{
			if (init(true) == false)
			{
				return code;
			}
		}
	}

	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, &write_data)))
			fprintf(stderr, "error at CURLOPT_WRITEFUNCTION.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, &stream)))
			fprintf(stderr, "error at CURLOPT_WRITEDATA.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_NOPROGRESS, 1L)))
			fprintf(stderr, "error at CURLOPT_NOPROGRESS.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_FOLLOWLOCATION, 1L)))
			fprintf(stderr, "error at CURLOPT_FOLLOWLOCATION.\n");
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

	curl_easy_getinfo(m_curl_handle, CURLINFO_COOKIELIST, &cookies);

	std::string myCookie = cookies->data;
	vCookies = split(myCookie, '\t');
	std::memset(sCookies, 0, 1024 *sizeof(char));
	std::strcpy(sCookies, vCookies.at(vCookies.size() -2).c_str());
	std::strcat(sCookies, "=");
	std::strcat(sCookies, vCookies.at(vCookies.size() -1).c_str());
	fprintf(stderr, "eka cookies1...... %s.\n", sCookies);
//	for (std::vector<std::string>::iterator iter = vCookies.begin(); iter != vCookies.end(); ++iter)
//	{
//		fprintf(stderr, "cookies.... *%s*\n", (*iter).c_str());
//	}
	init(false);

	return code;

}

CURLcode ServerConnection::doHttpGet2 (const char * url, std::ostream& os, long timeout)
{
	CURLcode code(CURLE_FAILED_INIT);

	init(true);

	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, &write_data)))
			fprintf(stderr, "error at CURLOPT_WRITEFUNCTION.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, &stream)))
			fprintf(stderr, "error at CURLOPT_WRITEDATA.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_HTTPGET, 1L)))
			fprintf(stderr, "error at CURLOPT_HTTPGET.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_NOPROGRESS, 1L)))
			fprintf(stderr, "error at CURLOPT_NOPROGRESS.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_FOLLOWLOCATION, 1L)))
			fprintf(stderr, "error at CURLOPT_FOLLOWLOCATION.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_FILE, &os)))
			fprintf(stderr, "error at CURLOPT_FILE.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_TIMEOUT, timeout)))
			fprintf(stderr, "error at CURLOPT_TIMEOUT.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_URL, url)))
			fprintf(stderr, "error at CURLOPT_URL.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_COOKIEFILE, "")))
			fprintf(stderr, "error at CURLOPT_COOKIEFILE.\n");
	if (CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_COOKIE, sCookies)))
		fprintf(stderr, "error at CURLOPT_COOKIE.\n");
	if (CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_COOKIELIST, sCookies)))
		fprintf(stderr, "error at CURLOPT_COOKIE.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_VERBOSE, 1L)))
			fprintf(stderr, "error at CURLOPT_VERBOSE.\n");

	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_SSL_VERIFYPEER, 0L)))
			fprintf(stderr, "error at CURLOPT_SSL_VERIFYPEER.\n");

	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_SSL_VERIFYHOST, 0L)))
			fprintf(stderr, "error at CURLOPT_SSL_VERIFYHOST.\n");
	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_CERTINFO, 1L)))
			fprintf(stderr, "error at CURLOPT_CERTINFO.\n");


	if (CURLE_OK != (code = curl_easy_perform(m_curl_handle)))
		fprintf(stderr, "error at curl_easy_perform.\n");

	init(false);
	//curl_easy_cleanup(m_curl_handle);
	return code;
}

//CURLcode ServerConnection::doRTStart(const char * url, std::ostream& os, long timeout)
//{
//	CURLcode code(CURLE_FAILED_INIT);
//
//	fprintf(stderr, "periksa 1.\n");
////	if (m_curl_handle == NULL)
////	{
////		fprintf(stderr, "m_curl_handle == NULL.\n");
////		if (init(true) == false)
////		{
////			return code;
////		}
////	}
//
//	curl_global_init(CURL_GLOBAL_ALL);
//	m_curl_handle = curl_easy_init();
//
//	fprintf(stderr, "periksa 2.\n");
////	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, &write_dataRT)))
////			fprintf(stderr, "error at CURLOPT_WRITEFUNCTION.\n");
////	fprintf(stderr, "periksa 2-1.\n");
////	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, &stream_RT)))
////			fprintf(stderr, "error at CURLOPT_WRITEDATA.\n");
////	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_NOPROGRESS, 1L)))
////			fprintf(stderr, "error at CURLOPT_NOPROGRESS.\n");
////	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_FOLLOWLOCATION, 1L)))
////			fprintf(stderr, "error at CURLOPT_FOLLOWLOCATION.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_FILE, &os)))
//			fprintf(stderr, "error at CURLOPT_FILE.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_TIMEOUT, timeout)))
//			fprintf(stderr, "error at CURLOPT_TIMEOUT.\n");
//	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_URL, url)))
//			fprintf(stderr, "error at CURLOPT_URL.\n");
////	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_COOKIEFILE, "")))
////			fprintf(stderr, "error at CURLOPT_COOKIEFILE.\n");
////	if(CURLE_OK != (code = curl_easy_setopt(m_curl_handle, CURLOPT_VERBOSE, 1L)))
////			fprintf(stderr, "error at CURLOPT_VERBOSE.\n");
//	code = curl_easy_perform(m_curl_handle);
//
////	if(CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, &write_dataRT))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, &stream_RT))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_NOPROGRESS, 1L))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_FOLLOWLOCATION, 1L))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_FILE, &os))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_TIMEOUT, timeout))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_URL, url))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_COOKIEFILE, ""))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_VERBOSE, 1L))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_SSL_VERIFYPEER, 1L))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_SSL_VERIFYHOST, 1L))
////	&& CURLE_OK == (code = curl_easy_setopt(m_curl_handle, CURLOPT_CERTINFO, 1L))
////	)
////	{
////		fprintf(stderr, "periksa 3.\n");
////		code = curl_easy_perform(m_curl_handle);
////	}
//
//	fprintf(stderr, "periksa 4.\n");
//	init(false);
//
//	fprintf(stderr, "periksa 5.\n");
//	return code;
//}


CURLcode ServerConnection::doHttpGet(const char * url, std::ostream& os, long timeout = 30.0f)
{
	CURLcode code(CURLE_FAILED_INIT);

	if (init(true) == false)
	{
		return code;
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
		print_cookies(m_curl_handle);

		// ambil cookies
		CURLcode res;
		struct curl_slist *cookies;
		res = curl_easy_getinfo(m_curl_handle, CURLINFO_COOKIELIST, &cookies);
		if (res == CURLE_OK)
		{
			std::string sCookie = cookies->data;
			vCookies = split(sCookie, '\t');
//			for (std::vector<std::string>::iterator iter = vCookies.begin(); iter != vCookies.end(); iter++)
//			{
//				fprintf (stderr, "cookies : %s", *iter);
//			}
		}
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
