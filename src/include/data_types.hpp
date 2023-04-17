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

	double_t open_interest;

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
		trading_day(0),
		open_interest(.0F)
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

typedef enum deal_direction
{
	DD_DOWN = -1,	//����
	DD_FLAT = 0,	//ƽ
	DD_UP = 1,		//����
}deal_direction;

typedef enum deal_status
{
	DS_INVALID,
	DS_DOUBLE_OPEN, //˫��
	DS_OPEN,		//����
	DS_CHANGE,		//����
	DS_CLOSE,		//ƽ��
	DS_DOUBLE_CLOSE,//˫ƽ

}deal_status;

struct deal_info
{
	//����
	uint32_t	volume_delta;
	//����
	double_t	interest_delta;
	//����
	deal_direction	direction;

	deal_info() :
		volume_delta(0),
		interest_delta(.0F),
		direction(DD_FLAT)
	{}

	deal_status get_status()
	{
		if(volume_delta == interest_delta && interest_delta > 0)
		{
			return DS_DOUBLE_OPEN;
		}
		if (volume_delta > interest_delta && interest_delta > 0)
		{
			return DS_OPEN;
		}
		if (volume_delta > interest_delta && interest_delta == 0)
		{
			return DS_CHANGE;
		}
		if (volume_delta > -interest_delta && -interest_delta > 0)
		{
			return DS_CLOSE;
		}
		if (volume_delta == -interest_delta && -interest_delta > 0)
		{
			return DS_DOUBLE_CLOSE;
		}
	}
};
struct position_item
{
	//��λ
	uint32_t	postion;
	//�۸�
	double_t	price;
	//����
	uint32_t	frozen;

	position_item() :
		postion(0),
		price(.0F),
		frozen(0)
	{}

	uint32_t usable()const
	{
		return postion - frozen;
	}

	bool empty()const
	{
		return postion == 0;
	}

	void clear()
	{
		postion = 0;
		price = .0F;
		frozen = 0 ;
	}
};

struct position_info
{
	code_t id; //��ԼID
	position_info(const code_t& code) :id(code) {}
	//���
	position_item today_long;
	position_item today_short;


	//���
	position_item yestoday_long;
	position_item yestoday_short;

	bool empty()const
	{
		return today_long.empty()&& today_short.empty()&& yestoday_long.empty()&& yestoday_short.empty();
	}

	uint32_t get_total()const 
	{
		return today_long.postion + today_short.postion + yestoday_long.postion + yestoday_short.postion;
	}

	uint32_t get_long_position()const
	{
		return today_long.postion+ yestoday_long.postion;
	}

	uint32_t get_short_position()const
	{
		return today_short.postion + yestoday_short.postion;
	}
	uint32_t get_long_frozen()const
	{
		return today_long.frozen + yestoday_long.frozen;
	}

	uint32_t get_short_frozen()const
	{
		return today_short.frozen + yestoday_short.frozen;
	}
	position_info()
	{}
};
const position_info default_position;

struct account_info
{
	double money;

	double frozen_monery;

	account_info() :
		money(.0F),
		frozen_monery(.0F)
		
	{}
};
const account_info default_account;



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
	OT_CLOSE		//ƽ��,����Ϊƽ��
} offset_type;

/*
 *	��շ���
 */
typedef enum direction_type
{
	DT_LONG = '0',	//����
	DT_SHORT		//����
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

	double_t		price;

	order_info() :
		est_id(INVALID_ESTID),
		offset(OT_OPEN),
		direction(DT_LONG),
		total_volume(0),
		last_volume(0),
		create_time(0),
		price(.0f)
	{}

	bool is_valid()
	{
		return est_id != INVALID_ESTID;
	}

	
};
const order_info default_order ;


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
	//��������
	uint32_t error_amount;

	order_statistic():
		place_order_amount(0),
		entrust_amount(0),
		trade_amount(0),
		cancel_amount(0),
		error_amount(0)
	{}

};

const order_statistic default_statistic;


struct transfer_info
{
	code_t expire_code;
	double_t price_offset;

	transfer_info() :price_offset(.0F)
	{}

	transfer_info(const code_t expire, double_t offset) :expire_code(expire), price_offset(offset)
	{}

	bool operator == (const transfer_info& other)const
	{
		return expire_code == other.expire_code;
	}
	bool operator != (const transfer_info& other)const
	{
		return expire_code != other.expire_code;
	}
};
const transfer_info default_transfer;

typedef enum error_type
{
	ET_PLACE_ORDER,
	ET_CANCEL_ORDER,
	ET_OTHER_ERROR
}error_type;