#pragma once
#include <define.h>
#include <data_types.hpp>

/***  
* 
* �û�����һ���µ�����������ʵ�ֿ�ƽ��ת����ع��ܵĲ��
* strategy ��Ϊ��������ͷ�ڵ㣬�м������������ڵ㣬exec_ctx ��Ϊ�������Ľ����ڵ�
* ʵ�ֲ�ͬ�Ĺ��ܣ�ֻ��Ҫ���м����ӽڵ㼴��
*/
class pod_chain
{

protected:
	
	pod_chain* _next ;

	class trader_api* _trader ;

public:
	pod_chain(class trader_api* trader, pod_chain* next):_next(next), _trader(trader)
	{}

	virtual ~pod_chain()
	{
		if(_trader)
		{
			_trader = nullptr ;
		}
		if(_next)
		{
			delete _next;
			_next = nullptr ;
		}
	}

	virtual estid_t place_order(offset_type offset, direction_type direction, code_t code, uint32_t count, double_t price, order_flag flag) = 0;

protected:

	uint32_t get_pending_position(code_t code)const;
	
};

class close_to_open_chain : public pod_chain
{
	//���ŷ���ѣ�ƽת����
private:
	uint32_t _max_position ;
public:
	close_to_open_chain(class trader_api* trader,uint32_t max_position, pod_chain* next) :pod_chain(trader,next), _max_position(max_position)
	{}
	virtual ~close_to_open_chain()
	{}

	virtual estid_t place_order(offset_type offset, direction_type direction, code_t code, uint32_t count, double_t price, order_flag flag) override;

};

class open_to_close_chain : public pod_chain
{
	//���� ��֤�� ����תƽ��

public:
	open_to_close_chain(class trader_api* trader, pod_chain* next) :pod_chain(trader, next)
	{}

	virtual ~open_to_close_chain()
	{}

	virtual estid_t place_order(offset_type offset, direction_type direction, code_t code, uint32_t count, double_t price, order_flag flag) override;

};

class price_to_cancel_chain : public pod_chain
{
	
public:
	price_to_cancel_chain(class trader_api* trader, pod_chain* next) :pod_chain(trader, next)
	{}

	virtual ~price_to_cancel_chain()
	{}

	virtual estid_t place_order(offset_type offset, direction_type direction, code_t code, uint32_t count, double_t price, order_flag flag) override;

};

class the_end_chain : public pod_chain
{
private:
	uint32_t _max_position ;
public:
	
	the_end_chain(class trader_api* trader,uint32_t max_position) :pod_chain(trader, nullptr), _max_position(max_position)
	{}

	virtual ~the_end_chain()
	{}

	virtual estid_t place_order(offset_type offset, direction_type direction, code_t code, uint32_t count, double_t price, order_flag flag) override;


};