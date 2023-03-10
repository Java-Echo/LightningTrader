#pragma once
#include "define.h"
#include "data_types.hpp"


#define LIGHTNING_VERSION 0.2.0


enum context_type
{
	CT_INVALID,
	CT_RUNTIME,
	CT_EVALUATE
};

struct ltobj
{
	void* obj_ptr;

	context_type obj_type;

	//ltobj(context_type type):obj_type(type), obj_ptr(nullptr) {}
};

extern "C"
{
#define VOID_DEFAULT

#define LT_INTERFACE_DECLARE(return_type, func_name, args) EXPORT_FLAG return_type lt_##func_name args

#define LT_INTERFACE_CHECK(object_name, default_return) \
	if (lt.obj_type != CT_RUNTIME && lt.obj_type != CT_EVALUATE)\
	{\
		return default_return; \
	}\
	object_name* c = (object_name*)(lt.obj_ptr); \
	if (c == nullptr)\
	{\
		return default_return; \
	}

#define LT_INTERFACE_CALL(func_name, args) return c->func_name args;

#define LT_INTERFACE_IMPLEMENTATION(return_type ,default_return, object_name ,func_name, formal_args, real_args) return_type lt_##func_name formal_args\
{\
LT_INTERFACE_CHECK(object_name,default_return)\
LT_INTERFACE_CALL(func_name,real_args)\
}

	typedef void (PORTER_FLAG * tick_callback)(const tick_info&);

	typedef void (PORTER_FLAG * entrust_callback)(const order_info&);

	typedef void (PORTER_FLAG * deal_callback)(estid_t, uint32_t , uint32_t);

	typedef void (PORTER_FLAG * trade_callback)(estid_t, const code_t&, offset_type, direction_type, double_t, uint32_t);

	typedef void (PORTER_FLAG * cancel_callback)(estid_t, const code_t&, offset_type, direction_type, double_t, uint32_t, uint32_t);

	typedef bool (PORTER_FLAG * condition_callback)(estid_t, const tick_info&);

	typedef void (PORTER_FLAG * error_callback)(error_type , estid_t, uint32_t);

	typedef void (PORTER_FLAG * ready_callback)();

	typedef bool (PORTER_FLAG * filter_callback)(const code_t& code, offset_type offset, direction_type direction, uint32_t count, double_t price, order_flag flag);

	EXPORT_FLAG ltobj lt_create_context(context_type ctx_type, const char* config_path);
	
	EXPORT_FLAG void lt_destory_context(ltobj& obj);
	
	/*����*/
	LT_INTERFACE_DECLARE(void, start_service, (const ltobj&));
	
	/*ֹͣ*/
	LT_INTERFACE_DECLARE(void, stop_service, (const ltobj&));
	
	/*
	�µ�
	*/
	LT_INTERFACE_DECLARE(estid_t, place_order, (const ltobj&, untid_t, offset_type, direction_type, const code_t&, uint32_t, double_t, order_flag));
	
	/*
	* ��������
	*/
	LT_INTERFACE_DECLARE(void, cancel_order, (const ltobj&, estid_t));

	/**
	* ��ȡ��λ��Ϣ
	*/
	LT_INTERFACE_DECLARE(const position_info&, get_position, (const ltobj&, const code_t&));

	/**
	* ��ȡ�˻��ʽ�
	*/
	LT_INTERFACE_DECLARE(const account_info&, get_account, (const ltobj&));

	/**
	* ��ȡί�ж���
	**/
	LT_INTERFACE_DECLARE(const order_info&, get_order, (const ltobj&, estid_t));
	
	/**
	* ��������
	**/
	LT_INTERFACE_DECLARE(void, subscribe, (const ltobj&, const code_t&));
	
	/**
	* ȡ����������
	**/
	LT_INTERFACE_DECLARE(void, unsubscribe, (const ltobj&, const code_t&));

	/**
	* ��ȡʱ��
	*
	*/
	LT_INTERFACE_DECLARE(time_t, get_last_time, (const ltobj&));
	
	/*
	* ���ó�������
	*/
	LT_INTERFACE_DECLARE(void, set_cancel_condition, (const ltobj&, estid_t, condition_callback));

	/*
	* ���ý��׹�����
	*/
	LT_INTERFACE_DECLARE(void, set_trading_filter, (const ltobj&, filter_callback));
	
	/*
	* �󶨻ص� 
	*/
	LT_INTERFACE_DECLARE(void, bind_callback, (const ltobj&, tick_callback, entrust_callback, deal_callback 
		, trade_callback, cancel_callback, error_callback, ready_callback));
	
	/**
	* ������ʷ����
	*
	*/
	LT_INTERFACE_DECLARE(void, playback_history, (const ltobj& , uint32_t));
	
	/**
	* ��ȡ���һ���µ�ʱ��
	*	�罻���շ���0
	*/
	LT_INTERFACE_DECLARE(time_t, last_order_time, (const ltobj&));
	
	/**
	* ��ȡ��ǰ�����յĶ���ͳ��
	*	�罻���ջᱻ���
	*/
	LT_INTERFACE_DECLARE(const order_statistic&, get_order_statistic, (const ltobj&));

	/**
	* ��ȡ�û�����ָ��
	*/
	LT_INTERFACE_DECLARE(void*, get_userdata, (const ltobj& , uint32_t, size_t));

	/**
	* �Ƿ��ڽ�����
	*/
	LT_INTERFACE_DECLARE(bool, is_trading_ready, (const ltobj&));
	
	/**
	* ��ȡ������
	*/
	LT_INTERFACE_DECLARE(uint32_t, get_trading_day, (const ltobj&));

	/**
	* ��ȡ����ʱ��
	*/
	LT_INTERFACE_DECLARE(time_t, get_close_time, (const ltobj&));

	/**
	* ʹ���Զ��彻��ͨ��
	*/
	LT_INTERFACE_DECLARE(void, use_custom_chain, (const ltobj&, untid_t, trading_optimal, bool));


	/**
	* ���Ʋ���Ϣ
	*/
	LT_INTERFACE_DECLARE(void, bind_transfer_info, (const ltobj&, const code_t&, const code_t& , double_t ));
}
