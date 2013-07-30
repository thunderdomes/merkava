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

	fprintf(stderr, "load general assets.\n");
	m_header_bar_bg.load("app/native/assets/umum/bar.png");
	m_header_bar_bg.setPosition(0.0f, m_screenHeight - 137.0f);
	m_header_post.load("app/native/assets/umum/post.png");
	m_header_post.setPosition((m_screenWidth - m_header_post.Width())/2, m_screenHeight - 124.0f);
	m_btn_info_bg.load("app/native/assets/umum/info_blue.png");
	m_btn_menu_bg.load("app/native/assets/umum/menu_blue.png");
	m_btn_menu_bg.setPosition(25.0f, m_screenHeight - 128.0f);
	m_btn_sell_bg.load("app/native/assets/umum/sell.png");
	m_btn_sell_bg.setPosition(622.0f, m_screenHeight - 1254.0f);
	m_btn_buy_bg.load("app/native/assets/umum/post.png");
	m_btn_buy_bg.setPosition(460.0f, m_screenHeight - 1254.0f);

	m_btn_info.regular = &m_btn_info_bg;
	m_btn_info.pressed = &m_btn_info_bg;
	m_btn_info.sizeX	= m_btn_info_bg.Width();
	m_btn_info.sizeY	= m_btn_info_bg.Height();
	m_btn_info.font	= m_font;
	m_btn_info.text	= "";
	m_btn_info.isPressed	= false;
	m_btn_info.setPosition( 680.0f, m_screenHeight - 128.0 );
	m_btn_menu.regular = &m_btn_menu_bg;
	m_btn_menu.pressed = &m_btn_menu_bg;
	m_btn_menu.sizeX	= m_btn_menu_bg.Width();
	m_btn_menu.sizeY	= m_btn_menu_bg.Height();
	m_btn_menu.font	= m_font;
	m_btn_menu.text	= "";
	m_btn_menu.isPressed	= false;
	m_btn_menu.setPosition( 25.0f, m_screenHeight - 128.0 );
	m_btn_buy.regular = &m_btn_buy_bg;
	m_btn_buy.pressed = &m_btn_buy_bg;
	m_btn_buy.sizeX	= m_btn_buy_bg.Width();
	m_btn_buy.sizeY	= m_btn_buy_bg.Height();
	m_btn_buy.font	= m_font;
	m_btn_buy.text	= "";
	m_btn_buy.isPressed	= false;
	m_btn_buy.setPosition(622.0f, m_screenHeight - 1254.0f);
	m_btn_sell.regular = &m_btn_sell_bg;
	m_btn_sell.pressed = &m_btn_sell_bg;
	m_btn_sell.sizeX	= m_btn_sell_bg.Width();
	m_btn_sell.sizeY	= m_btn_sell_bg.Height();
	m_btn_sell.font	= m_font;
	m_btn_sell.text	= "";
	m_btn_sell.isPressed	= false;
	m_btn_sell.setPosition( 460.0f, m_screenHeight - 1254.0f);
	//ihsg
	m_ihsg2.load("app/native/assets/login/ihsg.png");
	m_ihsg2.setPosition(17.0f, m_screenHeight - 80.0f);
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

	//TRADE
	m_rt_caption.load("app/native/assets/running_trade/rt_bar_title.png");
	m_rt_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_rt_table_title.load("app/native/assets/running_trade/rt_table_title.png");
	m_rt_table_title.setPosition(0.0f, m_screenHeight - 262.0f);

	//stock watch
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
	m_cb_caption.load("app/native/assets/complete_book/completebook_caption.png");
	m_cb_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_cb_top_band.load("app/native/assets/complete_book/completebook_caption.png");
	m_cb_top_band.setPosition(0.0f, m_screenHeight - 263.0f);
	m_cb_table_title1.load("app/native/assets/complete_book/completebook_caption.png");
	m_cb_table_title1.setPosition(27.0f, m_screenHeight - 452.0f);
	m_cb_table_title2.load("app/native/assets/complete_book/completebook_caption.png");
	m_cb_table_title2.setPosition(27.0f, m_screenHeight - 738.0f);

	// stock quote
	m_sq_caption.load("app/native/assets/stock_quote/sq_caption.png");
	m_sq_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_sq_table_title.load("app/native/assets/stock_quote/sq_table_title.png");
	m_sq_table_title.setPosition(0.0f, m_screenHeight - 262.0f);

	// broker quote
	m_bq_caption.load("app/native/assets/broker_quote/bq_caption.png");
	m_bq_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_bq_table_title.load("app/native/assets/broker_quote/bq_table_title.png");
	m_bq_table_title.setPosition(0.0f, m_screenHeight - 262.0f);

	// stock summary
	m_ss_caption.load("app/native/assets/stock_summary/ss_caption.png");
	m_ss_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_ss_table_title.load("app/native/assets/stock_summary/ss_table_title.png");
	m_ss_table_title.setPosition(0.0f, m_screenHeight - 262.0f);

	// broker summary
	m_bs_caption.load("app/native/assets/broker_summary/bs_caption.png");
	m_bs_caption.setPosition(27.0f, m_screenHeight - 200.0f);
	m_bs_table_title.load("app/native/assets/broker_summary/bs_table_title.png");
	m_bs_table_title.setPosition(0.0f, m_screenHeight - 262.0f);


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
	m_btn_sell.draw();
	m_btn_buy.draw();
	m_ihsg2.draw();
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
