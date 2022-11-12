#include "define.h"
#include "data_types.hpp"


#define LIGHTNING_VERSION 0.0.1

extern "C"
{
	typedef void (PORTER_FLAG * on_tick_callback)(const tick_info*);

	typedef void (PORTER_FLAG * on_entrust_callback)(estid_t);

	typedef void (PORTER_FLAG * on_deal_callback)(estid_t, uint32_t , uint32_t);

	typedef void (PORTER_FLAG * on_trade_callback)(estid_t, code_t, offset_type, direction_type, double_t, uint32_t);

	typedef void (PORTER_FLAG * on_cancel_callback)(estid_t, code_t, offset_type, direction_type, double_t, uint32_t, uint32_t);

	typedef bool (PORTER_FLAG * on_condition_callback)(const tick_info*);

	EXPORT_FLAG ltobj* create_runtime_context(const char* config_path);

	EXPORT_FLAG void destory_runtime_context(ltobj* ctx);

	EXPORT_FLAG ltobj* create_evaluate_context(const char* config_path);

	EXPORT_FLAG void destory_evaluate_context(ltobj* ctx);

	/*����*/
	EXPORT_FLAG void start(ltobj* ctx);

	/*ֹͣ*/
	EXPORT_FLAG void stop(ltobj* ctx);

	/*
	�µ�
	*/
	EXPORT_FLAG estid_t place_order(ltobj* ctx,offset_type offset, direction_type direction, code_t code, uint32_t count, double_t price, order_flag flag);

	/*
	* ��������
	*/
	EXPORT_FLAG void cancel_order(ltobj* ctx,estid_t order_id);

	/*
	* ���ý��׹���
	*/
	EXPORT_FLAG void set_trading_optimize(ltobj* ctx, uint32_t max_position, trading_optimal opt, bool flag);

	/**
	* ��ȡ��λ��Ϣ
	*/
	EXPORT_FLAG const position_info* get_position(ltobj* ctx, code_t code) ;

	/**
	* ��ȡ�˻��ʽ�
	*/
	EXPORT_FLAG const account_info* get_account(ltobj* ctx) ;

	/**
	* ��ȡί�ж���
	**/
	EXPORT_FLAG const order_info* get_order(ltobj* ctx, estid_t order_id) ;


	/**
	* ��������
	**/
	EXPORT_FLAG void subscribe(ltobj* ctx, code_t code);

	/**
	* ȡ����������
	**/
	EXPORT_FLAG void unsubscribe(ltobj* ctx, code_t code);

	/**
	* ��ȡʱ��
	*
	*/
	EXPORT_FLAG time_t get_last_time(ltobj* ctx);

	/*
	* ���ó�������
	*/
	EXPORT_FLAG void set_cancel_condition(ltobj* ctx, estid_t order_id, on_condition_callback callback);
}
