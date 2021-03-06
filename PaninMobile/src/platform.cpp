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
#include <bps/virtualkeyboard.h>

#include <sys/keycodes.h>
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

	// Lock in potrait mode.
	navigator_rotation_lock(true);
	bbutil_init_egl(m_screenContext);
	m_DateTime = new DateTime();
	m_serverConnection = new ServerConnection();

	user_name = "";
	user_pw = "";

	m_orientation = 0;

	// nouvelle: https://202.53.249.2:8443/
	server1 = "https://202.53.249.2:8443";
	server2 = "172.31.2.78:8443";
}

platform::~platform() {
	// TODO Auto-generated destructor stub
	bbutil_terminate();
	delete m_DateTime;
	delete m_serverConnection;
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
            else if (screenEventType == SCREEN_EVENT_KEYBOARD)
            {
                screen_get_event_property_iv(screenEvent, SCREEN_PROPERTY_KEY_FLAGS, &screenEventType);

                if (screenEventType & KEY_DOWN) {
                    screen_get_event_property_iv(screenEvent, SCREEN_PROPERTY_KEY_SYM,&screenEventType);

                    fprintf(stderr, "The '%c' key was pressed\n", (char)screenEventType);

                    //m_handler->onKeyPressed(static_cast<char>(screenEventType));
                    m_handler->onKeyPressed(screenEventType);
                    /*switch (screenEventType) {
                    default:
                        break;
                    }*/
                }
            }
        } else if (dialog_get_domain() == domain) {
            if (DIALOG_RESPONSE == code) {
                ASSERT(m_promptInProgress);
                m_promptInProgress = false;
                m_handler->onPromptOk(dialog_event_get_prompt_input_field(event));
            }
        }
        if (virtualkeyboard_get_domain() == domain) {
            switch (code) {
            case VIRTUALKEYBOARD_EVENT_VISIBLE:
                m_keyboard_visible = true;
                break;
            case VIRTUALKEYBOARD_EVENT_HIDDEN:
                m_keyboard_visible = false;
                break;
            }
        } else {
            //fprintf(stderr, "Unrecognized and unrequested event! domain: %d, code: %d\n", domain, code);
        }
    }
}

void platform::beginRender() {
    // TODO
}

void platform::finishRender() {
    bbutil_swap();
}

void platform::setOrientation(int i)
{

	navigator_rotation_lock(false);
	bps_event_t* event = NULL;
	int rc = bps_get_event(&event, 0);

    ASSERT(BPS_SUCCESS == rc);
    if (rc != BPS_SUCCESS) {
        fprintf(stderr, "BPS error getting an event: %d\n", errno);
        return;
    }

    navigator_request_events(0);
    navigator_orientation_check_response(event, true);

    char * id;


    m_orientation = i;

    if (m_orientation == 1)
    {
    	navigator_set_orientation(NAVIGATOR_RIGHT_UP, &id);
    	bbutil_rotate_screen_surface(90);
    }
    else
    {
    	navigator_set_orientation(NAVIGATOR_PORTRAIT, &id);
    	bbutil_rotate_screen_surface(0);
    }
	navigator_done_orientation(event);
	navigator_rotation_lock(true);

}

int platform::getOrientation()
{
	return m_orientation;
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
	return m_DateTime->getDate();
}

char* platform::getTime()
{
	return m_DateTime->getTime();
}

char* platform::getDateTime()
{
	return m_DateTime->getDateTime();
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
