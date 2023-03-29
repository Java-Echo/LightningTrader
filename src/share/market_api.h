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

};

class futures_market : public market_api, public event_source<64>
{

};
