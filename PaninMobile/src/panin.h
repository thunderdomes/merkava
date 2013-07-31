/*
 * panin.h
 *
 *  Created on: 28 juil. 2013
 *      Author: Eka Chan
 */

#ifndef PANIN_H_
#define PANIN_H_

#include "platform.h"
#include "Sound.h"
#include "bbutil.h"
#include "Sprite.h"

#include <GLES/gl.h>

#ifndef NDEBUG
#include <assert.h>
#define ASSERT(a) (assert(a))
#else
#define ASSERT(a)
#endif

namespace paninMobile
{

class panin : public PlatformEventHandler{
public:
	panin(platform& myPlatform);
	virtual ~panin() {};
	void run();

private:
	platform& m_platform;
	bool m_shutdown;

	enum state {
		LOADING = 0,
		HOME,
		RUNNING_TRADE,
		STOCK_WATCH,
		STOCK_QUOTE,
		STOCK_SUMMARY,
		BROKER_SUMMARY,
		BROKER_QUOTE,
		COMPLETE_BOOK
	};

	state m_state;

	font_t* m_font;
	font_t* m_font_global;
	font_t* m_font_ihsg_val;
	font_t* m_font_ihsg_vol;
	font_t* m_font_tanggal;

	float m_screenWidth, m_screenHeight;
	bool	m_bZ10;


	struct button {
		float posX;
		float posY;
		float sizeX;
		float sizeY;
		bool isPressed;
		Sprite* regular;
		Sprite* pressed;
		float textX;
		float textY;
		font_t* font;
		const char* text;

		void draw() const;

		void setPosition(float x, float y);

		bool isWithin(float clickX, float clickY) const {
			return ((clickX >= posX) && (clickX <= posX + sizeX) && (clickY >= posY) && (clickY <= posY  + sizeY));
		}
	};

	// umum
	Sprite m_latar;
	Sprite m_header_bar_bg;
	Sprite m_header_post;
	Sprite m_btn_info_bg;
	Sprite m_btn_menu_bg;
	Sprite m_btn_sell_bg;
	Sprite m_btn_buy_bg;
	Sprite m_ihsg2;
	button m_btn_info;
	button m_btn_menu;
	button m_btn_sell;
	button m_btn_buy;

	Sprite m_buy_bg;
	Sprite m_buy_caption;
	Sprite m_buy_refresh;
	Sprite m_buy_execute;
	Sprite m_buy_band;
	Sprite m_buy_x;
	button m_btn_buy_refresh;
	button m_btn_buy_execute;
	button m_btn_buy_x;

	Sprite m_sell_bg;
	Sprite m_sell_caption;
	Sprite m_sell_refresh;
	Sprite m_sell_execute;
	Sprite m_sell_band;
	Sprite m_sell_x;
	button m_btn_sell_refresh;
	button m_btn_sell_execute;
	button m_btn_sell_x;

	//Sprite m_white_band;
	Sprite m_dialog_bg;
	Sprite m_blue_rect;
	button m_btn_conf_ok;
	button m_btn_conf_cancel;
	// home setelan
	Sprite m_setel_bg;
	button m_btn_setel_default;
	button m_btn_setel_set202;
	button m_btn_setel_set107;
	button m_btn_setel_save;

	// untuk home
	Sprite m_logo;
	Sprite m_username_textfield;
	Sprite m_password_textfield;
	Sprite m_ihsg_bar;
	Sprite m_ihsg_value_bg;
	Sprite m_ihsg_volume_bg;
	Sprite m_tanggal_bg;
	Sprite m_login_default;
	Sprite m_login_pressed;
	Sprite m_home_info_default;
	Sprite m_home_info_pressed;
	Sprite m_home_setel_default;
	Sprite m_home_setel_pressed;
	button m_btn_login;
	button m_btn_home_info;
	button m_btn_home_setel;

	// running trade
	Sprite m_rt_caption;
	Sprite m_rt_table_title;

	//stock watch
	Sprite m_sw_caption;
	Sprite m_sw_box_black;
	Sprite m_sw_port1;
	Sprite m_sw_banking;
	Sprite m_sw_mining;
	Sprite m_sw_cons;
	Sprite m_sw_plus_green;
	Sprite m_sw_val_green;
	Sprite m_sw_val_yellow;
	Sprite m_sw_val_red;


	// complete book
	Sprite m_cb_caption;
	Sprite m_cb_top_band;
	Sprite m_cb_table_title1;
	Sprite m_cb_table_title2;


	// stock quote
	Sprite m_sq_caption;
	Sprite m_sq_table_title;

	// broker quote
	Sprite m_bq_caption;
	Sprite m_bq_table_title;

	// stock summary
	Sprite m_ss_caption;
	Sprite m_ss_table_title;

	// broker summary
	Sprite m_bs_caption;
	Sprite m_bs_table_title;

	// Non regular

	// companies
	Sprite m_cpy_company1;
	Sprite m_cpy_financial1;
	Sprite m_cpy_ratio1;
	Sprite m_cpy_company2;
	Sprite m_cpy_financial2;
	Sprite m_cpy_ratio2;
	button m_cpy_btn_company;
	button m_cpy_btn_financial;
	button m_cpy_btn_ratio;

	// corporate action
	Sprite m_ca_caption;
	Sprite m_ca_table_title;
	Sprite m_ca_dividen1;
	Sprite m_ca_dividen2;
	Sprite m_ca_bonus1;
	Sprite m_ca_bonus2;
	Sprite m_ca_split1;
	Sprite m_ca_split2;
	Sprite m_ca_warrant1;
	Sprite m_ca_warrant2;
	Sprite m_ca_rights1;
	Sprite m_ca_rights2;
	Sprite m_ca_rups1;
	Sprite m_ca_rups2;
	button m_ca_btn_dividen;
	button m_ca_btn_bonus;
	button m_ca_btn_split;
	button m_ca_btn_warrant;
	button m_ca_btn_rights;
	button m_ca_btn_rups;

	// research
	Sprite m_rs_caption;

	// portfolio
	Sprite m_pf_caption;
	Sprite m_pf_table_title;

	// my account
	Sprite m_ac_password;
	Sprite m_ac_trading_pin;
	Sprite m_ac_bg_black;
	Sprite m_ac_textfield_bg;
	Sprite m_ac_save;
	button m_btn_save;

	// tradelist
	Sprite m_tl_order_caption;
	Sprite m_tl_tradelist_caption;
	Sprite m_tl_order_table_caption;
	Sprite m_tl_tradelist_table_caption;


	// charts

	// information

	// order and trade

	// my account




	const char* m_message;
	float m_messagePosX, m_messagePosY;

	virtual void onLeftPress(float x, float y);
	virtual void onLeftRelease(float x, float y);
	virtual void onExit();
	virtual void onPromptOk(const std::string& input);

	// void renderLoading();
	void enable2D();
	void renderHome();
	void renderCompleteBook();
	void renderStockQuote();
	void renderStockWatch();
	void renderStockSummary();
	void renderBrokerQuote();
	void renderBrokerSummary();
	void renderRunningTrade();

	void addHeader();
	void addFooter();

	void update();
};

}		/* namespace paninMobile*/
#endif /* PANIN_H_ */
