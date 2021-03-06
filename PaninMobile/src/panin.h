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
//#include "Label.h"
//#include "Button.h"


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

	std::ostringstream oss;


	enum state {
		LOADING = 0,
		HOME,
		RUNNING_TRADE,
		STOCK_WATCH,
		COMPLETE_BOOK,
		STOCK_QUOTE,
		BROKER_QUOTE,
		STOCK_SUMMARY,
		BROKER_SUMMARY,
		NON_REGULAR,
		CHARTS,
		INFORMATIONS,
		NEWS,
		COMPANY_INFO,
		PORTFOLIO,
		ORDER_TRADE,
		MY_ACCOUNT,
		LAST_STATE
	};

	state m_state;

	enum eConfiguration {
		CONF_DEFAULT = 0,
		CONF_SET202,
		CONF_SET107,
		CONF_SAVE
	};
	eConfiguration m_eConfiguration;

	font_t* m_font;
	font_t* m_font_global;
	font_t* m_font_ihsg_val;
	font_t* m_font_ihsg_vol;
	font_t* m_font_tanggal;
	font_t* m_font8;
	font_t* m_font9;
	font_t* m_font10;
	font_t* m_font11;
	font_t* m_font12;
	font_t* m_font14;
	font_t* m_font20;
	font_t* m_font24;
	font_t* m_font28;
	font_t* m_font36;

	time_t m_time;

	float m_screenWidth, m_screenHeight;
	float m_ePosX, m_ePosY;
	float m_fmenu_width, m_fmenu_animation;
	bool	m_bZ10;
	float m_fLeftReffPos;

	// menu
	bool	m_bShowMenu;
	bool	m_bMenuActive;
	bool	m_bMenuShowAnimation;
	bool	m_bMenuHideAnimation;
	bool	m_bShowSubmenuTC;
	bool	m_bShowSubmenuInformation;

	bool	m_bShowInfo;

	// buy and sell
	bool	m_bShowBuy;
	bool	m_bShowSell;
	bool	m_bAccountIdFocused;
	bool	m_bStockTradeFocused;
	bool	m_bPriceFocused;
	bool	m_bVolumeFocused;

	bool	m_bVirtualKeyboardShow;


	// home
	bool	m_bShowHomeInfo;
	bool	m_bShowHomeSetel;
	bool	m_bUsernameFocus;
	bool	m_bPasswordFocus;

	// my account
	bool	m_bOldPaswordFocus;
	bool	m_bNewPaswordFocus;
	bool	m_bConfirmPwdFocus;
	bool	m_bOldPinFocus;
	bool	m_bNewPinFocus;
	bool	m_bConfirmPinFocus;
	std::string m_sOldPass;
	std::string m_sNewPass;
	std::string m_sConfirmPass;
	std::string m_sOldPin;
	std::string m_sNewPin;
	std::string m_sConfirmPin;

	struct button {
		float posX;
		float posY;
		float sizeX;
		float sizeY;
		bool isPressed;
		bool isEnabled;
		Sprite* regular;
		Sprite* pressed;
		float textX;
		float textY;
		font_t* font;
		const char* text;

		void draw() const;

		void setPosition(float x, float y);

		bool isWithin(float clickX, float clickY) const {
			//fprintf(stderr, "clicked at: %f, %f for box: %f, %f, %f, %f and sprite %f, %f.\n", clickX, clickY, posX, posY, posX+ sizeX, posY + sizeY, regular->PosX(), regular->PosY());
			return ((clickX >= posX) && (clickX <= posX + sizeX) && (clickY >= posY) && (clickY <= posY  + sizeY));
		}
	};

	struct _rtData {
		std::string tgl;
		std::string simp;
		std::string rg;
		std::string price;
		std::string volume_lot;
		std::string prev;
		std::string buyer_code;
		std::string buyer_type;
		std::string seller_code;
		std::string seller_type;
		std::string stock_type;
	} rtData;

	struct _sqData {
		std::string aali;
		std::string ng;
		std::string prev;
		std::string open;
		std::string high;
		std::string low;
		std::string last;
		std::string volume;
		std::string value;
		std::string freq;
		std::string best_bid_price;
		std::string best_bid_vol;
		std::string best_offer_vol;
		std::string last_trade_vol;
		std::string total_dom_sell_vol;
		std::string total_dom_sell_freq;
		std::string total_dom_sell_val;
		std::string total_dom_buy_vol;
		std::string total_dom_buy_freq;
		std::string total_dom_buy_val;
		std::string total_fgn_sell_vol;
		std::string total_fgn_sell_freq;
		std::string total_fgn_sell_val;
		std::string total_fgn_buy_vol;
		std::string total_fgn_buy_freq;
		std::string total_fgn_buy_val;
	} sqData;

	struct _bqData {
		std::string cc;
		std::string rg;
		std::string buy_freq;
		std::string buy_vol;
		std::string buy_val;
		std::string sell_freq;
		std::string sell_vol;
		std::string sell_val;
		std::string rg1;
	} bqData;

	struct _composite {
		std::string composite;
		std::string prev_price;
		std::string open_price;
		std::string last;
		std::string high;
		std::string low;
		std::string freq;
		std::string vol;
		std::string value;
	} composite;

	struct _regionalIdx {
		std::string hsifut;
		std::string prev;
		std::string open;
		std::string high;
		std::string low;
		std::string last;
		std::string vol;
		std::string future;
	} regionaldx;

	struct _currencies {
		std::string eurusd;
		std::string bid;
		std::string ask;
		std::string last;
		std::string usd;
	} currencies;

	struct _newsTitle {
		std::string newsId;
		std::string datetime;
		std::string iqp;
		std::string title;
	} newsTitle;

	struct _tradeBook {
		std::string price;
		std::string volume;
		std::string freq;
	} tradeBook;

	struct _orderBook {
		std::string ob;
		std::string sequence_no;
		std::string price;
		std::string volume;
		std::string freq;
	} orderBook;

	struct _stockSummary {
		std::string az;
		std::string domestic_buy_freq;
		std::string domestic_buy_vol;
		std::string domestic_buy_val;
		std::string domestic_sell_freq;
		std::string domestic_sell_vol;
		std::string domestic_sell_val;
		std::string foreign_buy_freq;
		std::string foreign_buy_vol;
		std::string foreign_buy_val;
		std::string foreign_sell_freq;
		std::string foreign_sell_vol;
		std::string foreign_sell_val;
	} stockSummary;

	struct _brokerSmmary {
		std::string asii;
		std::string domestic_buy_freq;
		std::string domestic_buy_vol;
		std::string domestic_buy_val;
		std::string domestic_sell_freq;
		std::string domestic_sell_vol;
		std::string domestic_sell_val;
		std::string foreign_buy_freq;
		std::string foreign_buy_vol;
		std::string foreign_buy_val;
		std::string foreign_sell_freq;
		std::string foreign_sell_vol;
		std::string foreign_sell_val;
	} brokerSummary;

	struct _stockChartUpdate {
		std::string datetime;
		std::string open;
		std::string high;
		std::string low;
		std::string close;
		std::string volume;
	};



	// umum
	Sprite m_latar;
	Sprite m_header_bar_bg;
	Sprite m_header_post;
	Sprite m_btn_info_bg;
	Sprite m_btn_info_p_bg;
	Sprite m_btn_menu_bg;
	Sprite m_btn_menu_bg_p;
	Sprite m_btn_sell_bg;
	Sprite m_btn_sell_bg_p;
	Sprite m_btn_buy_bg;
	Sprite m_btn_buy_bg_p;
	Sprite m_ihsg2;
	button m_btn_info;
	button m_btn_menu;
	button m_btn_sell;
	button m_btn_buy;

	Sprite m_buy_bg;
	Sprite m_buy_caption;
	Sprite m_buy_refresh;
	Sprite m_buy_refresh_p;
	Sprite m_buy_execute;
	Sprite m_buy_execute_p;
	Sprite m_buy_band;
	Sprite m_buy_x;
	Sprite m_buy_x_p;
	button m_btn_buy_refresh;
	button m_btn_buy_execute;
	button m_btn_buy_x;

	Sprite m_sell_bg;
	Sprite m_sell_caption;
	Sprite m_sell_refresh;
	Sprite m_sell_refresh_p;
	Sprite m_sell_execute;
	Sprite m_sell_execute_p;
	Sprite m_sell_band;
	Sprite m_sell_x;
	Sprite m_sell_x_p;
	button m_btn_sell_refresh;
	button m_btn_sell_execute;
	button m_btn_sell_x;

	Sprite m_buysell_textfield_bg;
	Sprite m_buysell_textfield_bg_focus;

	Sprite m_textfield_bg;
	//Sprite m_white_band;
	Sprite m_dialog_bg;
	Sprite m_blue_rect;
	Sprite m_blue_rect_p;
	button m_btn_conf_ok;
	button m_btn_conf_cancel;
	// home setelan
	Sprite m_setel_bg;
	Sprite m_setel_default;
	Sprite m_setel_set202;
	Sprite m_setel_set107;
	Sprite m_setel_save;
	Sprite m_setel_x;
	Sprite m_setel_default_p;
	Sprite m_setel_set202_p;
	Sprite m_setel_set107_p;
	Sprite m_setel_save_p;
	Sprite m_setel_x_p;
	button m_btn_setel_default;
	button m_btn_setel_set202;
	button m_btn_setel_set107;
	button m_btn_setel_save;
	button m_btn_setel_x;

	// untuk home
	Sprite m_logo;
	Sprite m_username_textfield_default;
	Sprite m_username_textfield_regular;
	Sprite m_password_textfield_default;
	Sprite m_password_textfield_regular;
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
	button m_btn_home_username;
	button m_btn_home_password;

	// running trade
	Sprite m_rt_caption;
	Sprite m_rt_table_title;

	//stock watch
	Sprite m_sw_caption;
	Sprite m_sw_box_black;
	Sprite m_sw_port1;
	Sprite m_sw_port1_p;
	Sprite m_sw_banking;
	Sprite m_sw_banking_p;
	Sprite m_sw_mining;
	Sprite m_sw_mining_p;
	Sprite m_sw_cons;
	Sprite m_sw_cons_p;
	Sprite m_sw_plus_green;
	Sprite m_sw_plus_green_p;
	Sprite m_sw_val_green;
	Sprite m_sw_val_yellow;
	Sprite m_sw_val_red;
	button m_sw_btn_port1;
	button m_sw_btn_banking;
	button m_sw_btn_mining;
	button m_sw_btn_cons;
	button m_sw_btn_plus_green;


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
	Sprite m_cpy_caption;
	Sprite m_cpy_company;
	Sprite m_cpy_financial;
	Sprite m_cpy_ratio;
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
	Sprite m_ca_bonus3;
	Sprite m_ca_split1;
	Sprite m_ca_split2;
	Sprite m_ca_split3;
	Sprite m_ca_warrant1;
	Sprite m_ca_warrant2;
	Sprite m_ca_warrant3;
	Sprite m_ca_rights1;
	Sprite m_ca_rights2;
	Sprite m_ca_rights3;
	Sprite m_ca_rups1;
	Sprite m_ca_rups2;
	button m_ca_btn_dividen;
	button m_ca_btn_bonus;
	button m_ca_btn_split;
	button m_ca_btn_warrant;
	button m_ca_btn_rights;
	button m_ca_btn_rups;

	// my account
	Sprite m_ac_password;
	Sprite m_ac_trading_pin;
	Sprite m_ac_bg_black;
	Sprite m_ac_bg_black2;
	Sprite m_ac_textfield_bg;
	Sprite m_ac_tf_focus;
	Sprite m_ac_save;
	Sprite m_ac_save_p;
	Sprite m_ac_save2;
	Sprite m_ac_save2_p;
	button m_btn_save1;
	button m_btn_save2;

	// tradelist
	Sprite m_tl_order_caption;
	Sprite m_tl_tradelist_caption;
	Sprite m_tl_order_table_caption;
	Sprite m_tl_tradelist_table_caption;


	// charts
	Sprite m_chart_bg;
	Sprite m_chart_post_bar;
	Sprite m_chart_caption_bottom;
	Sprite m_chart_text_bg;
	Sprite m_icon_search;
	Sprite m_chart_1day_big;
	Sprite m_chart_1week_big;
	Sprite m_chart_1month_big;
	Sprite m_chart_1year_big;
	Sprite m_chart_3year_big;
	Sprite m_chart_1day_small;
	Sprite m_chart_1week_small;
	Sprite m_chart_1month_small;
	Sprite m_chart_1year_small;
	Sprite m_chart_3year_small;
	button m_chart_btn_search;
	button m_chart_btn_1day;
	button m_chart_btn_1week;
	button m_chart_btn_1month;
	button m_chart_btn_1year;
	button m_chart_btn_3year;

	// information

	// order and trade

	// my account

	// menu
	Sprite m_menu_bg;
	Sprite m_menu_tc_bg;
	Sprite m_menu_acc_number;
	Sprite m_menu_trade_central;
	Sprite m_menu_charts;
	Sprite m_menu_informations;
	Sprite m_menu_portfolio;
	Sprite m_menu_order_trade;
	Sprite m_menu_my_account;
	Sprite m_menu_logout;
	Sprite m_menu_tc_running_trade;
	Sprite m_menu_tc_stock_watch;
	Sprite m_menu_tc_complete_book;
	Sprite m_menu_tc_stock_quote;
	Sprite m_menu_tc_broker_quote;
	Sprite m_menu_tc_stock_summary;
	Sprite m_menu_tc_broker_summary;
	Sprite m_menu_tc_non_regular;
	Sprite m_menu_trade_central_p;
	Sprite m_menu_charts_p;
	Sprite m_menu_informations_p;
	Sprite m_menu_portfolio_p;
	Sprite m_menu_order_trade_p;
	Sprite m_menu_my_account_p;
	Sprite m_menu_logout_p;
	Sprite m_menu_tc_running_trade_p;
	Sprite m_menu_tc_stock_watch_p;
	Sprite m_menu_tc_complete_book_p;
	Sprite m_menu_tc_stock_quote_p;
	Sprite m_menu_tc_broker_quote_p;
	Sprite m_menu_tc_stock_summary_p;
	Sprite m_menu_tc_broker_summary_p;
	Sprite m_menu_tc_non_regular_p;
	Sprite m_menu_i_news;
	Sprite m_menu_i_news_p;
	Sprite m_menu_i_compinfo;
	Sprite m_menu_i_compinfo_p;
	button m_menu_btn_trade_central;
	button m_menu_btn_charts;
	button m_menu_btn_informations;
	button m_menu_btn_portfolio;
	button m_menu_btn_order_trade;
	button m_menu_btn_my_account;
	button m_menu_btn_logout;
	button m_menu_tc_btn_running_trade;
	button m_menu_tc_btn_stock_watch;
	button m_menu_tc_btn_complete_book;
	button m_menu_tc_btn_stock_quote;
	button m_menu_tc_btn_broker_quote;
	button m_menu_tc_btn_stock_summary;
	button m_menu_tc_btn_broker_summary;
	button m_menu_tc_btn_non_regular;
	button m_menu_i_btn_news;
	button m_menu_i_btn_compinfo;


	// password
	Sprite m_pw_caption;
	Sprite m_pw_text_bg;
	Sprite m_pw_save;
	button m_pw_btn_save;

	// portfolio
	Sprite m_pf_caption;
	Sprite m_pf_table_title;
	Sprite m_pf_acc_number;

	// research
	Sprite m_research_caption;

	const char* m_message;
	float m_messagePosX, m_messagePosY;

	bool m_bLogged;
	std::string m_u_name;
	std::string m_u_pass;
	std::string m_sIhsg_val;
	std::string m_sIhsg_volume;
	std::string m_sIhsg_percent;

	std::string m_sAccNumber;
	std::string m_sAccName;

	// buy sell dialog var
	std::string m_sAccID;
	std::string m_sStockCode;
	std::string m_sPrice;
	std::string m_sLot;
	std::string m_sMaxBuy;
	std::string m_sStockValue;
	std::string m_sTransFee;
	std::string m_sPayable;

	float m_footerHeight;
	float m_headerHeight;

	int companyInfoFlag;
	int corporateActionFlag;

	std::string m_s_pf_tradingLimit;
	std::string m_s_pf_ratio;
	std::string m_s_pf_equity;
	std::string m_s_pf_cashloan;
	std::string m_s_pf_stockValue;
	std::string m_s_pf_nettToday;

	std::string m_s_pf_tableContent[5][10];

	std::vector<std::string> m_vRT;
	std::vector<std::string> m_vSQ;
	std::vector<std::string> m_vBQ;
	std::vector<std::string> m_vSW;
	std::vector<std::string> m_vSS;
	std::vector<std::string> m_vBS;



	virtual void onLeftPress(float x, float y);
	virtual void onLeftRelease(float x, float y);
	virtual void onKeyPressed(int c);
	virtual void onExit();
	virtual void onPromptOk(const std::string& input);

	// void renderLoading();
	void enable2D();
	void enable2D_land();

	void renderHome();
	void renderHomeSetel();
	void renderHomeInfo();
	void renderRunningTrade();
	void renderStockWatch();
	void renderCompleteBook();
	void renderStockQuote();
	void renderBrokerQuote();
	void renderStockSummary();
	void renderBrokerSummary();

	void renderNonRegular();
	void renderCharts();
	void renderInformations();
	void renderNews();
	void renderCompanyInfo();
	void renderCorporateAction();
	void renderPortfolio();
	void renderOrderTrade();
	void renderResearch();
	void renderMyAccount();


	void renderMenu();

	void addHeader();
	void addFooter();

	void renderBuyDialog();
	void renderSellDialog();

	void update();
	void updateForLandscape();
	void updateForPotrait();
	void updateHome();

	void setConfiguration(eConfiguration conf);

	void periksaLogin();
	void ambilDataRunningTrade();
	void ambilDataStockQuote();
	void ambilDataBrokerQuote();
	void ambilDataStockWatch();
	void ambilDataStockSummary();
	void ambilDataBrokerSummary();

	bool periksaPointer(float pX, float pY, float kiri, float bawah, float lebar, float tinggi);
};

}		/* namespace paninMobile*/
#endif /* PANIN_H_ */
