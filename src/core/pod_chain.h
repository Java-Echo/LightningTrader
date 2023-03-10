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
	
	class trader_api* _trader;
	class context* _ctx ;
	
public:
	pod_chain(context* ctx, pod_chain* next);
	virtual ~pod_chain();
	
	virtual estid_t place_order(offset_type offset, direction_type direction, const code_t& code, uint32_t count, double_t price, order_flag flag) = 0;

protected:

	uint32_t get_open_pending()const;
	
};

class close_to_open_chain : public pod_chain
{
	//���ŷ���ѣ�ƽת����

public:
	
	close_to_open_chain(context* ctx,pod_chain* next) ;

	virtual estid_t place_order(offset_type offset, direction_type direction, const code_t& code, uint32_t count, double_t price, order_flag flag) override;

};

class open_to_close_chain : public pod_chain
{
	//���� ��֤�� ����תƽ��

public:
	open_to_close_chain(context* ctx, pod_chain* next) :pod_chain(ctx, next)
	{}

	virtual estid_t place_order(offset_type offset, direction_type direction, const code_t& code, uint32_t count, double_t price, order_flag flag) override;

};

class price_to_cancel_chain : public pod_chain
{
	
public:
	price_to_cancel_chain(context* ctx, pod_chain* next) :pod_chain(ctx, next)
	{}

	virtual estid_t place_order(offset_type offset, direction_type direction, const code_t& code, uint32_t count, double_t price, order_flag flag) override;

};
//�Ʋ�
class transfer_position_chain : public pod_chain
{

public:
	transfer_position_chain(context* ctx, pod_chain* next) :pod_chain(ctx, next)
	{}

	virtual estid_t place_order(offset_type offset, direction_type direction, const code_t& code, uint32_t count, double_t price, order_flag flag) override;
};

//��֤
class verify_chain : public pod_chain
{

public:
	
	verify_chain(context* ctx) :pod_chain(ctx, nullptr)
	{}


	virtual estid_t place_order(offset_type offset, direction_type direction, const code_t& code, uint32_t count, double_t price, order_flag flag) override;


};