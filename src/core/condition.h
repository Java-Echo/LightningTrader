#pragma once
#include <data_types.hpp>

struct condition
{
	virtual bool check(const tick_info* tick) = 0;
};
//ʱ�䵽��Ŀ��ʱ�䴥��
struct time_out_cdt : condition
{
	time_out_cdt(time_t target_time):_target_time(target_time)
	{
	
	}
	virtual bool check(const tick_info* tick) override ;

private:
	time_t _target_time;
};

//�۸����ǳ���Ŀ��۸�ʱ�򴥷�
struct price_up_cdt : condition
{
	price_up_cdt(double_t price) :_target_price(price)
	{

	}
	virtual bool check(const tick_info* tick) override;
	
private:
	double_t _target_price;
};

//�۸����Ŀ��۴���
struct price_down_cdt : condition
{
	price_down_cdt(double_t price) :_target_price(price)
	{

	}
	virtual bool check(const tick_info* tick) override;
	
private:
	double_t _target_price;
};

//��߻���ָ����λ����
struct fall_back_cdt : condition
{
	fall_back_cdt(double_t price, double_t fall_offset) :_highest_price(price), _fall_offset(fall_offset)
	{

	}
	virtual bool check(const tick_info* tick) override;

private:
	double_t _highest_price;
	double_t _fall_offset ;
};

//���׷���ָ����λ����
struct bounce_back_cdt : condition
{
	bounce_back_cdt(double_t price, double_t bounce_offset) :_lowest_price(price), _bounce_offset(bounce_offset)
	{

	}
	virtual bool check(const tick_info* tick) override;

private:
	double_t _lowest_price;
	double_t _bounce_offset;
};
