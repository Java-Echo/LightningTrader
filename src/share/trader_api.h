#pragma once
#include <define.h>
#include <data_types.hpp>
#include "event_center.hpp"

//�µ��ӿڹ���ӿ�
class trader_api
{
public:
	virtual ~trader_api(){}

public:

	/*
	 *	�Ƿ����
	 */
	virtual bool is_usable()const = 0;

	/*
	 *	�µ��ӿ�
	 *	entrust �µ��ľ������ݽṹ
	 */
	virtual estid_t place_order(offset_type offset, direction_type direction , const code_t& code, uint32_t count, double_t price , order_flag flag) = 0;

	/*
	 *	����
	 *	action	�����ľ������ݽṹ
	 */
	virtual void cancel_order(estid_t order_id) = 0;

	/*
	 *	��ȡ�˻���Ϣ
	 */
	virtual const account_info get_account() const = 0;
	
	/*
	*	��ȡ�ֲ���Ϣ
	*/
	virtual const position_info get_position(const code_t& code) const = 0;
	
	/*
	 *	��ȡ������Ϣ
	 */
	virtual const order_info get_order(estid_t order_id) const = 0;

	/*
	*	��ȡ�˻���Ϣ
	*/
	virtual void find_orders(std::vector<order_info>& order_result,std::function<bool(const order_info&)> func) const = 0;

	/*
	 *	�ύ���㵥
	 */
	virtual void submit_settlement() = 0 ;

};

class futures_trader : public trader_api, public event_source
{

};
