/*
 * platform.cpp
 *
 *  Created on: 28 juil. 2013
 *      Author: Eka Chan
 */

#include "platform.h"
#include "bbutil.h"

#include <sqlite3.h>

#include <bps/bps.h>
#include <bps/dialog.h>
#include <bps/event.h>
#include <bps/navigator.h>
#include <bps/screen.h>

#include <sys/stat.h>

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef NDEBUG
#include <assert.h>
#define ASSERT(a) (assert(a))
#else
#define ASSERT(a)
#endif


namespace paninMobile {

platform::platform()
	: m_handler(NULL),
	  m_screenContext(NULL),
	  m_username(NULL),
	  m_password(NULL)
{
	// TODO Auto-generated constructor stub
	bps_initialize();

	screen_create_context(&m_screenContext, 0);

	screen_request_events(m_screenContext);
	navigator_request_events(0);
	dialog_request_events(0);

	// Lock in landscape mode.
	navigator_rotation_lock(true);
	bbutil_init_egl(m_screenContext);
}

platform::~platform() {
	// TODO Auto-generated destructor stub
	bbutil_terminate();
	screen_stop_events(m_screenContext);
	screen_destroy_context(m_screenContext);
	bps_shutdown();
}

bool platform::init() {

	return true;
}

void platform::processEvents() {
    ASSERT(m_handler);

    while (true) {
        bps_event_t* event = NULL;
        int rc = bps_get_event(&event, 0);

        ASSERT(BPS_SUCCESS == rc);
        if (rc != BPS_SUCCESS) {
            fprintf(stderr, "BPS error getting an event: %d\n", errno);
            break;
        }

        if (event == NULL) {
            // No more events in the queue
            break;
        }

        // Give Scoreloop the first shot at handling the event
        // (for callbacks)
        //if (SC_HandleBPSEvent(&m_scoreloopInitData, event) == BPS_SUCCESS) {
        //    continue;
        //}

        // Not a ScoreLoopCore event, continue processing...
        int domain = bps_event_get_domain(event);
        int code = bps_event_get_code(event);
        if (navigator_get_domain() == domain) {
            switch(code) {
            case NAVIGATOR_EXIT:
                m_handler->onExit();
                break;
            case NAVIGATOR_WINDOW_INACTIVE:
//                m_isPaused = true;
//                m_handler->onPause();
                break;
            case NAVIGATOR_WINDOW_ACTIVE:
//                if (m_isPaused) {
//                    m_handler->onResume();
//                    m_isPaused = false;
//                }
                break;
            }
        } else if (screen_get_domain() == domain) {
            screen_event_t screenEvent = screen_event_get_event(event);
            int screenEventType;
            int screenEventPosition[2];

            screen_get_event_property_iv(screenEvent, SCREEN_PROPERTY_TYPE, &screenEventType);
            screen_get_event_property_iv(screenEvent, SCREEN_PROPERTY_SOURCE_POSITION, screenEventPosition);

            if (screenEventType == SCREEN_EVENT_MTOUCH_TOUCH) {
                m_handler->onLeftPress(static_cast<float>(screenEventPosition[0]), static_cast<float>(screenEventPosition[1]));
            } else if (screenEventType == SCREEN_EVENT_MTOUCH_RELEASE) {
                m_handler->onLeftRelease(static_cast<float>(screenEventPosition[0]), static_cast<float>(screenEventPosition[1]));
            } else if (screenEventType == SCREEN_EVENT_POINTER) {
                int pointerButton;
                screen_get_event_property_iv(screenEvent, SCREEN_PROPERTY_BUTTONS, &pointerButton);

                if (pointerButton == SCREEN_LEFT_MOUSE_BUTTON) {
                    ASSERT(!m_buttonPressed);
                    m_buttonPressed = true;
                    m_handler->onLeftPress(static_cast<float>(screenEventPosition[0]), static_cast<float>(screenEventPosition[1]));
                } else if (m_buttonPressed) {
                    m_handler->onLeftRelease(static_cast<float>(screenEventPosition[0]), static_cast<float>(screenEventPosition[1]));
                    m_buttonPressed = false;
                }
            }
        } else if (dialog_get_domain() == domain) {
            if (DIALOG_RESPONSE == code) {
                ASSERT(m_promptInProgress);
                m_promptInProgress = false;
                m_handler->onPromptOk(dialog_event_get_prompt_input_field(event));
            }
        } else {
            fprintf(stderr, "Unrecognized and unrequested event! domain: %d, code: %d\n", domain, code);
        }
    }
}

void platform::beginRender() {
    // TODO
}

void platform::finishRender() {
    bbutil_swap();
}

int platform::getDPI() const {
    return bbutil_calculate_dpi(m_screenContext);
}

void platform::getSize(float& width, float& height) const {
    EGLint surfaceWidth = 0;
    EGLint surfaceHeight = 0;

    eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surfaceWidth);
    eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surfaceHeight);

    EGLint rc = eglGetError();

    if (rc != 0x3000) {
        fprintf(stderr, "Unable to query egl surface dimensions: %d\n", rc);
    }

    width = static_cast<float>(surfaceWidth);
    height = static_cast<float>(surfaceHeight);
}

time_t platform::getCurrentTime() const {
    return time(NULL);
}

char* platform::getDate()
{
	//char * mytanggal = new char [20];
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

char* platform::getTime()
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

char* platform::ambilBulan(int bulanke)
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

char* platform::getDateTime()
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

void platform::displayPrompt(const std::string& prompt) {
    if (m_promptInProgress) {
        fprintf(stderr, "There's already a dialog prompt being displayed!\n");
        ASSERT(!"Prompt already displayed");
        return;
    }
    dialog_instance_t displayNamePrompt;
    dialog_create_prompt(&displayNamePrompt);

    dialog_set_prompt_message_text(displayNamePrompt, prompt.c_str());
    dialog_add_button(displayNamePrompt, DIALOG_OK_LABEL, true, NULL, true);
    dialog_set_default_button_index(displayNamePrompt, 0);
    dialog_show(displayNamePrompt);

    m_promptInProgress = true;
}

PlatformEventHandler* platform::setEventHandler(PlatformEventHandler* handler) {
    PlatformEventHandler* oldHandler = m_handler;
    if (handler) {
        m_handler = handler;
    } else {
        fprintf(stderr, "Attempt to set event handler to NULL\n");
        ASSERT(!"Should not set the event handler to NULL");
    }

    return oldHandler;
}

} /* namespace paninMobile */
