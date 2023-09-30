#pragma once
#include <string>

#include "CSVRow.h"

class CSVBinder
{
public:
	// TODO: CSV binder gains ownership here. Is this a memory leak?
	CSVBinder(CSVRow row) : row(row) {}

	// Don't like this, but it works for now.
	void Bind(std::string* a, const char* column)
	{
		a->assign(row.GetColumn(column));
	};

	void Bind(int32_t* a, const char* column)
	{
		*a = std::stoi(row.GetColumn(column));
	};

	void Bind(uint32_t* a, const char* column)
	{
		*a = std::stoul(row.GetColumn(column));
	};

	void Bind(float* a, const char* column)
	{
		*a = std::stof(row.GetColumn(column));
	};

private:
	CSVRow row;
};
