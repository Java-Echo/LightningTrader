#pragma once
#include <string>

class dll_mgr
{
	/*
	* ���� dll ģ��
	*/
	virtual bool load(const std::string& file_name) = 0;

	/*
	 *	ж��
	 */
	virtual void unload() = 0;
};