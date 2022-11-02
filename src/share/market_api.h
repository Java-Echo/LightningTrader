#pragma once
#include "define.h"
#include "event_center.hpp"
#include "data_types.hpp"

/*
 *	�������ģ��ӿ�
 */
class market_api 
{
public:
	virtual ~market_api(){}

public:

	/*
	 *	���ĺ�Լ�б�
	 */
	virtual void subscribe(const std::set<code_t>& codes) = 0;

	/*
	 *	�˶���Լ�б�
	 */
	virtual void unsubscribe(const std::set<code_t>& codes) = 0;

	/***  
	* ��ȡʱ��
	*/
	virtual time_t last_tick_time()const = 0;

	/***  
	* ����tick��Ϣ
	*/
	virtual void pop_tick_info(std::vector<const tick_info*>& result) = 0;

	/**   
	* ��ȡ��ǰ������  
	*/
	virtual uint32_t get_trading_day()const = 0 ;
};

class actual_market_api : public market_api,public event_source
{
public:

	void update()
	{
		handle_event();
	}
};
