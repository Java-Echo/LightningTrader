#pragma once
#include <data_types.hpp>

struct condition
{
	virtual bool check(const tick_info* tick) const = 0;
};
//ʱ�䵽��Ŀ��ʱ�䴥��
struct time_out_cdt : condition
{
	time_out_cdt(uint32_t seconds):_delay_seconds(seconds)
	{
	
	}
	virtual bool check(const tick_info* tick)const override ;

private:
	uint32_t _delay_seconds;
};

//�۸����ǳ���Ŀ��۸�ʱ�򴥷�
struct price_up_cdt : condition
{
	price_up_cdt(uint32_t price) :_target_price(price)
	{

	}
	virtual bool check(const tick_info* tick)const override;
	
private:
	uint32_t _target_price;
};


struct price_down_cdt : condition
{
	price_down_cdt(uint32_t price) :_target_price(price)
	{

	}
	virtual bool check(const tick_info* tick)const override;
	
private:
	uint32_t _target_price;
};