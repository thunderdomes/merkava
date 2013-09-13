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
#include <pthread.h>

#include <sys/keycodes.h>
#include <bps/virtualkeyboard.h>

typedef struct user {
	std::string username;
	std::string password;
} user;

user myUser;

typedef struct threadVar {
	user t_myUser;
} threadVar;

enum _loginStatus {
	NOT_SIGNIN = 0, SIGNINGIN, SIGNEDIN, SIGN_FAILED
};

_loginStatus loginStatus;

ServerConnection * myServerConnection;
std::ostringstream osStream;
std::ostringstream osStreamLogin;

bool bIsGettingRT;
bool bIsGettingSQ;
bool bIsGettingBQ;
bool bIsGettingSW;
bool bIsGettingSS;
bool bIsGettingBS;


namespace paninMobile {

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

panin::panin(platform &myPlatform) :
		PlatformEventHandler(), m_platform(myPlatform),
		m_shutdown(false),
		m_state(HOME),
		m_bZ10(false),
		m_bShowMenu(false),
		m_bShowSubmenuTC(false),
		m_bShowSubmenuInformation(false),
		m_bShowInfo(false),
		m_bShowBuy(false),
		m_bShowSell(false),
		m_bAccountIdFocused(false),
		m_bStockTradeFocused(false),
		m_bPriceFocused(false),
		m_bVolumeFocused(false),
		m_bVirtualKeyboardShow(false),
		m_bShowHomeInfo(false),
		m_bShowHomeSetel(false),
		m_bUsernameFocus(false),
		m_bPasswordFocus(false),
		m_bLogged(false)
{
	// TODO Auto-generated constructor stub
	m_platform.setEventHandler(this);
	m_platform.getSize(m_screenWidth, m_screenHeight);
	fprintf(stderr, "width, height: %f, %f\n", m_screenWidth, m_screenHeight);

	m_footerHeight = 100.0f;
	m_headerHeight = m_screenHeight - 80.0f;

	int dpi = m_platform.getDPI();
	int point_size = (int) (15.0f / ((float) dpi / 170.0f));

	m_font = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	m_font_global = bbutil_load_font(
			"/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (36.0f / ((float) dpi / 170.0f));
	m_font_ihsg_val = bbutil_load_font(
			"/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (15.0f / ((float) dpi / 170.0f));
	m_font_ihsg_vol = bbutil_load_font(
			"/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (15.0f / ((float) dpi / 170.0f));
	m_font_tanggal = bbutil_load_font(
			"/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (8.0f / ((float) dpi / 170.0f));
	m_font8 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (9.0f / ((float) dpi / 170.0f));
	m_font9 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (10.0f / ((float) dpi / 170.0f));
	m_font10 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (11.0f / ((float) dpi / 170.0f));
	m_font11 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (12.0f / ((float) dpi / 170.0f));
	m_font12 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (14.0f / ((float) dpi / 170.0f));
	m_font14 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (20.0f / ((float) dpi / 170.0f));
	m_font20 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (24.0f / ((float) dpi / 170.0f));
	m_font24 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (28.0f / ((float) dpi / 170.0f));
	m_font28 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int) (36.0f / ((float) dpi / 170.0f));
	m_font36 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf",
			point_size, dpi);
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

	if (m_screenHeight == m_screenWidth && m_screenWidth == 720) {
		m_bZ10 = false;
		m_latar.load("app/native/assets/umum/latarQ10.png");
	} else {
		m_bZ10 = true;
		m_latar.load("app/native/assets/umum/latarZ10.png");
	}

	m_fLeftReffPos = 0.0f;
	m_latar.setPosition(m_fLeftReffPos, 0.0f);

	fprintf(stderr, "load general assets.\n");
	m_header_bar_bg.load("app/native/assets/umum/bar.png");
	m_header_bar_bg.setPosition(m_latar.PosX(), m_headerHeight);
	m_header_post.load("app/native/assets/umum/post.png");
	m_header_post.setPosition((m_screenWidth - m_header_post.Width()) / 2,
			m_header_bar_bg.PosY()
					+ (m_header_bar_bg.Height() - m_header_post.Height()) / 2);
	m_btn_info_bg.load("app/native/assets/umum/info_blue.png");
	m_btn_info_p_bg.load("app/native/assets/umum/info_blue_p.png");
	m_btn_menu_bg.load("app/native/assets/umum/menu_blue.png");
	m_btn_menu_bg_p.load("app/native/assets/umum/menu_blue_p.png");
	m_btn_sell_bg.load("app/native/assets/umum/sell.png");
	m_btn_sell_bg_p.load("app/native/assets/umum/sell_p.png");
	m_btn_buy_bg.load("app/native/assets/umum/buy.png");
	m_btn_buy_bg_p.load("app/native/assets/umum/buy_p.png");

	m_btn_info.regular = &m_btn_info_bg;
	m_btn_info.pressed = &m_btn_info_p_bg;
	m_btn_info.sizeX = m_btn_info_bg.Width();
	m_btn_info.sizeY = m_btn_info_bg.Height();
	m_btn_info.font = m_font_global;
	m_btn_info.text = "";
	m_btn_info.isPressed = false;
	m_btn_info.isEnabled = true;
	m_btn_info.setPosition(
			m_header_bar_bg.PosX() + m_screenWidth - 1.5 * m_btn_info.sizeX,
			m_header_bar_bg.PosY()
					+ (m_header_bar_bg.Height() - m_btn_info.sizeY) / 2);
	m_btn_menu.regular = &m_btn_menu_bg;
	m_btn_menu.pressed = &m_btn_menu_bg_p;
	m_btn_menu.sizeX = m_btn_menu_bg.Width();
	m_btn_menu.sizeY = m_btn_menu_bg.Height();
	m_btn_menu.font = m_font;
	m_btn_menu.text = "";
	m_btn_menu.isPressed = false;
	m_btn_menu.isEnabled = true;
	m_btn_menu.setPosition(m_header_bar_bg.PosX() + 0.5 * m_btn_menu.sizeX,
			m_header_bar_bg.PosY()
					+ (m_header_bar_bg.Height() - m_btn_menu.sizeY) / 2);
	m_btn_sell.regular = &m_btn_sell_bg;
	m_btn_sell.pressed = &m_btn_sell_bg_p;
	m_btn_sell.sizeX = m_btn_sell_bg.Width();
	m_btn_sell.sizeY = m_btn_sell_bg.Height();
	m_btn_sell.font = m_font;
	m_btn_sell.text = "";
	m_btn_sell.isPressed = false;
	m_btn_sell.isEnabled = true;
	m_btn_sell.setPosition(
			m_latar.PosX() + (m_screenWidth - m_btn_sell.sizeX - 20.0f),
			(m_footerHeight - m_btn_sell.sizeY) / 2);
	m_btn_buy.regular = &m_btn_buy_bg;
	m_btn_buy.pressed = &m_btn_buy_bg_p;
	m_btn_buy.sizeX = m_btn_buy_bg.Width();
	m_btn_buy.sizeY = m_btn_buy_bg.Height();
	m_btn_buy.font = m_font;
	m_btn_buy.text = "";
	m_btn_buy.isPressed = false;
	m_btn_buy.isEnabled = true;
	m_btn_buy.setPosition(m_btn_sell.posX - m_btn_buy.sizeX - 10.0f,
			m_btn_sell.posY);

	//ihsg
	m_ihsg2.load("app/native/assets/umum/ihsg.png");
	m_ihsg2.setPosition(0.0f, (m_footerHeight - m_ihsg2.Height()) / 2);
	// buy
	m_buy_bg.load("app/native/assets/umum/buy_bg.png");
	m_buy_bg.setPosition(
			m_latar.PosX() + (m_screenWidth - m_buy_bg.Width()) / 2,
			(m_screenHeight - m_buy_bg.Height()) / 2);
	m_buy_caption.load("app/native/assets/umum/buy_caption.png");
	m_buy_caption.setPosition(m_buy_bg.PosX() + 20.0f,
			m_buy_bg.PosY() + m_buy_bg.Height() - 2 * m_buy_caption.Height());
	m_buy_refresh.load("app/native/assets/umum/buy_refresh.png");
	m_buy_refresh_p.load("app/native/assets/umum/buy_refresh_p.png");
	m_buy_execute.load("app/native/assets/umum/buy_execute.png");
	m_buy_execute_p.load("app/native/assets/umum/buy_execute_p.png");
	m_buy_band.load("app/native/assets/umum/white_bar.png");
	m_buy_band.setPosition(m_buy_bg.PosX() + 0.0f + 20.0f,
			m_buy_bg.PosY() + m_buy_bg.Height() - 600.0f);
	m_buy_x.load("app/native/assets/umum/buy_x.png");
	m_buy_x_p.load("app/native/assets/umum/buy_x_p.png");
	m_btn_buy_refresh.regular = &m_buy_refresh;
	m_btn_buy_refresh.pressed = &m_buy_refresh_p;
	m_btn_buy_refresh.sizeX = m_buy_refresh.Width();
	m_btn_buy_refresh.sizeY = m_buy_refresh.Height();
	m_btn_buy_refresh.font = m_font;
	m_btn_buy_refresh.text = "";
	m_btn_buy_refresh.isPressed = false;
	m_btn_buy_refresh.setPosition(m_buy_bg.PosX() + 120.0f,
			m_buy_band.PosY()
					+ (m_buy_band.Height() - m_btn_buy_refresh.sizeY) / 2);
	m_btn_buy_execute.regular = &m_buy_execute;
	m_btn_buy_execute.pressed = &m_buy_execute_p;
	m_btn_buy_execute.sizeX = m_buy_execute.Width();
	m_btn_buy_execute.sizeY = m_buy_execute.Height();
	m_btn_buy_execute.font = m_font;
	m_btn_buy_execute.text = "";
	m_btn_buy_execute.isPressed = false;
	m_btn_buy_execute.setPosition(
			m_btn_buy_refresh.posX + m_btn_buy_refresh.sizeX + 100.0f,
			m_btn_buy_refresh.posY);
	m_btn_buy_x.regular = &m_buy_x;
	m_btn_buy_x.pressed = &m_buy_x;
	m_btn_buy_x.sizeX = m_buy_x.Width();
	m_btn_buy_x.sizeY = m_buy_x.Height();
	m_btn_buy_x.font = m_font;
	m_btn_buy_x.text = "";
	m_btn_buy_x.isPressed = false;
	m_btn_buy_x.setPosition(
			m_buy_caption.PosX() + m_buy_caption.Width()
					- 1.2 * m_btn_buy_x.sizeX,
			m_buy_caption.PosY()
					+ (m_buy_caption.Height() - m_btn_buy_x.sizeY) / 2 + 4.0f);
	//sell
	m_sell_bg.load("app/native/assets/umum/sell_bg.png");
	m_sell_bg.setPosition(
			m_latar.PosX() + (m_screenWidth - m_sell_bg.Width()) / 2,
			(m_screenHeight - m_sell_bg.Height()) / 2);
	m_sell_caption.load("app/native/assets/umum/sell_caption.png");
	m_sell_caption.setPosition(m_sell_bg.PosX() + 20.0f,
			m_sell_bg.PosY() + m_sell_bg.Height()
					- 2 * m_sell_caption.Height());
	m_sell_refresh.load("app/native/assets/umum/sell_refresh.png");
	m_sell_refresh_p.load("app/native/assets/umum/sell_refresh_p.png");
	m_sell_execute.load("app/native/assets/umum/sell_execute.png");
	m_sell_execute_p.load("app/native/assets/umum/sell_execute_p.png");
	m_sell_band.load("app/native/assets/umum/white_bar.png");
	m_sell_band.setPosition(m_sell_bg.PosX() + 0.0f + 20.0f,
			m_sell_bg.PosY() + m_sell_bg.Height() - 600.0f);
	m_sell_x.load("app/native/assets/umum/sell_x.png");
	m_sell_x_p.load("app/native/assets/umum/sell_x_p.png");
	m_btn_sell_refresh.regular = &m_sell_refresh;
	m_btn_sell_refresh.pressed = &m_sell_refresh_p;
	m_btn_sell_refresh.sizeX = m_sell_refresh.Width();
	m_btn_sell_refresh.sizeY = m_sell_refresh.Height();
	m_btn_sell_refresh.font = m_font;
	m_btn_sell_refresh.text = "";
	m_btn_sell_refresh.isPressed = false;
	m_btn_sell_refresh.isEnabled = true;
	m_btn_sell_refresh.setPosition(m_sell_bg.PosX() + 120.0f,
			m_sell_band.PosY()
					+ (m_sell_band.Height() - m_btn_sell_refresh.sizeY) / 2);
	m_btn_sell_execute.regular = &m_sell_execute;
	m_btn_sell_execute.pressed = &m_sell_execute_p;
	m_btn_sell_execute.sizeX = m_sell_execute.Width();
	m_btn_sell_execute.sizeY = m_sell_execute.Height();
	m_btn_sell_execute.font = m_font;
	m_btn_sell_execute.text = "";
	m_btn_sell_execute.isPressed = false;
	m_btn_sell_execute.isEnabled = true;
	m_btn_sell_execute.setPosition(
			m_btn_sell_refresh.posX + m_btn_sell_refresh.sizeX + 100.0f,
			m_btn_sell_refresh.posY);
	m_btn_sell_x.regular = &m_sell_x;
	m_btn_sell_x.pressed = &m_sell_x_p;
	m_btn_sell_x.sizeX = m_sell_x.Width();
	m_btn_sell_x.sizeY = m_sell_x.Height();
	m_btn_sell_x.font = m_font;
	m_btn_sell_x.text = "";
	m_btn_sell_x.isPressed = false;
	m_btn_sell_x.isEnabled = true;
	m_btn_sell_x.setPosition(
			m_sell_caption.PosX() + m_sell_caption.Width()
					- 1.0 * m_btn_sell_x.sizeX,
			m_sell_caption.PosY()
					+ (m_sell_caption.Height() - m_btn_sell_x.sizeY) / 2
					+ 2.0f);

	m_buysell_textfield_bg.load("app/native/assets/umum/table_bg.png");
	m_buysell_textfield_bg_focus.load("app/native/assets/umum/table_bg_focus.png");

	m_textfield_bg.load("app/native/assets/umum/textfield_bg.png");
	m_dialog_bg.load("app/native/assets/umum/dialog_bg.png");
	m_dialog_bg.setPosition((m_screenWidth - m_dialog_bg.Width()) / 2,
			(m_screenHeight - m_dialog_bg.Height()) / 2);
	m_blue_rect.load("app/native/assets/umum/btn_blue.png");
	m_blue_rect_p.load("app/native/assets/umum/btn_blue_p.png");
	m_setel_bg.load("app/native/assets/umum/setel_bg.png");
	m_setel_bg.setPosition((m_screenWidth - m_setel_bg.Width()) / 2,
			(m_screenHeight - m_setel_bg.Height()) / 2);
	m_setel_default.load("app/native/assets/umum/btndefault.png");
	m_setel_set202.load("app/native/assets/umum/btn202.png");
	m_setel_set107.load("app/native/assets/umum/btn107.png");
	m_setel_save.load("app/native/assets/umum/btnsave.png");
	m_setel_x.load("app/native/assets/umum/btn_x.png");
	m_setel_default_p.load("app/native/assets/umum/btndefault_p.png");
	m_setel_set202_p.load("app/native/assets/umum/btn202_p.png");
	m_setel_set107_p.load("app/native/assets/umum/btn107_p.png");
	m_setel_save_p.load("app/native/assets/umum/btnsave_p.png");
	m_setel_x_p.load("app/native/assets/umum/btn_x_p.png");
	m_btn_conf_ok.regular = &m_blue_rect;
	m_btn_conf_ok.pressed = &m_blue_rect_p;
	m_btn_conf_ok.sizeX = m_blue_rect.Width();
	m_btn_conf_ok.sizeY = m_blue_rect.Height();
	m_btn_conf_ok.font = m_font;
	m_btn_conf_ok.text = "OK";
	m_btn_conf_ok.isPressed = false;
	m_btn_conf_ok.isEnabled = true;
	m_btn_conf_ok.setPosition(m_dialog_bg.PosX() + 435.0f,
			m_dialog_bg.PosY() + 60.0f);
	m_btn_conf_cancel.regular = &m_blue_rect;
	m_btn_conf_cancel.pressed = &m_blue_rect_p;
	m_btn_conf_cancel.sizeX = m_blue_rect.Width();
	m_btn_conf_cancel.sizeY = m_blue_rect.Height();
	m_btn_conf_cancel.font = m_font;
	m_btn_conf_cancel.text = "CANCEL";
	m_btn_conf_cancel.isPressed = false;
	m_btn_conf_cancel.isEnabled = true;
	m_btn_conf_cancel.setPosition(m_dialog_bg.PosX() + 210.0f,
			m_btn_conf_ok.posX);
	m_btn_setel_default.regular = &m_setel_default;
	m_btn_setel_default.pressed = &m_setel_default_p;
	m_btn_setel_default.regular->setPosition(0.0f, 0.0f);
	m_btn_setel_default.sizeX = m_setel_default.Width();
	m_btn_setel_default.sizeY = m_setel_default.Height();
	m_btn_setel_default.font = m_font;
	m_btn_setel_default.text = "";
	m_btn_setel_default.isPressed = false;
	m_btn_setel_default.isEnabled = true;
	m_btn_setel_default.setPosition(m_dialog_bg.PosX() + 64.0f,
			m_dialog_bg.PosY() + 60.0f);
	m_btn_setel_set202.regular = &m_setel_set202;
	m_btn_setel_set202.pressed = &m_setel_set202_p;
	m_btn_setel_set202.sizeX = m_setel_set202.Width();
	m_btn_setel_set202.sizeY = m_setel_set202.Height();
	m_btn_setel_set202.font = m_font;
	m_btn_setel_set202.text = "";
	m_btn_setel_set202.isPressed = false;
	m_btn_setel_set202.isEnabled = true;
	m_btn_setel_set202.setPosition(m_dialog_bg.PosX() + 220.0f,
			m_btn_setel_default.posY);
	m_btn_setel_set107.regular = &m_setel_set107;
	m_btn_setel_set107.pressed = &m_setel_set107_p;
	m_btn_setel_set107.sizeX = m_setel_set107.Width();
	m_btn_setel_set107.sizeY = m_setel_set107.Height();
	m_btn_setel_set107.font = m_font;
	m_btn_setel_set107.text = "";
	m_btn_setel_set107.isPressed = false;
	m_btn_setel_set107.isEnabled = true;
	m_btn_setel_set107.setPosition(m_dialog_bg.PosX() + 377.0f,
			m_btn_setel_default.posY);
	m_btn_setel_save.regular = &m_setel_save;
	m_btn_setel_save.pressed = &m_setel_save_p;
	m_btn_setel_save.sizeX = m_setel_save.Width();
	m_btn_setel_save.sizeY = m_setel_save.Height();
	m_btn_setel_save.font = m_font;
	m_btn_setel_save.text = "";
	m_btn_setel_save.isPressed = false;
	m_btn_setel_save.isEnabled = true;
	m_btn_setel_save.setPosition(m_dialog_bg.PosX() + 536.0f,
			m_btn_setel_default.posY);
	m_btn_setel_x.regular = &m_setel_x;
	m_btn_setel_x.pressed = &m_setel_x_p;
	m_btn_setel_x.sizeX = m_setel_x.Width();
	m_btn_setel_x.sizeY = m_setel_x.Height();
	m_btn_setel_x.font = m_font;
	m_btn_setel_x.text = "";
	m_btn_setel_x.isPressed = false;
	m_btn_setel_x.isEnabled = true;
	m_btn_setel_x.setPosition(
			m_dialog_bg.PosX() + m_dialog_bg.Width() - 1.8 * m_btn_setel_x.sizeX,
			m_dialog_bg.PosY() + m_dialog_bg.Height() - 1.8 * m_btn_setel_x.sizeY);

	// initialize home screen
	fprintf(stderr, "Load home.\n");
	m_logo.load("app/native/assets/login/logo.png");
	m_logo.setPosition((m_screenWidth - m_logo.Width()) / 2,
			m_screenHeight - m_logo.Height() - 106.0f);
	m_username_textfield_default.load("app/native/assets/login/username.png");
	m_username_textfield_regular.load("app/native/assets/login/username1.png");
	m_password_textfield_default.load("app/native/assets/login/password.png");
	m_password_textfield_regular.load("app/native/assets/login/password1.png");
	m_ihsg_bar.load("app/native/assets/login/ihsg.png");
	m_ihsg_bar.setPosition(0.0f, m_screenHeight - m_ihsg_bar.Height() - 827.0f);
	m_ihsg_value_bg.load("app/native/assets/login/ihsg_val.png");
	m_ihsg_value_bg.setPosition((m_screenWidth - m_ihsg_value_bg.Width()) / 2,
			m_screenHeight - m_ihsg_value_bg.Height() - 908.0f);
	m_ihsg_volume_bg.load("app/native/assets/login/ihsg_vol.png");
	m_ihsg_volume_bg.setPosition((m_screenWidth - m_ihsg_volume_bg.Width()) / 2,
			m_screenHeight - m_ihsg_volume_bg.Height() - 984.0f);
	m_tanggal_bg.load("app/native/assets/login/latar_tanggal.png");
	m_tanggal_bg.setPosition((m_screenWidth - m_tanggal_bg.Width()) / 2,
			m_screenHeight - m_tanggal_bg.Height() - 1057.0f);
	m_login_default.load("app/native/assets/login/login.png");
	m_login_pressed.load("app/native/assets/login/login_p.png");
	m_home_info_default.load("app/native/assets/login/info.png");
	m_home_info_pressed.load("app/native/assets/login/info_p.png");
	m_home_setel_default.load("app/native/assets/login/setel.png");
	m_home_setel_pressed.load("app/native/assets/login/setel_p.png");

	fprintf(stderr, "Load m_btn_home_username.\n");
	m_btn_home_username.regular = &m_username_textfield_default;
	m_btn_home_username.pressed = &m_username_textfield_regular;
	m_btn_home_username.sizeX = m_username_textfield_default.Width();
	m_btn_home_username.sizeY = m_username_textfield_default.Height();
	m_btn_home_username.font = m_font;
	m_btn_home_username.text = "";
	m_btn_home_username.isPressed = false;
	m_btn_home_username.isEnabled = true;
	if (m_bZ10) {
		m_btn_home_username.setPosition(
				(m_screenWidth - m_btn_home_username.sizeX) / 2,
				m_screenHeight - m_username_textfield_regular.Height()
						- 574.0f);
	} else {
		m_btn_home_username.setPosition(
				(m_screenWidth - m_btn_home_username.sizeX) / 2, 417.0f);
	}

	fprintf(stderr, "Load m_btn_home_password.\n");
	m_btn_home_password.regular = &m_password_textfield_default;
	m_btn_home_password.pressed = &m_password_textfield_regular;
	m_btn_home_password.sizeX = m_password_textfield_default.Width();
	m_btn_home_password.sizeY = m_password_textfield_default.Height();
	m_btn_home_password.font = m_font;
	m_btn_home_password.text = "";
	m_btn_home_password.isPressed = false;
	m_btn_home_password.isEnabled = true;
	m_btn_home_password.setPosition(
			(m_screenWidth - m_btn_home_password.sizeX) / 2,
			m_btn_home_username.posY - 62.0f);

	fprintf(stderr, "Load btn_login.\n");
	m_btn_login.regular = &m_login_default;
	m_btn_login.pressed = &m_login_pressed;
	m_btn_login.sizeX = m_login_default.Width();
	m_btn_login.sizeY = m_login_default.Height();
	m_btn_login.font = m_font;
	m_btn_login.text = "";
	m_btn_login.isPressed = false;
	m_btn_login.isEnabled = true;
	m_btn_login.setPosition((m_screenWidth - m_btn_login.sizeX) / 2,
			m_btn_home_password.posY - 90.0);

	fprintf(stderr, "Load m_btn_home_info.\n");
	m_btn_home_info.regular = &m_home_info_default;
	m_btn_home_info.pressed = &m_home_info_pressed;
	m_btn_home_info.sizeX = m_home_info_default.Width();
	m_btn_home_info.sizeY = m_home_info_default.Height();
	m_btn_home_info.font = m_font;
	m_btn_home_info.text = "";
	m_btn_home_info.isPressed = false;
	m_btn_home_info.isEnabled = true;
	m_btn_home_info.setPosition(
			m_screenWidth / 2 - m_btn_home_info.sizeX - 20.0f,
			(80.0f - m_btn_home_info.sizeY));

	fprintf(stderr, "Load m_btn_home_setel.\n");
	m_btn_home_setel.regular = &m_home_setel_default;
	m_btn_home_setel.pressed = &m_home_setel_pressed;
	m_btn_home_setel.sizeX = m_home_setel_default.Width();
	m_btn_home_setel.sizeY = m_home_setel_default.Height();
	m_btn_home_setel.font = m_font;
	m_btn_home_setel.text = "";
	m_btn_home_setel.isPressed = false;
	m_btn_home_setel.isEnabled = true;
	m_btn_home_setel.setPosition(m_screenWidth / 2 + 20.0f,
			(80.0f - m_btn_home_setel.sizeY));

	//TRADE
	fprintf(stderr, "Load running trade.\n");
	m_rt_caption.load("app/native/assets/running_trade/rt_bar_title.png");
	m_rt_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_rt_caption.Height() - 20.0f);
	m_rt_table_title.load("app/native/assets/running_trade/rt_table_title.png");
	m_rt_table_title.setPosition(m_latar.PosX(),
			m_rt_caption.PosY() - m_rt_table_title.Height() - 20.0f);

	//stock watch
	fprintf(stderr, "Load stock watch.\n");
	m_sw_caption.load("app/native/assets/stock_watch/sw_caption.png");
	m_sw_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_sw_caption.Height() - 20.0f);
	m_sw_box_black.load("app/native/assets/stock_watch/sw_box_black.png");
	m_sw_box_black.setPosition(m_latar.PosX() + 27.0f, m_screenHeight - 455.0f);
	m_sw_port1.load("app/native/assets/stock_watch/sw_port1.png");
	m_sw_port1_p.load("app/native/assets/stock_watch/sw_port1_p.png");
	//m_sw_port1.setPosition(m_latar.PosX() + 41.0f,
	//		m_sw_caption.PosY() - m_sw_port1.Height() - 20.0f);
	m_sw_banking.load("app/native/assets/stock_watch/sw_banking.png");
	m_sw_banking_p.load("app/native/assets/stock_watch/sw_banking_p.png");
	//m_sw_banking.setPosition(
	//		m_latar.PosX() + m_sw_port1.PosX() + m_sw_port1.Width() + 10.0f,
	//		m_sw_port1.PosY());
	m_sw_mining.load("app/native/assets/stock_watch/sw_mining.png");
	m_sw_mining_p.load("app/native/assets/stock_watch/sw_mining_p.png");
	//m_sw_mining.setPosition(
	//		m_latar.PosX() + m_sw_banking.PosX() + m_sw_banking.Width() + 10.0f,
	//		m_sw_port1.PosY());
	m_sw_cons.load("app/native/assets/stock_watch/sw_cons.png");
	m_sw_cons_p.load("app/native/assets/stock_watch/sw_cons_p.png");
	//m_sw_cons.setPosition(
	//		m_latar.PosX() + m_sw_mining.PosX() + m_sw_mining.Width() + 10.0f,
	//		m_sw_port1.PosY());
	m_sw_plus_green.load("app/native/assets/stock_watch/sw_plus_green.png");
	m_sw_plus_green_p.load("app/native/assets/stock_watch/sw_plus_green_p.png");
	//m_sw_plus_green.setPosition(
	//		m_latar.PosX() + m_sw_cons.PosX() + m_sw_cons.Width() + 10.0f,
	//		m_sw_port1.PosY());
	m_sw_val_green.load("app/native/assets/stock_watch/sw_green.png");
	m_sw_val_green.setPosition(m_latar.PosX() + 40.0f, m_screenHeight - 413.0f);
	m_sw_val_yellow.load("app/native/assets/stock_watch/sw_yellow.png");
	m_sw_val_yellow.setPosition(m_latar.PosX() + 40.0f,
			m_screenHeight - 413.0f);
	m_sw_val_red.load("app/native/assets/stock_watch/sw_red.png");
	m_sw_val_red.setPosition(m_latar.PosX() + 240.0f, m_screenHeight - 413.0f);
	//m_sw_btn_port1
	m_sw_btn_port1.regular = &m_sw_port1;
	m_sw_btn_port1.pressed = &m_sw_port1_p;
	m_sw_btn_port1.sizeX = m_sw_port1.Width();
	m_sw_btn_port1.sizeY = m_sw_port1.Height();
	m_sw_btn_port1.font = m_font;
	m_sw_btn_port1.text = "";
	m_sw_btn_port1.isPressed = false;
	m_sw_btn_port1.isEnabled = true;
	m_sw_btn_port1.setPosition(m_latar.PosX() + 41.0f,
			m_sw_caption.PosY() - m_sw_port1.Height() - 20.0f);

	m_sw_btn_banking.regular = &m_sw_banking;
	m_sw_btn_banking.pressed = &m_sw_banking_p;
	m_sw_btn_banking.sizeX = m_sw_banking.Width();
	m_sw_btn_banking.sizeY = m_sw_banking.Height();
	m_sw_btn_banking.font = m_font;
	m_sw_btn_banking.text = "";
	m_sw_btn_banking.isPressed = false;
	m_sw_btn_banking.isEnabled = true;
	m_sw_btn_banking.setPosition(m_sw_btn_port1.posX + m_sw_btn_port1.sizeX + 10.0f,
			m_sw_btn_port1.posY);

	m_sw_btn_mining.regular = &m_sw_mining;
	m_sw_btn_mining.pressed = &m_sw_mining_p;
	m_sw_btn_mining.sizeX = m_sw_mining.Width();
	m_sw_btn_mining.sizeY = m_sw_mining.Height();
	m_sw_btn_mining.font = m_font;
	m_sw_btn_mining.text = "";
	m_sw_btn_mining.isPressed = false;
	m_sw_btn_mining.isEnabled = true;
	m_sw_btn_mining.setPosition(m_sw_btn_banking.posX + m_sw_btn_banking.sizeX + 10.0f,	m_sw_btn_banking.posY);

	m_sw_btn_cons.regular = &m_sw_cons;
	m_sw_btn_cons.pressed = &m_sw_cons_p;
	m_sw_btn_cons.sizeX = m_sw_cons.Width();
	m_sw_btn_cons.sizeY = m_sw_cons.Height();
	m_sw_btn_cons.font = m_font;
	m_sw_btn_cons.text = "";
	m_sw_btn_cons.isPressed = false;
	m_sw_btn_cons.isEnabled = true;
	m_sw_btn_cons.setPosition(m_sw_btn_mining.posX + m_sw_btn_mining.sizeX + 10.0f,	m_sw_btn_mining.posY);

	m_sw_btn_plus_green.regular = &m_sw_plus_green;
	m_sw_btn_plus_green.pressed = &m_sw_plus_green_p;
	m_sw_btn_plus_green.sizeX = m_sw_plus_green.Width();
	m_sw_btn_plus_green.sizeY = m_sw_plus_green.Height();
	m_sw_btn_plus_green.font = m_font;
	m_sw_btn_plus_green.text = "";
	m_sw_btn_plus_green.isPressed = false;
	m_sw_btn_plus_green.isEnabled = true;
	m_sw_btn_plus_green.setPosition(m_sw_btn_cons.posX + m_sw_btn_cons.sizeX + 10.0f,	m_sw_btn_cons.posY);

	// complete book
	fprintf(stderr, "Load complete book.\n");
	m_cb_caption.load(
			"app/native/assets/complete_book/completebook_caption.png");
	m_cb_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_cb_caption.Height() - 20.0f);
	m_cb_top_band.load("app/native/assets/complete_book/m_cb_top_band.png");
	m_cb_top_band.setPosition(m_latar.PosX() + 0.0f,
			m_cb_caption.PosY() - m_cb_top_band.Height() - 20.0f);
	m_cb_table_title1.load(
			"app/native/assets/complete_book/m_cb_table_title1.png");
	m_cb_table_title1.setPosition(m_latar.PosX() + 0.0f,
			m_cb_top_band.PosY() - 190.0f);
	m_cb_table_title2.load(
			"app/native/assets/complete_book/m_cb_table_title2.png");
	m_cb_table_title2.setPosition(m_latar.PosX() + 0.0f,
			m_cb_table_title1.PosY() - 300.0f);

	// stock quote
	fprintf(stderr, "Load stock quote.\n");
	m_sq_caption.load("app/native/assets/stock_quote/sq_caption.png");
	m_sq_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_sq_caption.Height() - 20.0f);
	m_sq_table_title.load("app/native/assets/stock_quote/sq_table_title.png");
	m_sq_table_title.setPosition(m_latar.PosX() + 0.0f,
			m_sq_caption.PosY() - m_sq_table_title.Height() - 20.0f);

	// broker quote
	fprintf(stderr, "Load broker quote.\n");
	m_bq_caption.load("app/native/assets/broker_quote/bq_caption.png");
	m_bq_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_bq_caption.Height() - 20.0f);
	m_bq_table_title.load("app/native/assets/broker_quote/bq_table_title.png");
	m_bq_table_title.setPosition(m_latar.PosX() + 0.0f,
			m_bq_caption.PosY() - m_bq_table_title.Height() - 20.0f);

	// stock summary
	fprintf(stderr, "Load stock summary.\n");
	m_ss_caption.load("app/native/assets/stock_summary/ss_caption.png");
	m_ss_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_ss_caption.Height() - 20.0f);
	m_ss_table_title.load("app/native/assets/stock_summary/ss_table_title.png");
	m_ss_table_title.setPosition(m_latar.PosX() + 0.0f,
			m_ss_caption.PosY() - m_ss_table_title.Height() - 20.0f);

	// broker summary
	fprintf(stderr, "Load broker summary.\n");
	m_bs_caption.load("app/native/assets/broker_summary/bs_caption.png");
	m_bs_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_bs_caption.Height() - 20.0f);
	m_bs_table_title.load(
			"app/native/assets/broker_summary/bs_table_title.png");
	m_bs_table_title.setPosition(m_latar.PosX() + 0.0f,
			m_bs_caption.PosY() - m_bs_table_title.Height() - 20.0f);

	// company
	fprintf(stderr, "Load company.\n");
	m_cpy_caption.load("app/native/assets/companies/cpy_caption.png");
	m_cpy_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_cpy_caption.Height() - 20.0f);
	m_cpy_company.load("app/native/assets/companies/company.png");
	m_cpy_company1.load("app/native/assets/companies/company1.png");
	m_cpy_company2.load("app/native/assets/companies/company2.png");
	m_cpy_financial.load("app/native/assets/companies/finance.png");
	m_cpy_financial1.load("app/native/assets/companies/financial1.png");
	m_cpy_financial2.load("app/native/assets/companies/financial2.png");
	m_cpy_ratio.load("app/native/assets/companies/ratio.png");
	m_cpy_ratio1.load("app/native/assets/companies/ratio1.png");
	m_cpy_ratio2.load("app/native/assets/companies/ratio2.png");

	m_cpy_company.setPosition(m_cpy_caption.PosX(), m_cpy_caption.PosY());
	m_cpy_financial.setPosition(m_cpy_company.PosX(), m_cpy_company.PosY());
	m_cpy_ratio.setPosition(m_cpy_company.PosX(), m_cpy_company.PosY());

	m_cpy_btn_company.regular = &m_cpy_company1;
	m_cpy_btn_company.pressed = &m_cpy_company1;
	m_cpy_btn_company.sizeX = m_cpy_company1.Width();
	m_cpy_btn_company.sizeY = m_cpy_company1.Height();
	m_cpy_btn_company.font = m_font;
	m_cpy_btn_company.text = "";
	m_cpy_btn_company.isPressed = false;
	m_cpy_btn_company.isEnabled = true;
	m_cpy_btn_company.setPosition(m_sw_btn_cons.posX + m_sw_btn_cons.sizeX + 10.0f,	m_sw_btn_cons.posY);

	m_cpy_btn_financial.regular = &m_cpy_financial1;
	m_cpy_btn_financial.pressed = &m_cpy_financial1;
	m_cpy_btn_financial.sizeX = m_cpy_financial1.Width();
	m_cpy_btn_financial.sizeY = m_cpy_financial1.Height();
	m_cpy_btn_financial.font = m_font;
	m_cpy_btn_financial.text = "";
	m_cpy_btn_financial.isPressed = false;
	m_cpy_btn_financial.isEnabled = true;
	m_cpy_btn_financial.setPosition(m_sw_btn_cons.posX + m_cpy_btn_financial.sizeX + 10.0f,	m_sw_btn_cons.posY);

	m_cpy_btn_ratio.regular = &m_cpy_ratio1;
	m_cpy_btn_ratio.pressed = &m_cpy_ratio1;
	m_cpy_btn_ratio.sizeX = m_cpy_ratio1.Width();
	m_cpy_btn_ratio.sizeY = m_cpy_ratio1.Height();
	m_cpy_btn_ratio.font = m_font;
	m_cpy_btn_ratio.text = "";
	m_cpy_btn_ratio.isPressed = false;
	m_cpy_btn_ratio.isEnabled = true;
	m_cpy_btn_ratio.setPosition(m_sw_btn_cons.posX + m_cpy_btn_ratio.sizeX + 10.0f,	m_sw_btn_cons.posY);

	//corporate action
	fprintf(stderr, "Load corporate action.\n");
	m_ca_caption.load("app/native/assets/corporate_action/ca_caption.png");
	m_ca_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_ca_caption.Height() - 20.0f);
	m_ca_dividen1.load("app/native/assets/corporate_action/devidend1.png");
	m_ca_dividen2.load("app/native/assets/corporate_action/devidend2.png");
	m_ca_bonus1.load("app/native/assets/corporate_action/bonus1.png");
	m_ca_bonus2.load("app/native/assets/corporate_action/bonus2.png");
	m_ca_bonus3.load("app/native/assets/corporate_action/bonus3.png");
	m_ca_split1.load("app/native/assets/corporate_action/split1.png");
	m_ca_split2.load("app/native/assets/corporate_action/split2.png");
	m_ca_split3.load("app/native/assets/corporate_action/split3.png");
	m_ca_warrant1.load("app/native/assets/corporate_action/warrant1.png");
	m_ca_warrant2.load("app/native/assets/corporate_action/warrant2.png");
	m_ca_warrant3.load("app/native/assets/corporate_action/warrant3.png");
	m_ca_rights1.load("app/native/assets/corporate_action/rights1.png");
	m_ca_rights2.load("app/native/assets/corporate_action/rights2.png");
	m_ca_rights3.load("app/native/assets/corporate_action/rights3.png");
	m_ca_rups1.load("app/native/assets/corporate_action/rups1.png");
	m_ca_rups2.load("app/native/assets/corporate_action/rups2.png");

	m_ca_btn_dividen.regular = &m_ca_dividen1;
	m_ca_btn_dividen.pressed = &m_ca_dividen1;
	m_ca_btn_dividen.sizeX = m_ca_dividen1.Width();
	m_ca_btn_dividen.sizeY = m_ca_dividen1.Height();
	m_ca_btn_dividen.font = m_font;
	m_ca_btn_dividen.text = "";
	m_ca_btn_dividen.isPressed = false;
	m_ca_btn_dividen.isEnabled = true;
	m_ca_btn_dividen.setPosition(m_ca_caption.PosX(), m_ca_caption.PosY() - m_ca_btn_dividen.sizeY - 10.0f);

	m_ca_btn_bonus.regular = &m_ca_bonus1;
	m_ca_btn_bonus.pressed = &m_ca_bonus1;
	m_ca_btn_bonus.sizeX = m_ca_bonus1.Width();
	m_ca_btn_bonus.sizeY = m_ca_bonus1.Height();
	m_ca_btn_bonus.font = m_font;
	m_ca_btn_bonus.text = "";
	m_ca_btn_bonus.isPressed = false;
	m_ca_btn_bonus.isEnabled = true;
	m_ca_btn_bonus.setPosition(m_ca_btn_dividen.posX + m_ca_btn_dividen.sizeX + 10.0f, m_ca_btn_dividen.posY);

	m_ca_btn_split.regular = &m_ca_split1;
	m_ca_btn_split.pressed = &m_ca_split1;
	m_ca_btn_split.sizeX = m_ca_split1.Width();
	m_ca_btn_split.sizeY = m_ca_split1.Height();
	m_ca_btn_split.font = m_font;
	m_ca_btn_split.text = "";
	m_ca_btn_split.isPressed = false;
	m_ca_btn_split.isEnabled = true;
	m_ca_btn_split.setPosition(m_ca_btn_bonus.posX + m_ca_btn_bonus.sizeX + 10.0f, m_ca_btn_bonus.posY);

	m_ca_btn_warrant.regular = &m_ca_warrant1;
	m_ca_btn_warrant.pressed = &m_ca_warrant1;
	m_ca_btn_warrant.sizeX = m_ca_warrant1.Width();
	m_ca_btn_warrant.sizeY = m_ca_warrant1.Height();
	m_ca_btn_warrant.font = m_font;
	m_ca_btn_warrant.text = "";
	m_ca_btn_warrant.isPressed = false;
	m_ca_btn_warrant.isEnabled = true;
	m_ca_btn_warrant.setPosition(m_ca_btn_split.posX + m_ca_btn_split.sizeX + 10.0f, m_ca_btn_split.posY);

	m_ca_btn_rights.regular = &m_ca_dividen1;
	m_ca_btn_rights.pressed = &m_ca_dividen1;
	m_ca_btn_rights.sizeX = m_ca_dividen1.Width();
	m_ca_btn_rights.sizeY = m_ca_dividen1.Height();
	m_ca_btn_rights.font = m_font;
	m_ca_btn_rights.text = "";
	m_ca_btn_rights.isPressed = false;
	m_ca_btn_rights.isEnabled = true;
	m_ca_btn_rights.setPosition(m_ca_btn_warrant.posX + m_ca_btn_warrant.sizeX + 10.0f, m_ca_btn_warrant.posY);

	m_ca_btn_rups.regular = &m_ca_dividen1;
	m_ca_btn_rups.pressed = &m_ca_dividen1;
	m_ca_btn_rups.sizeX = m_ca_dividen1.Width();
	m_ca_btn_rups.sizeY = m_ca_dividen1.Height();
	m_ca_btn_rups.font = m_font;
	m_ca_btn_rups.text = "";
	m_ca_btn_rups.isPressed = false;
	m_ca_btn_rups.isEnabled = true;
	m_ca_btn_rups.setPosition(m_ca_btn_rights.posX + m_ca_btn_rights.sizeX + 10.0f, m_ca_btn_rights.posY);

	// portfolio
	fprintf(stderr, "Load portfolio.\n");
	m_ca_caption.load("app/native/assets/portfolio/pf_caption.png");

	// my account
	fprintf(stderr, "Load my account.\n");
	m_ac_password.load("app/native/assets/password/pw_caption.png");
	m_ac_password.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_ac_password.Height() - 20.0f);
	m_ac_bg_black.load("app/native/assets/password/ac_bg1.png");
	m_ac_bg_black.setPosition(m_latar.PosX(),m_ac_password.PosY() - m_ac_bg_black.Height() - 20.0f );
	m_ac_trading_pin.load("app/native/assets/password/pw_caption.png");
	m_ac_trading_pin.setPosition(m_latar.PosX() + 27.0f,
			m_ac_bg_black.PosY() - m_ac_trading_pin.Height() - 20.0f);
	m_ac_bg_black2 = m_ac_bg_black;
	m_ac_bg_black2.setPosition(m_latar.PosX(),m_ac_trading_pin.PosY() - m_ac_bg_black2.Height() - 20.0f);
	m_ac_save.load("app/native/assets/password/btn_save.png");
	m_ac_save_p.load("app/native/assets/password/btn_save_p.png");
	m_ac_save2.load("app/native/assets/password/btn_save.png");;
	m_ac_save2_p.load("app/native/assets/password/btn_save_p.png");;

	m_btn_save1.regular = &m_ac_save;
	m_btn_save1.pressed = &m_ac_save_p;
	m_btn_save1.sizeX = m_ac_save.Width();
	m_btn_save1.sizeY = m_ac_save.Height();
	m_btn_save1.font = m_font;
	m_btn_save1.text = "";
	m_btn_save1.isPressed = false;
	m_btn_save1.isEnabled = true;
	m_btn_save1.setPosition(m_ac_bg_black.PosX() + m_ac_bg_black.Width() - m_ac_save.Width() - 55.0f, m_ac_bg_black.PosY() + 50.0f);

	m_btn_save2.regular = &m_ac_save2;
	m_btn_save2.pressed = &m_ac_save2_p;
	m_btn_save2.sizeX = m_ac_save2.Width();
	m_btn_save2.sizeY = m_ac_save2.Height();
	m_btn_save2.font = m_font;
	m_btn_save2.text = "";
	m_btn_save2.isPressed = false;
	m_btn_save2.isEnabled = true;
	m_btn_save2.setPosition(m_ac_bg_black2.PosX() + m_ac_bg_black2.Width() - m_ac_save2.Width() - 55.0f, m_ac_bg_black2.PosY() + 50.0f);

	// menu
	fprintf(stderr, "Load menu.\n");
	m_menu_bg.load("app/native/assets/menu/menu_bg.png");
	//m_menu_bg.setPosition(-m_menu_bg.Width(), m_screenHeight - m_menu_bg.Height());
	m_menu_bg.setPosition(0.0f, m_header_bar_bg.PosY() - m_menu_bg.Height());
	m_menu_acc_number.load("app/native/assets/menu/acc_number.png");
	m_menu_acc_number.setPosition(m_menu_bg.PosX(),
			m_header_bar_bg.PosY() - m_menu_acc_number.Height());
	m_menu_tc_bg.load("app/native/assets/menu/menu_tc_bg.png");
	m_menu_tc_bg.setPosition(m_menu_bg.PosX(),
			m_menu_acc_number.PosY() - m_menu_tc_bg.Height());
	m_menu_trade_central.load("app/native/assets/menu/trade_central.png");
	m_menu_charts.load("app/native/assets/menu/charts.png");
	m_menu_informations.load("app/native/assets/menu/informations.png");
	m_menu_portfolio.load("app/native/assets/menu/portfolio.png");
	m_menu_order_trade.load("app/native/assets/menu/order_trade.png");
	m_menu_my_account.load("app/native/assets/menu/my_account.png");
	m_menu_logout.load("app/native/assets/menu/logout.png");
	m_menu_tc_running_trade.load("app/native/assets/menu/tc_running_trade.png");
	m_menu_tc_stock_watch.load("app/native/assets/menu/tc_stock_watch.png");
	m_menu_tc_complete_book.load("app/native/assets/menu/tc_complete_book.png");
	m_menu_tc_stock_quote.load("app/native/assets/menu/tc_stock_quote.png");
	m_menu_tc_broker_quote.load("app/native/assets/menu/tc_broker_quote.png");
	m_menu_tc_stock_summary.load("app/native/assets/menu/tc_stock_summary.png");
	m_menu_tc_broker_summary.load(
			"app/native/assets/menu/tc_broker_summary.png");
	m_menu_tc_non_regular.load("app/native/assets/menu/tc_non_regular.png");
	m_menu_i_news.load("app/native/assets/menu/i_news.png");
	m_menu_i_compinfo.load("app/native/assets/menu/i_compinfo.png");

	m_menu_trade_central_p.load("app/native/assets/menu/trade_central_p.png");
	m_menu_charts_p.load("app/native/assets/menu/charts_p.png");
	m_menu_informations_p.load("app/native/assets/menu/informations_p.png");
	m_menu_portfolio_p.load("app/native/assets/menu/portfolio_p.png");
	m_menu_order_trade_p.load("app/native/assets/menu/order_trade_p.png");
	m_menu_my_account_p.load("app/native/assets/menu/my_account_p.png");
	m_menu_logout_p.load("app/native/assets/menu/logout_p.png");
	m_menu_tc_running_trade_p.load("app/native/assets/menu/tc_running_trade_p.png");
	m_menu_tc_stock_watch_p.load("app/native/assets/menu/tc_stock_watch_p.png");
	m_menu_tc_complete_book_p.load("app/native/assets/menu/tc_complete_book_p.png");
	m_menu_tc_stock_quote_p.load("app/native/assets/menu/tc_stock_quote_p.png");
	m_menu_tc_broker_quote_p.load("app/native/assets/menu/tc_broker_quote_p.png");
	m_menu_tc_stock_summary_p.load("app/native/assets/menu/tc_stock_summary_p.png");
	m_menu_tc_broker_summary_p.load(
			"app/native/assets/menu/tc_broker_summary_p.png");
	m_menu_tc_non_regular_p.load("app/native/assets/menu/tc_non_regular_p.png");
	m_menu_i_news_p.load("app/native/assets/menu/i_news_p.png");
	m_menu_i_compinfo_p.load("app/native/assets/menu/i_compinfo_p.png");

	// button menu trade central
	m_menu_btn_trade_central.regular = &m_menu_trade_central;
	m_menu_btn_trade_central.pressed = &m_menu_trade_central;
	m_menu_btn_trade_central.sizeX = m_menu_trade_central.Width();
	m_menu_btn_trade_central.sizeY = m_menu_trade_central.Height();
	m_menu_btn_trade_central.font = m_font;
	m_menu_btn_trade_central.text = "";
	m_menu_btn_trade_central.isPressed = false;
	m_menu_btn_trade_central.isEnabled = true;
	m_menu_btn_trade_central.setPosition(m_menu_bg.PosX(),
			m_menu_acc_number.PosY() - m_menu_trade_central.Height());
	// button menu charts
	m_menu_btn_charts.regular = &m_menu_charts;
	m_menu_btn_charts.pressed = &m_menu_charts;
	m_menu_btn_charts.sizeX = m_menu_charts.Width();
	m_menu_btn_charts.sizeY = m_menu_charts.Height();
	m_menu_btn_charts.font = m_font;
	m_menu_btn_charts.text = "";
	m_menu_btn_charts.isPressed = false;
	m_menu_btn_charts.isEnabled = true;
	m_menu_btn_charts.setPosition(m_menu_bg.PosX(),
			m_menu_trade_central.PosY() - m_menu_charts.Height());
	// button menu information
	m_menu_btn_informations.regular = &m_menu_informations;
	m_menu_btn_informations.pressed = &m_menu_informations;
	m_menu_btn_informations.sizeX = m_menu_informations.Width();
	m_menu_btn_informations.sizeY = m_menu_informations.Height();
	m_menu_btn_informations.font = m_font;
	m_menu_btn_informations.text = "";
	m_menu_btn_informations.isPressed = false;
	m_menu_btn_informations.isEnabled = true;
	m_menu_btn_informations.setPosition(m_menu_bg.PosX(),
			m_menu_btn_charts.posY - m_menu_informations.Height());
	// button menu portfolio
	m_menu_btn_portfolio.regular = &m_menu_portfolio;
	m_menu_btn_portfolio.pressed = &m_menu_portfolio;
	m_menu_btn_portfolio.sizeX = m_menu_portfolio.Width();
	m_menu_btn_portfolio.sizeY = m_menu_portfolio.Height();
	m_menu_btn_portfolio.font = m_font;
	m_menu_btn_portfolio.text = "";
	m_menu_btn_portfolio.isPressed = false;
	m_menu_btn_portfolio.isEnabled = true;
	m_menu_btn_portfolio.setPosition(m_menu_bg.PosX(),
			m_menu_btn_informations.posY - m_menu_portfolio.Height());
	// button menu charts
	m_menu_btn_order_trade.regular = &m_menu_order_trade;
	m_menu_btn_order_trade.pressed = &m_menu_order_trade;
	m_menu_btn_order_trade.sizeX = m_menu_order_trade.Width();
	m_menu_btn_order_trade.sizeY = m_menu_order_trade.Height();
	m_menu_btn_order_trade.font = m_font;
	m_menu_btn_order_trade.text = "";
	m_menu_btn_order_trade.isPressed = false;
	m_menu_btn_order_trade.isEnabled = true;
	m_menu_btn_order_trade.setPosition(m_menu_bg.PosX(),
			m_menu_btn_portfolio.posY - m_menu_order_trade.Height());
	// button menu my account
	m_menu_btn_my_account.regular = &m_menu_my_account;
	m_menu_btn_my_account.pressed = &m_menu_my_account;
	m_menu_btn_my_account.sizeX = m_menu_my_account.Width();
	m_menu_btn_my_account.sizeY = m_menu_my_account.Height();
	m_menu_btn_my_account.font = m_font;
	m_menu_btn_my_account.text = "";
	m_menu_btn_my_account.isPressed = false;
	m_menu_btn_my_account.isEnabled = true;
	m_menu_btn_my_account.setPosition(m_menu_bg.PosX(),
			m_menu_btn_order_trade.posY - m_menu_my_account.Height());
	// button menu logout
	m_menu_btn_logout.regular = &m_menu_logout;
	m_menu_btn_logout.pressed = &m_menu_logout;
	m_menu_btn_logout.sizeX = m_menu_logout.Width();
	m_menu_btn_logout.sizeY = m_menu_logout.Height();
	m_menu_btn_logout.font = m_font;
	m_menu_btn_logout.text = "";
	m_menu_btn_logout.isPressed = false;
	m_menu_btn_logout.isEnabled = true;
	m_menu_btn_logout.setPosition(m_menu_bg.PosX(),
			m_menu_btn_my_account.posY - m_menu_logout.Height());

	m_menu_tc_btn_running_trade.regular = &m_menu_tc_running_trade;
	m_menu_tc_btn_running_trade.pressed = &m_menu_tc_running_trade;
	m_menu_tc_btn_running_trade.sizeX = m_menu_tc_running_trade.Width();
	m_menu_tc_btn_running_trade.sizeY = m_menu_tc_running_trade.Height();
	m_menu_tc_btn_running_trade.font = m_font;
	m_menu_tc_btn_running_trade.text = "";
	m_menu_tc_btn_running_trade.isPressed = false;
	m_menu_tc_btn_running_trade.isEnabled = true;
	m_menu_tc_btn_running_trade.setPosition(m_menu_bg.PosX(),
			m_menu_btn_trade_central.posY - m_menu_tc_running_trade.Height());

	m_menu_tc_btn_stock_watch.regular = &m_menu_tc_stock_watch;
	m_menu_tc_btn_stock_watch.pressed = &m_menu_tc_stock_watch;
	m_menu_tc_btn_stock_watch.sizeX = m_menu_tc_stock_watch.Width();
	m_menu_tc_btn_stock_watch.sizeY = m_menu_tc_stock_watch.Height();
	m_menu_tc_btn_stock_watch.font = m_font;
	m_menu_tc_btn_stock_watch.text = "";
	m_menu_tc_btn_stock_watch.isPressed = false;
	m_menu_tc_btn_stock_watch.isEnabled = true;
	m_menu_tc_btn_stock_watch.setPosition(m_menu_bg.PosX(),
			m_menu_tc_btn_running_trade.posY - m_menu_tc_stock_watch.Height());

	m_menu_tc_btn_complete_book.regular = &m_menu_tc_complete_book;
	m_menu_tc_btn_complete_book.pressed = &m_menu_tc_complete_book;
	m_menu_tc_btn_complete_book.sizeX = m_menu_tc_complete_book.Width();
	m_menu_tc_btn_complete_book.sizeY = m_menu_tc_complete_book.Height();
	m_menu_tc_btn_complete_book.font = m_font;
	m_menu_tc_btn_complete_book.text = "";
	m_menu_tc_btn_complete_book.isPressed = false;
	m_menu_tc_btn_complete_book.isEnabled = true;
	m_menu_tc_btn_complete_book.setPosition(m_menu_bg.PosX(),
			m_menu_tc_btn_stock_watch.posY - m_menu_tc_complete_book.Height());

	m_menu_tc_btn_stock_quote.regular = &m_menu_tc_stock_quote;
	m_menu_tc_btn_stock_quote.pressed = &m_menu_tc_stock_quote;
	m_menu_tc_btn_stock_quote.sizeX = m_menu_tc_stock_quote.Width();
	m_menu_tc_btn_stock_quote.sizeY = m_menu_tc_stock_quote.Height();
	m_menu_tc_btn_stock_quote.font = m_font;
	m_menu_tc_btn_stock_quote.text = "";
	m_menu_tc_btn_stock_quote.isPressed = false;
	m_menu_tc_btn_stock_quote.isEnabled = true;
	m_menu_tc_btn_stock_quote.setPosition(m_menu_bg.PosX(),
			m_menu_tc_btn_complete_book.posY - m_menu_tc_stock_quote.Height());

	m_menu_tc_btn_broker_quote.regular = &m_menu_tc_broker_quote;
	m_menu_tc_btn_broker_quote.pressed = &m_menu_tc_broker_quote;
	m_menu_tc_btn_broker_quote.sizeX = m_menu_tc_broker_quote.Width();
	m_menu_tc_btn_broker_quote.sizeY = m_menu_tc_broker_quote.Height();
	m_menu_tc_btn_broker_quote.font = m_font;
	m_menu_tc_btn_broker_quote.text = "";
	m_menu_tc_btn_broker_quote.isPressed = false;
	m_menu_tc_btn_broker_quote.isEnabled = true;
	m_menu_tc_btn_broker_quote.setPosition(m_menu_bg.PosX(),
			m_menu_tc_btn_stock_quote.posY - m_menu_tc_broker_quote.Height());

	m_menu_tc_btn_stock_summary.regular = &m_menu_tc_stock_summary;
	m_menu_tc_btn_stock_summary.pressed = &m_menu_tc_stock_summary;
	m_menu_tc_btn_stock_summary.sizeX = m_menu_tc_stock_summary.Width();
	m_menu_tc_btn_stock_summary.sizeY = m_menu_tc_stock_summary.Height();
	m_menu_tc_btn_stock_summary.font = m_font;
	m_menu_tc_btn_stock_summary.text = "";
	m_menu_tc_btn_stock_summary.isPressed = false;
	m_menu_tc_btn_stock_summary.isEnabled = true;
	m_menu_tc_btn_stock_summary.setPosition(m_menu_bg.PosX(),
			m_menu_tc_btn_broker_quote.posY - m_menu_tc_stock_summary.Height());

	m_menu_tc_btn_broker_summary.regular = &m_menu_tc_broker_summary;
	m_menu_tc_btn_broker_summary.pressed = &m_menu_tc_broker_summary;
	m_menu_tc_btn_broker_summary.sizeX = m_menu_tc_broker_summary.Width();
	m_menu_tc_btn_broker_summary.sizeY = m_menu_tc_broker_summary.Height();
	m_menu_tc_btn_broker_summary.font = m_font;
	m_menu_tc_btn_broker_summary.text = "";
	m_menu_tc_btn_broker_summary.isPressed = false;
	m_menu_tc_btn_broker_summary.isEnabled = true;
	m_menu_tc_btn_broker_summary.setPosition(m_menu_bg.PosX(),
			m_menu_tc_btn_stock_summary.posY
					- m_menu_tc_broker_summary.Height());

	m_menu_tc_btn_non_regular.regular = &m_menu_tc_non_regular;
	m_menu_tc_btn_non_regular.pressed = &m_menu_tc_non_regular;
	m_menu_tc_btn_non_regular.sizeX = m_menu_tc_non_regular.Width();
	m_menu_tc_btn_non_regular.sizeY = m_menu_tc_non_regular.Height();
	m_menu_tc_btn_non_regular.font = m_font;
	m_menu_tc_btn_non_regular.text = "";
	m_menu_tc_btn_non_regular.isPressed = false;
	m_menu_tc_btn_non_regular.isEnabled = true;
	m_menu_tc_btn_non_regular.setPosition(m_menu_bg.PosX(),
			m_menu_tc_btn_broker_summary.posY - m_menu_tc_non_regular.Height());

	m_menu_i_btn_news.regular = &m_menu_i_news;
	m_menu_i_btn_news.pressed = &m_menu_i_news_p;
	m_menu_i_btn_news.sizeX = m_menu_i_news.Width();
	m_menu_i_btn_news.sizeY = m_menu_i_news.Height();
	m_menu_i_btn_news.font = m_font;
	m_menu_i_btn_news.text = "";
	m_menu_i_btn_news.isPressed = false;
	m_menu_i_btn_news.isEnabled = true;
	m_menu_i_btn_news.setPosition(m_menu_bg.PosX(),
			m_menu_btn_informations.posY - m_menu_i_news.Height());

	m_menu_i_btn_compinfo.regular = &m_menu_i_compinfo;
	m_menu_i_btn_compinfo.pressed = &m_menu_i_compinfo_p;
	m_menu_i_btn_compinfo.sizeX = m_menu_i_compinfo.Width();
	m_menu_i_btn_compinfo.sizeY = m_menu_i_compinfo.Height();
	m_menu_i_btn_compinfo.font = m_font;
	m_menu_i_btn_compinfo.text = "";
	m_menu_i_btn_compinfo.isPressed = false;
	m_menu_i_btn_compinfo.isEnabled = true;
	m_menu_i_btn_compinfo.setPosition(m_menu_bg.PosX(),
			m_menu_i_btn_news.posY - m_menu_i_compinfo.Height());

	// password
	m_pw_caption.load("app/native/assets/password/pw_caption.png");
	m_pw_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_pw_caption.Height() - 20.0f);
	m_pw_text_bg.load("app/native/assets/password/pw_text_bg.png");
	m_pw_save.load("app/native/assets/password/btn_save.png");
	m_pw_btn_save.regular = &m_pw_save;
	m_pw_btn_save.pressed = &m_pw_save;
	m_pw_btn_save.sizeX = m_pw_save.Width();
	m_pw_btn_save.sizeY = m_pw_save.Height();
	m_pw_btn_save.font = m_font;
	m_pw_btn_save.text = "";
	m_pw_btn_save.isPressed = false;
	m_pw_btn_save.isEnabled = true;
	m_pw_btn_save.setPosition(0.0f, 0.0f);

	// portfolio
	m_pf_caption.load("app/native/assets/portfolio/pf_caption.png");
	m_pf_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_pf_caption.Height() - 20.0f);
	m_pf_table_title.load("app/native/assets/portfolio/pf_table_title.png");
	m_pf_table_title.setPosition(m_latar.PosX() + 0.0f,
			m_pf_caption.PosY() - m_pf_table_title.Height() - 160.0f);
	m_pf_acc_number.load("app/native/assets/portfolio/acc_no.png");
	m_pf_acc_number.setPosition(m_latar.PosX() + 0.0f, m_screenHeight - 262.0f);

	// research
	m_research_caption.load("app/native/assets/research/research_caption.png");
	m_research_caption.setPosition(m_latar.PosX() + 27.0f,
			m_headerHeight - m_research_caption.Height() - 20.0f);

	// chart
	m_chart_bg.load("app/native/assets/charts/chart_bg.png");
	m_chart_bg.setPosition(0.0f, 0.0f);
	m_chart_post_bar.load("app/native/assets/charts/post_2.png");
	//m_chart_post_bar.setPosition(m_chart_bg.PosX(), m_chart_bg.PosY() + m_screenHeight - m_chart_post_bar.Height() - 2.0f);
	m_chart_post_bar.setPosition(m_latar.PosX(), m_headerHeight);
	m_chart_caption_bottom.load("app/native/assets/charts/chart_caption_bottom.png");
	m_chart_caption_bottom.setPosition(m_chart_bg.PosX() +20.0f, 27.0f);
	m_chart_text_bg.load("app/native/assets/charts/text_bg.png");
	m_chart_text_bg.setPosition(m_chart_bg.PosX() +80.0f, 570.0f);
	m_icon_search.load("app/native/assets/charts/icon_search.png");
	m_icon_search.setPosition(m_chart_text_bg.PosX() + m_chart_text_bg.Width() - m_icon_search.Width(), m_chart_text_bg.PosY());
	m_chart_1day_big.load("app/native/assets/charts/1day_big.png");
	m_chart_1day_big.setPosition(m_chart_bg.PosX() +20.0f, 27.0f);
	m_chart_1week_big.load("app/native/assets/charts/1week_big.png");
	m_chart_1week_big.setPosition(m_chart_bg.PosX() +20.0f, 27.0f);
	m_chart_1month_big.load("app/native/assets/charts/1month_big.png");
	m_chart_1month_big.setPosition(m_chart_bg.PosX() +20.0f, 27.0f);
	m_chart_1year_big.load("app/native/assets/charts/1year_big.png");
	m_chart_1year_big.setPosition(m_chart_bg.PosX() +20.0f, 27.0f);
	m_chart_3year_big.load("app/native/assets/charts/3year_big.png");
	m_chart_3year_big.setPosition(m_chart_bg.PosX() +20.0f, 27.0f);
	m_chart_1day_small.load("app/native/assets/charts/1day_small.png");
	m_chart_1week_small.load("app/native/assets/charts/1week_small.png");
	m_chart_1month_small.load("app/native/assets/charts/1month_small.png");
	m_chart_1year_small.load("app/native/assets/charts/1year_small.png");
	m_chart_3year_small.load("app/native/assets/charts/3year_small.png");

	m_chart_btn_search.regular = &m_icon_search;
	m_chart_btn_search.pressed = &m_icon_search;
	m_chart_btn_search.sizeX = m_icon_search.Width();
	m_chart_btn_search.sizeY = m_icon_search.Height();
	m_chart_btn_search.font = m_font;
	m_chart_btn_search.text = "";
	m_chart_btn_search.isPressed = false;
	m_chart_btn_search.isEnabled = true;
	m_chart_btn_search.setPosition(m_chart_text_bg.PosX() + m_chart_text_bg.Width() - m_icon_search.Width(), m_chart_text_bg.PosY());

	m_chart_btn_1day.regular = &m_chart_1day_small;
	m_chart_btn_1day.pressed = &m_chart_1day_small;
	m_chart_btn_1day.sizeX = m_chart_1day_small.Width();
	m_chart_btn_1day.sizeY = m_chart_1day_small.Height();
	m_chart_btn_1day.font = m_font;
	m_chart_btn_1day.text = "";
	m_chart_btn_1day.isPressed = false;
	m_chart_btn_1day.isEnabled = true;
	m_chart_btn_1day.setPosition(m_chart_caption_bottom.PosY() + 222.0f, m_chart_caption_bottom.PosX() + 35.0f);

	m_chart_btn_1week.regular = &m_chart_1week_small;
	m_chart_btn_1week.pressed = &m_chart_1week_small;
	m_chart_btn_1week.sizeX = m_chart_1week_small.Width();
	m_chart_btn_1week.sizeY = m_chart_1week_small.Height();
	m_chart_btn_1week.font = m_font;
	m_chart_btn_1week.text = "";
	m_chart_btn_1week.isPressed = false;
	m_chart_btn_1week.isEnabled = true;
	m_chart_btn_1week.setPosition(m_chart_btn_1day.posX, m_chart_btn_1day.posY);

	m_chart_btn_1month.regular = &m_chart_1month_small;
	m_chart_btn_1month.pressed = &m_chart_1month_small;
	m_chart_btn_1month.sizeX = m_chart_1month_small.Width();
	m_chart_btn_1month.sizeY = m_chart_1month_small.Height();
	m_chart_btn_1month.font = m_font;
	m_chart_btn_1month.text = "";
	m_chart_btn_1month.isPressed = false;
	m_chart_btn_1month.isEnabled = true;
	m_chart_btn_1month.setPosition(m_chart_btn_1day.posX + m_chart_btn_1day.sizeX + 10.0f, m_chart_btn_1day.posY);

	m_chart_btn_1year.regular = &m_chart_1year_small;
	m_chart_btn_1year.pressed = &m_chart_1year_small;
	m_chart_btn_1year.sizeX = m_chart_1year_small.Width();
	m_chart_btn_1year.sizeY = m_chart_1year_small.Height();
	m_chart_btn_1year.font = m_font;
	m_chart_btn_1year.text = "";
	m_chart_btn_1year.isPressed = false;
	m_chart_btn_1year.isEnabled = true;
	m_chart_btn_1year.setPosition(m_chart_btn_1month.posX + m_chart_btn_1month.sizeX + 10.0f, m_chart_btn_1month.posY);

	m_chart_btn_3year.regular = &m_chart_3year_small;
	m_chart_btn_3year.pressed = &m_chart_3year_small;
	m_chart_btn_3year.sizeX = m_chart_3year_small.Width();
	m_chart_btn_3year.sizeY = m_chart_3year_small.Height();
	m_chart_btn_3year.font = m_font;
	m_chart_btn_3year.text = "";
	m_chart_btn_3year.isPressed = false;
	m_chart_btn_3year.isEnabled = true;
	m_chart_btn_3year.setPosition(m_chart_btn_1year.posX + m_chart_btn_1year.sizeX + 10.0f, m_chart_btn_1year.posY);

	// tradelist
	m_tl_order_caption.load("app/native/assets/orderlist/orderlist_caption.png");
	m_tl_order_caption.setPosition(m_latar.PosX() + 27.0f,	m_headerHeight - m_tl_order_caption.Height() - 20.0f);
	m_tl_order_table_caption.load("app/native/assets/orderlist/orderlist_table_title.png");
	m_tl_order_table_caption.setPosition(m_latar.PosX(),	m_tl_order_caption.PosY() - m_tl_order_table_caption.Height() - 20.0f);
	m_tl_tradelist_caption.load("app/native/assets/orderlist/tradelist_caption.png");
	m_tl_tradelist_caption.setPosition(m_latar.PosX() + 27.0f,	m_tl_order_table_caption.PosY() - m_tl_tradelist_caption.Height() - 190.0f);
	m_tl_tradelist_table_caption.load("app/native/assets/orderlist/orderlist_table_title.png");
	m_tl_tradelist_table_caption.setPosition(m_latar.PosX(),	m_tl_tradelist_caption.PosY() - m_tl_order_table_caption.Height() - 20.0f);


	m_state = HOME;
	//m_state = RUNNING_TRADE;
	m_ePosX = 0.0f;
	m_ePosY = 0.0f;
	m_bMenuShowAnimation = false;
	m_bMenuHideAnimation = false;
	m_fmenu_width = m_menu_bg.Width();
	m_fmenu_animation = -m_fmenu_width;

	m_u_name = "";
	m_u_pass = "";
	m_sIhsg_val = "";
	m_sIhsg_volume = "";
	m_sIhsg_percent = "";
	m_bUsernameFocus = false;
	m_bPasswordFocus = false;

	m_sAccID = "";
	m_sStockCode = "";
	m_sPrice = "";
	m_sLot = "";
	m_sMaxBuy = "";
	m_sStockValue = "";
	m_sTransFee = "";
	m_sPayable = "";

	companyInfoFlag = 0;		// 0: company, 1: financial, 2: ratio.
	corporateActionFlag = 0;	// 0: devidend, 1: bonus, 2: split, 3: warrant, 4: rights, 5 rups.

	loginStatus = NOT_SIGNIN;

	fprintf(stderr, "Finish instantiate panin.\n");
}

//panin::~panin() {
//	// TODO Auto-generated destructor stub
//}

void panin::enable2D() {
	//Initialize GL for 2D rendering
	glViewport(0, 0, static_cast<int>(m_screenWidth),
			static_cast<int>(m_screenHeight));

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

void panin::enable2D_land() {
	//Initialize GL for 2D rendering
	glViewport(0, 0, static_cast<int>(m_screenWidth),
			static_cast<int>(m_screenHeight));

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
			updateHome();
			renderHome();
			if (loginStatus == SIGNEDIN) {
				m_state = RUNNING_TRADE;
				m_platform.user_name = m_u_name;
				m_platform.user_pw	= m_u_pass;
				m_u_name = "";
				m_u_pass = "";
			} else if (loginStatus == SIGN_FAILED) {
				m_u_name = "username false";
				loginStatus = NOT_SIGNIN;
				m_state = HOME;
				//m_platform.displayPrompt("wrong user.\n");
			}
			break;

		case LOADING:
			fprintf(stderr, "eka at loading.");
			//update();
			//renderGame();
			break;

		case RUNNING_TRADE:
			update();
			renderRunningTrade();
			ambilDataRunningTrade();
			break;

		case STOCK_WATCH:
			update();
			renderStockWatch();
			break;

		case COMPLETE_BOOK:
			update();
			renderCompleteBook();
			break;

		case STOCK_QUOTE:
			update();
			renderStockQuote();
			break;

		case BROKER_QUOTE:
			update();
			renderBrokerSummary();
			break;

		case STOCK_SUMMARY:
			update();
			renderStockSummary();
			break;

		case BROKER_SUMMARY:
			update();
			renderBrokerSummary();
			break;

		case NON_REGULAR:
			update();
			renderNonRegular();
			break;

		case CHARTS:
			update();
			renderCharts();
			break;

		case INFORMATIONS:
			update();
			renderInformations();
			break;

		case NEWS:
			update();
			renderNews();
			break;

		case COMPANY_INFO:
			update();
			renderCompanyInfo();
			break;

		case PORTFOLIO:
			update();
			renderPortfolio();
			break;

		case ORDER_TRADE:
			update();
			renderOrderTrade();
			break;

		case MY_ACCOUNT:
			update();
			renderMyAccount();
			break;

		default:
			fprintf(stderr, "eka at default.");
			break;
		}
	}
}

void panin::update() {
	if (m_bMenuShowAnimation) {
		if (m_fmenu_animation < 0.0f) {
			m_fmenu_animation += 20.0f;
		} else {
			m_bMenuShowAnimation = false;
			m_bMenuActive = true;
			m_fmenu_animation = 0.0f;
		}
	} else if (m_bMenuHideAnimation) {
		if (m_fmenu_animation > -m_fmenu_width) {
			m_fmenu_animation -= 20.0f;
		} else {
			m_bMenuHideAnimation = false;
			m_bMenuActive = false;
			m_fmenu_animation = 0.0f;
		}
	}

	m_ePosX = m_fmenu_animation;

}

void panin::updateForLandscape() {
	m_chart_post_bar.setPosition(m_latar.PosX(), m_screenHeight - m_chart_post_bar.Height() -2.0f);
	m_btn_info.setPosition(
			m_chart_post_bar.PosX() + m_screenWidth - 1.5 * m_btn_info.sizeX,
			m_chart_post_bar.PosY()
					+ (m_chart_post_bar.Height() - m_btn_info.sizeY) / 2);

	m_btn_menu.setPosition(m_chart_post_bar.PosX() + 0.5 * m_btn_menu.sizeX,
			m_chart_post_bar.PosY()
						+ (m_chart_post_bar.Height() - m_btn_menu.sizeY) / 2);

	m_menu_bg.setPosition(0.0f, m_chart_post_bar.PosY() - m_menu_bg.Height());

	m_menu_acc_number.setPosition(m_menu_bg.PosX(),
			m_chart_post_bar.PosY() - m_menu_acc_number.Height());

	m_menu_tc_bg.setPosition(m_menu_bg.PosX(),
			m_menu_acc_number.PosY() - m_menu_tc_bg.Height());

	m_menu_btn_trade_central.setPosition(m_menu_bg.PosX(),
			m_menu_acc_number.PosY() - m_menu_trade_central.Height());
}

void panin::updateForPotrait() {

	m_btn_info.setPosition(
			m_header_bar_bg.PosX() + m_screenWidth - 1.5 * m_btn_info.sizeX,
			m_header_bar_bg.PosY()
					+ (m_header_bar_bg.Height() - m_btn_info.sizeY) / 2);

	m_btn_menu.setPosition(m_header_bar_bg.PosX() + 0.5 * m_btn_menu.sizeX,
				m_header_bar_bg.PosY()
						+ (m_header_bar_bg.Height() - m_btn_menu.sizeY) / 2);

	m_menu_bg.setPosition(0.0f, m_header_bar_bg.PosY() - m_menu_bg.Height());

	m_menu_acc_number.setPosition(m_menu_bg.PosX(),
			m_header_bar_bg.PosY() - m_menu_acc_number.Height());

	m_menu_tc_bg.setPosition(m_menu_bg.PosX(),
			m_menu_acc_number.PosY() - m_menu_tc_bg.Height());

	m_menu_btn_trade_central.setPosition(m_menu_bg.PosX(),
			m_menu_acc_number.PosY() - m_menu_trade_central.Height());
}

void panin::updateHome() {
	//get suitable value.
	if (m_u_name.length() == 0) {
		if (!m_bUsernameFocus) {
			m_u_name = "username";
		}
	}
	if (m_u_pass.length() == 0) {
		if (!m_bPasswordFocus) {
			m_u_pass = "password";
		}
	}

	if (m_bUsernameFocus)
	{
		m_btn_home_username.regular = &m_username_textfield_regular;
		virtualkeyboard_show();
	}
	else
	{
		m_btn_home_username.regular = &m_username_textfield_default;
	}

	if (m_bPasswordFocus)
	{
		m_btn_home_password.regular = &m_password_textfield_regular;
		virtualkeyboard_show();
	}
	else
	{
		m_btn_home_password.regular = &m_password_textfield_default;
	}
	m_sIhsg_val = "5000";
	m_sIhsg_volume = "3415.10 bn";
	m_sIhsg_percent = "17.77 (30%)";

}

void panin::renderHome() {

	m_platform.beginRender();

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (m_bShowMenu)
		m_bShowMenu = false;

	m_latar.draw();
	m_logo.draw();
	//m_username_textfield_regular.draw();
	//m_password_textfield_regular.draw();
	m_btn_home_username.draw();
	m_btn_home_password.draw();
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
	float text_width, text_height, pos_x, pos_y;
	bbutil_measure_text(m_font_global, m_u_name.c_str(), &text_width,
			&text_height);
	pos_x = m_btn_home_username.posX + 300.0f;
	pos_y = m_btn_home_username.posY + 30.0f;
	bbutil_render_text(m_font_global, m_u_name.c_str(), pos_x, pos_y, 0.05f,
			0.05f, 0.05f, 1.0f);

	bbutil_measure_text(m_font_global, m_u_pass.c_str(), &text_width,
			&text_height);
	pos_y = m_btn_home_password.posY + 30.0f;
	bbutil_render_text(m_font_global, m_u_pass.c_str(), pos_x, pos_y, 0.05f,
			0.05f, 0.05f, 1.0f);

	bbutil_measure_text(m_font_ihsg_val, m_sIhsg_val.c_str(), &text_width,
			&text_height);
	pos_x = (m_screenWidth - text_width) / 2;
	pos_y = m_screenHeight - 990;
	bbutil_render_text(m_font_ihsg_val, m_sIhsg_val.c_str(), pos_x, pos_y,
			0.05f, 1.0f, 0.05f, 1.0f);

	float p1;
	bbutil_measure_text(m_font_ihsg_vol, m_sIhsg_volume.c_str(), &text_width,
			&text_height);
	p1 = text_width;
	pos_x = (m_screenWidth - text_width) / 2;
	pos_y = m_screenHeight - 1050;
	bbutil_render_text(m_font_ihsg_vol, m_sIhsg_volume.c_str(), pos_x, pos_y,
			0.95f, 0.95f, 0.95f, 1.0f);

	const char* waktu = m_platform.getDateTime();
	bbutil_measure_text(m_font_tanggal, waktu, &text_width, &text_height);
	pos_x = (m_screenWidth - text_width) / 2;
	pos_y = m_screenHeight - 1125;
	//bbutil_render_text(m_font_tanggal, "30 September 2013 23:59:59", pos_x, pos_y, 0.92f, 0.73f, 0.33f, 1.0f);
	bbutil_render_text(m_font_tanggal, waktu, pos_x, pos_y, 0.92f, 0.73f, 0.33f,
			1.0f);

	bbutil_render_text(m_font_tanggal, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	if (m_bShowHomeSetel) {
		//fprintf(stderr, "render HomeSetel.\n");
		renderHomeSetel();
	}

	m_platform.finishRender();
}

void panin::renderHomeSetel() {
	//glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//m_dialog_bg.draw();
	m_setel_bg.draw();
	//m_textfield_bg.setPosition(80.0f, m_screenHeight - 686.0f);
	//m_textfield_bg.draw();
	//m_textfield_bg.setPosition(80.0f, m_screenHeight - 784.0f);
	//m_textfield_bg.draw();
	m_btn_setel_default.draw();
	m_btn_setel_set107.draw();
	m_btn_setel_set202.draw();
	m_btn_setel_save.draw();
	m_btn_setel_x.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	//bbutil_render_text(m_font, "SERVER A", 80.0f, m_screenHeight - 644.0f, 1.0f,
	//		1.0f, 1.0f, 1.0f);
	//bbutil_render_text(m_font, "SERVER B", 80.0f, m_screenHeight - 744.0f, 1.0f,
	//		1.0f, 1.0f, 1.0f);
	//bbutil_render_text(m_font, "172.31.2.78:8080", 120.0f, m_screenHeight - 682.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	//bbutil_render_text(m_font, "172.31.2.78:8443", 120.0f, m_screenHeight - 780.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font, m_platform.server1.c_str(), m_setel_bg.PosX() + 140.0f,
			m_setel_bg.PosY() + 250.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font, m_platform.server2.c_str(), m_setel_bg.PosX() + 140.0f,
			m_setel_bg.PosY() + 152.0f, 1.0f, 1.0f, 1.0f, 1.0f);

}

void panin::renderHomeInfo() {

}

void panin::renderMenu() {
	m_menu_bg.draw();
	m_menu_acc_number.draw();
	m_menu_btn_trade_central.draw();
	float p1 = m_menu_btn_trade_central.posY;
	if (m_bShowSubmenuTC) {
		m_menu_tc_btn_running_trade.draw();
		m_menu_tc_btn_stock_watch.draw();
		m_menu_tc_btn_complete_book.draw();
		m_menu_tc_btn_stock_quote.draw();
		m_menu_tc_btn_broker_quote.draw();
		m_menu_tc_btn_stock_summary.draw();
		m_menu_tc_btn_broker_summary.draw();
		m_menu_tc_btn_non_regular.draw();
		p1 = m_menu_tc_btn_non_regular.posY;
	}

	m_menu_btn_charts.setPosition(m_menu_btn_charts.posX,
			p1 - m_menu_btn_charts.sizeY);
	m_menu_btn_charts.draw();
	m_menu_btn_informations.setPosition(m_menu_btn_informations.posX,
			m_menu_btn_charts.posY - m_menu_btn_informations.sizeY);
	m_menu_btn_informations.draw();
	p1 = m_menu_btn_informations.posY;
	if (m_bShowSubmenuInformation)
	{
		m_menu_i_btn_news.draw();
		m_menu_i_btn_compinfo.draw();
		p1 = m_menu_i_btn_compinfo.posY;
	}
	m_menu_btn_portfolio.setPosition(m_menu_btn_portfolio.posX,
			p1 - m_menu_btn_portfolio.sizeY);
	m_menu_btn_portfolio.draw();
	m_menu_btn_order_trade.setPosition(m_menu_btn_order_trade.posX,
			m_menu_btn_portfolio.posY - m_menu_btn_order_trade.sizeY);
	m_menu_btn_order_trade.draw();
	m_menu_btn_my_account.setPosition(m_menu_btn_my_account.posX,
			m_menu_btn_order_trade.posY - m_menu_btn_my_account.sizeY);
	m_menu_btn_my_account.draw();
	m_menu_btn_logout.setPosition(m_menu_btn_logout.posX,
			m_menu_btn_my_account.posY - m_menu_btn_logout.sizeY);
	m_menu_btn_logout.draw();

}

void panin::renderRunningTrade() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

//	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation)
//	{
//		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
//		//renderMenu();
//		m_menu_bg.draw();
//	}
	m_latar.draw();

	addHeader();

	m_rt_caption.draw();
	m_rt_table_title.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	float myY = m_rt_table_title.PosY() - 30;

	if (bIsGettingRT)
	{
		std::string hasil = osStream.str();
		std::vector<std::string>::size_type nol = 0;
		if (hasil.length() > 0)
		{
			std::vector<std::string> vRTStream;
			vRTStream = split(osStream.str(), '\n');

			//vector <int>::size_type ukuran;

			if (vRTStream.capacity() > nol)
			{
				fprintf(stderr, "----------------------\n");
				for (std::vector<std::string>::iterator iter = vRTStream.begin(); iter != vRTStream.end(); ++iter)
				{
					std::basic_string <char>::size_type pos_start, pos_end;
					pos_start	= (*iter).find('[');
					pos_end	= (*iter).find(']');
					std::string s1 = (*iter).substr(pos_start +1, s1.length() - (s1.length() - pos_end) - pos_start -1);
					//fprintf(stderr, "hasil RT: %s.\n", s1.c_str());

					std::vector<std::string>::size_type batas = 45;
					m_vRT.push_back(s1);
					if (m_vRT.capacity() > batas)
					{
						//fprintf(stderr, "erase data. %d\n", m_vRT.size());
						m_vRT.erase(m_vRT.begin());
					}
//					do
//					{
//						fprintf(stderr, "erase data. %d\n", m_vRT.size());
//						m_vRT.erase(m_vRT.begin());
//					} while (m_vRT.capacity() > batas);
				}
			}
		}

		if (m_vRT.capacity() > nol)
		{
			fprintf(stderr, "m_vRT size: %d\n", m_vRT.size());
			std::vector<std::string>::iterator iter = m_vRT.begin();
			do {
				std::string s1 = *iter;
				fprintf(stderr, "%s\n", s1.c_str());
				std::vector<std::string> vs1;
				vs1 = split(s1, ',');

				int j = 0;
				for (std::vector<std::string>::iterator i = vs1.begin(); i != vs1.end(); ++i)
				{
					std::string s2 = *i;
					char * c1 = new char[2];
					std::memset(c1, 0, 2);
					std::strncpy(c1, s2.c_str(), 1);
					char c2[] = "\"";
					if (std::strncmp(c1, c2, 1) == 0)
					{
						s2 = s2.substr(1, s2.length()-2);
					}

					if (j == 0)
					{
						bbutil_render_text(m_font9, s2.c_str(), 10.0f, myY, 1.0f, 0.0f, 0.0f,1.0f);
					}
					if (j == 1)
					{
						bbutil_render_text(m_font9, s2.c_str(), 135.0f, myY, 1.0f, 0.0f, 0.0f,1.0f);
					}
					if (j == 2)
					{
						bbutil_render_text(m_font9, s2.c_str(), 195.0f, myY, 1.0f, 0.0f, 0.0f,1.0f);
					}
					if (j == 3)
					{
						bbutil_render_text(m_font9, s2.c_str(), 285.0f, myY, 1.0f, 0.0f, 0.0f,1.0f);
					}
					if (j == 4)
					{
						bbutil_render_text(m_font9, s2.c_str(), 355.0f, myY, 1.0f, 0.0f, 0.0f,1.0f);
					}
					if (j == 5)
					{
						bbutil_render_text(m_font9, s2.c_str(), 420.0f, myY, 1.0f, 0.0f, 0.0f,1.0f);
					}
					if (j == 6)
					{
						bbutil_render_text(m_font9, s2.c_str(), 485.0f, myY, 1.0f, 0.0f, 0.0f,1.0f);
					}
					if (j == 7)
					{
						bbutil_render_text(m_font9, s2.c_str(), 550.0f, myY, 1.0f, 0.0f, 0.0f,1.0f);
					}
					if (j == 8)
					{
						bbutil_render_text(m_font9, s2.c_str(), 625.0f, myY, 1.0f, 0.0f, 0.0f,1.0f);
					}
					if (j == 9)
					{
						bbutil_render_text(m_font9, s2.c_str(), 705.0f, myY, 1.0f, 0.0f, 0.0f,1.0f);
					}

					++j;
				}
				myY -= 30.0f;
				++iter;
			} while (myY > m_footerHeight || iter != m_vRT.end());
		}
	}

//	do {
//		bbutil_render_text(m_font9, "11:11:11", 10.0f, myY, 1.0f, 0.0f, 0.0f,
//				1.0f);
//		bbutil_render_text(m_font9, "B", 135.0f, myY, 1.0f, 0.0f, 0.0f, 1.0f);
//		bbutil_render_text(m_font9, "KAEF", 195.0f, myY, 1.0f, 0.0f, 0.0f,
//				1.0f);
//		bbutil_render_text(m_font9, "RG", 285.0f, myY, 1.0f, 1.0f, 1.0f, 1.0f);
//		bbutil_render_text(m_font9, "990", 355.0f, myY, 1.0f, 1.0f, 0.0f, 1.0f);
//		bbutil_render_text(m_font9, "990", 420.0f, myY, 1.0f, 1.0f, 0.0f, 1.0f);
//		bbutil_render_text(m_font9, "0", 485.0f, myY, 1.0f, 1.0f, 0.0f, 1.0f);
//		bbutil_render_text(m_font9, "RG", 550.0f, myY, 1.0f, 1.0f, 0.0f, 1.0f);
//		bbutil_render_text(m_font9, "RG", 625.0f, myY, 1.0f, 1.0f, 1.0f, 1.0f);
//		bbutil_render_text(m_font9, "RG", 705.0f, myY, 1.0f, 1.0f, 1.0f, 1.0f);
//		myY -= 30.0f;
//	} while (myY > m_footerHeight);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	addFooter();

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	m_platform.finishRender();

}

void panin::renderStockWatch() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	m_sw_caption.draw();
	m_sw_btn_port1.draw();
	m_sw_btn_banking.draw();
	m_sw_btn_mining.draw();
	m_sw_btn_cons.draw();
	//m_sw_btn_plus_green.draw();

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 3; ++j) {
			float mX = j * m_sw_box_black.Width() + 10.0f;
			float mY = m_sw_port1.PosY() - i * m_sw_box_black.Height() - 200.0f;
			m_sw_box_black.setPosition(mX, mY);
			m_sw_box_black.draw();
			mX = m_sw_box_black.PosX() + 10.0f;
			mY = m_sw_box_black.PosY() + 36.0f;
			if (j == 0) {
				m_sw_val_green.setPosition(mX, mY);
				m_sw_val_green.draw();
			} else if (j == 1) {
				m_sw_val_yellow.setPosition(mX, mY);
				m_sw_val_yellow.draw();
			} else if (j == 2) {
				m_sw_val_red.setPosition(mX, mY);
				m_sw_val_red.draw();
			}

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);

			float text_width, text_height, pos_x, pos_y;

			bbutil_measure_text(m_font20, "PANS", &text_width, &text_height);
			pos_x = m_sw_box_black.PosX()
					+ (m_sw_box_black.Width() - text_width) / 2;
			pos_y = m_sw_box_black.PosY() + m_sw_box_black.Height()
					- text_height - 4.0f;
			bbutil_render_text(m_font20, "PANS", pos_x, pos_y, 1.0f, 1.0f, 1.0f,
					1.0f);

			bbutil_measure_text(m_font10, "Panin Securitas Tbk", &text_width,
					&text_height);
			pos_x = m_sw_box_black.PosX()
					+ (m_sw_box_black.Width() - text_width) / 2;
			pos_y = m_sw_box_black.PosY() + m_sw_box_black.Height()
					- text_height - 44.0f;
			bbutil_render_text(m_font10, "Panin Securitas Tbk", pos_x, pos_y,
					1.0f, 1.0f, 1.0f, 1.0f);

			bbutil_measure_text(m_font11, "9.0 %", &text_width, &text_height);
			pos_x = m_sw_box_black.PosX() + 10.0f;
			pos_y = m_sw_box_black.PosY() + m_sw_box_black.Height()
					- text_height - 130.0f;
			bbutil_render_text(m_font11, "9.0 %", pos_x, pos_y, 1.0f, 1.0f,
					1.0f, 1.0f);

			bbutil_measure_text(m_font11, "-100", &text_width, &text_height);
			pos_x = m_sw_box_black.PosX()
					+ (m_sw_box_black.Width() - text_width - 20.0f);
			pos_y = m_sw_box_black.PosY() + m_sw_box_black.Height()
					- text_height - 130.0f;
			bbutil_render_text(m_font11, "-100", pos_x, pos_y, 1.0f, 1.0f, 1.0f,
					1.0f);

			bbutil_render_text(m_font9, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

			glEnable(GL_TEXTURE_2D);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}

	//m_sw_port1.draw();
	//m_sw_banking.draw();
	//m_sw_mining.draw();
	//m_sw_cons.draw();
	//m_sw_plus_green.draw();
	m_sw_val_green.draw();
	m_sw_val_yellow.draw();
	m_sw_val_red.draw();

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderCompleteBook() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	m_cb_caption.draw();
	m_cb_top_band.draw();
	m_cb_table_title1.draw();
	m_cb_table_title2.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	float text_width, text_height, pos_x, pos_y;

	bbutil_measure_text(m_font12, "Last", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 40.0f;
	pos_y = m_cb_top_band.PosY() - 36.0f;
	bbutil_render_text(m_font12, "Last", pos_x, pos_y, 0.3828f, 0.7969f,
			0.9180f, 1.0f);

	bbutil_measure_text(m_font12, "Open", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 40.0f;
	pos_y = m_cb_top_band.PosY() - 72.0f;
	bbutil_render_text(m_font12, "Open", pos_x, pos_y, 0.3828f, 0.7969f,
			0.9180f, 1.0f);

	bbutil_measure_text(m_font12, "Vol", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 40.0f;
	pos_y = m_cb_top_band.PosY() - 108.0f;
	bbutil_render_text(m_font12, "Vol", pos_x, pos_y, 0.3828f, 0.7969f, 0.9180f,
			1.0f);

	bbutil_measure_text(m_font12, "Last", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 116.0f;
	pos_y = m_cb_top_band.PosY() - 36.0f;
	bbutil_render_text(m_font12, "Last", pos_x, pos_y, 1.0f, 0.0f, 0.0f, 1.0f);

	bbutil_measure_text(m_font12, "Open", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 116.0f;
	pos_y = m_cb_top_band.PosY() - 72.0f;
	bbutil_render_text(m_font12, "Open", pos_x, pos_y, 0.0f, 1.0f, 0.0f, 1.0f);

	bbutil_measure_text(m_font12, "Vol", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 116.0f;
	pos_y = m_cb_top_band.PosY() - 108.0f;
	bbutil_render_text(m_font12, "Vol", pos_x, pos_y, 1.0f, 0.0f, 1.0f, 1.0f);

	//--------------------

	bbutil_measure_text(m_font12, "Prev", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 267.0f;
	pos_y = m_cb_top_band.PosY() - 36.0f;
	bbutil_render_text(m_font12, "Prev", pos_x, pos_y, 0.3828f, 0.7969f,
			0.9180f, 1.0f);

	bbutil_measure_text(m_font12, "Chg", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 267.0f;
	pos_y = m_cb_top_band.PosY() - 72.0f;
	bbutil_render_text(m_font12, "Chg", pos_x, pos_y, 0.3828f, 0.7969f, 0.9180f,
			1.0f);

	bbutil_measure_text(m_font12, "Val", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 267.0f;
	pos_y = m_cb_top_band.PosY() - 108.0f;
	bbutil_render_text(m_font12, "Val", pos_x, pos_y, 0.3828f, 0.7969f, 0.9180f,
			1.0f);

	bbutil_measure_text(m_font12, "Prev", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 340.0f;
	pos_y = m_cb_top_band.PosY() - 36.0f;
	bbutil_render_text(m_font12, "Prev", pos_x, pos_y, 1.0f, 0.0f, 0.0f, 1.0f);

	bbutil_measure_text(m_font12, "Chg", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 340.0f;
	pos_y = m_cb_top_band.PosY() - 72.0f;
	bbutil_render_text(m_font12, "Chg", pos_x, pos_y, 0.0f, 1.0f, 0.0f, 1.0f);

	bbutil_measure_text(m_font12, "Val", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 340.0f;
	pos_y = m_cb_top_band.PosY() - 108.0f;
	bbutil_render_text(m_font12, "Val", pos_x, pos_y, 1.0f, 0.0f, 1.0f, 1.0f);

	//--------------------

	bbutil_measure_text(m_font12, "Hi", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 560.0f;
	pos_y = m_cb_top_band.PosY() - 36.0f;
	bbutil_render_text(m_font12, "Hi", pos_x, pos_y, 0.3828f, 0.7969f, 0.9180f,
			1.0f);

	bbutil_measure_text(m_font12, "Low", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 560.0f;
	pos_y = m_cb_top_band.PosY() - 72.0f;
	bbutil_render_text(m_font12, "Low", pos_x, pos_y, 0.3828f, 0.7969f, 0.9180f,
			1.0f);

	bbutil_measure_text(m_font12, "M.Cp", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 560.0f;
	pos_y = m_cb_top_band.PosY() - 108.0f;
	bbutil_render_text(m_font12, "M.Cp", pos_x, pos_y, 0.3828f, 0.7969f,
			0.9180f, 1.0f);

	bbutil_measure_text(m_font12, "Hi", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 636.0f;
	pos_y = m_cb_top_band.PosY() - 36.0f;
	bbutil_render_text(m_font12, "Hi", pos_x, pos_y, 1.0f, 0.0f, 0.0f, 1.0f);

	bbutil_measure_text(m_font12, "Low", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 636.0f;
	pos_y = m_cb_top_band.PosY() - 72.0f;
	bbutil_render_text(m_font12, "Low", pos_x, pos_y, 0.0f, 1.0f, 0.0f, 1.0f);

	bbutil_measure_text(m_font12, "M.Cp", &text_width, &text_height);
	pos_x = m_cb_top_band.PosX() + 636.0f;
	pos_y = m_cb_top_band.PosY() - 108.0f;
	bbutil_render_text(m_font12, "M.Cp", pos_x, pos_y, 1.0f, 0.0f, 1.0f, 1.0f);

	//--------------------

	for (int i = 0; i < 7; ++i) {
		//bbutil_measure_text(m_font12, "M.Cp", &text_width, &text_height);
		//pos_x = m_cb_top_band.PosX() + 636.0f;
		//pos_y = m_cb_top_band.PosY() - 108.0f;
		pos_y = m_cb_table_title1.PosY() + 4.0f - (i + 1) * 33.0f;
		bbutil_render_text(m_font12, "20", 40.0f, pos_y, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font12, "20", 160.0f, pos_y, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font12, "20", 255.0f, pos_y, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font12, "20", 390.0f, pos_y, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font12, "20", 540.0f, pos_y, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font12, "20", 670.0f, pos_y, 1.0f, 0.0f, 0.0f,
				1.0f);
	}

	for (int i = 0; i < 7; ++i) {
		pos_y = m_cb_table_title2.PosY() + 4.0f - (i + 1) * 33.0f;
		bbutil_render_text(m_font12, "20", 30.0f, pos_y, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font12, "20", 160.0f, pos_y, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font12, "20", 300.0f, pos_y, 1.0f, 0.0f, 0.0f,
				1.0f);

	}

	bbutil_render_text(m_font9, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderStockQuote() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	m_sq_caption.draw();
	m_sq_table_title.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	float myY = m_sq_table_title.PosY() - 30;
	do {
		bbutil_render_text(m_font11, "RX", 40.0f, myY, 1.0f, 0.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font11, "2000", 170.0f, myY, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 320.0f, myY, 1.0f, 1.0f, 1.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 480.0f, myY, 1.0f, 1.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 640.0f, myY, 1.0f, 1.0f, 0.0f,
				1.0f);
		myY -= 30.0f;
	} while (myY > m_footerHeight);

	bbutil_render_text(m_font9, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderBrokerQuote() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	m_bq_caption.draw();
	m_bq_table_title.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	float myY = m_bq_table_title.PosY() - 30;
	do {
		bbutil_render_text(m_font11, "RX", 30.0f, myY, 1.0f, 0.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font11, "Nama", 140.0f, myY, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 425.0f, myY, 1.0f, 1.0f, 1.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 555.0f, myY, 1.0f, 1.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 685.0f, myY, 1.0f, 1.0f, 0.0f,
				1.0f);
		myY -= 30.0f;
	} while (myY > m_footerHeight);

	bbutil_render_text(m_font9, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderStockSummary() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();
	addHeader();

	m_ss_caption.draw();
	m_ss_table_title.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	float myY = m_ss_table_title.PosY() - 30;
	do {
		bbutil_render_text(m_font11, "RX", 30.0f, myY, 1.0f, 0.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font11, "Nama", 160.0f, myY, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 330.0f, myY, 1.0f, 1.0f, 1.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 500.0f, myY, 1.0f, 1.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 640.0f, myY, 1.0f, 1.0f, 0.0f,
				1.0f);
		myY -= 30.0f;
	} while (myY > m_footerHeight);

	bbutil_render_text(m_font9, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	addFooter();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderBrokerSummary() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	m_bs_caption.draw();
	m_bs_table_title.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	float myY = m_bs_table_title.PosY() - 30;
	do {
		bbutil_render_text(m_font11, "RX", 30.0f, myY, 1.0f, 0.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font11, "Nama", 150.0f, myY, 1.0f, 0.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 300.0f, myY, 1.0f, 1.0f, 1.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 440.0f, myY, 1.0f, 1.0f, 0.0f,
				1.0f);
		bbutil_render_text(m_font11, "2000", 620.0f, myY, 1.0f, 1.0f, 0.0f,
				1.0f);
		myY -= 30.0f;
	} while (myY > m_footerHeight);

	bbutil_render_text(m_font9, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderNonRegular() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	m_bs_caption.draw();
	m_bs_table_title.draw();

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderCharts() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_chart_bg.draw();
	m_chart_caption_bottom.draw();
	//m_chart_post_bar.draw();
	m_chart_text_bg.draw();
	m_chart_btn_search.draw();
	m_chart_btn_1day.draw();
	m_chart_btn_1week.draw();
	m_chart_btn_1month.draw();
	m_chart_btn_1year.draw();
	m_chart_btn_3year.draw();

	addHeader();

//	addFooter();

//	if (m_bShowBuy) {
//		renderBuyDialog();
//	}
//
//	if (m_bShowSell) {
//		renderSellDialog();
//	}



	// latar chart
	GLfloat vertices[8];
    vertices[0] = -0.25f;
    vertices[1] = -0.25f;

    vertices[2] = 0.25f;
    vertices[3] = -0.25f;

    vertices[4] = -0.25f;
    vertices[5] = 0.25f;

    vertices[6] = 0.25f;
    vertices[7] = 0.25f;

    GLfloat colors[16];
    colors[0] = 1.0f;
    colors[1] = 0.0f;
    colors[2] = 1.0f;
    colors[3] = 1.0f;

    colors[4] = 1.0f;
    colors[5] = 1.0f;
    colors[6] = 0.0f;
    colors[7] = 1.0f;

    colors[8] = 0.0f;
    colors[9] = 1.0f;
    colors[10] = 1.0f;
    colors[11] = 1.0f;

    colors[12] = 0.0f;
    colors[13] = 1.0f;
    colors[14] = 1.0f;
    colors[15] = 1.0f;

	GLfloat eka[4], ekav[4];
	eka[0] = 0.0f;
	eka[1] = 0.50f;
	eka[2] = 1.0f;
	eka[3] = 0.50f;
	ekav[0] = 0.0f;
	ekav[1] = m_screenHeight/2;
	ekav[2] = m_screenWidth;
	ekav[3] = m_screenHeight/2;

//    glVertexPointer(2, GL_FLOAT, 0, vertices);
//    glTexCoordPointer(2, GL_FLOAT, 0, vertices);
//
//    glEnableClientState(GL_COLOR_ARRAY);
//    glColorPointer(4, GL_FLOAT, 0, colors);
//
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

//	GLfloat dashedLine[1296];
//	float a, b;
//	int i = 0;
//	for (a = -0.4f; a <= 0.4f; a += 0.1f)
//	{
//		for (b = -0.825f; b <= 0.950f; b += 0.025f)
//		{
//			dashedLine[i] = a;
//			i++;
//			dashedLine[i] = b;
//			i++;
//		}
//	}
//
//
//
//	glLineWidth(1.0f);
//	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//	glVertexPointer(2, GL_FLOAT, 0, dashedLine);
//	glDrawArrays(GL_LINES, 0, 648);



//	glLineWidth(4.0f);
//	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
//	glVertexPointer(2, GL_FLOAT, 0, ekav);
//	glTexCoordPointer(2, GL_FLOAT, 0, eka);
//	glDrawArrays(GL_LINES, 0, 2);
//	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderInformations() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderNews() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderCompanyInfo() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();
	m_cpy_caption.draw();
	if (companyInfoFlag == 0)
	{

	}
	//m_cpy_btn_financial.draw();
	//m_cpy_btn_ratio.draw();

	addHeader();

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderCorporateAction() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();
	m_ca_caption.draw();

	m_ca_btn_dividen.draw();
	m_ca_btn_bonus.draw();
	m_ca_btn_split.draw();
	m_ca_btn_warrant.draw();
	m_ca_btn_rights.draw();
	m_ca_btn_rups.draw();

	m_ca_table_title.draw();

	addHeader();

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderPortfolio() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();
	m_pf_caption.draw();
	m_pf_table_title.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	float pos_x, pos_y, text_width, text_height;

	// acc number
	bbutil_measure_text(m_font11, m_sAccNumber.c_str(), &text_width, &text_height);
	pos_x = m_pf_caption.PosX();
	pos_y = m_pf_caption.PosY() - 40.0f;
	bbutil_render_text(m_font11, m_sAccNumber.c_str(), pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	/////
	bbutil_measure_text(m_font11, "TRADING LIMIT", &text_width, &text_height);
	pos_x = m_pf_caption.PosX();
	pos_y = m_pf_caption.PosY() - 40.0f;
	bbutil_render_text(m_font11, "TRADING LIMIT", pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	pos_x += text_width + 10.0f;
	bbutil_render_text(m_font11, m_s_pf_tradingLimit.c_str(), pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	bbutil_measure_text(m_font11, "RATIO", &text_width, &text_height);
	pos_x = m_pf_caption.PosX();
	pos_y = m_pf_caption.PosY() - 80.0f;
	bbutil_render_text(m_font11, "RATIO", pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	pos_x += text_width + 10.0f;
	bbutil_render_text(m_font11, m_s_pf_ratio.c_str(), pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	bbutil_measure_text(m_font11, "EQUITY", &text_width, &text_height);
	pos_x = m_pf_caption.PosX();
	pos_y = m_pf_caption.PosY() - 120.0f;
	bbutil_render_text(m_font11, "EQUITY", pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	pos_x += text_width + 10.0f;
	bbutil_render_text(m_font11, m_s_pf_equity.c_str(), pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	bbutil_measure_text(m_font11, "CASH / LOAN", &text_width, &text_height);
	pos_x = m_pf_caption.PosX() + 380.0f;
	pos_y = m_pf_caption.PosY() - 40.0f;
	bbutil_render_text(m_font11, "CASH / LOAN", pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	pos_x += text_width + 10.0f;
	bbutil_render_text(m_font11, m_s_pf_cashloan.c_str(), pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	bbutil_measure_text(m_font11, "STOCK VALUE", &text_width, &text_height);
	pos_x = m_pf_caption.PosX() + 380.0f;
	pos_y = m_pf_caption.PosY() - 80.0f;
	bbutil_render_text(m_font11, "STOCK VALUE", pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	pos_x += text_width + 10.0f;
	bbutil_render_text(m_font11, m_s_pf_stockValue.c_str(), pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	bbutil_measure_text(m_font11, "NETT. TODAY", &text_width, &text_height);
	pos_x = m_pf_caption.PosX() + 380.0f;
	pos_y = m_pf_caption.PosY() - 120.0f;
	bbutil_render_text(m_font11, "NETT. TODAY", pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	pos_x += text_width + 10.0f;
	bbutil_render_text(m_font11, m_s_pf_nettToday.c_str(), pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);



	// nama di bawah
	std::string sNama;
	sNama = "NAMA : " + m_sAccName;
	bbutil_measure_text(m_font12, sNama.c_str(), &text_width, &text_height);
	pos_x = m_screenWidth - text_width - 20.0f;
	pos_y = m_footerHeight + 20.0f;
	bbutil_render_text(m_font12, sNama.c_str(), pos_x, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);

	// isi tabel.
	pos_y = m_pf_table_title.PosY() - 40.0f;
	for (int i = 0; i < 30; ++i)
	{
//		m_s_pf_tableContent[i][0] = "1000";
//		m_s_pf_tableContent[i][1] = "2000";
//		m_s_pf_tableContent[i][2] = "3000";
//		m_s_pf_tableContent[i][3] = "4000";
//		m_s_pf_tableContent[i][4] = "5000";
		bbutil_render_text(m_font12, "1000", m_pf_table_title.PosX() + 30.0f, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);
		bbutil_render_text(m_font12, "1000", m_pf_table_title.PosX() + 140.0f, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);
		bbutil_render_text(m_font12, "1000", m_pf_table_title.PosX() + 310.0f, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);
		bbutil_render_text(m_font12, "1000", m_pf_table_title.PosX() + 490.0f, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);
		bbutil_render_text(m_font12, "1000", m_pf_table_title.PosX() + 660.0f, pos_y, 1.0f, 1.0f,	1.0f, 1.0f);
		pos_y -= 40.0f;
		if (pos_y < m_footerHeight + 60.0f)
		{
			break;
		}
	}

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	addHeader();

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderOrderTrade() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	m_tl_order_caption.draw();
	m_tl_order_table_caption.draw();
	m_tl_tradelist_caption.draw();
	m_tl_tradelist_table_caption.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	float text_width, text_height, pos_x, pos_y;

	// order list item
	bbutil_measure_text(m_font11, "12:34:56", &text_width, &text_height);
	pos_x = (m_tl_order_table_caption.PosX() + (175.0f - text_width)/2);
	pos_y = m_tl_order_table_caption.PosY() - 30.0f;
	bbutil_render_text(m_font11, "12:34:56", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_measure_text(m_font11, "PANS", &text_width, &text_height);
	pos_x = (m_tl_order_table_caption.PosX() + 175.0f + (165.0f - text_width)/2);
	pos_y = m_tl_order_table_caption.PosY() - 30.0f;
	bbutil_render_text(m_font11, "PANS", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_measure_text(m_font11, "S", &text_width, &text_height);
	pos_x = (m_tl_order_table_caption.PosX() + 340.0f + (130.0f - text_width)/2);
	pos_y = m_tl_order_table_caption.PosY() - 30.0f;
	bbutil_render_text(m_font11, "S", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_measure_text(m_font11, "1000", &text_width, &text_height);
	pos_x = (m_tl_order_table_caption.PosX() + 470.0f + (135.0f - text_width)/2);
	pos_y = m_tl_order_table_caption.PosY() - 30.0f;
	bbutil_render_text(m_font11, "1000", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_measure_text(m_font11, "100000", &text_width, &text_height);
	pos_x = (m_tl_order_table_caption.PosX() + 605.0f + (165.0f - text_width)/2);
	pos_y = m_tl_order_table_caption.PosY() - 30.0f;
	bbutil_render_text(m_font11, "100000", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	// trade list item
	bbutil_measure_text(m_font11, "12:34:56", &text_width, &text_height);
	pos_x = (m_tl_tradelist_table_caption.PosX() + (175.0f - text_width)/2);
	pos_y = m_tl_tradelist_table_caption.PosY() - 30.0f;
	bbutil_render_text(m_font11, "12:34:56", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_measure_text(m_font11, "PANS", &text_width, &text_height);
	pos_x = (m_tl_tradelist_table_caption.PosX() + 175.0f + (165.0f - text_width)/2);
	pos_y = m_tl_tradelist_table_caption.PosY() - 30.0f;
	bbutil_render_text(m_font11, "PANS", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_measure_text(m_font11, "S", &text_width, &text_height);
	pos_x = (m_tl_tradelist_table_caption.PosX() + 340.0f + (130.0f - text_width)/2);
	pos_y = m_tl_tradelist_table_caption.PosY() - 30.0f;
	bbutil_render_text(m_font11, "S", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_measure_text(m_font11, "1000", &text_width, &text_height);
	pos_x = (m_tl_tradelist_table_caption.PosX() + 470.0f + (135.0f - text_width)/2);
	pos_y = m_tl_tradelist_table_caption.PosY() - 30.0f;
	bbutil_render_text(m_font11, "1000", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_measure_text(m_font11, "100000", &text_width, &text_height);
	pos_x = (m_tl_tradelist_table_caption.PosX() + 605.0f + (165.0f - text_width)/2);
	pos_y = m_tl_tradelist_table_caption.PosY() - 30.0f;
	bbutil_render_text(m_font11, "100000", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	addHeader();
	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderResearch() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	m_research_caption.draw();

	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderMyAccount() {
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	m_ac_password.draw();
	m_ac_bg_black.draw();
	//m_ac_textfield_bg.draw();
	m_ac_trading_pin.draw();
	m_ac_bg_black2.draw();
	m_btn_save1.draw();
	m_btn_save2.draw();

	if (m_bOldPaswordFocus)
	{

	}
	addFooter();

	if (m_bShowBuy) {
		renderBuyDialog();
	}

	if (m_bShowSell) {
		renderSellDialog();
	}

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation) {
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}


void panin::addHeader() {
	if (m_platform.getOrientation() == 0)
	{
		m_header_bar_bg.draw();
		m_header_post.draw();
	}
	else
	{
		m_chart_post_bar.draw();
	}
	m_btn_info.draw();
	m_btn_menu.draw();

}

void panin::addFooter() {
	m_ihsg2.draw();
	m_btn_sell.draw();
	m_btn_buy.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	float text_width, text_height, pos_x, pos_y;
	bbutil_measure_text(m_font_ihsg_val, m_sIhsg_val.c_str(), &text_width,
			&text_height);
	pos_x = (m_ihsg2.PosX() + 20.0f);
	pos_y = m_ihsg2.PosY() + text_height / 2 - 10.0f;
	bbutil_render_text(m_font28, m_sIhsg_val.c_str(), pos_x, pos_y, 0.05f, 1.0f,
			0.05f, 1.0f);

	bbutil_measure_text(m_font14, m_sIhsg_volume.c_str(), &text_width,
			&text_height);
	pos_x = (m_ihsg2.PosX() + m_ihsg2.Width() - text_width - 30.0f);
	pos_y = m_ihsg2.PosY() + 2 * text_height + 0.0f;
	bbutil_render_text(m_font14, m_sIhsg_volume.c_str(), pos_x, pos_y, 0.05f,
			1.0f, 0.05f, 1.0f);

	//bbutil_measure_text(m_font14, m_sIhsg_percent.c_str(), &text_width, &text_height);
	//pos_x = (m_ihsg2.PosX() + m_ihsg2.Width() - text_width - 20.0f);
	pos_y = m_ihsg2.PosY() + 14.0f;
	bbutil_render_text(m_font14, m_sIhsg_percent.c_str(), pos_x, pos_y, 0.05f,
			1.0f, 0.05f, 1.0f);

	bbutil_render_text(m_font14, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void panin::renderBuyDialog() {
	m_buy_bg.draw();
	m_buy_caption.draw();
	m_buy_band.draw();
	m_btn_buy_refresh.draw();
	m_btn_buy_execute.draw();
	m_btn_buy_x.draw();

	m_buysell_textfield_bg.setPosition(m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 545.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 495.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 450.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 400.0f);
	m_buysell_textfield_bg.draw();

	if (m_bAccountIdFocused)
	{
		m_buysell_textfield_bg_focus.setPosition(m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 545.0f);
	}
	if (m_bStockTradeFocused)
	{
		m_buysell_textfield_bg_focus.setPosition(m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 495.0f);
	}
	if (m_bPriceFocused)
	{
		m_buysell_textfield_bg_focus.setPosition(m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 450.0f);
	}
	if (m_bVolumeFocused)
	{
		m_buysell_textfield_bg_focus.setPosition(m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 400.0f);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	bbutil_render_text(m_font14, "ACCOUNT ID", m_buy_bg.PosX() + 130.0f, m_buy_bg.PosY() + 545.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "STOCK TRADE", m_buy_bg.PosX() + 130.0f, m_buy_bg.PosY() + 495.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "PRICE", m_buy_bg.PosX() + 130.0f, m_buy_bg.PosY() + 450.0f, 1.0f,
			1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "VOLUME", m_buy_bg.PosX() + 130.0f, m_buy_bg.PosY() + 400.0f,
			1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, m_sAccID.c_str(), m_buy_bg.PosX() + 430.0f, m_buy_bg.PosY() + 545.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sStockCode.c_str(), m_buy_bg.PosX() + 430.0f, m_buy_bg.PosY() + 495.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sPrice.c_str(), m_buy_bg.PosX() + 430.0f, m_buy_bg.PosY() + 450.0f, 1.0f,
			1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sLot.c_str(), m_buy_bg.PosX() + 430.0f, m_buy_bg.PosY() + 400.0f,
			1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, "Max Buy", m_buy_bg.PosX() + 37.0f, m_buy_bg.PosY() + 335.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Stock Value", m_buy_bg.PosX() + 37.0f, m_buy_bg.PosY() + 295.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Trans Fee", m_buy_bg.PosX() + 37.0f, m_buy_bg.PosY() + 250.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Payable", m_buy_bg.PosX() + 37.0f, m_buy_bg.PosY() + 205.0f,
			1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, m_sMaxBuy.c_str(), m_buy_bg.PosX() + 250.0f,
			m_buy_bg.PosY() + 335.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sStockValue.c_str(), m_buy_bg.PosX() + 250.0f,
			m_buy_bg.PosY() + 295.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sTransFee.c_str(), m_buy_bg.PosX() + 250.0f,
			m_buy_bg.PosY() + 250.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sPayable.c_str(), m_buy_bg.PosX() + 250.0f,
			m_buy_bg.PosY() + 205.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void panin::renderSellDialog() {
	m_sell_bg.draw();
	m_sell_caption.draw();
	m_sell_band.draw();
	m_btn_sell_refresh.draw();
	m_btn_sell_execute.draw();
	m_btn_sell_x.draw();

	m_buysell_textfield_bg.setPosition(m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 545.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 495.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 450.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 400.0f);
	m_buysell_textfield_bg.draw();

	if (m_bAccountIdFocused)
	{
		m_buysell_textfield_bg_focus.setPosition(m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 545.0f);
	}
	if (m_bStockTradeFocused)
	{
		m_buysell_textfield_bg_focus.setPosition(m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 495.0f);
	}
	if (m_bPriceFocused)
	{
		m_buysell_textfield_bg_focus.setPosition(m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 450.0f);
	}
	if (m_bVolumeFocused)
	{
		m_buysell_textfield_bg_focus.setPosition(m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 400.0f);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	bbutil_render_text(m_font14, "ACCOUNT ID", m_sell_bg.PosX() + 130.0f, m_sell_bg.PosY() + 545.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "STOCK TRADE", m_sell_bg.PosX() + 130.0f, m_sell_bg.PosY() + 495.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "PRICE", m_sell_bg.PosX() + 130.0f, m_sell_bg.PosY() + 450.0f, 1.0f,
			1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "VOLUME", m_sell_bg.PosX() + 130.0f, m_sell_bg.PosY() + 400.0f,
			1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, m_sAccID.c_str(), m_sell_bg.PosX() + 430.0f, m_sell_bg.PosY() + 545.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sStockCode.c_str(), m_sell_bg.PosX() + 430.0f, m_sell_bg.PosY() + 495.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sPrice.c_str(), m_sell_bg.PosX() + 430.0f, m_sell_bg.PosY() + 450.0f, 1.0f,
			1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sLot.c_str(), m_sell_bg.PosX() + 430.0f, m_sell_bg.PosY() + 400.0f,
			1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, "Max Buy", m_sell_bg.PosX() + 37.0f, m_sell_bg.PosY() + 335.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Stock Value", m_sell_bg.PosX() + 37.0f, m_sell_bg.PosY() + 295.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Trans Fee", m_sell_bg.PosX() + 37.0f, m_sell_bg.PosY() + 250.0f,
			1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Payable", m_sell_bg.PosX() + 37.0f, m_sell_bg.PosY() + 205.0f,
			1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, m_sMaxBuy.c_str(), m_sell_bg.PosX() + 250.0f,
			m_sell_bg.PosY() + 335.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sStockValue.c_str(), m_sell_bg.PosX() + 250.0f,
			m_sell_bg.PosY() + 295.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sTransFee.c_str(), m_sell_bg.PosX() + 250.0f,
			m_sell_bg.PosY() + 250.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sPayable.c_str(), m_sell_bg.PosX() + 250.0f,
			m_sell_bg.PosY() + 205.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void panin::onLeftRelease(float x, float y) {
	fprintf(stderr, "onLeftRelease.\n");
	float pX, pY;
	pX = x;
	pY = m_screenHeight - y;

	if (m_state == HOME)
	{
		if (m_btn_login.isEnabled)
		{
			if (m_btn_login.isWithin(pX, pY))
			{
				fprintf(stderr, "button login is released.\n");
				m_btn_login.isPressed = false;

				loginStatus = SIGNINGIN;
				m_bUsernameFocus = false;
				m_bPasswordFocus = false;

				periksaLogin();
				return;
				//m_state = RUNNING_TRADE;
			}
		}


		if (m_btn_home_info.isEnabled)
		{
			if (m_btn_home_info.isWithin(pX, pY))
			{
				fprintf(stderr, "button home info is released.\n");
				m_btn_home_info.isPressed = false;
				m_bShowHomeInfo = true;

				m_bUsernameFocus = false;
				m_bPasswordFocus = false;
				/*
				 m_btn_login.isEnabled = false;
				 m_btn_home_info.isEnabled = false;
				 m_btn_home_setel.isEnabled = false;
				 m_btn_setel_default.isEnabled = true;
				 m_btn_setel_set202.isEnabled = true;
				 m_btn_setel_set107.isEnabled = true;
				 m_btn_setel_save.isEnabled = true;
				 m_btn_setel_x.isEnabled = true;
				 */
			}
		}

		if (m_btn_home_setel.isEnabled)
		{
			if (m_btn_home_setel.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel is released.\n");
				m_btn_home_setel.isPressed = false;
				m_bShowHomeSetel = true;

				m_btn_login.isEnabled = false;
				m_btn_home_info.isEnabled = false;
				m_btn_home_setel.isEnabled = false;
				m_btn_setel_default.isEnabled = true;
				m_btn_setel_set202.isEnabled = true;
				m_btn_setel_set107.isEnabled = true;
				m_btn_setel_save.isEnabled = true;
				m_btn_setel_x.isEnabled = true;

				m_bUsernameFocus = false;
				m_bPasswordFocus = false;

				return;
			}
		}

		if (m_btn_setel_default.isEnabled)
		{
			if (m_btn_setel_default.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel default is released.\n");
				m_btn_setel_default.isPressed = false;

				setConfiguration(CONF_DEFAULT);
				return;
			}
		}
		if (m_btn_setel_set202.isEnabled)
		{
			if (m_btn_setel_set202.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel set202 is released.\n");
				m_btn_setel_set202.isPressed = false;

				setConfiguration(CONF_SET202);
				return;
			}
		}
		if (m_btn_setel_set107.isEnabled)
		{
			if (m_btn_setel_set107.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel set107 is released.\n");
				m_btn_setel_set107.isPressed = false;

				setConfiguration(CONF_SET107);
				return;
			}
		}
		if (m_btn_setel_save.isEnabled)
		{
			if (m_btn_setel_save.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel save is released.\n");
				m_btn_setel_save.isPressed = false;

				m_bShowHomeSetel = false;
				m_btn_login.isEnabled = true;
				m_btn_home_info.isEnabled = true;
				m_btn_home_setel.isEnabled = true;
				m_btn_setel_default.isEnabled = false;
				m_btn_setel_set202.isEnabled = false;
				m_btn_setel_set107.isEnabled = false;
				m_btn_setel_save.isEnabled = false;
				m_btn_setel_x.isEnabled = false;
				setConfiguration(CONF_SAVE);
				return;
			}
		}
		if (m_btn_setel_x.isEnabled)
		{
			if (m_btn_setel_x.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel x is released.\n");
				m_btn_setel_x.isPressed = false;

				m_bShowHomeSetel = false;
				m_btn_login.isEnabled = true;
				m_btn_home_info.isEnabled = true;
				m_btn_home_setel.isEnabled = true;
				m_btn_setel_default.isEnabled = false;
				m_btn_setel_set202.isEnabled = false;
				m_btn_setel_set107.isEnabled = false;
				m_btn_setel_save.isEnabled = false;
				m_btn_setel_x.isEnabled = false;

				return;
			}
		}
		if (m_btn_home_username.isEnabled)
		{
			if (m_btn_home_username.isWithin(pX, pY))
			{
				fprintf(stderr, "button home username x is released.\n");
				m_btn_home_username.isPressed = false;
				m_u_name.clear();
				m_bUsernameFocus = true;
				m_bPasswordFocus = false;
				virtualkeyboard_show();
			}
		}

		if (m_btn_home_password.isEnabled)
		{
			if (m_btn_home_password.isWithin(pX, pY))
			{
				fprintf(stderr, "button home password x is released.\n");
				m_btn_home_password.isPressed = false;
				m_u_pass.clear();
				m_bUsernameFocus = false;
				m_bPasswordFocus = true;
				virtualkeyboard_show();
			}
		}
	}
	else
	{
		if (m_btn_menu.isEnabled)
		{
			if (m_btn_menu.isWithin(pX, pY))
			{
				fprintf(stderr, "button menu is released.\n");
				m_btn_menu.isPressed = false;
				m_bShowMenu = !m_bShowMenu;
				if (m_bShowMenu)
				{
					fprintf(stderr, "Show Menu.\n");
					//m_bMenuShowAnimation = true;
					fprintf(stderr, "posisi m_menu_acc_number: %f, %f.\n", m_menu_acc_number.PosX(), m_menu_acc_number.PosY());
					m_bMenuActive = true;
				}
				else
				{
					fprintf(stderr, "Hide Menu.\n");
					//m_bMenuHideAnimation = true;
					m_bMenuActive = false;
				}

				// update semua posisi.
				return;
			}
		}

		if (m_btn_info.isEnabled)
		{
			if (m_btn_info.isWithin(pX, pY))
			{
				m_btn_info.isPressed = false;
			}
		}

		if (m_btn_buy.isEnabled)
		{
			if (m_btn_buy.isWithin(pX, pY))
			{
				fprintf(stderr, "button buy is released.\n");
				m_btn_buy.isPressed = false;
				m_bShowBuy = true;
				m_btn_buy.isEnabled = false;
				m_btn_sell.isEnabled = false;

				m_bAccountIdFocused = false;
				m_bStockTradeFocused = false;
				m_bPriceFocused = false;
				m_bVolumeFocused = false;
				return;
			}
		}

		if (m_btn_sell.isEnabled)
		{
			if (m_btn_sell.isWithin(pX, pY))
			{
				fprintf(stderr, "button sell is released.\n");
				m_btn_sell.isPressed = false;
				m_bShowSell = true;
				m_btn_buy.isEnabled = false;
				m_btn_sell.isEnabled = false;

				m_bAccountIdFocused = false;
				m_bStockTradeFocused = false;
				m_bPriceFocused = false;
				m_bVolumeFocused = false;
				return;
			}
		}

		if (m_bShowSell)
		{
			m_bAccountIdFocused = false;
			m_bStockTradeFocused = false;
			m_bPriceFocused		= false;
			m_bVolumeFocused	= false;

			if (m_btn_sell_execute.isWithin(pX, pY))
			{
				fprintf(stderr, "button sell execute is released.\n");
				m_btn_sell_execute.isPressed = false;
				return;
			}
			if (m_btn_sell_refresh.isWithin(pX, pY))
			{
				fprintf(stderr, "button sell refresh is released.\n");
				m_btn_sell_refresh.isPressed = false;
				return;
			}
			if (m_btn_sell_x.isWithin(pX, pY))
			{
				fprintf(stderr, "button sell x is released.\n");
				m_btn_sell_x.isPressed = false;
				m_bShowSell = false;
				m_btn_sell.isEnabled = true;
				m_btn_buy.isEnabled = true;
				return;
			}

			if (periksaPointer(pX, pY, m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 545.0f, 210.0f, 30.0f))
			{
				m_bAccountIdFocused = true;
				if (!m_bVirtualKeyboardShow)
				{
					virtualkeyboard_show();
				}
				return;
			}

			if (periksaPointer(pX, pY, m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 495.0f, 210.0f, 30.0f))
			{
				m_bStockTradeFocused = true;
				if (!m_bVirtualKeyboardShow)
				{
					virtualkeyboard_show();
				}
				return;
			}

			if (periksaPointer(pX, pY, m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 450.0f, 210.0f, 30.0f))
			{
				m_bPriceFocused = true;
				if (!m_bVirtualKeyboardShow)
				{
					virtualkeyboard_show();
				}
				return;
			}

			if (periksaPointer(pX, pY, m_sell_bg.PosX() + 388.0f, m_sell_bg.PosY() + 400.0f, 210.0f, 30.0f))
			{
				m_bVolumeFocused = true;
				if (!m_bVirtualKeyboardShow)
				{
					virtualkeyboard_show();
				}
				return;
			}

			if (m_bVirtualKeyboardShow)
			{
				virtualkeyboard_hide();
			}
		}

		if (m_bShowBuy)
		{
			m_bAccountIdFocused = false;
			m_bStockTradeFocused = false;
			m_bPriceFocused		= false;
			m_bVolumeFocused	= false;
			if (m_btn_buy_execute.isWithin(pX, pY))
			{
				fprintf(stderr, "button buy execute is released.\n");
				m_btn_buy_execute.isPressed = false;
				return;
			}
			if (m_btn_buy_refresh.isWithin(pX, pY))
			{
				fprintf(stderr, "button buy refresh is released.\n");
				m_btn_buy_refresh.isPressed = false;
				return;
			}
			if (m_btn_buy_x.isWithin(pX, pY))
			{
				fprintf(stderr, "button buy x is released.\n");
				m_btn_buy_x.isPressed = false;
				m_bShowBuy = false;
				m_btn_sell.isEnabled = true;
				m_btn_buy.isEnabled = true;
				return;
			}

			if (periksaPointer(pX, pY, m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 545.0f, 210.0f, 30.0f))
			{
				m_bAccountIdFocused = true;
				if (!m_bVirtualKeyboardShow)
				{
					virtualkeyboard_show();
				}
				return;
			}

			if (periksaPointer(pX, pY, m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 495.0f, 210.0f, 30.0f))
			{
				m_bStockTradeFocused = true;
				if (!m_bVirtualKeyboardShow)
				{
					virtualkeyboard_show();
				}
				return;
			}

			if (periksaPointer(pX, pY, m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 450.0f, 210.0f, 30.0f))
			{
				m_bPriceFocused = true;
				if (!m_bVirtualKeyboardShow)
				{
					virtualkeyboard_show();
				}
				return;
			}

			if (periksaPointer(pX, pY, m_buy_bg.PosX() + 388.0f, m_buy_bg.PosY() + 400.0f, 210.0f, 30.0f))
			{
				m_bVolumeFocused = true;
				if (!m_bVirtualKeyboardShow)
				{
					virtualkeyboard_show();
				}
				return;
			}

			if (m_bVirtualKeyboardShow)
			{
				virtualkeyboard_hide();
			}
		}

		// menu item di klik
		if (m_bMenuActive)
		{
			if (m_menu_btn_trade_central.isWithin(pX, pY))
			{
				fprintf(stderr, "klik m_menu_btn_trade_central.\n");
//				if (m_platform.getOrientation() != 0)
//				{
//					m_platform.setOrientation(0);
//					sleep(3);
//					m_platform.getSize(m_screenWidth, m_screenHeight);
//					enable2D();
//					updateForPotrait();
//				}

				m_menu_btn_trade_central.isPressed = false;
				m_bShowSubmenuTC = !m_bShowSubmenuTC;
				//m_bShowMenu = false;
				//m_bMenuActive = false;
				//m_bMenuHideAnimation = true;
				m_bShowSubmenuInformation = false;
				return;
			}
			if (m_menu_btn_charts.isWithin(pX, pY))
			{
				fprintf(stderr, "klik m_menu_btn_charts.\n");
				if (m_platform.getOrientation() != 1)
				{
					m_platform.setOrientation(1);
					sleep(3);
					m_platform.getSize(m_screenWidth, m_screenHeight);
					enable2D_land();
					updateForLandscape();
				}

				m_menu_btn_charts.isPressed = false;

				m_state = CHARTS;
				m_bShowMenu = false;
				m_bMenuActive = false;
				//m_bMenuHideAnimation = true;
				m_bShowSubmenuTC = false;
				m_bShowSubmenuInformation = false;
				return;
			}
			if (m_menu_btn_informations.isWithin(pX, pY))
			{
				fprintf(stderr, "klik m_menu_btn_informations.\n");
//				if (m_platform.getOrientation() != 0)
//				{
//					m_platform.setOrientation(0);
//					sleep(3);
//					m_platform.getSize(m_screenWidth, m_screenHeight);
//					enable2D();
//					updateForPotrait();
//				}
				m_menu_btn_informations.isPressed = false;
				m_bShowSubmenuInformation = !m_bShowSubmenuInformation;

				//m_state = INFORMATIONS;
				//m_bShowMenu = false;
				//m_bMenuActive = false;
				//m_bMenuHideAnimation = true;
				m_bShowSubmenuTC = false;
				return;
			}
			if (m_menu_btn_portfolio.isWithin(pX, pY))
			{
				fprintf(stderr, "klik m_menu_btn_informations.\n");
				if (m_platform.getOrientation() != 0)
				{
					m_platform.setOrientation(0);
					sleep(3);
					m_platform.getSize(m_screenWidth, m_screenHeight);
					enable2D();
					updateForPotrait();
				}
				m_menu_btn_portfolio.isPressed = false;
				m_state = PORTFOLIO;
				m_bShowMenu = false;
				m_bMenuActive = false;
				//m_bMenuHideAnimation = true;
				m_bShowSubmenuTC = false;
				m_bShowSubmenuInformation = false;
				return;
			}
			if (m_menu_btn_order_trade.isWithin(pX, pY))
			{
				fprintf(stderr, "klik m_menu_btn_order_trade.\n");
				if (m_platform.getOrientation() != 0)
				{
					m_platform.setOrientation(0);
					sleep(3);
					m_platform.getSize(m_screenWidth, m_screenHeight);
					enable2D();
					updateForPotrait();
				}
				m_menu_btn_order_trade.isPressed = false;

				m_state = ORDER_TRADE;
				m_bShowMenu = false;
				m_bMenuActive = false;
				//m_bMenuHideAnimation = true;
				m_bShowSubmenuTC = false;
				m_bShowSubmenuInformation = false;
				return;
			}
			if (m_menu_btn_my_account.isWithin(pX, pY))
			{
				fprintf(stderr, "klik m_menu_btn_my_account.\n");
				if (m_platform.getOrientation() != 0)
				{
					m_platform.setOrientation(0);
					sleep(3);
					m_platform.getSize(m_screenWidth, m_screenHeight);
					enable2D();
					updateForPotrait();
				}
				m_menu_btn_my_account.isPressed = false;

				m_state = MY_ACCOUNT;
				m_bShowMenu = false;
				m_bMenuActive = false;
				//m_bMenuHideAnimation = true;
				m_bShowSubmenuTC = false;
				m_bShowSubmenuInformation = false;
				return;
			}
			if (m_menu_btn_logout.isWithin(pX, pY))
			{
				fprintf(stderr, "klik m_menu_btn_logout.\n");
				m_menu_btn_logout.isPressed = false;

				m_state = HOME;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bLogged = false;
				m_bShowSubmenuTC = false;
				m_bShowSubmenuInformation = false;
				loginStatus = NOT_SIGNIN;
				return;
			}

			if (m_bShowSubmenuTC)
			{
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bShowSubmenuTC = false;
				m_bShowSubmenuInformation = false;
				if (m_menu_tc_btn_running_trade.isWithin(pX, pY))
				{
					fprintf(stderr, "klik m_menu_tc_btn_running_trade.\n");
					if (m_platform.getOrientation() != 0)
					{
						m_platform.setOrientation(0);
						sleep(3);
						m_platform.getSize(m_screenWidth, m_screenHeight);
						enable2D();
						updateForPotrait();
					}
					m_menu_tc_btn_running_trade.isPressed = false;

					m_state = RUNNING_TRADE;
					ambilDataRunningTrade();
					//m_bMenuHideAnimation = true;
					return;
				}
				if (m_menu_tc_btn_stock_watch.isWithin(pX, pY))
				{
					fprintf(stderr, "klik m_menu_tc_btn_stock_watch.\n");
					if (m_platform.getOrientation() != 0)
					{
						m_platform.setOrientation(0);
						sleep(3);
						m_platform.getSize(m_screenWidth, m_screenHeight);
						enable2D();
						updateForPotrait();
					}
					m_menu_tc_btn_stock_watch.isPressed = false;

					m_state = STOCK_WATCH;
					//m_bMenuHideAnimation = true;
					return;
				}
				if (m_menu_tc_btn_complete_book.isWithin(pX, pY))
				{
					fprintf(stderr, "klik m_menu_tc_btn_complete_book.\n");
					if (m_platform.getOrientation() != 0)
					{
						m_platform.setOrientation(0);
						sleep(3);
						m_platform.getSize(m_screenWidth, m_screenHeight);
						enable2D();
						updateForPotrait();
					}
					m_menu_tc_btn_complete_book.isPressed = false;

					m_state = COMPLETE_BOOK;
					//m_bMenuHideAnimation = true;
					return;
				}
				if (m_menu_tc_btn_stock_quote.isWithin(pX, pY))
				{
					fprintf(stderr, "klik m_menu_tc_btn_stock_quote.\n");
					if (m_platform.getOrientation() != 0)
					{
						m_platform.setOrientation(0);
						sleep(3);
						m_platform.getSize(m_screenWidth, m_screenHeight);
						enable2D();
						updateForPotrait();
					}
					m_menu_tc_btn_stock_quote.isPressed = false;

					m_state = STOCK_QUOTE;
					//m_bMenuHideAnimation = true;
					return;
				}
				if (m_menu_tc_btn_broker_quote.isWithin(pX, pY))
				{
					fprintf(stderr, "klik m_menu_tc_btn_broker_quote.\n");
					if (m_platform.getOrientation() != 0)
					{
						m_platform.setOrientation(0);
						sleep(3);
						m_platform.getSize(m_screenWidth, m_screenHeight);
						enable2D();
						updateForPotrait();
					}
					m_menu_tc_btn_broker_quote.isPressed = false;

					m_state = BROKER_QUOTE;
					//m_bMenuHideAnimation = true;
					return;
				}
				if (m_menu_tc_btn_stock_summary.isWithin(pX, pY))
				{
					fprintf(stderr, "klik m_menu_tc_btn_stock_summary.\n");
					if (m_platform.getOrientation() != 0)
					{
						m_platform.setOrientation(0);
						sleep(3);
						m_platform.getSize(m_screenWidth, m_screenHeight);
						enable2D();
						updateForPotrait();
					}
					m_menu_tc_btn_stock_summary.isPressed = false;

					m_state = STOCK_SUMMARY;
					//m_bMenuHideAnimation = true;
					return;
				}
				if (m_menu_tc_btn_broker_summary.isWithin(pX, pY))
				{
					fprintf(stderr, "klik m_menu_tc_btn_broker_summary.\n");
					if (m_platform.getOrientation() != 0)
					{
						m_platform.setOrientation(0);
						sleep(3);
						m_platform.getSize(m_screenWidth, m_screenHeight);
						enable2D();
						updateForPotrait();
					}
					m_menu_tc_btn_broker_summary.isPressed = false;

					m_state = BROKER_SUMMARY;
					//m_bMenuHideAnimation = true;
					return;
				}
				if (m_menu_tc_btn_non_regular.isWithin(pX, pY))
				{
					fprintf(stderr, "klik m_menu_tc_btn_non_regular.\n");
					if (m_platform.getOrientation() != 0)
					{
						m_platform.setOrientation(0);
						sleep(3);
						m_platform.getSize(m_screenWidth, m_screenHeight);
						enable2D();
						updateForPotrait();
					}
					m_menu_tc_btn_non_regular.isPressed = false;

					m_state = NON_REGULAR;
					//m_bMenuHideAnimation = true;
					return;
				}
			}

			if (m_bShowSubmenuInformation)
			{
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bShowSubmenuTC = false;
				m_bShowSubmenuInformation = false;

				if (m_menu_i_btn_news.isWithin(pX, pY))
				{
					fprintf(stderr, "klik m_menu_i_btn_news.\n");
					if (m_platform.getOrientation() != 0)
					{
						m_platform.setOrientation(0);
						sleep(3);
						m_platform.getSize(m_screenWidth, m_screenHeight);
						enable2D();
						updateForPotrait();
					}
					m_menu_i_btn_news.isPressed = false;
					m_state = NEWS;
					return;
				}

				if (m_menu_i_btn_compinfo.isWithin(pX, pY))
				{
					fprintf(stderr, "klik m_menu_i_btn_compinfo.\n");
					if (m_platform.getOrientation() != 0)
					{
						m_platform.setOrientation(0);
						sleep(3);
						m_platform.getSize(m_screenWidth, m_screenHeight);
						enable2D();
						updateForPotrait();
					}
					m_menu_i_btn_compinfo.isPressed = false;
					m_state = COMPANY_INFO;
					return;
				}
			}


			m_bShowMenu = false;
			m_bMenuActive = false;
		}

		switch (m_state)
		{
			case RUNNING_TRADE:
			case STOCK_WATCH:
				if (m_sw_btn_port1.isEnabled)
				{
					if (m_sw_btn_port1.isWithin(pX, pY))
					{
						m_sw_btn_port1.isPressed = false;
						return;
					}
				}
				if (m_sw_btn_banking.isEnabled)
				{
					if (m_sw_btn_banking.isWithin(pX, pY))
					{
						m_sw_btn_banking.isPressed = false;
						return;
					}
				}
				if (m_sw_btn_mining.isEnabled)
				{
					if (m_sw_btn_mining.isWithin(pX, pY))
					{
						m_sw_btn_mining.isPressed = false;
						return;
					}
				}
				if (m_sw_btn_cons.isEnabled)
				{
					if (m_sw_btn_cons.isWithin(pX, pY))
					{
						m_sw_btn_cons.isPressed = false;
						return;
					}
				}
				if (m_sw_btn_plus_green.isEnabled)
				{
					if (m_sw_btn_plus_green.isWithin(pX, pY))
					{
						m_sw_btn_plus_green.isPressed = false;
						return;
					}
				}
				break;
			case COMPLETE_BOOK:
			case STOCK_QUOTE:
			case BROKER_QUOTE:
			case STOCK_SUMMARY:
			case BROKER_SUMMARY:
			case NON_REGULAR:
			case CHARTS:
			case INFORMATIONS:
			case PORTFOLIO:
			case ORDER_TRADE:
				break;
			case MY_ACCOUNT:
				break;
		}
	}

}

void panin::onLeftPress(float x, float y) {
	fprintf(stderr, "onLeftPress.\n");
	float pX, pY;
	pX = x;
	pY = m_screenHeight - y;

	fprintf(stderr, "posisi: %f, %f, %f, %f.\n", pX, pY, x, y);

	if (m_state == HOME)
	{
		if (m_btn_login.isEnabled)
		{
			if (m_btn_login.isWithin(pX, pY))
			{
				m_btn_login.isPressed = true;
				fprintf(stderr, "Button login di tekan.\n");
				return;
			}

		}


		if (m_btn_home_info.isEnabled)
		{
			if (m_btn_home_info.isWithin(pX, pY))
			{
				m_btn_home_info.isPressed = true;
				fprintf(stderr, "Button info ditekan.\n");
				return;
			}
		}

		if (m_btn_home_setel.isEnabled)
		{
			if (m_btn_home_setel.isWithin(pX, pY))
			{
				m_btn_home_setel.isPressed = true;
				fprintf(stderr, "Button setel ditekan.\n");
				return;
			}
		}

		if (m_btn_setel_default.isEnabled)
		{
			if (m_btn_setel_default.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel default is released.\n");
				m_btn_setel_default.isPressed = true;
				return;
			}
		}
		if (m_btn_setel_set202.isEnabled)
		{
			if (m_btn_setel_set202.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel set202 is released.\n");
				m_btn_setel_set202.isPressed = true;
				return;
			}
		}
		if (m_btn_setel_set107.isEnabled)
		{
			if (m_btn_setel_set107.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel set107 is released.\n");
				m_btn_setel_set107.isPressed = true;
				return;
			}
		}
		if (m_btn_setel_save.isEnabled)
		{
			if (m_btn_setel_save.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel save is released.\n");
				m_btn_setel_save.isPressed = true;
				return;
			}
		}
		if (m_btn_setel_x.isEnabled)
		{
			if (m_btn_setel_x.isWithin(pX, pY))
			{
				fprintf(stderr, "button home setel x is released.\n");
				m_btn_setel_x.isPressed = true;
				return;
			}
		}
		if (m_btn_home_username.isEnabled)
		{
			if (m_btn_home_username.isWithin(pX, pY))
			{
				fprintf(stderr, "button home username is released.\n");
				m_btn_home_username.isPressed = true;
				return;
			}
		}

		if (m_btn_home_password.isEnabled)
		{
			if (m_btn_home_password.isWithin(pX, pY))
			{
				fprintf(stderr, "button home password is released.\n");
				m_btn_home_password.isPressed = true;
				return;
			}
		}
	}
	else
	{
		if (m_btn_menu.isEnabled)
		{
			if (m_btn_menu.isWithin(pX, pY))
			{
				m_btn_menu.isPressed = true;
				return;
			}
		}

		if (m_btn_info.isEnabled)
		{
			if (m_btn_info.isWithin(pX, pY))
			{
				m_btn_info.isPressed = true;
				return;
			}
		}

		if (m_btn_buy.isEnabled)
		{
			if (m_btn_buy.isWithin(pX, pY))
			{
				m_btn_buy.isPressed = true;
				return;
			}
		}

		if (m_btn_sell.isEnabled)
		{
			if (m_btn_sell.isWithin(pX, pY))
			{
				m_btn_sell.isPressed = true;
				return;
			}
		}

		if (m_bShowSell)
		{
			if (m_btn_sell_execute.isWithin(pX, pY))
			{
				m_btn_sell_execute.isPressed = true;
				return;
			}
			if (m_btn_sell_refresh.isWithin(pX, pY))
			{
				m_btn_sell_refresh.isPressed = true;
				return;
			}
			if (m_btn_sell_x.isWithin(pX, pY))
			{
				m_btn_sell_x.isPressed = true;
				return;
			}
		}

		if (m_bShowBuy)
		{
			if (m_btn_buy_execute.isWithin(pX, pY))
			{
				m_btn_buy_execute.isPressed = true;
				return;
			}
			if (m_btn_buy_refresh.isWithin(pX, pY))
			{
				m_btn_buy_refresh.isPressed = true;
				return;
			}
			if (m_btn_buy_x.isWithin(pX, pY))
			{
				m_btn_buy_x.isPressed = true;
				return;
			}
		}

		// menu item di klik
		if (m_bMenuActive)
		{
			if (m_menu_btn_trade_central.isWithin(pX, pY))
			{
				m_menu_btn_trade_central.isPressed = true;
				return;
			}
			if (m_menu_btn_charts.isWithin(pX, pY))
			{
				m_menu_btn_charts.isPressed = true;
				return;
			}
			if (m_menu_btn_informations.isWithin(pX, pY))
			{
				m_menu_btn_informations.isPressed = true;
				return;
			}
			if (m_menu_btn_portfolio.isWithin(pX, pY))
			{
				m_menu_btn_portfolio.isPressed = true;
				return;
			}
			if (m_menu_btn_order_trade.isWithin(pX, pY))
			{
				m_menu_btn_order_trade.isPressed = true;
				return;
			}
			if (m_menu_btn_my_account.isWithin(pX, pY))
			{
				m_menu_btn_my_account.isPressed = true;
				return;
			}
			if (m_menu_btn_logout.isWithin(pX, pY))
			{
				m_menu_btn_logout.isPressed = true;
				return;
			}

			if (m_bShowSubmenuTC)
			{
				if (m_menu_tc_btn_running_trade.isWithin(pX, pY))
				{
					m_menu_tc_btn_running_trade.isPressed = true;
					return;
				}
				if (m_menu_tc_btn_stock_watch.isWithin(pX, pY))
				{
					m_menu_tc_btn_stock_watch.isPressed = true;
					return;
				}
				if (m_menu_tc_btn_complete_book.isWithin(pX, pY))
				{
					m_menu_tc_btn_complete_book.isPressed = true;
					return;
				}
				if (m_menu_tc_btn_stock_quote.isWithin(pX, pY))
				{
					m_menu_tc_btn_stock_quote.isPressed = true;
					return;
				}
				if (m_menu_tc_btn_broker_quote.isWithin(pX, pY))
				{
					m_menu_tc_btn_broker_quote.isPressed = true;
					return;
				}
				if (m_menu_tc_btn_stock_summary.isWithin(pX, pY))
				{
					m_menu_tc_btn_stock_summary.isPressed = true;
					return;
				}
				if (m_menu_tc_btn_broker_summary.isWithin(pX, pY))
				{
					m_menu_tc_btn_broker_summary.isPressed = true;
					return;
				}
				if (m_menu_tc_btn_non_regular.isWithin(pX, pY))
				{
					m_menu_tc_btn_non_regular.isPressed = true;
					return;
				}
			}

			if (m_bShowSubmenuInformation)
			{
				if (m_menu_i_btn_news.isWithin(pX, pY))
				{
					m_menu_i_btn_news.isPressed = true;
					return;
				}
				if (m_menu_i_btn_compinfo.isWithin(pX, pY))
				{
					m_menu_i_btn_compinfo.isPressed = true;
					return;
				}
			}
		}

		switch (m_state)
		{
			case RUNNING_TRADE:
			case STOCK_WATCH:
				if (m_sw_btn_port1.isEnabled)
				{
					if (m_sw_btn_port1.isWithin(pX, pY))
					{
						m_sw_btn_port1.isPressed = true;
						return;
					}
				}
				if (m_sw_btn_banking.isEnabled)
				{
					if (m_sw_btn_banking.isWithin(pX, pY))
					{
						m_sw_btn_banking.isPressed = true;
						return;
					}
				}
				if (m_sw_btn_mining.isEnabled)
				{
					if (m_sw_btn_mining.isWithin(pX, pY))
					{
						m_sw_btn_mining.isPressed = true;
						return;
					}
				}
				if (m_sw_btn_cons.isEnabled)
				{
					if (m_sw_btn_cons.isWithin(pX, pY))
					{
						m_sw_btn_cons.isPressed = true;
						return;
					}
				}
				if (m_sw_btn_plus_green.isEnabled)
				{
					if (m_sw_btn_plus_green.isWithin(pX, pY))
					{
						m_sw_btn_plus_green.isPressed = true;
						return;
					}
				}
				break;
			case COMPLETE_BOOK:
			case STOCK_QUOTE:
			case BROKER_QUOTE:
			case STOCK_SUMMARY:
			case BROKER_SUMMARY:
			case NON_REGULAR:
			case CHARTS:
			case INFORMATIONS:
			case PORTFOLIO:
			case ORDER_TRADE:
				break;

			case MY_ACCOUNT:
				m_bOldPaswordFocus = false;
				m_bNewPaswordFocus = false;
				m_bConfirmPwdFocus = false;
				m_bOldPinFocus = false;
				m_bNewPinFocus = false;
				m_bConfirmPinFocus = false;

				if (periksaPointer(pX, pY, m_ac_bg_black.PosX() + 60.0f, m_ac_bg_black.PosY() + 340.0f, 600.0f, 25.0f))
				{
					m_bOldPaswordFocus = true;
					if (!m_bVirtualKeyboardShow)
					{
						virtualkeyboard_show();
					}
				}
				else if (periksaPointer(pX, pY, m_ac_bg_black.PosX() + 60.0f, m_ac_bg_black.PosY() + 240.0f, 600.0f, 25.0f))
				{
					m_bNewPaswordFocus = true;
					if (!m_bVirtualKeyboardShow)
					{
						virtualkeyboard_show();
					}
				}
				else if (periksaPointer(pX, pY, m_ac_bg_black.PosX() + 60.0f, m_ac_bg_black.PosY() + 145.0f, 600.0f, 25.0f))
				{
					m_bConfirmPwdFocus = true;
					if (!m_bVirtualKeyboardShow)
					{
						virtualkeyboard_show();
					}
				}
				else if (periksaPointer(pX, pY, m_ac_bg_black2.PosX() + 60.0f, m_ac_bg_black2.PosY() + 340.0f, 600.0f, 25.0f))
				{
					m_bOldPinFocus = true;
					if (!m_bVirtualKeyboardShow)
					{
						virtualkeyboard_show();
					}
				}
				else if (periksaPointer(pX, pY, m_ac_bg_black2.PosX() + 60.0f, m_ac_bg_black2.PosY() + 240.0f, 600.0f, 25.0f))
				{
					m_bNewPinFocus = true;
					if (!m_bVirtualKeyboardShow)
					{
						virtualkeyboard_show();
					}
				}
				else if (periksaPointer(pX, pY, m_ac_bg_black2.PosX() + 60.0f, m_ac_bg_black2.PosY() + 145.0f, 600.0f, 25.0f))
				{
					m_bConfirmPinFocus = true;
					if (!m_bVirtualKeyboardShow)
					{
						virtualkeyboard_show();
					}
				}
				else
				{
					if (!m_bVirtualKeyboardShow)
					{
						virtualkeyboard_hide();
					}
				}
				break;
		}
	}
}

void panin::onKeyPressed(int c) {
	fprintf(stderr, "The '%c' key was pressed\n", (char) c);
	if (m_bUsernameFocus)
	{
		if (c == KEYCODE_RETURN || c == KEYCODE_TAB)
		{
			m_bUsernameFocus = false;
			m_bPasswordFocus = true;
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_u_name.length() > 0)
			{
				char name [m_u_name.length()];
				std::memset(name, 0, m_u_name.length());
				std::strncpy(name, m_u_name.c_str(), m_u_name.length()-1);
				m_u_name = "";
				m_u_name = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_u_name = m_u_name + (char)c;
		}
	}
	else if (m_bPasswordFocus)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bUsernameFocus = false;
			m_bPasswordFocus = false;
			periksaLogin();
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_u_pass.length() > 0)
			{
				char name [m_u_pass.length()];
				std::memset(name, 0, m_u_pass.length());
				std::strncpy(name, m_u_pass.c_str(), m_u_pass.length()-1);
				m_u_pass = "";
				m_u_pass = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_u_pass = m_u_pass + (char)c;
		}

	}
	else if (m_bAccountIdFocused)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bAccountIdFocused = false;
			m_bStockTradeFocused = true;
			m_bPriceFocused = false;
			m_bVolumeFocused = false;
			if (!m_bVirtualKeyboardShow)
			{
				virtualkeyboard_show();
			}
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_sAccID.length() > 0)
			{
				char name [m_sAccID.length()];
				std::memset(name, 0, m_sAccID.length());
				std::strncpy(name, m_sAccID.c_str(), m_sAccID.length()-1);
				m_sAccID = "";
				m_sAccID = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_sAccID = m_sAccID + (char)c;
		}
	}
	else if (m_bStockTradeFocused)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bAccountIdFocused = false;
			m_bStockTradeFocused = false;
			m_bPriceFocused = true;
			m_bVolumeFocused = false;
			if (!m_bVirtualKeyboardShow)
			{
				virtualkeyboard_show();
			}
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_sStockCode.length() > 0)
			{
				char name [m_sStockCode.length()];
				std::memset(name, 0, m_sStockCode.length());
				std::strncpy(name, m_sStockCode.c_str(), m_sStockCode.length()-1);
				m_sStockCode = "";
				m_sStockCode = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_sStockCode = m_sStockCode + (char)c;
		}
	}
	else if (m_bPriceFocused)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bAccountIdFocused = false;
			m_bStockTradeFocused = false;
			m_bPriceFocused = false;
			m_bVolumeFocused = true;
			if (!m_bVirtualKeyboardShow)
			{
				virtualkeyboard_show();
			}
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_sPrice.length() > 0)
			{
				char name [m_sPrice.length()];
				std::memset(name, 0, m_sPrice.length());
				std::strncpy(name, m_sPrice.c_str(), m_sPrice.length()-1);
				m_sPrice = "";
				m_sPrice = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_sPrice = m_sPrice + (char)c;
		}
	}
	else if (m_bVolumeFocused)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bAccountIdFocused = false;
			m_bStockTradeFocused = false;
			m_bPriceFocused = false;
			m_bVolumeFocused = false;
			if (m_bVirtualKeyboardShow)
			{
				virtualkeyboard_hide();
			}
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_sLot.length() > 0)
			{
				char name [m_sLot.length()];
				std::memset(name, 0, m_sLot.length());
				std::strncpy(name, m_sLot.c_str(), m_sLot.length()-1);
				m_sLot = "";
				m_sLot = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_sLot = m_sLot + (char)c;
		}
	}
	else if (m_bOldPaswordFocus)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bOldPaswordFocus = false;
			m_bNewPaswordFocus = false;
			m_bConfirmPwdFocus = false;
			m_bOldPinFocus = false;
			m_bNewPinFocus = false;
			m_bConfirmPinFocus = false;
			//UpdatePassword();
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_sOldPass.length() > 0)
			{
				char name [m_sOldPass.length()];
				std::memset(name, 0, m_sOldPass.length());
				std::strncpy(name, m_sOldPass.c_str(), m_sOldPass.length()-1);
				m_sOldPass = "";
				m_sOldPass = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_sOldPass = m_sOldPass + (char)c;
		}

	}
	else if (m_bNewPaswordFocus)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bOldPaswordFocus = false;
			m_bNewPaswordFocus = false;
			m_bConfirmPwdFocus = false;
			m_bOldPinFocus = false;
			m_bNewPinFocus = false;
			m_bConfirmPinFocus = false;
			//UpdatePassword();
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_sNewPass.length() > 0)
			{
				char name [m_sNewPass.length()];
				std::memset(name, 0, m_sNewPass.length());
				std::strncpy(name, m_sNewPass.c_str(), m_sNewPass.length()-1);
				m_sNewPass = "";
				m_sNewPass = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_sNewPass = m_sNewPass + (char)c;
		}
	}
	else if (m_bConfirmPwdFocus)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bOldPaswordFocus = false;
			m_bNewPaswordFocus = false;
			m_bConfirmPwdFocus = false;
			m_bOldPinFocus = false;
			m_bNewPinFocus = false;
			m_bConfirmPinFocus = false;
			//UpdatePassword();
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_sConfirmPass.length() > 0)
			{
				char name [m_sConfirmPass.length()];
				std::memset(name, 0, m_sConfirmPass.length());
				std::strncpy(name, m_sConfirmPass.c_str(), m_sConfirmPass.length()-1);
				m_sConfirmPass = "";
				m_sConfirmPass = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_sConfirmPass = m_sConfirmPass + (char)c;
		}
	}
	else if (m_bOldPinFocus)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bOldPaswordFocus = false;
			m_bNewPaswordFocus = false;
			m_bConfirmPwdFocus = false;
			m_bOldPinFocus = false;
			m_bNewPinFocus = false;
			m_bConfirmPinFocus = false;
			//UpdatePassword();
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_sOldPin.length() > 0)
			{
				char name [m_sOldPin.length()];
				std::memset(name, 0, m_sOldPin.length());
				std::strncpy(name, m_sOldPin.c_str(), m_sOldPin.length()-1);
				m_sOldPin = "";
				m_sOldPin = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_sOldPin = m_sOldPin + (char)c;
		}
	}
	else if (m_bNewPinFocus)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bOldPaswordFocus = false;
			m_bNewPaswordFocus = false;
			m_bConfirmPwdFocus = false;
			m_bOldPinFocus = false;
			m_bNewPinFocus = false;
			m_bConfirmPinFocus = false;
			//UpdatePassword();
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_sNewPin.length() > 0)
			{
				char name [m_sNewPin.length()];
				std::memset(name, 0, m_sNewPin.length());
				std::strncpy(name, m_sNewPin.c_str(), m_sNewPin.length()-1);
				m_sNewPin = "";
				m_sNewPin = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_sNewPin = m_sNewPin + (char)c;
		}
	}
	else if (m_bConfirmPinFocus)
	{
		if (c == KEYCODE_RETURN)
		{
			m_bOldPaswordFocus = false;
			m_bNewPaswordFocus = false;
			m_bConfirmPwdFocus = false;
			m_bOldPinFocus = false;
			m_bNewPinFocus = false;
			m_bConfirmPinFocus = false;
			//UpdatePassword();
		}
		else if (c == KEYCODE_BACKSPACE)
		{
			if (m_sConfirmPin.length() > 0)
			{
				char name [m_sConfirmPin.length()];
				std::memset(name, 0, m_sConfirmPin.length());
				std::strncpy(name, m_sConfirmPin.c_str(), m_sConfirmPin.length()-1);
				m_sConfirmPin = "";
				m_sConfirmPin = name;
			}
		}
		else if (c >= UNICODE_BASIC_LATIN_FIRST && c <= UNICODE_BASIC_LATIN_LAST)
		{
			m_sConfirmPin = m_sConfirmPin + (char)c;
		}
	}
}

void panin::button::setPosition(float x, float y) {
	posX = x;
	posY = y;
	regular->setPosition(x, y);
	pressed->setPosition(x, y);
}

void panin::button::draw() const {

	if (isPressed == true) {
		pressed->draw();
	} else {
		regular->draw();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	bbutil_render_text(font, text, posX + textX, posY + textY, 1.0f, 1.0f, 1.0f,
			1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void panin::onExit() {
	m_shutdown = true;
}

void panin::onPromptOk(const std::string& input) {
	//m_platform.submitUserName(input);
}

void panin::setConfiguration(eConfiguration conf) {
	switch (conf) {
	case CONF_DEFAULT:
	default:
		m_platform.server1 = "172.31.2.78:8080";
		m_platform.server2 = "172.31.2.78:8443";
		break;

	case CONF_SET107:
		m_platform.server1 = "172.31.2.78:8080";
		m_platform.server2 = "172.31.2.78:8443";
		break;

	case CONF_SET202:
		m_platform.server1 = "172.31.2.78:8080";
		m_platform.server2 = "172.31.2.78:8443";
		break;

	case CONF_SAVE:
		m_platform.server1 = "172.31.2.78:8080";
		m_platform.server2 = "172.31.2.78:8443";
		break;
	}
}

void * threadLogin(void * Var) {
	std::string u_name, u_pass;

	//u_name = *((std::string *) data);
	//u_pass = *((std::string *) data +1);

	threadVar myVar;
	myVar = *((threadVar *) Var);

	u_name = myVar.t_myUser.username;
	u_pass = myVar.t_myUser.password;

	char * url = new char[1024];
	std::strcpy(url, "http://202.53.249.2:8080/mi2/marketInfoData?request=login&user=");
	//std::strcpy(url, "https://202.53.249.3:443/mi2/marketInfoData?request=login&user=");
	std::strcat(url, u_name.c_str());
	std::strcat(url, "&password=");
	std::strcat(url, u_pass.c_str());

	fprintf(stderr, "url yang diakses : %s.\n", url);
	myServerConnection = new ServerConnection();

	if (CURLE_OK == myServerConnection->doLogin(url, osStream, 30.0f)) {
		std::string hasil = osStream.str();
		fprintf(stderr, "hasil balikan: %s -- %s.\n", hasil.c_str(), osStream.str().c_str());
		char s1[hasil.length() + 1];
		std::memset(s1, 0, hasil.length() + 1);
		std::strncpy(s1, hasil.c_str(), hasil.length()-2);
		char s2[] = "true";
		if (std::strncmp(s1, s2, std::strlen(s2)) == 0) {
			loginStatus = SIGNEDIN;
			osStream.clear();
			fprintf(stderr, "login berhasil.\n");
		}
		else
		{
			loginStatus = SIGN_FAILED;
			fprintf(stderr, "login gagal.\n");
		}

//		for (int i = 0; i < 10; ++i)
//		{
//			hasil = osStream.str();
//			fprintf(stderr, "hasil balikan: %s -- %s.\n", hasil.c_str(), osStream.str().c_str());
//			sleep(3);
//		}
	}
	else
	{
		fprintf(stderr, "curl tidak ok.\n");
	}

	delete url;

	return NULL;
}

void panin::periksaLogin() {
	//std::string hasil;
	pthread_t pth;

	myUser.username = "test6";
	myUser.password = "123456";
	//myUser.username = m_u_name;
	//myUser.password = m_u_pass;

	threadVar myThreadVar[1];
	myThreadVar[0].t_myUser.username = myUser.username;
	myThreadVar[0].t_myUser.password = myUser.password;

	virtualkeyboard_hide();
	osStream.str("");
	osStream.clear();
	pthread_create(&pth, NULL, threadLogin, (void*) myThreadVar);

}

void * threadDataRT(void* var) {
	char * url = new char[1024];
	std::strcpy(url, "http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=start");

	//std::strcpy(url,"http://202.53.249.2:8080/mi2/marketInfoData?request=currencies&act=start");

	fprintf(stderr, "url yang diakses : %s.\n", url);
	if (myServerConnection == NULL) {
		myServerConnection = new ServerConnection();
	}

	osStream.str("");
	osStream.clear();
	if (CURLE_OK == myServerConnection->doHttpGet2(url, osStream, 30.0f))
	{
		std::string hasil = osStream.str();
		fprintf(stderr, "hasil balikan start running trade: >>%s<<.\n", hasil.c_str());
	}

	std::memset(url, 0, 1024 * sizeof(url[0]));
	std::strcpy(url,
			"http://202.53.249.2:8080/mi2/marketInfoData?request=dataStream");
	osStream.str("");
	osStream.clear();

	bIsGettingRT = true;
	do
	{
		osStream.str("");
		osStream.clear();
		myServerConnection->doHttpGet2(url, osStream, 3.0f);

//		std::string hasil = osStream.str();
//		fprintf(stderr, "hasil balikan start dataStream: >>%s<<.\n", hasil.c_str());
	}
	while (bIsGettingRT);

	if (!bIsGettingRT)
	{
		osStream.str("");
		osStream.clear();
		std::memset(url, 0, 1024 * sizeof(url[0]));
		std::strcpy(url,
				"http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=stop");
		myServerConnection->doHttpGet2(url, osStream, 30.0f);
	}

	return NULL;
}

void panin::ambilDataRunningTrade() {
	pthread_t pth;

	m_vRT.clear();
	fprintf(stderr, "ambilDataRunningTrade.\n");
	pthread_create(&pth, NULL, threadDataRT, (void*) NULL);
}

void * threadDataSQ(void* var) {
	char * url = new char[1024];
	std::strcpy(url, "http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=start");

	fprintf(stderr, "url yang diakses : %s.\n", url);
	if (myServerConnection == NULL) {
		myServerConnection = new ServerConnection();
	}

	osStream.str("");
	osStream.clear();
	if (CURLE_OK == myServerConnection->doHttpGet2(url, osStream, 30.0f))
	{
		std::string hasil = osStream.str();
		fprintf(stderr, "hasil balikan start running trade: >>%s<<.\n", hasil.c_str());
	}

	std::memset(url, 0, 1024 * sizeof(url[0]));
	std::strcpy(url,
			"http://202.53.249.2:8080/mi2/marketInfoData?request=dataStream");
	osStream.str("");
	osStream.clear();

	bIsGettingSQ = true;
	do
	{
		osStream.str("");
		osStream.clear();
		myServerConnection->doHttpGet2(url, osStream, 3.0f);
	}
	while (bIsGettingSQ);

	if (!bIsGettingSQ)
	{
		osStream.str("");
		osStream.clear();
		std::memset(url, 0, 1024 * sizeof(url[0]));
		std::strcpy(url,
				"http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=stop");
		myServerConnection->doHttpGet2(url, osStream, 30.0f);
	}

	return NULL;
}

void panin::ambilDataStockQuote() {
	pthread_t pth;

	m_vSQ.clear();
	fprintf(stderr, "ambilDataRunningTrade.\n");
	pthread_create(&pth, NULL, threadDataSQ, (void*) NULL);
}

void * threadDataBQ(void* var) {
	char * url = new char[1024];
	std::strcpy(url, "http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=start");

	fprintf(stderr, "url yang diakses : %s.\n", url);
	if (myServerConnection == NULL) {
		myServerConnection = new ServerConnection();
	}

	osStream.str("");
	osStream.clear();
	if (CURLE_OK == myServerConnection->doHttpGet2(url, osStream, 30.0f))
	{
		std::string hasil = osStream.str();
		fprintf(stderr, "hasil balikan start running trade: >>%s<<.\n", hasil.c_str());
	}

	std::memset(url, 0, 1024 * sizeof(url[0]));
	std::strcpy(url,
			"http://202.53.249.2:8080/mi2/marketInfoData?request=dataStream");
	osStream.str("");
	osStream.clear();

	bIsGettingBQ = true;
	do
	{
		osStream.str("");
		osStream.clear();
		myServerConnection->doHttpGet2(url, osStream, 3.0f);
	}
	while (bIsGettingBQ);

	if (!bIsGettingBQ)
	{
		osStream.str("");
		osStream.clear();
		std::memset(url, 0, 1024 * sizeof(url[0]));
		std::strcpy(url,
				"http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=stop");
		myServerConnection->doHttpGet2(url, osStream, 30.0f);
	}

	return NULL;
}

void panin::ambilDataBrokerQuote() {
	pthread_t pth;

	m_vBQ.clear();
	fprintf(stderr, "ambilDataRunningTrade.\n");
	pthread_create(&pth, NULL, threadDataBQ, (void*) NULL);
}

void * threadDataSW(void* var) {
	char * url = new char[1024];
	std::strcpy(url, "http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=start");

	fprintf(stderr, "url yang diakses : %s.\n", url);
	if (myServerConnection == NULL) {
		myServerConnection = new ServerConnection();
	}

	osStream.str("");
	osStream.clear();
	if (CURLE_OK == myServerConnection->doHttpGet2(url, osStream, 30.0f))
	{
		std::string hasil = osStream.str();
		fprintf(stderr, "hasil balikan start running trade: >>%s<<.\n", hasil.c_str());
	}

	std::memset(url, 0, 1024 * sizeof(url[0]));
	std::strcpy(url,
			"http://202.53.249.2:8080/mi2/marketInfoData?request=dataStream");
	osStream.str("");
	osStream.clear();

	bIsGettingSW = true;
	do
	{
		osStream.str("");
		osStream.clear();
		myServerConnection->doHttpGet2(url, osStream, 3.0f);
	}
	while (bIsGettingSW);

	if (!bIsGettingSW)
	{
		osStream.str("");
		osStream.clear();
		std::memset(url, 0, 1024 * sizeof(url[0]));
		std::strcpy(url,
				"http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=stop");
		myServerConnection->doHttpGet2(url, osStream, 30.0f);
	}

	return NULL;
}

void panin::ambilDataStockWatch() {
	pthread_t pth;

	m_vSW.clear();
	fprintf(stderr, "ambilDataRunningTrade.\n");
	pthread_create(&pth, NULL, threadDataSW, (void*) NULL);
}

void * threadDataSS(void* var) {
	char * url = new char[1024];
	std::strcpy(url, "http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=start");

	fprintf(stderr, "url yang diakses : %s.\n", url);
	if (myServerConnection == NULL) {
		myServerConnection = new ServerConnection();
	}

	osStream.str("");
	osStream.clear();
	if (CURLE_OK == myServerConnection->doHttpGet2(url, osStream, 30.0f))
	{
		std::string hasil = osStream.str();
		fprintf(stderr, "hasil balikan start running trade: >>%s<<.\n", hasil.c_str());
	}

	std::memset(url, 0, 1024 * sizeof(url[0]));
	std::strcpy(url,
			"http://202.53.249.2:8080/mi2/marketInfoData?request=dataStream");
	osStream.str("");
	osStream.clear();

	bIsGettingSS = true;
	do
	{
		osStream.str("");
		osStream.clear();
		myServerConnection->doHttpGet2(url, osStream, 3.0f);
	}
	while (bIsGettingSS);

	if (!bIsGettingSS)
	{
		osStream.str("");
		osStream.clear();
		std::memset(url, 0, 1024 * sizeof(url[0]));
		std::strcpy(url,
				"http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=stop");
		myServerConnection->doHttpGet2(url, osStream, 30.0f);
	}

	return NULL;
}

void panin::ambilDataStockSummary() {
	pthread_t pth;

	m_vSS.clear();
	fprintf(stderr, "ambilDataRunningTrade.\n");
	pthread_create(&pth, NULL, threadDataSS, (void*) NULL);
}

void * threadDataBS(void* var) {
	char * url = new char[1024];
	std::strcpy(url, "http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=start");

	fprintf(stderr, "url yang diakses : %s.\n", url);
	if (myServerConnection == NULL) {
		myServerConnection = new ServerConnection();
	}

	osStream.str("");
	osStream.clear();
	if (CURLE_OK == myServerConnection->doHttpGet2(url, osStream, 30.0f))
	{
		std::string hasil = osStream.str();
		fprintf(stderr, "hasil balikan start running trade: >>%s<<.\n", hasil.c_str());
	}

	std::memset(url, 0, 1024 * sizeof(url[0]));
	std::strcpy(url,
			"http://202.53.249.2:8080/mi2/marketInfoData?request=dataStream");
	osStream.str("");
	osStream.clear();

	bIsGettingBS = true;
	do
	{
		osStream.str("");
		osStream.clear();
		myServerConnection->doHttpGet2(url, osStream, 3.0f);
	}
	while (bIsGettingBS);

	if (!bIsGettingBS)
	{
		osStream.str("");
		osStream.clear();
		std::memset(url, 0, 1024 * sizeof(url[0]));
		std::strcpy(url,
				"http://202.53.249.2:8080/mi2/marketInfoData?request=runningTrade&act=stop");
		myServerConnection->doHttpGet2(url, osStream, 30.0f);
	}

	return NULL;
}

void panin::ambilDataBrokerSummary() {
	pthread_t pth;

	m_vBS.clear();
	fprintf(stderr, "ambilDataRunningTrade.\n");
	pthread_create(&pth, NULL, threadDataBS, (void*) NULL);
}

//bool isWithin(float clickX, float clickY) const {
bool panin::periksaPointer(float pX, float pY, float kiri, float bawah, float lebar, float tinggi)
{
	return ((pX >= kiri) && (pX <= kiri + lebar) && (pY >= bawah) && (pY <= bawah  + tinggi));
}

} /* namespace paninMobile */
