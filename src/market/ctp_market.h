#pragma once
#include <define.h>
#include <market_api.h>
#include <event_center.hpp>
#include <mutex>
#include <condition_variable>
#include <ThostFtdcMdApi.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/pool/object_pool.hpp>



class ctp_market :	public actual_market_api,public CThostFtdcMdSpi
{
public:

	ctp_market();

	virtual ~ctp_market();
	
	bool init(const boost::property_tree::ptree& config);

	void release();

//IMarketAPI 接口
public:


	virtual void subscribe(const std::set<code_t>& codes) override;

	virtual void unsubscribe(const std::set<code_t>& codes) override;

	virtual void pop_tick_info(std::vector<const tick_info*>& result) override;

	virtual uint32_t get_trading_day() const override
	{
		return _current_trading_day;
	}
	virtual time_t last_tick_time() const override
	{
		return _last_tick_time;
	}

//CThostFtdcMdSpi 接口
public:
	virtual void OnRspError( CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast );

	virtual void OnFrontConnected();

	virtual void OnRspUserLogin( CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast );

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnFrontDisconnected( int nReason );

	virtual void OnRtnDepthMarketData( CThostFtdcDepthMarketDataField *pDepthMarketData );

	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast );

	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

private:
	/*
	 *	发送登录请求
	 */
	void do_userlogin();
	/*
	 *	订阅品种行情
	 */
	void do_subscribe();
	
	void do_unsubscribe(const std::vector<code_t>& code_list);

private:
	
	CThostFtdcMdApi*	_md_api;

	std::string			_front_addr;
	std::string			_broker_id;
	std::string			_userid;
	std::string			_password;
	
	int					_reqid;

	std::mutex _mutex;
	std::unique_lock<std::mutex> _process_mutex;
	std::condition_variable _process_signal;

	boost::object_pool<tick_info> _tick_pool;
	boost::lockfree::spsc_queue<tick_info*, boost::lockfree::capacity<1024>>  _tick_queue;
	
	std::vector<code_t> _instrument_id_list;

	time_t _last_tick_time ;

	uint32_t _current_trading_day;

	bool _is_inited ;

};

