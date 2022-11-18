#pragma once
#include "define.h"

struct tick_info
{
	code_t id; //��ԼID

	time_t time; //ʱ��

	uint32_t tick; //������

	double_t price;  //pDepthMarketData->LastPrice

	double_t open;
	
	double_t close;

	double_t high;

	double_t low;

	double_t high_limit;

	double_t low_limit;

	double_t standard;

	uint32_t volume;

	uint32_t trading_day;

	std::array<std::pair<double_t, uint32_t>, 5> buy_order;
	std::array<std::pair<double_t, uint32_t>, 5> sell_order;

	double_t buy_price()const
	{
		if (buy_order.empty())
		{
			return 0;
		}
		return buy_order[0].first;
	}
	double_t sell_price()const
	{
		if (sell_order.empty())
		{
			return 0;
		}
		return sell_order[0].first;
	}
	tick_info()
		:time(0),
		tick(0),
		open(0),
		close(0),
		high(0),
		low(0),
		high_limit(0),
		low_limit(0),
		price(0),
		standard(0),
		volume(0),
		trading_day(0)
	{}


	int32_t total_buy_valume()const
	{
		int32_t reuslt = 0;
		for (auto& it : buy_order)
		{
			reuslt += it.second;
		}
		return reuslt;
	}

	int32_t total_sell_valume()const
	{
		int32_t reuslt = 0;
		for (auto& it : sell_order)
		{
			reuslt += it.second;
		}
		return reuslt;
	}
};

struct position_info
{
	code_t id; //��ԼID

	uint32_t long_postion;
	uint32_t short_postion;

	double_t	buy_price;
	double_t	sell_price;

	uint32_t long_frozen;
	uint32_t short_frozen;
	
	uint32_t get_total()const 
	{
		return long_postion + short_postion;
	}
	/*
		�ѱ�ռ�õ�
	*/
	uint32_t get_occupy()const
	{
		return long_postion + short_postion + long_frozen + short_frozen;
	}
	/**  
	* ������ʾ��֣�������ʾ�ղ�
	*/
	uint32_t get_real()const
	{
		return long_postion - short_postion;
	}

	uint32_t is_mepty()const
	{
		return long_postion == 0 && short_postion == 0;
	}

	position_info() :
		long_postion(0),
		short_postion(0),
		long_frozen(0),
		short_frozen(0)
	{}
};
const position_info default_position;

struct account_info
{
	double money;

	double frozen_monery;

	account_info() :
		money(0),
		frozen_monery(0)
	{}
};
const account_info default_account;

typedef enum trading_optimal
{
	TO_INVALID = 0,
	//��֤�����ţ����ƽ����ȡ��������Ʒ�֣�ƽת����
	TO_CLOSE_TO_OPEN = 1,
	//���������ţ���תƽ�����Խ�Լ��֤���������λ��
	TO_OPEN_TO_CLOSE = 2
} trading_optimal;



/*
 *	������־
 */
typedef enum order_flag
{
	OF_NOR = '0',		//��ͨ����
	OF_FAK,			//ȫ��ȫ�������ȴ��Զ�����
	OF_FOK,			//���ɲ��������ȴ��Զ�����
} order_flag;

/*
 *	��ƽ����
 */
typedef enum offset_type
{
	OT_OPEN = '0',	//����
	OT_CLOSE,		//ƽ��,����Ϊƽ��
} offset_type;

/*
 *	��շ���
 */
typedef enum direction_type
{
	DT_LONG = '0',	//����
	DT_SHORT,		//����
	DT_NET			//��
} direction_type;

struct order_info
{
	
	estid_t		est_id;

	code_t			code;

	std::string		unit_id ;

	uint32_t		total_volume;

	uint32_t		last_volume;

	time_t			create_time;

	offset_type		offset;

	direction_type	direction;

	order_flag		flag;

	double_t		price;

	order_info() :
		est_id(INVALID_ESTID),
		offset(OT_OPEN),
		direction(DT_LONG),
		total_volume(0),
		last_volume(0),
		create_time(0),
		price(.0f),
		flag(OF_NOR)
	{}

};
const order_info default_order ;

struct trade_info
{
public:
	trade_info()
	
	{}
	
	virtual ~trade_info() {}



protected:

	std::string		est_id;

	code_t			code;

	std::string		unit_id;

	time_t	trade_time;
	
	int		volume;
	
	double		price;
	
	double		amount;

};

//����ͳ������
struct order_statistic
{
	//�µ�����
	uint32_t place_order_amount;
	//ί������
	uint32_t entrust_amount;
	//�ɽ�����
	uint32_t trade_amount;
	//��������
	uint32_t cancel_amount;

};

const order_statistic default_statistic;