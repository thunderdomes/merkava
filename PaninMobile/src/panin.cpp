/*
 * panin.cpp
 *
 *  Created on: 28 juil. 2013
 *      Author: Eka Chan
 */

#include "panin.h"
#include "platform.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

namespace paninMobile
{

panin::panin(platform &myPlatform)
	: PlatformEventHandler(),
	  m_platform(myPlatform),
	  m_shutdown(false),
	  m_state(HOME),
	  m_bZ10(false)
{
	// TODO Auto-generated constructor stub
	m_platform.setEventHandler(this);
	m_platform.getSize(m_screenWidth, m_screenHeight);

	int dpi = m_platform.getDPI();
	int point_size = (int)(15.0f / ((float)dpi / 170.0f ));

	m_font = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	//Initialize message
	float textSizeX, textSizeY;
	m_message = "Loading...";
	bbutil_measure_text(m_font, m_message, &textSizeX, &textSizeY);
	m_messagePosX = (m_screenWidth - textSizeX) / 2;
	m_messagePosY = (m_screenHeight - textSizeY) / 2;

	fprintf(stderr, "Load latar.\n");

	if (m_screenHeight == m_screenWidth && m_screenWidth == 720)
	{
		m_bZ10 = false;
		m_latar.load("app/native/assets/umum/latarQ10.png");
	}
	else
	{
		m_bZ10 = true;
		m_latar.load("app/native/assets/umum/latarZ10.png");
	}

	m_latar.setPosition(0.0f, 0.0f);

	// initialize home screen
	fprintf(stderr, "Load home.\n");
	m_logo.load("app/native/assets/login/logo.png");
	m_logo.setPosition((m_screenWidth - m_logo.Width())/2, m_screenHeight - m_logo.Height() - 106.0f);
	m_username_textfield.load("app/native/assets/login/username.png");
	m_username_textfield.setPosition((m_screenWidth - m_username_textfield.Width())/2, m_screenHeight - m_username_textfield.Height() - 574.0f);
	m_password_textfield.load("app/native/assets/login/password.png");
	m_password_textfield.setPosition((m_screenWidth - m_password_textfield.Width())/2, m_screenHeight - m_password_textfield.Height() - 635.0f);
	m_ihsg_bar.load("app/native/assets/login/ihsg.png");
	m_ihsg_bar.setPosition(0.0f, m_screenHeight - m_ihsg_bar.Height() - 827.0f);
	m_ihsg_value_bg.load("app/native/assets/login/ihsg_val.png");
	m_ihsg_value_bg.setPosition((m_screenWidth - m_ihsg_value_bg.Width())/2, m_screenHeight - m_ihsg_value_bg.Height() - 908.0f);
	m_ihsg_volume_bg.load("app/native/assets/login/ihsg_vol.png");
	m_ihsg_volume_bg.setPosition((m_screenWidth - m_ihsg_volume_bg.Width())/2, m_screenHeight - m_ihsg_volume_bg.Height() - 984.0f);
	m_tanggal_bg.load("app/native/assets/login/latar_tanggal.png");
	m_tanggal_bg.setPosition((m_screenWidth - m_tanggal_bg.Width())/2, m_screenHeight - m_tanggal_bg.Height() - 1057.0f);
	m_login_default.load("app/native/assets/login/login.png");
	m_login_pressed.load("app/native/assets/login/login.png");
	m_home_info_default.load("app/native/assets/login/info.png");
	m_home_info_pressed.load("app/native/assets/login/info.png");
	m_home_setel_default.load("app/native/assets/login/setel.png");
	m_home_setel_pressed.load("app/native/assets/login/setel.png");

	fprintf(stderr, "Load btn_login.\n");
	m_btn_login.regular = &m_login_default;
	m_btn_login.pressed = &m_login_pressed;
	m_btn_login.sizeX	= m_login_default.Width();
	m_btn_login.sizeY	= m_login_default.Height();
	m_btn_login.font	= m_font;
	m_btn_login.text	= "";
	m_btn_login.isPressed	= false;
	m_btn_login.setPosition( (m_screenWidth - m_btn_login.sizeX)/2, m_screenHeight - m_btn_login.sizeY - 710.0 );

	fprintf(stderr, "Load m_btn_home_info.\n");
	m_btn_home_info.regular = &m_home_info_default;
	m_btn_home_info.pressed = &m_home_info_pressed;
	m_btn_home_info.sizeX	= m_home_info_default.Width();
	m_btn_home_info.sizeY	= m_home_info_default.Height();
	m_btn_home_info.font	= m_font;
	m_btn_home_info.text	= "";
	m_btn_home_info.isPressed	= false;
	m_btn_home_info.setPosition( m_screenWidth/2 - m_btn_home_info.sizeX -20.0f, (100.0f - m_btn_home_info.sizeY) );

	fprintf(stderr, "Load m_btn_home_setel.\n");
	m_btn_home_setel.regular = &m_home_setel_default;
	m_btn_home_setel.pressed = &m_home_setel_pressed;
	m_btn_home_setel.sizeX	= m_home_setel_default.Width();
	m_btn_home_setel.sizeY	= m_home_setel_default.Height();
	m_btn_home_setel.font	= m_font;
	m_btn_home_setel.text	= "";
	m_btn_home_setel.isPressed	= false;
	m_btn_home_setel.setPosition( m_screenWidth/2 + 20.0f, (100.0f - m_btn_home_setel.sizeY) );


//    m_playButton.sizeX = m_buttonRegular.Width();
//    m_playButton.sizeY = m_buttonRegular.Height();
//    m_playButton.isPressed = false;
//    m_playButton.regular = &m_buttonRegular;
//    m_playButton.pressed = &m_buttonPressed;
//    m_playButton.font = m_font;
//    m_playButton.text = "Play Again";
//    bbutil_measure_text(m_font, m_playButton.text, &textSizeX, &textSizeY);
//    m_playButton.textX = - textSizeX / 2;
//    m_playButton.textY = - textSizeY / 2;
//    m_playButton.setPosition(m_sceneWidth / 2, m_leaderBoard.PosY() - m_leaderBoard.Height() / 2);


}

//panin::~panin() {
//	// TODO Auto-generated destructor stub
//}

void panin::enable2D() {
    //Initialize GL for 2D rendering
    glViewport(0, 0, static_cast<int>(m_screenWidth), static_cast<int>(m_screenHeight));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrthof(0.0f, m_screenWidth / m_screenHeight, 0.0f, 1.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Set world coordinates to coincide with screen pixels
    glScalef(1.0f / m_screenHeight, 1.0f / m_screenHeight, 1.0f);
    glClearColor(0.775f, 0.775f, 0.775f, 1.0f);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void panin::run() {
    enable2D();


    while (!m_shutdown) {
        // platform handle input
        m_platform.processEvents();

        switch (m_state) {
        case HOME:
            renderHome();
            break;

        case LOADING:
        	fprintf(stderr, "eka at loading.");
            //update();
            //renderGame();
            break;
        default:
        	fprintf(stderr, "eka at default.");
            break;
        }
    }
}

void panin::update()
{

}

void panin::renderHome()
{
	m_platform.beginRender();

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();
	m_logo.draw();
	m_username_textfield.draw();
	m_password_textfield.draw();
	m_ihsg_bar.draw();
	m_ihsg_value_bg.draw();
	m_ihsg_volume_bg.draw();
	m_tanggal_bg.draw();
	m_btn_login.draw();
	m_btn_home_info.draw();
	m_btn_home_setel.draw();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    //bbutil_render_text(m_font, m_message, m_messagePosX, m_messagePosY, 0.75f, 0.75f, 0.75f, 1.0f);

    m_platform.finishRender();
}

void panin::onLeftRelease(float x, float y)
{
	fprintf(stderr, "onLeftRelease.\n");
	if (m_btn_login.isWithin(x, m_screenHeight - y))
	{
		m_btn_login.isPressed = false;
		fprintf(stderr, "Button login di lepas.\n");
	}
}

void panin::onLeftPress(float x, float y)
{
	fprintf(stderr, "onLeftPress.\n");
	if (m_btn_login.isWithin(x, m_screenHeight - y))
	{
		m_btn_login.isPressed = true;
		fprintf(stderr, "Button login di tekan.\n");
	}
}

void panin::button::setPosition(float x, float y) {
    posX = x;
    posY = y;
    regular->setPosition(x, y);
    pressed->setPosition(x, y);
}

void panin::button::draw() const {
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (isPressed == true) {
        pressed->draw();
    } else {
        regular->draw();
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    bbutil_render_text(font, text, posX + textX, posY + textY, 1.0f, 1.0f, 1.0f, 1.0f);
}

void panin::onExit() {
    m_shutdown = true;
}

void panin::onPromptOk(const std::string& input) {
    //m_platform.submitUserName(input);
}

} /* namespace paninMobile */
