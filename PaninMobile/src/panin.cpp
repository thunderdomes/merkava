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
	  m_bZ10(false),
	  m_bShowMenu(false),
	  m_bShowSubmenuTC(false),
	  m_bShowInfo(false),
	  m_bShowBuy(false),
	  m_bShowSell(false),
	  m_bShowHomeInfo(false),
	  m_bShowHomeSetel(false),
	  m_bUsernameFocus(false),
	  m_bPasswordFocus(false)
{
	// TODO Auto-generated constructor stub
	m_platform.setEventHandler(this);
	m_platform.getSize(m_screenWidth, m_screenHeight);
	fprintf(stderr, "width, height: %f, %f\n", m_screenWidth, m_screenHeight);

	int dpi = m_platform.getDPI();
	int point_size = (int)(15.0f / ((float)dpi / 170.0f ));

	m_font = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	m_font_global = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(36.0f / ((float)dpi / 170.0f ));
	m_font_ihsg_val = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(15.0f / ((float)dpi / 170.0f ));
	m_font_ihsg_vol = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(15.0f / ((float)dpi / 170.0f ));
	m_font_tanggal = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(8.0f / ((float)dpi / 170.0f ));
	m_font8 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(9.0f / ((float)dpi / 170.0f ));
	m_font9 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(10.0f / ((float)dpi / 170.0f ));
	m_font10 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(11.0f / ((float)dpi / 170.0f ));
	m_font11 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(12.0f / ((float)dpi / 170.0f ));
	m_font12 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(14.0f / ((float)dpi / 170.0f ));
	m_font14 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(20.0f / ((float)dpi / 170.0f ));
	m_font20 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(24.0f / ((float)dpi / 170.0f ));
	m_font24 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(28.0f / ((float)dpi / 170.0f ));
	m_font28 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
	if (!m_font) {
		fprintf(stderr, "Unable to load font\n");
	}

	point_size = (int)(36.0f / ((float)dpi / 170.0f ));
	m_font36 = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);
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

	fprintf(stderr, "load general assets.\n");
	m_header_bar_bg.load("app/native/assets/umum/bar.png");
	m_header_bar_bg.setPosition(0.0f, m_screenHeight - 137.0f);
	m_header_post.load("app/native/assets/umum/post.png");
	m_header_post.setPosition((m_screenWidth - m_header_post.Width())/2, m_screenHeight - 124.0f);
	m_btn_info_bg.load("app/native/assets/umum/info_blue.png");
	m_btn_menu_bg.load("app/native/assets/umum/menu_blue.png");
	//m_btn_menu_bg.setPosition(25.0f, m_screenHeight - 128.0f);
	m_btn_sell_bg.load("app/native/assets/umum/sell.png");
	//m_btn_sell_bg.setPosition(622.0f, m_screenHeight - 1254.0f);
	m_btn_buy_bg.load("app/native/assets/umum/buy.png");
	//m_btn_buy_bg.setPosition(460.0f, m_screenHeight - 1254.0f);

	m_btn_info.regular = &m_btn_info_bg;
	m_btn_info.pressed = &m_btn_info_bg;
	m_btn_info.sizeX	= m_btn_info_bg.Width();
	m_btn_info.sizeY	= m_btn_info_bg.Height();
	m_btn_info.font	= m_font_global;
	m_btn_info.text	= "";
	m_btn_info.isPressed = false;
	m_btn_info.isEnabled = true;
	m_btn_info.setPosition( 680.0f, (m_screenHeight - 128.0) );
	m_btn_menu.regular = &m_btn_menu_bg;
	m_btn_menu.pressed = &m_btn_menu_bg;
	m_btn_menu.sizeX	= m_btn_menu_bg.Width();
	m_btn_menu.sizeY	= m_btn_menu_bg.Height();
	m_btn_menu.font	= m_font;
	m_btn_menu.text	= "";
	m_btn_menu.isPressed	= false;
	m_btn_menu.isEnabled = true;
	m_btn_menu.setPosition( 25.0f, (m_screenHeight - 128.0) );
	m_btn_buy.regular = &m_btn_buy_bg;
	m_btn_buy.pressed = &m_btn_buy_bg;
	m_btn_buy.sizeX	= m_btn_buy_bg.Width();
	m_btn_buy.sizeY	= m_btn_buy_bg.Height();
	m_btn_buy.font	= m_font;
	m_btn_buy.text	= "";
	m_btn_buy.isPressed	= false;
	m_btn_buy.isEnabled = true;
	m_btn_buy.setPosition(622.0f, (m_screenHeight - 1254.0f));
	m_btn_sell.regular = &m_btn_sell_bg;
	m_btn_sell.pressed = &m_btn_sell_bg;
	m_btn_sell.sizeX	= m_btn_sell_bg.Width();
	m_btn_sell.sizeY	= m_btn_sell_bg.Height();
	m_btn_sell.font	= m_font;
	m_btn_sell.text	= "";
	m_btn_sell.isPressed	= false;
	m_btn_sell.isEnabled = true;
	m_btn_sell.setPosition( 460.0f, (m_screenHeight - 1254.0f));
	//ihsg
	m_ihsg2.load("app/native/assets/umum/ihsg.png");
	//m_ihsg2.setPosition(17.0f, 20.0f);
	m_ihsg2.setPosition(0.0f, 0.0f);
	// buy
	m_buy_bg.load("app/native/assets/umum/buy_bg.png");
	m_buy_bg.setPosition(57.0f, m_screenHeight - 1020.0f);
	m_buy_caption.load("app/native/assets/umum/buy_caption.png");
	m_buy_caption.setPosition(75.0f, m_screenHeight - 416.0f);
	m_buy_refresh.load("app/native/assets/umum/buy_refresh.png");
	m_buy_execute.load("app/native/assets/umum/buy_execute.png");
	m_buy_band.load("app/native/assets/umum/white_bar.png");
	m_buy_band.setPosition(74.0f, m_screenHeight - 922.0f);
	m_buy_x.load("app/native/assets/umum/buy_x.png");
	m_btn_buy_refresh.regular = &m_buy_refresh;
	m_btn_buy_refresh.pressed = &m_buy_refresh;
	m_btn_buy_refresh.sizeX	= m_buy_refresh.Width();
	m_btn_buy_refresh.sizeY	= m_buy_refresh.Height();
	m_btn_buy_refresh.font	= m_font;
	m_btn_buy_refresh.text	= "";
	m_btn_buy_refresh.isPressed	= false;
	m_btn_buy_refresh.setPosition( 173.0f, m_screenHeight - 918.0 );
	m_btn_buy_execute.regular = &m_buy_execute;
	m_btn_buy_execute.pressed = &m_buy_execute;
	m_btn_buy_execute.sizeX	= m_buy_execute.Width();
	m_btn_buy_execute.sizeY	= m_buy_execute.Height();
	m_btn_buy_execute.font	= m_font;
	m_btn_buy_execute.text	= "";
	m_btn_buy_execute.isPressed	= false;
	m_btn_buy_execute.setPosition( 450.0f, m_screenHeight - 918.0 );
	m_btn_buy_x.regular = &m_buy_x;
	m_btn_buy_x.pressed = &m_buy_x;
	m_btn_buy_x.sizeX	= m_buy_x.Width();
	m_btn_buy_x.sizeY	= m_buy_x.Height();
	m_btn_buy_x.font	= m_font;
	m_btn_buy_x.text	= "";
	m_btn_buy_x.isPressed	= false;
	m_btn_buy_x.setPosition( 662.0f, m_screenHeight - 412.0 );
	//sell
	m_sell_bg.load("app/native/assets/umum/sell_bg.png");
	m_sell_bg.setPosition(57.0f, m_screenHeight - 1020.0f);
	m_sell_caption.load("app/native/assets/umum/sell_caption.png");
	m_sell_caption.setPosition(75.0f, m_screenHeight - 416.0f);
	m_sell_refresh.load("app/native/assets/umum/sell_refresh.png");
	m_sell_execute.load("app/native/assets/umum/sell_execute.png");
	m_sell_band.load("app/native/assets/umum/white_bar.png");
	m_sell_band.setPosition(74.0f, m_screenHeight - 922.0f);
	m_sell_x.load("app/native/assets/umum/sell_x.png");
	m_btn_sell_refresh.regular = &m_sell_refresh;
	m_btn_sell_refresh.pressed = &m_sell_refresh;
	m_btn_sell_refresh.sizeX	= m_sell_refresh.Width();
	m_btn_sell_refresh.sizeY	= m_sell_refresh.Height();
	m_btn_sell_refresh.font	= m_font;
	m_btn_sell_refresh.text	= "";
	m_btn_sell_refresh.isPressed	= false;
	m_btn_sell_refresh.isEnabled = true;
	m_btn_sell_refresh.setPosition( 173.0f, m_screenHeight - 918.0 );
	m_btn_sell_execute.regular = &m_sell_execute;
	m_btn_sell_execute.pressed = &m_sell_execute;
	m_btn_sell_execute.sizeX	= m_sell_execute.Width();
	m_btn_sell_execute.sizeY	= m_sell_execute.Height();
	m_btn_sell_execute.font	= m_font;
	m_btn_sell_execute.text	= "";
	m_btn_sell_execute.isPressed	= false;
	m_btn_sell_execute.isEnabled = true;
	m_btn_sell_execute.setPosition( 450.0f, m_screenHeight - 918.0 );
	m_btn_sell_x.regular = &m_sell_x;
	m_btn_sell_x.pressed = &m_sell_x;
	m_btn_sell_x.sizeX	= m_sell_x.Width();
	m_btn_sell_x.sizeY	= m_sell_x.Height();
	m_btn_sell_x.font	= m_font;
	m_btn_sell_x.text	= "";
	m_btn_sell_x.isPressed	= false;
	m_btn_sell_x.isEnabled = true;
	m_btn_sell_x.setPosition( 662.0f, m_screenHeight - 412.0 );

	m_buysell_textfield_bg.load("app/native/assets/umum/table_bg.png");

	m_textfield_bg.load("app/native/assets/umum/textfield_bg.png");
	m_dialog_bg.load("app/native/assets/umum/dialog_bg.png");
	m_dialog_bg.setPosition(0.0f, m_screenHeight - 940.0f);
	m_blue_rect.load("app/native/assets/umum/btn_blue.png");
	m_setel_default.load("app/native/assets/umum/btndefault.png");
	m_setel_set202.load("app/native/assets/umum/btn202.png");
	m_setel_set107.load("app/native/assets/umum/btn107.png");
	m_setel_save.load("app/native/assets/umum/btnsave.png");
	m_setel_x.load("app/native/assets/umum/btn_x.png");
	m_btn_conf_ok.regular = &m_blue_rect;
	m_btn_conf_ok.pressed = &m_blue_rect;
	m_btn_conf_ok.sizeX	= m_blue_rect.Width();
	m_btn_conf_ok.sizeY	= m_blue_rect.Height();
	m_btn_conf_ok.font	= m_font;
	m_btn_conf_ok.text	= "OK";
	m_btn_conf_ok.isPressed	= false;
	m_btn_conf_ok.isEnabled = true;
	m_btn_conf_ok.setPosition( 435.0f, m_screenHeight - 713.0 );
	m_btn_conf_cancel.regular = &m_blue_rect;
	m_btn_conf_cancel.pressed = &m_blue_rect;
	m_btn_conf_cancel.sizeX	= m_blue_rect.Width();
	m_btn_conf_cancel.sizeY	= m_blue_rect.Height();
	m_btn_conf_cancel.font	= m_font;
	m_btn_conf_cancel.text	= "CANCEL";
	m_btn_conf_cancel.isPressed	= false;
	m_btn_conf_cancel.isEnabled = true;
	m_btn_conf_cancel.setPosition( 220.0f, m_screenHeight - 713.0 );
	m_btn_setel_default.regular = &m_setel_default;
	m_btn_setel_default.pressed = &m_setel_default;
	m_btn_setel_default.regular->setPosition(0.0f, 0.0f);
	m_btn_setel_default.sizeX	= m_setel_default.Width();
	m_btn_setel_default.sizeY	= m_setel_default.Height();
	m_btn_setel_default.font	= m_font;
	m_btn_setel_default.text	= "";
	m_btn_setel_default.isPressed	= false;
	m_btn_setel_default.isEnabled = true;
	m_btn_setel_default.setPosition( 64.0f, m_screenHeight - 866.0f );
	m_btn_setel_set202.regular = &m_setel_set202;
	m_btn_setel_set202.pressed = &m_setel_set202;
	m_btn_setel_set202.sizeX	= m_setel_set202.Width();
	m_btn_setel_set202.sizeY	= m_setel_set202.Height();
	m_btn_setel_set202.font	= m_font;
	m_btn_setel_set202.text	= "";
	m_btn_setel_set202.isPressed	= false;
	m_btn_setel_set202.isEnabled = true;
	m_btn_setel_set202.setPosition( 220.0f, m_screenHeight - 866.0f );
	m_btn_setel_set107.regular = &m_setel_set107;
	m_btn_setel_set107.pressed = &m_setel_set107;
	m_btn_setel_set107.sizeX	= m_setel_set107.Width();
	m_btn_setel_set107.sizeY	= m_setel_set107.Height();
	m_btn_setel_set107.font	= m_font;
	m_btn_setel_set107.text	= "";
	m_btn_setel_set107.isPressed	= false;
	m_btn_setel_set107.isEnabled = true;
	m_btn_setel_set107.setPosition( 377.0f, m_screenHeight - 866.0f );
	m_btn_setel_save.regular = &m_setel_save;
	m_btn_setel_save.pressed = &m_setel_save;
	m_btn_setel_save.sizeX	= m_setel_save.Width();
	m_btn_setel_save.sizeY	= m_setel_save.Height();
	m_btn_setel_save.font	= m_font;
	m_btn_setel_save.text	= "";
	m_btn_setel_save.isPressed	= false;
	m_btn_setel_save.isEnabled = true;
	m_btn_setel_save.setPosition(536.0f, m_screenHeight - 866.0f );
	m_btn_setel_x.regular = &m_setel_x;
	m_btn_setel_x.pressed = &m_setel_x;
	m_btn_setel_x.sizeX	= m_setel_x.Width();
	m_btn_setel_x.sizeY	= m_setel_x.Height();
	m_btn_setel_x.font	= m_font;
	m_btn_setel_x.text	= "";
	m_btn_setel_x.isPressed	= false;
	m_btn_setel_x.isEnabled = true;
	m_btn_setel_x.setPosition( 664.0f, m_screenHeight - 600.0f );

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
	m_btn_login.isEnabled = true;
	m_btn_login.setPosition( (m_screenWidth - m_btn_login.sizeX)/2, m_screenHeight - m_btn_login.sizeY - 710.0 );

	fprintf(stderr, "Load m_btn_home_info.\n");
	m_btn_home_info.regular = &m_home_info_default;
	m_btn_home_info.pressed = &m_home_info_pressed;
	m_btn_home_info.sizeX	= m_home_info_default.Width();
	m_btn_home_info.sizeY	= m_home_info_default.Height();
	m_btn_home_info.font	= m_font;
	m_btn_home_info.text	= "";
	m_btn_home_info.isPressed	= false;
	m_btn_home_info.isEnabled = true;
	m_btn_home_info.setPosition( m_screenWidth/2 - m_btn_home_info.sizeX -20.0f, (80.0f - m_btn_home_info.sizeY) );

	fprintf(stderr, "Load m_btn_home_setel.\n");
	m_btn_home_setel.regular = &m_home_setel_default;
	m_btn_home_setel.pressed = &m_home_setel_pressed;
	m_btn_home_setel.sizeX	= m_home_setel_default.Width();
	m_btn_home_setel.sizeY	= m_home_setel_default.Height();
	m_btn_home_setel.font	= m_font;
	m_btn_home_setel.text	= "";
	m_btn_home_setel.isPressed	= false;
	m_btn_home_setel.isEnabled = true;
	m_btn_home_setel.setPosition( m_screenWidth/2 + 20.0f, (80.0f - m_btn_home_setel.sizeY) );

	//TRADE
	fprintf(stderr, "Load running trade.\n");
	m_rt_caption.load("app/native/assets/running_trade/rt_bar_title.png");
	m_rt_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_rt_table_title.load("app/native/assets/running_trade/rt_table_title.png");
	m_rt_table_title.setPosition(0.0f, m_screenHeight - 262.0f);

	//stock watch
	fprintf(stderr, "Load stock watch.\n");
	m_sw_caption.load("app/native/assets/stock_watch/sw_caption.png");
	m_sw_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_sw_box_black.load("app/native/assets/stock_watch/sw_box_black.png");
	m_sw_box_black.setPosition(27.0f, m_screenHeight - 455.0f);
	m_sw_port1.load("app/native/assets/stock_watch/sw_port1.png");
	m_sw_port1.setPosition(41.0f, m_screenHeight - 270.0f);
	m_sw_banking.load("app/native/assets/stock_watch/sw_banking.png");
	m_sw_banking.setPosition(201.0f, m_screenHeight - 270.0f);
	m_sw_mining.load("app/native/assets/stock_watch/sw_mining.png");
	m_sw_mining.setPosition(362.0f, m_screenHeight - 270.0f);
	m_sw_cons.load("app/native/assets/stock_watch/sw_cons.png");
	m_sw_cons.setPosition(520.0f, m_screenHeight - 270.0f);
	m_sw_plus_green.load("app/native/assets/stock_watch/sw_plus_green.png");
	m_sw_plus_green.setPosition(676.0f, m_screenHeight - 270.0f);
	m_sw_val_green.load("app/native/assets/stock_watch/sw_green.png");
	m_sw_val_green.setPosition(40.0f, m_screenHeight - 413.0f);
	m_sw_val_yellow.load("app/native/assets/stock_watch/sw_yellow.png");
	m_sw_val_yellow.setPosition(40.0f, m_screenHeight - 413.0f);
	m_sw_val_red.load("app/native/assets/stock_watch/sw_red.png");
	m_sw_val_red.setPosition(240.0f, m_screenHeight - 413.0f);

	// complete book
	fprintf(stderr, "Load complete book.\n");
	m_cb_caption.load("app/native/assets/complete_book/completebook_caption.png");
	m_cb_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_cb_top_band.load("app/native/assets/complete_book/m_cb_top_band.png");
	m_cb_top_band.setPosition(0.0f, m_screenHeight - 260.0f);
	m_cb_table_title1.load("app/native/assets/complete_book/m_cb_table_title1.png");
	m_cb_table_title1.setPosition(0.0f, m_screenHeight - 450.0f);
	m_cb_table_title2.load("app/native/assets/complete_book/m_cb_table_title2.png");
	m_cb_table_title2.setPosition(0.0f, m_screenHeight - 730.0f);

	// stock quote
	fprintf(stderr, "Load stock quote.\n");
	m_sq_caption.load("app/native/assets/stock_quote/sq_caption.png");
	m_sq_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_sq_table_title.load("app/native/assets/stock_quote/sq_table_title.png");
	m_sq_table_title.setPosition(0.0f, m_screenHeight - 262.0f);

	// broker quote
	fprintf(stderr, "Load broker quote.\n");
	m_bq_caption.load("app/native/assets/broker_quote/bq_caption.png");
	m_bq_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_bq_table_title.load("app/native/assets/broker_quote/bq_table_title.png");
	m_bq_table_title.setPosition(0.0f, m_screenHeight - 262.0f);

	// stock summary
	fprintf(stderr, "Load stock summary.\n");
	m_ss_caption.load("app/native/assets/stock_summary/ss_caption.png");
	m_ss_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_ss_table_title.load("app/native/assets/stock_summary/ss_table_title.png");
	m_ss_table_title.setPosition(0.0f, m_screenHeight - 262.0f);

	// broker summary
	fprintf(stderr, "Load broker summary.\n");
	m_bs_caption.load("app/native/assets/broker_summary/bs_caption.png");
	m_bs_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_bs_table_title.load("app/native/assets/broker_summary/bs_table_title.png");
	m_bs_table_title.setPosition(0.0f, m_screenHeight - 262.0f);

	// menu
	fprintf(stderr, "Load menu.\n");
	m_menu_bg.load("app/native/assets/menu/menu_bg.png");
	//m_menu_bg.setPosition(-m_menu_bg.Width(), m_screenHeight - m_menu_bg.Height());
	m_menu_bg.setPosition(0.0f, m_screenHeight - m_menu_bg.Height() -140.0f);
	m_menu_acc_number.load("app/native/assets/menu/acc_number.png");
	m_menu_acc_number.setPosition(m_menu_bg.PosX(), m_screenHeight - m_menu_acc_number.Height() -50.0f);
	m_menu_tc_bg.load("app/native/assets/menu/menu_tc_bg.png");
	m_menu_tc_bg.setPosition(m_menu_bg.PosX(), m_menu_acc_number.PosY() - m_menu_tc_bg.Height());
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
	m_menu_tc_broker_summary.load("app/native/assets/menu/tc_broker_summary.png");
	m_menu_tc_non_regular.load("app/native/assets/menu/tc_non_regular.png");
	// button menu trade central
	m_menu_btn_trade_central.regular = &m_menu_trade_central;
	m_menu_btn_trade_central.pressed = &m_menu_trade_central;
	m_menu_btn_trade_central.sizeX	= m_menu_trade_central.Width();
	m_menu_btn_trade_central.sizeY	= m_menu_trade_central.Height();
	m_menu_btn_trade_central.font	= m_font;
	m_menu_btn_trade_central.text	= "";
	m_menu_btn_trade_central.isPressed	= false;
	m_menu_btn_trade_central.isEnabled = true;
	m_menu_btn_trade_central.setPosition( m_menu_bg.PosX(), m_menu_acc_number.PosY() - m_menu_trade_central.Height() );
	// button menu charts
	m_menu_btn_charts.regular = &m_menu_charts;
	m_menu_btn_charts.pressed = &m_menu_charts;
	m_menu_btn_charts.sizeX	= m_menu_charts.Width();
	m_menu_btn_charts.sizeY	= m_menu_charts.Height();
	m_menu_btn_charts.font	= m_font;
	m_menu_btn_charts.text	= "";
	m_menu_btn_charts.isPressed	= false;
	m_menu_btn_charts.isEnabled = true;
	m_menu_btn_charts.setPosition( m_menu_bg.PosX(), m_menu_trade_central.PosY() - m_menu_charts.Height() );
	// button menu information
	m_menu_btn_informations.regular = &m_menu_informations;
	m_menu_btn_informations.pressed = &m_menu_informations;
	m_menu_btn_informations.sizeX	= m_menu_informations.Width();
	m_menu_btn_informations.sizeY	= m_menu_informations.Height();
	m_menu_btn_informations.font	= m_font;
	m_menu_btn_informations.text	= "";
	m_menu_btn_informations.isPressed	= false;
	m_menu_btn_informations.isEnabled = true;
	m_menu_btn_informations.setPosition( m_menu_bg.PosX(), m_menu_btn_charts.posY - m_menu_informations.Height() );
	// button menu portfolio
	m_menu_btn_portfolio.regular = &m_menu_portfolio;
	m_menu_btn_portfolio.pressed = &m_menu_portfolio;
	m_menu_btn_portfolio.sizeX	= m_menu_portfolio.Width();
	m_menu_btn_portfolio.sizeY	= m_menu_portfolio.Height();
	m_menu_btn_portfolio.font	= m_font;
	m_menu_btn_portfolio.text	= "";
	m_menu_btn_portfolio.isPressed	= false;
	m_menu_btn_portfolio.isEnabled = true;
	m_menu_btn_portfolio.setPosition( m_menu_bg.PosX(), m_menu_btn_informations.posY - m_menu_portfolio.Height() );
	// button menu charts
	m_menu_btn_order_trade.regular = &m_menu_order_trade;
	m_menu_btn_order_trade.pressed = &m_menu_order_trade;
	m_menu_btn_order_trade.sizeX	= m_menu_order_trade.Width();
	m_menu_btn_order_trade.sizeY	= m_menu_order_trade.Height();
	m_menu_btn_order_trade.font	= m_font;
	m_menu_btn_order_trade.text	= "";
	m_menu_btn_order_trade.isPressed	= false;
	m_menu_btn_order_trade.isEnabled = true;
	m_menu_btn_order_trade.setPosition( m_menu_bg.PosX(), m_menu_btn_portfolio.posY - m_menu_order_trade.Height() );
	// button menu my account
	m_menu_btn_my_account.regular = &m_menu_my_account;
	m_menu_btn_my_account.pressed = &m_menu_my_account;
	m_menu_btn_my_account.sizeX	= m_menu_my_account.Width();
	m_menu_btn_my_account.sizeY	= m_menu_my_account.Height();
	m_menu_btn_my_account.font	= m_font;
	m_menu_btn_my_account.text	= "";
	m_menu_btn_my_account.isPressed	= false;
	m_menu_btn_my_account.isEnabled = true;
	m_menu_btn_my_account.setPosition( m_menu_bg.PosX(), m_menu_btn_order_trade.posY - m_menu_my_account.Height() );
	// button menu logout
	m_menu_btn_logout.regular = &m_menu_logout;
	m_menu_btn_logout.pressed = &m_menu_logout;
	m_menu_btn_logout.sizeX	= m_menu_logout.Width();
	m_menu_btn_logout.sizeY	= m_menu_logout.Height();
	m_menu_btn_logout.font	= m_font;
	m_menu_btn_logout.text	= "";
	m_menu_btn_logout.isPressed	= false;
	m_menu_btn_logout.isEnabled = true;
	m_menu_btn_logout.setPosition( m_menu_bg.PosX(), m_menu_btn_my_account.posY - m_menu_logout.Height() );

	m_menu_tc_btn_running_trade.regular = &m_menu_tc_running_trade;
	m_menu_tc_btn_running_trade.pressed = &m_menu_tc_running_trade;
	m_menu_tc_btn_running_trade.sizeX	= m_menu_tc_running_trade.Width();
	m_menu_tc_btn_running_trade.sizeY	= m_menu_tc_running_trade.Height();
	m_menu_tc_btn_running_trade.font	= m_font;
	m_menu_tc_btn_running_trade.text	= "";
	m_menu_tc_btn_running_trade.isPressed	= false;
	m_menu_tc_btn_running_trade.isEnabled = true;
	m_menu_tc_btn_running_trade.setPosition( m_menu_bg.PosX(), m_menu_btn_trade_central.posY - m_menu_tc_running_trade.Height() );

	m_menu_tc_btn_stock_watch.regular = &m_menu_tc_stock_watch;
	m_menu_tc_btn_stock_watch.pressed = &m_menu_tc_stock_watch;
	m_menu_tc_btn_stock_watch.sizeX	= m_menu_tc_stock_watch.Width();
	m_menu_tc_btn_stock_watch.sizeY	= m_menu_tc_stock_watch.Height();
	m_menu_tc_btn_stock_watch.font	= m_font;
	m_menu_tc_btn_stock_watch.text	= "";
	m_menu_tc_btn_stock_watch.isPressed	= false;
	m_menu_tc_btn_stock_watch.isEnabled = true;
	m_menu_tc_btn_stock_watch.setPosition( m_menu_bg.PosX(), m_menu_tc_btn_running_trade.posY - m_menu_tc_stock_watch.Height() );

	m_menu_tc_btn_complete_book.regular = &m_menu_tc_complete_book;
	m_menu_tc_btn_complete_book.pressed = &m_menu_tc_complete_book;
	m_menu_tc_btn_complete_book.sizeX	= m_menu_tc_complete_book.Width();
	m_menu_tc_btn_complete_book.sizeY	= m_menu_tc_complete_book.Height();
	m_menu_tc_btn_complete_book.font	= m_font;
	m_menu_tc_btn_complete_book.text	= "";
	m_menu_tc_btn_complete_book.isPressed	= false;
	m_menu_tc_btn_complete_book.isEnabled = true;
	m_menu_tc_btn_complete_book.setPosition( m_menu_bg.PosX(), m_menu_tc_btn_stock_watch.posY - m_menu_tc_complete_book.Height() );

	m_menu_tc_btn_stock_quote.regular = &m_menu_tc_stock_quote;
	m_menu_tc_btn_stock_quote.pressed = &m_menu_tc_stock_quote;
	m_menu_tc_btn_stock_quote.sizeX	= m_menu_tc_stock_quote.Width();
	m_menu_tc_btn_stock_quote.sizeY	= m_menu_tc_stock_quote.Height();
	m_menu_tc_btn_stock_quote.font	= m_font;
	m_menu_tc_btn_stock_quote.text	= "";
	m_menu_tc_btn_stock_quote.isPressed	= false;
	m_menu_tc_btn_stock_quote.isEnabled = true;
	m_menu_tc_btn_stock_quote.setPosition( m_menu_bg.PosX(), m_menu_tc_btn_complete_book.posY - m_menu_tc_stock_quote.Height() );

	m_menu_tc_btn_broker_quote.regular = &m_menu_tc_broker_quote;
	m_menu_tc_btn_broker_quote.pressed = &m_menu_tc_broker_quote;
	m_menu_tc_btn_broker_quote.sizeX	= m_menu_tc_broker_quote.Width();
	m_menu_tc_btn_broker_quote.sizeY	= m_menu_tc_broker_quote.Height();
	m_menu_tc_btn_broker_quote.font	= m_font;
	m_menu_tc_btn_broker_quote.text	= "";
	m_menu_tc_btn_broker_quote.isPressed	= false;
	m_menu_tc_btn_broker_quote.isEnabled = true;
	m_menu_tc_btn_broker_quote.setPosition( m_menu_bg.PosX(), m_menu_tc_btn_stock_quote.posY - m_menu_tc_broker_quote.Height() );

	m_menu_tc_btn_stock_summary.regular = &m_menu_tc_stock_summary;
	m_menu_tc_btn_stock_summary.pressed = &m_menu_tc_stock_summary;
	m_menu_tc_btn_stock_summary.sizeX	= m_menu_tc_stock_summary.Width();
	m_menu_tc_btn_stock_summary.sizeY	= m_menu_tc_stock_summary.Height();
	m_menu_tc_btn_stock_summary.font	= m_font;
	m_menu_tc_btn_stock_summary.text	= "";
	m_menu_tc_btn_stock_summary.isPressed	= false;
	m_menu_tc_btn_stock_summary.isEnabled = true;
	m_menu_tc_btn_stock_summary.setPosition( m_menu_bg.PosX(), m_menu_tc_btn_broker_quote.posY - m_menu_tc_stock_summary.Height() );

	m_menu_tc_btn_broker_summary.regular = &m_menu_tc_broker_summary;
	m_menu_tc_btn_broker_summary.pressed = &m_menu_tc_broker_summary;
	m_menu_tc_btn_broker_summary.sizeX	= m_menu_tc_broker_summary.Width();
	m_menu_tc_btn_broker_summary.sizeY	= m_menu_tc_broker_summary.Height();
	m_menu_tc_btn_broker_summary.font	= m_font;
	m_menu_tc_btn_broker_summary.text	= "";
	m_menu_tc_btn_broker_summary.isPressed	= false;
	m_menu_tc_btn_broker_summary.isEnabled = true;
	m_menu_tc_btn_broker_summary.setPosition( m_menu_bg.PosX(), m_menu_tc_btn_stock_summary.posY - m_menu_tc_broker_summary.Height() );

	m_menu_tc_btn_non_regular.regular = &m_menu_tc_non_regular;
	m_menu_tc_btn_non_regular.pressed = &m_menu_tc_non_regular;
	m_menu_tc_btn_non_regular.sizeX	= m_menu_tc_non_regular.Width();
	m_menu_tc_btn_non_regular.sizeY	= m_menu_tc_non_regular.Height();
	m_menu_tc_btn_non_regular.font	= m_font;
	m_menu_tc_btn_non_regular.text	= "";
	m_menu_tc_btn_non_regular.isPressed	= false;
	m_menu_tc_btn_non_regular.isEnabled = true;
	m_menu_tc_btn_non_regular.setPosition( m_menu_bg.PosX(), m_menu_tc_btn_broker_summary.posY - m_menu_tc_non_regular.Height() );

	// password
	m_pw_caption.load("app/native/assets/password/pw_caption.png");
	m_pw_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_pw_text_bg.load("app/native/assets/password/pw_text_bg.png");
	m_pw_save.load("app/native/assets/password/btn_save.png");
	m_pw_btn_save.regular = &m_pw_save;
	m_pw_btn_save.pressed = &m_pw_save;
	m_pw_btn_save.sizeX	= m_pw_save.Width();
	m_pw_btn_save.sizeY	= m_pw_save.Height();
	m_pw_btn_save.font	= m_font;
	m_pw_btn_save.text	= "";
	m_pw_btn_save.isPressed	= false;
	m_pw_btn_save.isEnabled = true;
	m_pw_btn_save.setPosition( 0.0f, 0.0f );

	// portofolio
	m_pf_caption.load("app/native/assets/portofolio/pf_caption.png");
	m_pf_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_pf_table_title.load("app/native/assets/portofolio/pf_table_title.png");
	m_pf_table_title.setPosition(0.0f, m_screenHeight - 262.0f);
	m_pf_acc_number.load("app/native/assets/portofolio/acc_no.png");
	m_pf_acc_number.setPosition(0.0f, m_screenHeight - 262.0f);

	// research
	m_research_caption.load("app/native/assets/research/research_caption.png");
	m_research_caption.setPosition(27.0f, m_screenHeight - 200.0f);

	m_state = HOME;
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

	fprintf(stderr, "Finish instantiate panin.\n");
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
        	updateHome();
            renderHome();
            break;

        case LOADING:
        	fprintf(stderr, "eka at loading.");
            //update();
            //renderGame();
            break;

        case RUNNING_TRADE:
        	update();
        	renderRunningTrade();
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

        case PORTFOLIO:
        	update();
        	renderPortfolio();
        	break;

        case ORDER_TRADE:
        	update();
        	renderOrderTrade();
        	break;


        default:
        	fprintf(stderr, "eka at default.");
            break;
        }
    }
}

void panin::update()
{
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

void panin::updateHome()
{
	//get suitable value.
	if (m_u_name.length() == 0)	m_u_name = "username";
	if (m_u_pass.length() == 0) m_u_pass = "password";

	m_sIhsg_val = "7000";
	m_sIhsg_volume = "3415.10 bn";
	m_sIhsg_percent = "17.77 (30%)";

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

	if (m_bShowMenu)
		m_bShowMenu = false;

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
    float text_width, text_height, pos_x, pos_y;
    bbutil_measure_text(m_font_global, m_u_name.c_str(), &text_width, &text_height);
    pos_x = 390.0f;
	pos_y = m_screenHeight -620.0f;
	bbutil_render_text(m_font_global, m_u_name.c_str(), pos_x, pos_y, 0.05f, 0.05f, 0.05f, 1.0f);

	bbutil_measure_text(m_font_global, m_u_pass.c_str(), &text_width, &text_height);
	pos_x = 390;
	pos_y = m_screenHeight -677;
	bbutil_render_text(m_font_global, m_u_pass.c_str(), pos_x, pos_y, 0.05f, 0.05f, 0.05f, 1.0f);

	bbutil_measure_text(m_font_ihsg_val, m_sIhsg_val.c_str(), &text_width, &text_height);
	pos_x = (m_screenWidth - text_width) /2;
	pos_y = m_screenHeight -990;
	bbutil_render_text(m_font_ihsg_val, m_sIhsg_val.c_str(), pos_x, pos_y, 0.05f, 1.0f, 0.05f, 1.0f);

	float p1;
	bbutil_measure_text(m_font_ihsg_vol, m_sIhsg_volume.c_str(), &text_width, &text_height);
	p1 = text_width;
	pos_x = (m_screenWidth - text_width) /2;
	pos_y = m_screenHeight -1050;
	bbutil_render_text(m_font_ihsg_vol, m_sIhsg_volume.c_str(), pos_x, pos_y, 0.95f, 0.95f, 0.95f, 1.0f);

	const char*  waktu = m_platform.getDateTime();
	bbutil_measure_text(m_font_tanggal, waktu, &text_width, &text_height);
	pos_x = (m_screenWidth - text_width) /2;
	pos_y = m_screenHeight -1125;
	//bbutil_render_text(m_font_tanggal, "30 September 2013 23:59:59", pos_x, pos_y, 0.92f, 0.73f, 0.33f, 1.0f);
	bbutil_render_text(m_font_tanggal, waktu, pos_x, pos_y, 0.92f, 0.73f, 0.33f, 1.0f);

	bbutil_render_text(m_font_tanggal, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);


	if (m_bShowHomeSetel)
	{
		//fprintf(stderr, "render HomeSetel.\n");
		renderHomeSetel();

	}

	m_platform.finishRender();
}

void panin::renderHomeSetel()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_dialog_bg.draw();
	m_textfield_bg.setPosition(80.0f, m_screenHeight - 686.0f);
	m_textfield_bg.draw();
	m_textfield_bg.setPosition(80.0f, m_screenHeight - 784.0f);
	m_textfield_bg.draw();
	m_btn_setel_default.draw();
	m_btn_setel_set107.draw();
	m_btn_setel_set202.draw();
	m_btn_setel_save.draw();
	m_btn_setel_x.draw();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    bbutil_render_text(m_font, "SERVER A", 80.0f, m_screenHeight - 644.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    bbutil_render_text(m_font, "SERVER B", 80.0f, m_screenHeight - 744.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    //bbutil_render_text(m_font, "172.31.2.78:8080", 120.0f, m_screenHeight - 682.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    //bbutil_render_text(m_font, "172.31.2.78:8443", 120.0f, m_screenHeight - 780.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    bbutil_render_text(m_font, m_platform.server1.c_str(), 120.0f, m_screenHeight - 682.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    bbutil_render_text(m_font, m_platform.server2.c_str(), 120.0f, m_screenHeight - 780.0f, 1.0f, 1.0f, 1.0f, 1.0f);

}

void panin::renderHomeInfo()
{

}

void panin::renderMenu()
{
	m_menu_bg.draw();
	m_menu_btn_trade_central.draw();
	float p1 = m_menu_btn_trade_central.posY;
	if (m_bShowSubmenuTC)
	{
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


	m_menu_btn_charts.setPosition(m_menu_btn_charts.posX, p1 - m_menu_btn_charts.sizeY);
	m_menu_btn_charts.draw();
	m_menu_btn_informations.setPosition(m_menu_btn_informations.posX, m_menu_btn_charts.posY - m_menu_btn_informations.sizeY);
	m_menu_btn_informations.draw();
	m_menu_btn_portfolio.setPosition(m_menu_btn_portfolio.posX, m_menu_btn_informations.posY - m_menu_btn_portfolio.sizeY);
	m_menu_btn_portfolio.draw();
	m_menu_btn_order_trade.setPosition(m_menu_btn_order_trade.posX, m_menu_btn_portfolio.posY - m_menu_btn_order_trade.sizeY);
	m_menu_btn_order_trade.draw();
	m_menu_btn_my_account.setPosition(m_menu_btn_my_account.posX, m_menu_btn_order_trade.posY - m_menu_btn_my_account.sizeY);
	m_menu_btn_my_account.draw();
	m_menu_btn_logout.setPosition(m_menu_btn_logout.posX, m_menu_btn_my_account.posY - m_menu_btn_logout.sizeY);
	m_menu_btn_logout.draw();

}

void panin::renderRunningTrade()
{
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

	do
	{
		bbutil_render_text(m_font9, "11:11:11", 10.0f, myY, 1.0f, 0.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font9, "B", 135.0f, myY, 1.0f, 0.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font9, "KAEF", 195.0f, myY, 1.0f, 0.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font9, "RG", 285.0f, myY, 1.0f, 1.0f, 1.0f, 1.0f);
		bbutil_render_text(m_font9, "990", 355.0f, myY, 1.0f, 1.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font9, "990", 420.0f, myY, 1.0f, 1.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font9, "0", 485.0f, myY, 1.0f, 1.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font9, "RG", 550.0f, myY, 1.0f, 1.0f, 0.0f, 1.0f);
		bbutil_render_text(m_font9, "RG", 625.0f, myY, 1.0f, 1.0f, 1.0f, 1.0f);
		bbutil_render_text(m_font9, "RG", 705.0f, myY, 1.0f, 1.0f, 1.0f, 1.0f);
		myY -= 30.0f;
	}
	while (myY > 100.0f);


	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	addFooter();

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation)
	{
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	if (m_bShowBuy)
	{
		renderBuyDialog();
	}

	if (m_bShowSell)
	{
		renderSellDialog();
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	m_platform.finishRender();

}

void panin::renderStockWatch()
{
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

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			float mX = j * m_sw_box_black.Width() + 10.0f;
			float mY = m_sw_port1.PosY() - i * m_sw_box_black.Height() - 200.0f;
			m_sw_box_black.setPosition(mX, mY);
			m_sw_box_black.draw();
			mX = m_sw_box_black.PosX() + 10.0f;
			mY = m_sw_box_black.PosY() + 36.0f;
			if (j == 0)
			{
				m_sw_val_green.setPosition(mX, mY);
				m_sw_val_green.draw();
			}
			else if (j == 1)
			{
				m_sw_val_yellow.setPosition(mX, mY);
				m_sw_val_yellow.draw();
			}
			else if (j == 2)
			{
				m_sw_val_red.setPosition(mX, mY);
				m_sw_val_red.draw();
			}

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);

			float text_width, text_height, pos_x, pos_y;

			bbutil_measure_text(m_font20, "PANS", &text_width, &text_height);
			pos_x = m_sw_box_black.PosX() + (m_sw_box_black.Width() - text_width)/2;
			pos_y = m_sw_box_black.PosY() + m_sw_box_black.Height() - text_height - 4.0f;
			bbutil_render_text(m_font20, "PANS", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

			bbutil_measure_text(m_font10, "Panin Securitas Tbk", &text_width, &text_height);
			pos_x = m_sw_box_black.PosX() + (m_sw_box_black.Width() - text_width)/2;
			pos_y = m_sw_box_black.PosY() + m_sw_box_black.Height() - text_height - 44.0f;
			bbutil_render_text(m_font10, "Panin Securitas Tbk", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

			bbutil_measure_text(m_font11, "9.0 %", &text_width, &text_height);
			pos_x = m_sw_box_black.PosX() + 10.0f;
			pos_y = m_sw_box_black.PosY() + m_sw_box_black.Height() - text_height - 130.0f;
			bbutil_render_text(m_font11, "9.0 %", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

			bbutil_measure_text(m_font11, "-100", &text_width, &text_height);
			pos_x = m_sw_box_black.PosX() + (m_sw_box_black.Width() - text_width - 20.0f);
			pos_y = m_sw_box_black.PosY() + m_sw_box_black.Height() - text_height - 130.0f;
			bbutil_render_text(m_font11, "-100", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

			bbutil_render_text(m_font9, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

			glEnable(GL_TEXTURE_2D);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}


	m_sw_port1.draw();
	m_sw_banking.draw();
	m_sw_mining.draw();
	m_sw_cons.draw();
	m_sw_plus_green.draw();
	m_sw_val_green.draw();
	m_sw_val_yellow.draw();
	m_sw_val_red.draw();

	addFooter();

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation)
	{
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderCompleteBook()
{
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

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	bbutil_render_text(m_font9, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font9, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	addFooter();

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation)
	{
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderStockQuote()
{
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

	addFooter();

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation)
	{
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderBrokerQuote()
{
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

	addFooter();

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation)
	{
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderStockSummary()
{
	m_platform.beginRender();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_latar.draw();

	addHeader();

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation)
	{
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	m_ss_caption.draw();
	m_ss_table_title.draw();

	addFooter();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}


void panin::renderBrokerSummary()
{
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

	if (m_bShowMenu || m_bMenuShowAnimation || m_bMenuHideAnimation)
	{
		//glTranslatef(m_ePosX, m_ePosY, 0.0f);
		renderMenu();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
}

void panin::renderNonRegular()
{

}

void panin::renderCharts()
{

}

void panin::renderInformations()
{

}

void panin::renderPortfolio()
{

}

void panin::renderOrderTrade()
{

}

void panin::addHeader()
{
	m_header_bar_bg.draw();
	m_header_post.draw();
	m_btn_info.draw();
	m_btn_menu.draw();

}

void panin::addFooter()
{
	m_ihsg2.draw();
	m_btn_sell.draw();
	m_btn_buy.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	float text_width, text_height, pos_x, pos_y;
	bbutil_measure_text(m_font_ihsg_val, m_sIhsg_val.c_str(), &text_width, &text_height);
	pos_x = (m_ihsg2.PosX() + 20.0f);
	pos_y = m_ihsg2.PosY() + text_height/2 - 10.0f;
	bbutil_render_text(m_font28, m_sIhsg_val.c_str(), pos_x, pos_y, 0.05f, 1.0f, 0.05f, 1.0f);

	bbutil_measure_text(m_font14, m_sIhsg_volume.c_str(), &text_width, &text_height);
	pos_x = (m_ihsg2.PosX() + m_ihsg2.Width() - text_width - 30.0f);
	pos_y = m_ihsg2.PosY() + 2*text_height + 0.0f;
	bbutil_render_text(m_font14, m_sIhsg_volume.c_str(), pos_x, pos_y, 0.05f, 1.0f, 0.05f, 1.0f);

	//bbutil_measure_text(m_font14, m_sIhsg_percent.c_str(), &text_width, &text_height);
	//pos_x = (m_ihsg2.PosX() + m_ihsg2.Width() - text_width - 20.0f);
	pos_y = m_ihsg2.PosY() + 14.0f;
	bbutil_render_text(m_font14, m_sIhsg_percent.c_str(), pos_x, pos_y, 0.05f, 1.0f, 0.05f, 1.0f);

	bbutil_render_text(m_font14, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void panin::renderBuyDialog()
{
	m_buy_bg.draw();
	m_buy_caption.draw();
	m_buy_band.draw();
	m_btn_buy_refresh.draw();
	m_btn_buy_execute.draw();
	m_btn_buy_x.draw();

	m_buysell_textfield_bg.setPosition(440.0f, m_screenHeight - 464.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(440.0f, m_screenHeight - 512.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(440.0f, m_screenHeight - 560.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(440.0f, m_screenHeight - 608.0f);
	m_buysell_textfield_bg.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	bbutil_render_text(m_font14, "ACCOUNT ID", 183.0f, m_screenHeight -465.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "STOCK TRADE", 183.0f, m_screenHeight -512.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "PRICE", 183.0f, m_screenHeight -560.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "VOLUME", 183.0f, m_screenHeight -609.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, "Max Buy", 183.0f, m_screenHeight -675.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Stock Value", 183.0f, m_screenHeight -718.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Trans Fee", 183.0f, m_screenHeight -760.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Payable", 183.0f, m_screenHeight -800.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, m_sMaxBuy.c_str(), 400.0f, m_screenHeight -675.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sStockValue.c_str(), 400.0f, m_screenHeight -718.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sTransFee.c_str(), 400.0f, m_screenHeight -760.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sPayable.c_str(), 400.0f, m_screenHeight -800.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void panin::renderSellDialog()
{
	m_sell_bg.draw();
	m_sell_caption.draw();
	m_sell_band.draw();
	m_btn_sell_refresh.draw();
	m_btn_sell_execute.draw();
	m_btn_sell_x.draw();

	m_buysell_textfield_bg.setPosition(440.0f, m_screenHeight - 464.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(440.0f, m_screenHeight - 512.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(440.0f, m_screenHeight - 560.0f);
	m_buysell_textfield_bg.draw();
	m_buysell_textfield_bg.setPosition(440.0f, m_screenHeight - 608.0f);
	m_buysell_textfield_bg.draw();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	bbutil_render_text(m_font14, "ACCOUNT ID", 183.0f, m_screenHeight -465.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "STOCK TRADE", 183.0f, m_screenHeight -512.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "PRICE", 183.0f, m_screenHeight -560.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "VOLUME", 183.0f, m_screenHeight -609.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, "Max Buy", 183.0f, m_screenHeight -675.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Stock Value", 183.0f, m_screenHeight -718.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Trans Fee", 183.0f, m_screenHeight -760.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, "Payable", 183.0f, m_screenHeight -800.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, m_sMaxBuy.c_str(), 400.0f, m_screenHeight -675.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sStockValue.c_str(), 400.0f, m_screenHeight -718.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sTransFee.c_str(), 400.0f, m_screenHeight -760.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	bbutil_render_text(m_font14, m_sPayable.c_str(), 400.0f, m_screenHeight -800.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	bbutil_render_text(m_font14, "", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void panin::onLeftRelease(float x, float y)
{
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

				periksaLogin();
				//m_state = RUNNING_TRADE;
				return;
			}
		}

		if (m_btn_home_info.isEnabled)
		{
			if (m_btn_home_info.isWithin(pX, pY))
				{
				fprintf(stderr, "button home info is released.\n");
				m_btn_home_info.isPressed = false;
				m_bShowHomeInfo = true;
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
	}
	else
	{
		if (m_btn_menu.isEnabled)
		{
			if (m_btn_menu.isWithin(pX, pY))
			{
				fprintf(stderr, "button menu is released.\n");
				m_bShowMenu = !m_bShowMenu;
				if (m_bShowMenu)
				{
					fprintf(stderr, "Show Menu.\n");
					//m_bMenuShowAnimation = true;
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

		if (m_btn_buy.isEnabled)
		{
			if (m_btn_buy.isWithin(pX, pY))
			{
				fprintf(stderr, "button buy is released.\n");
				m_bShowBuy = true;
				m_btn_buy.isEnabled = false;
				m_btn_sell.isEnabled = false;
				return;
			}
		}

		if (m_btn_sell.isEnabled)
		{
			if (m_btn_sell.isWithin(pX, pY))
			{
				fprintf(stderr, "button sell is released.\n");
				m_bShowSell = true;
				m_btn_buy.isEnabled = false;
				m_btn_sell.isEnabled = false;
				return;
			}
		}

		if (m_bShowSell)
		{
			if (m_btn_sell_execute.isWithin(pX, pY))
			{
				fprintf(stderr, "button sell execute is released.\n");
				return;
			}
			if (m_btn_sell_refresh.isWithin(pX, pY))
			{
				fprintf(stderr, "button sell refresh is released.\n");
				return;
			}
			if (m_btn_sell_x.isWithin(pX, pY))
			{
				fprintf(stderr, "button sell x is released.\n");
				m_bShowSell = false;
				m_btn_sell.isEnabled = true;
				m_btn_buy.isEnabled = true;
				return;
			}
		}

		if (m_bShowBuy)
		{
			if (m_btn_buy_execute.isWithin(pX, pY))
			{
				fprintf(stderr, "button buy execute is released.\n");
				return;
			}
			if (m_btn_buy_refresh.isWithin(pX, pY))
			{
				fprintf(stderr, "button buy refresh is released.\n");
				return;
			}
			if (m_btn_buy_x.isWithin(pX, pY))
			{
				fprintf(stderr, "button buy x is released.\n");
				m_bShowBuy = false;
				m_btn_sell.isEnabled = true;
				m_btn_buy.isEnabled = true;
				return;
			}
		}

		// menu item di klik
		if (m_bMenuActive)
		{
			if (m_menu_btn_trade_central.isWithin(pX, pY))
			{
				m_bShowSubmenuTC = !m_bShowSubmenuTC;
				//m_bShowMenu = false;
				//m_bMenuActive = false;
				//m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_btn_charts.isWithin(pX, pY))
			{
				m_state = CHARTS;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_btn_informations.isWithin(pX, pY))
			{
				m_state = INFORMATIONS;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_btn_portfolio.isWithin(pX, pY))
			{
				m_state = PORTFOLIO;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_btn_order_trade.isWithin(pX, pY))
			{
				m_state = ORDER_TRADE;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}

			if (m_menu_tc_btn_running_trade.isWithin(pX, pY))
			{
				m_state = RUNNING_TRADE;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_tc_btn_stock_watch.isWithin(pX, pY))
			{
				m_state = STOCK_WATCH;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_tc_btn_complete_book.isWithin(pX, pY))
			{
				m_state = COMPLETE_BOOK;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_tc_btn_stock_quote.isWithin(pX, pY))
			{
				m_state = STOCK_QUOTE;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_tc_btn_broker_quote.isWithin(pX, pY))
			{
				m_state = BROKER_QUOTE;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_tc_btn_stock_summary.isWithin(pX, pY))
			{
				m_state = STOCK_SUMMARY;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_tc_btn_broker_summary.isWithin(pX, pY))
			{
				m_state = BROKER_SUMMARY;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
			if (m_menu_tc_btn_non_regular.isWithin(pX, pY))
			{
				m_state = NON_REGULAR;
				m_bShowMenu = false;
				m_bMenuActive = false;
				m_bMenuHideAnimation = true;
				return;
			}
		}

		switch (m_state)
		{
		case RUNNING_TRADE:
		case STOCK_WATCH:
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
		}
	}


}

void panin::onLeftPress(float x, float y)
{
	fprintf(stderr, "onLeftPress.\n");
	if (m_state == HOME)
		{
		if (m_btn_login.isEnabled)
		{
			if (m_btn_login.isWithin(x, m_screenHeight - y))
			{
				m_btn_login.isPressed = true;
				fprintf(stderr, "Button login di tekan.\n");
			}
		}
		if (m_btn_home_setel.isEnabled)
		{
			if (m_btn_home_setel.isWithin(x, m_screenHeight -y))
			{
				m_btn_home_setel.isPressed = true;
				fprintf(stderr, "Button setel ditekan.\n");
			}
		}
	}
}

void panin::onKeyPressed(char c)
{
	fprintf(stderr, "The '%c' key was pressed\n", c);
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

    bbutil_render_text(font, text, posX + textX, posY + textY, 1.0f, 1.0f, 1.0f, 1.0f);

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

void panin::setConfiguration(eConfiguration conf)
{
	switch (conf)
	{
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

void panin::periksaLogin()
{
	std::string hasil;

	fprintf(stderr, "sebelum curl.\n");
	//const char * url = "http://202.53.249.2:8080/mi2/marketInfoData?request=login&user=parto&password=123456";
	char * url = new char[1024];
	std::strcpy(url, "http://202.53.249.2:8080/mi2/marketInfoData?request=login&user=");
	std::strcat(url, m_u_name.c_str());
	std::strcat(url, "&password=");
	std::strcat(url, m_u_pass.c_str());
	//url << "http://202.53.249.2:8080/mi2/marketInfoData?request=login&user=" << m_u_name.c_str() << "&password=" << m_u_pass.c_str();
	if (CURLE_OK == m_platform.m_serverConnection->doHttpGet(url, oss, 30.0f))
	{
		std::string hasil = oss.str();
		fprintf(stderr, "hasil : %s", hasil.c_str());
		if (hasil == "true")
		{
			m_btn_login.isEnabled = false;
			m_btn_home_info.isEnabled = false;
			m_btn_home_setel.isEnabled = false;
			m_btn_setel_default.isEnabled = false;
			m_btn_setel_set202.isEnabled = false;
			m_btn_setel_set107.isEnabled = false;
			m_btn_setel_save.isEnabled = false;
			m_btn_setel_x.isEnabled = false;

			m_state = RUNNING_TRADE;
		}
		else
		{
			m_u_name = "username salah";

			// by pass
			m_btn_login.isEnabled = false;
			m_btn_home_info.isEnabled = false;
			m_btn_home_setel.isEnabled = false;
			m_btn_setel_default.isEnabled = false;
			m_btn_setel_set202.isEnabled = false;
			m_btn_setel_set107.isEnabled = false;
			m_btn_setel_save.isEnabled = false;
			m_btn_setel_x.isEnabled = false;

			m_state = RUNNING_TRADE;
		}
	}
	else
	{
		fprintf(stderr, "curl tidak ok.\n");
	}

	delete url;
}

} /* namespace paninMobile */
