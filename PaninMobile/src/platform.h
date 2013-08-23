/*
 * platform.h
 *
 *  Created on: 28 juil. 2013
 *      Author: Eka Chan
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <scoreloop/sc_client.h>
#include <scoreloop/sc_init.h>

#include <screen/screen.h>

#include <sqlite3.h>

#include <vector>
#include <string>

#include <time.h>

#include "DateTime.h"
#include "ServerConnection.h"

namespace paninMobile {


class PlatformEventHandler {
public:

    virtual void onLeftPress(float x, float y) = 0;

    virtual void onLeftRelease(float x, float y) = 0;

    virtual void onExit() = 0;

    virtual void onKeyPressed(int c) = 0;

    //virtual void onPause() = 0;

    //virtual void onResume() = 0;

   // virtual void onSubmitScore() = 0;

    //virtual void onUserReady(const std::string& userName, bool isAnonymous, const std::string& errorString) = 0;

    virtual void onPromptOk(const std::string& userInput) = 0;

protected:
    ~PlatformEventHandler() {};
};

class platform {
public:
	platform();
	virtual ~platform();

	bool init();

	PlatformEventHandler* setEventHandler(PlatformEventHandler* handler);

	void processEvents();

	void beginRender();

	void finishRender();

	void getSize(float& width, float& height) const;

	int getDPI() const;

	time_t getCurrentTime() const;

	void displayPrompt(const std::string& prompt);

	char* getDate();

	char* getTime();

	char* ambilBulan(int bulanke);

	char* getDateTime();

	ServerConnection * m_serverConnection;

	std::string user_name;
	std::string user_pw;

	std::string server1;
	std::string server2;

private:

	SC_InitData_t m_scoreloopInitData;
	PlatformEventHandler* m_handler;
	screen_context_t m_screenContext;
	const char* m_username;
	const char* m_password;
	bool m_promptInProgress;
	bool m_buttonPressed;
	bool m_keyboard_visible;

	DateTime * m_DateTime;

};

} /* namespace paninMobile */
#endif /* PLATFORM_H_ */
