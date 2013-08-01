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

	point_size = (int)(20.0f / ((float)dpi / 170.0f ));
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
	m_btn_info.isPressed	= false;
	m_btn_info.setPosition( 680.0f, (m_screenHeight - 128.0) );
	m_btn_menu.regular = &m_btn_menu_bg;
	m_btn_menu.pressed = &m_btn_menu_bg;
	m_btn_menu.sizeX	= m_btn_menu_bg.Width();
	m_btn_menu.sizeY	= m_btn_menu_bg.Height();
	m_btn_menu.font	= m_font;
	m_btn_menu.text	= "";
	m_btn_menu.isPressed	= false;
	m_btn_menu.setPosition( 25.0f, (m_screenHeight - 128.0) );
	m_btn_buy.regular = &m_btn_buy_bg;
	m_btn_buy.pressed = &m_btn_buy_bg;
	m_btn_buy.sizeX	= m_btn_buy_bg.Width();
	m_btn_buy.sizeY	= m_btn_buy_bg.Height();
	m_btn_buy.font	= m_font;
	m_btn_buy.text	= "";
	m_btn_buy.isPressed	= false;
	m_btn_buy.setPosition(622.0f, (m_screenHeight - 1254.0f));
	m_btn_sell.regular = &m_btn_sell_bg;
	m_btn_sell.pressed = &m_btn_sell_bg;
	m_btn_sell.sizeX	= m_btn_sell_bg.Width();
	m_btn_sell.sizeY	= m_btn_sell_bg.Height();
	m_btn_sell.font	= m_font;
	m_btn_sell.text	= "";
	m_btn_sell.isPressed	= false;
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
	m_buy_band.setPosition(57.0f, m_screenHeight - 922.0f);
	m_buy_x.load("app/native/assets/umum/buy_x.png");
	m_btn_buy_refresh.regular = &m_buy_refresh;
	m_btn_buy_refresh.pressed = &m_buy_refresh;
	m_btn_buy_refresh.sizeX	= m_buy_refresh.Width();
	m_btn_buy_refresh.sizeY	= m_buy_refresh.Height();
	m_btn_buy_refresh.font	= m_font;
	m_btn_buy_refresh.text	= "";
	m_btn_buy_refresh.isPressed	= false;
	m_btn_buy_refresh.setPosition( 173.0f, m_screenHeight - 908.0 );
	m_btn_buy_execute.regular = &m_buy_execute;
	m_btn_buy_execute.pressed = &m_buy_execute;
	m_btn_buy_execute.sizeX	= m_buy_execute.Width();
	m_btn_buy_execute.sizeY	= m_buy_execute.Height();
	m_btn_buy_execute.font	= m_font;
	m_btn_buy_execute.text	= "";
	m_btn_buy_execute.isPressed	= false;
	m_btn_buy_execute.setPosition( 450.0f, m_screenHeight - 908.0 );
	m_btn_buy_x.regular = &m_buy_x;
	m_btn_buy_x.pressed = &m_buy_x;
	m_btn_buy_x.sizeX	= m_buy_x.Width();
	m_btn_buy_x.sizeY	= m_buy_x.Height();
	m_btn_buy_x.font	= m_font;
	m_btn_buy_x.text	= "";
	m_btn_buy_x.isPressed	= false;
	m_btn_buy_x.setPosition( 662.0f, m_screenHeight - 416.0 );
	//sell
	m_sell_bg.load("app/native/assets/umum/sell_bg.png");
	m_sell_bg.setPosition(57.0f, m_screenHeight - 1020.0f);
	m_sell_caption.load("app/native/assets/umum/sell_caption.png");
	m_sell_caption.setPosition(75.0f, m_screenHeight - 416.0f);
	m_sell_refresh.load("app/native/assets/umum/sell_refresh.png");
	m_sell_execute.load("app/native/assets/umum/sell_execute.png");
	m_sell_band.load("app/native/assets/umum/white_bar.png");
	m_sell_band.setPosition(57.0f, m_screenHeight - 922.0f);
	m_sell_x.load("app/native/assets/umum/sell_x.png");
	m_btn_sell_refresh.regular = &m_sell_refresh;
	m_btn_sell_refresh.pressed = &m_sell_refresh;
	m_btn_sell_refresh.sizeX	= m_sell_refresh.Width();
	m_btn_sell_refresh.sizeY	= m_sell_refresh.Height();
	m_btn_sell_refresh.font	= m_font;
	m_btn_sell_refresh.text	= "";
	m_btn_sell_refresh.isPressed	= false;
	m_btn_sell_refresh.setPosition( 173.0f, m_screenHeight - 908.0 );
	m_btn_sell_execute.regular = &m_sell_execute;
	m_btn_sell_execute.pressed = &m_sell_execute;
	m_btn_sell_execute.sizeX	= m_sell_execute.Width();
	m_btn_sell_execute.sizeY	= m_sell_execute.Height();
	m_btn_sell_execute.font	= m_font;
	m_btn_sell_execute.text	= "";
	m_btn_sell_execute.isPressed	= false;
	m_btn_sell_execute.setPosition( 450.0f, m_screenHeight - 908.0 );
	m_btn_sell_x.regular = &m_sell_x;
	m_btn_sell_x.pressed = &m_sell_x;
	m_btn_sell_x.sizeX	= m_sell_x.Width();
	m_btn_sell_x.sizeY	= m_sell_x.Height();
	m_btn_sell_x.font	= m_font;
	m_btn_sell_x.text	= "";
	m_btn_sell_x.isPressed	= false;
	m_btn_sell_x.setPosition( 662.0f, m_screenHeight - 416.0 );

	m_dialog_bg.load("app/native/assets/umum/dialog_bg.png");
	m_dialog_bg.setPosition(0.0f, m_screenHeight - 780.0f);
	m_blue_rect.load("app/native/assets/umum/btn_blue.png");
	m_btn_conf_ok.regular = &m_blue_rect;
	m_btn_conf_ok.pressed = &m_blue_rect;
	m_btn_conf_ok.sizeX	= m_blue_rect.Width();
	m_btn_conf_ok.sizeY	= m_blue_rect.Height();
	m_btn_conf_ok.font	= m_font;
	m_btn_conf_ok.text	= "OK";
	m_btn_conf_ok.isPressed	= false;
	m_btn_conf_ok.setPosition( 435.0f, m_screenHeight - 713.0 );
	m_btn_conf_cancel.regular = &m_blue_rect;
	m_btn_conf_cancel.pressed = &m_blue_rect;
	m_btn_conf_cancel.sizeX	= m_blue_rect.Width();
	m_btn_conf_cancel.sizeY	= m_blue_rect.Height();
	m_btn_conf_cancel.font	= m_font;
	m_btn_conf_cancel.text	= "CANCEL";
	m_btn_conf_cancel.isPressed	= false;
	m_btn_conf_cancel.setPosition( 220.0f, m_screenHeight - 713.0 );
	m_btn_setel_default.regular = &m_blue_rect;
	m_btn_setel_default.pressed = &m_blue_rect;
	m_btn_setel_default.sizeX	= m_blue_rect.Width();
	m_btn_setel_default.sizeY	= m_blue_rect.Height();
	m_btn_setel_default.font	= m_font;
	m_btn_setel_default.text	= "DEFAULT";
	m_btn_setel_default.isPressed	= false;
	m_btn_setel_default.setPosition( 74.0f, m_screenHeight - 713.0 );
	m_btn_setel_set202.regular = &m_blue_rect;
	m_btn_setel_set202.pressed = &m_blue_rect;
	m_btn_setel_set202.sizeX	= m_blue_rect.Width();
	m_btn_setel_set202.sizeY	= m_blue_rect.Height();
	m_btn_setel_set202.font	= m_font;
	m_btn_setel_set202.text	= "DEFAULT";
	m_btn_setel_set202.isPressed	= false;
	m_btn_setel_set202.setPosition( 230.0f, m_screenHeight - 713.0 );
	m_btn_setel_set107.regular = &m_blue_rect;
	m_btn_setel_set107.pressed = &m_blue_rect;
	m_btn_setel_set107.sizeX	= m_blue_rect.Width();
	m_btn_setel_set107.sizeY	= m_blue_rect.Height();
	m_btn_setel_set107.font	= m_font;
	m_btn_setel_set107.text	= "DEFAULT";
	m_btn_setel_set107.isPressed	= false;
	m_btn_setel_set107.setPosition( 387.0f, m_screenHeight - 713.0 );
	m_btn_setel_save.regular = &m_blue_rect;
	m_btn_setel_save.pressed = &m_blue_rect;
	m_btn_setel_save.sizeX	= m_blue_rect.Width();
	m_btn_setel_save.sizeY	= m_blue_rect.Height();
	m_btn_setel_save.font	= m_font;
	m_btn_setel_save.text	= "DEFAULT";
	m_btn_setel_save.isPressed	= false;
	m_btn_setel_save.setPosition( 546.0f, m_screenHeight - 713.0 );

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
	m_btn_home_info.setPosition( m_screenWidth/2 - m_btn_home_info.sizeX -20.0f, (80.0f - m_btn_home_info.sizeY) );

	fprintf(stderr, "Load m_btn_home_setel.\n");
	m_btn_home_setel.regular = &m_home_setel_default;
	m_btn_home_setel.pressed = &m_home_setel_pressed;
	m_btn_home_setel.sizeX	= m_home_setel_default.Width();
	m_btn_home_setel.sizeY	= m_home_setel_default.Height();
	m_btn_home_setel.font	= m_font;
	m_btn_home_setel.text	= "";
	m_btn_home_setel.isPressed	= false;
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
	m_cb_top_band.load("app/native/assets/complete_book/completebook_caption.png");
	m_cb_top_band.setPosition(0.0f, m_screenHeight - 263.0f);
	m_cb_table_title1.load("app/native/assets/complete_book/completebook_caption.png");
	m_cb_table_title1.setPosition(27.0f, m_screenHeight - 452.0f);
	m_cb_table_title2.load("app/native/assets/complete_book/completebook_caption.png");
	m_cb_table_title2.setPosition(27.0f, m_screenHeight - 738.0f);

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
	fprintf(stderr, "Load broker summary.\n");
	m_menu_bg.load("app/native/assets/menu/menu_bg.png");
	m_menu_bg.setPosition(0.0f, m_screenHeight - m_menu_bg.Height());
	m_menu_acc_number.load("app/native/assets/menu/acc_number.png");
	m_menu_acc_number.setPosition(0.0f, m_screenHeight - m_menu_acc_number.Height());
	m_menu_tc_bg.load("app/native/assets/menu/menu_tc_bg.png");
	m_menu_tc_bg.setPosition(0.0f, m_menu_acc_number.PosY() - m_menu_tc_bg.Height());
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
	m_menu_btn_trade_central.setPosition( 0.0f, m_menu_acc_number.PosY() - m_menu_trade_central.Height() );
	// button menu charts
	m_menu_btn_charts.regular = &m_menu_charts;
	m_menu_btn_charts.pressed = &m_menu_charts;
	m_menu_btn_charts.sizeX	= m_menu_charts.Width();
	m_menu_btn_charts.sizeY	= m_menu_charts.Height();
	m_menu_btn_charts.font	= m_font;
	m_menu_btn_charts.text	= "";
	m_menu_btn_charts.isPressed	= false;
	m_menu_btn_charts.setPosition( 0.0f, m_menu_trade_central.PosY() - m_menu_charts.Height() );
	// button menu information
	m_menu_btn_informations.regular = &m_menu_informations;
	m_menu_btn_informations.pressed = &m_menu_informations;
	m_menu_btn_informations.sizeX	= m_menu_informations.Width();
	m_menu_btn_informations.sizeY	= m_menu_informations.Height();
	m_menu_btn_informations.font	= m_font;
	m_menu_btn_informations.text	= "";
	m_menu_btn_informations.isPressed	= false;
	m_menu_btn_informations.setPosition( 0.0f, m_menu_btn_charts.posY - m_menu_informations.Height() );
	// button menu portfolio
	m_menu_btn_portfolio.regular = &m_menu_portfolio;
	m_menu_btn_portfolio.pressed = &m_menu_portfolio;
	m_menu_btn_portfolio.sizeX	= m_menu_portfolio.Width();
	m_menu_btn_portfolio.sizeY	= m_menu_portfolio.Height();
	m_menu_btn_portfolio.font	= m_font;
	m_menu_btn_portfolio.text	= "";
	m_menu_btn_portfolio.isPressed	= false;
	m_menu_btn_portfolio.setPosition( 0.0f, m_menu_btn_informations.posY - m_menu_portfolio.Height() );
	// button menu charts
	m_menu_btn_order_trade.regular = &m_menu_order_trade;
	m_menu_btn_order_trade.pressed = &m_menu_order_trade;
	m_menu_btn_order_trade.sizeX	= m_menu_order_trade.Width();
	m_menu_btn_order_trade.sizeY	= m_menu_order_trade.Height();
	m_menu_btn_order_trade.font	= m_font;
	m_menu_btn_order_trade.text	= "";
	m_menu_btn_order_trade.isPressed	= false;
	m_menu_btn_order_trade.setPosition( 0.0f, m_menu_btn_portfolio.posY - m_menu_order_trade.Height() );
	// button menu my account
	m_menu_btn_my_account.regular = &m_menu_my_account;
	m_menu_btn_my_account.pressed = &m_menu_my_account;
	m_menu_btn_my_account.sizeX	= m_menu_my_account.Width();
	m_menu_btn_my_account.sizeY	= m_menu_my_account.Height();
	m_menu_btn_my_account.font	= m_font;
	m_menu_btn_my_account.text	= "";
	m_menu_btn_my_account.isPressed	= false;
	m_menu_btn_my_account.setPosition( 0.0f, m_menu_btn_order_trade.posY - m_menu_my_account.Height() );
	// button menu logout
	m_menu_btn_logout.regular = &m_menu_logout;
	m_menu_btn_logout.pressed = &m_menu_logout;
	m_menu_btn_logout.sizeX	= m_menu_logout.Width();
	m_menu_btn_logout.sizeY	= m_menu_logout.Height();
	m_menu_btn_logout.font	= m_font;
	m_menu_btn_logout.text	= "";
	m_menu_btn_logout.isPressed	= false;
	m_menu_btn_logout.setPosition( 0.0f, m_menu_btn_my_account.posY - m_menu_logout.Height() );

	m_menu_tc_btn_running_trade.regular = &m_menu_tc_running_trade;
	m_menu_tc_btn_running_trade.pressed = &m_menu_tc_running_trade;
	m_menu_tc_btn_running_trade.sizeX	= m_menu_tc_running_trade.Width();
	m_menu_tc_btn_running_trade.sizeY	= m_menu_tc_running_trade.Height();
	m_menu_tc_btn_running_trade.font	= m_font;
	m_menu_tc_btn_running_trade.text	= "";
	m_menu_tc_btn_running_trade.isPressed	= false;
	m_menu_tc_btn_running_trade.setPosition( 0.0f, m_menu_btn_trade_central.posY - m_menu_tc_running_trade.Height() );

	m_menu_tc_btn_stock_watch.regular = &m_menu_tc_stock_watch;
	m_menu_tc_btn_stock_watch.pressed = &m_menu_tc_stock_watch;
	m_menu_tc_btn_stock_watch.sizeX	= m_menu_tc_stock_watch.Width();
	m_menu_tc_btn_stock_watch.sizeY	= m_menu_tc_stock_watch.Height();
	m_menu_tc_btn_stock_watch.font	= m_font;
	m_menu_tc_btn_stock_watch.text	= "";
	m_menu_tc_btn_stock_watch.isPressed	= false;
	m_menu_tc_btn_stock_watch.setPosition( 0.0f, m_menu_tc_btn_running_trade.posY - m_menu_tc_stock_watch.Height() );

	m_menu_tc_btn_complete_book.regular = &m_menu_tc_complete_book;
	m_menu_tc_btn_complete_book.pressed = &m_menu_tc_complete_book;
	m_menu_tc_btn_complete_book.sizeX	= m_menu_tc_complete_book.Width();
	m_menu_tc_btn_complete_book.sizeY	= m_menu_tc_complete_book.Height();
	m_menu_tc_btn_complete_book.font	= m_font;
	m_menu_tc_btn_complete_book.text	= "";
	m_menu_tc_btn_complete_book.isPressed	= false;
	m_menu_tc_btn_complete_book.setPosition( 0.0f, m_menu_tc_btn_stock_watch.posY - m_menu_tc_complete_book.Height() );

	m_menu_tc_btn_stock_quote.regular = &m_menu_tc_stock_quote;
	m_menu_tc_btn_stock_quote.pressed = &m_menu_tc_stock_quote;
	m_menu_tc_btn_stock_quote.sizeX	= m_menu_tc_stock_quote.Width();
	m_menu_tc_btn_stock_quote.sizeY	= m_menu_tc_stock_quote.Height();
	m_menu_tc_btn_stock_quote.font	= m_font;
	m_menu_tc_btn_stock_quote.text	= "";
	m_menu_tc_btn_stock_quote.isPressed	= false;
	m_menu_tc_btn_stock_quote.setPosition( 0.0f, m_menu_tc_btn_complete_book.posY - m_menu_tc_stock_quote.Height() );

	m_menu_tc_btn_broker_quote.regular = &m_menu_tc_broker_quote;
	m_menu_tc_btn_broker_quote.pressed = &m_menu_tc_broker_quote;
	m_menu_tc_btn_broker_quote.sizeX	= m_menu_tc_broker_quote.Width();
	m_menu_tc_btn_broker_quote.sizeY	= m_menu_tc_broker_quote.Height();
	m_menu_tc_btn_broker_quote.font	= m_font;
	m_menu_tc_btn_broker_quote.text	= "";
	m_menu_tc_btn_broker_quote.isPressed	= false;
	m_menu_tc_btn_broker_quote.setPosition( 0.0f, m_menu_tc_btn_stock_quote.posY - m_menu_tc_broker_quote.Height() );

	m_menu_tc_btn_stock_summary.regular = &m_menu_tc_stock_summary;
	m_menu_tc_btn_stock_summary.pressed = &m_menu_tc_stock_summary;
	m_menu_tc_btn_stock_summary.sizeX	= m_menu_tc_stock_summary.Width();
	m_menu_tc_btn_stock_summary.sizeY	= m_menu_tc_stock_summary.Height();
	m_menu_tc_btn_stock_summary.font	= m_font;
	m_menu_tc_btn_stock_summary.text	= "";
	m_menu_tc_btn_stock_summary.isPressed	= false;
	m_menu_tc_btn_stock_summary.setPosition( 0.0f, m_menu_tc_btn_broker_quote.posY - m_menu_tc_stock_summary.Height() );

	m_menu_tc_btn_broker_summary.regular = &m_menu_tc_broker_summary;
	m_menu_tc_btn_broker_summary.pressed = &m_menu_tc_broker_summary;
	m_menu_tc_btn_broker_summary.sizeX	= m_menu_tc_broker_summary.Width();
	m_menu_tc_btn_broker_summary.sizeY	= m_menu_tc_broker_summary.Height();
	m_menu_tc_btn_broker_summary.font	= m_font;
	m_menu_tc_btn_broker_summary.text	= "";
	m_menu_tc_btn_broker_summary.isPressed	= false;
	m_menu_tc_btn_broker_summary.setPosition( 0.0f, m_menu_tc_btn_stock_summary.posY - m_menu_tc_broker_summary.Height() );

	m_menu_tc_btn_non_regular.regular = &m_menu_tc_non_regular;
	m_menu_tc_btn_non_regular.pressed = &m_menu_tc_non_regular;
	m_menu_tc_btn_non_regular.sizeX	= m_menu_tc_non_regular.Width();
	m_menu_tc_btn_non_regular.sizeY	= m_menu_tc_non_regular.Height();
	m_menu_tc_btn_non_regular.font	= m_font;
	m_menu_tc_btn_non_regular.text	= "";
	m_menu_tc_btn_non_regular.isPressed	= false;
	m_menu_tc_btn_non_regular.setPosition( 0.0f, m_menu_tc_btn_broker_summary.posY - m_menu_tc_non_regular.Height() );

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
            renderHome();
            break;

        case LOADING:
        	fprintf(stderr, "eka at loading.");
            //update();
            //renderGame();
            break;

        case RUNNING_TRADE:
        	renderRunningTrade();
        	break;

        case STOCK_WATCH:
        	renderStockWatch();
        	break;

        case STOCK_QUOTE:
        	renderStockQuote();
        	break;

        case STOCK_SUMMARY:
        	renderStockSummary();
        	break;

        case BROKER_SUMMARY:
        	renderBrokerSummary();
        	break;

        case BROKER_QUOTE:
        	renderBrokerSummary();
        	break;

        case COMPLETE_BOOK:
        	renderCompleteBook();
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
    float text_width, text_height, pos_x, pos_y;
    bbutil_measure_text(m_font_global, "Username", &text_width, &text_height);
    pos_x = 390.0f;
	pos_y = m_screenHeight -620.0f;
	bbutil_render_text(m_font_global, "Username", pos_x, pos_y, 0.05f, 0.05f, 0.05f, 1.0f);

	bbutil_measure_text(m_font_global, "Password", &text_width, &text_height);
	pos_x = 390;
	pos_y = m_screenHeight -677;
	bbutil_render_text(m_font_global, "Password", pos_x, pos_y, 0.05f, 0.05f, 0.05f, 1.0f);

	bbutil_measure_text(m_font_ihsg_val, "5000.00", &text_width, &text_height);
	pos_x = (m_screenWidth - text_width) /2;
	pos_y = m_screenHeight -980;
	bbutil_render_text(m_font_ihsg_val, "5000.00", pos_x, pos_y, 0.05f, 1.0f, 0.05f, 1.0f);

	bbutil_measure_text(m_font_ihsg_vol, "3415.10 bn 17.77 (30%)", &text_width, &text_height);
	pos_x = (m_screenWidth - text_width) /2;
	pos_y = m_screenHeight -1050;
	bbutil_render_text(m_font_ihsg_vol, "3415.10 bn 17.77 (30%)", pos_x, pos_y, 0.95f, 0.95f, 0.95f, 1.0f);

	bbutil_measure_text(m_font_tanggal, "30 September 2013 23:59:59", &text_width, &text_height);
	pos_x = (m_screenWidth - text_width) /2;
	pos_y = m_screenHeight -1125;
	bbutil_render_text(m_font_tanggal, "30 September 2013 23:59:59", pos_x, pos_y, 0.92f, 0.73f, 0.33f, 1.0f);

	bbutil_render_text(m_font_tanggal, "", pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);

	m_platform.finishRender();
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

	m_latar.draw();

	addHeader();

	m_rt_caption.draw();
	m_rt_table_title.draw();

	addFooter();

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

	addFooter();

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
	m_sw_box_black.draw();
	m_sw_port1.draw();
	m_sw_banking.draw();
	m_sw_mining.draw();
	m_sw_cons.draw();
	m_sw_plus_green.draw();
	m_sw_val_green.draw();
	m_sw_val_yellow.draw();
	m_sw_val_red.draw();

	addFooter();
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

	m_ss_caption.draw();
	m_ss_table_title.draw();

	addFooter();

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

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_platform.finishRender();
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
}



void panin::onLeftRelease(float x, float y)
{
	fprintf(stderr, "onLeftRelease.\n");
	float pX, pY;
	pX = x;
	pY = m_screenHeight - y;

	if (m_state == HOME)
	{
		if (m_btn_login.isWithin(pX, pY))
		{
			fprintf(stderr, "button login is released.\n");
			m_btn_login.isPressed = false;
			m_state = STOCK_SUMMARY;
		}

		else if (m_btn_home_info.isWithin(pX, pY))
		{
			fprintf(stderr, "button home info is released.\n");
			m_btn_home_info.isPressed = false;
			m_bShowHomeInfo = true;
		}

		else if (m_btn_home_setel.isWithin(pX, pY))
		{
			fprintf(stderr, "button home setel is released.\n");
			m_btn_home_setel.isPressed = false;
			m_bShowHomeSetel = true;
		}

	}
	else
	{
		if (m_btn_menu.isWithin(pX, pY))
		{
			fprintf(stderr, "button menu is released.\n");
			m_bShowMenu = !m_bShowMenu;

			// update semua posisi.
			return;
		}
		else if (m_btn_buy.isWithin(pX, pY))
		{
			fprintf(stderr, "button buy is released.\n");
			m_bShowBuy = true;
			return;
		}
		else if (m_btn_sell.isWithin(pX, pY))
		{
			fprintf(stderr, "button sell is released.\n");
			m_bShowSell = true;
			return;
		}

		switch (m_state)
		{
		case RUNNING_TRADE:


			break;

		}
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

} /* namespace paninMobile */
