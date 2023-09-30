#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <type_traits>

#include "CSVRow.h"
#include "CSVBinder.h"

#define CSV_BIND_METHOD void Bind(CSVBinder* binder)

#define CSV_BIND_MEMBER(member, column) binder->Bind(&member, column)

template <typename TBind>
using Trait_BindMethod = decltype(std::declval<TBind>().Bind(std::declval<CSVBinder*>()));

template <typename TBind>
using Trait_HasBindMethod = std::is_same<Trait_BindMethod<TBind>, void>;

class CSVReader
{
public:
	CSVReader(std::istream& inStream, char delm = ',');

	const CSVRow* ReadRow();

	template <typename TBind>
	std::enable_if_t<Trait_HasBindMethod<TBind>::value, void> BindRow(TBind& object)
	{
		auto row = ReadRowData();
		if (row.empty())
		{
			return;
		}

		auto binder = CSVBinder(CSVRow(header, row));
		object.Bind(&binder);
	}

	const bool IsEOF() const;

	std::vector<std::string> GetHeaderDefinition() const { return header; }
private:
	void LoadHeaderData();

	// helper
	std::vector<std::string> ReadRowData();

private:
	// Input source
	std::istream& inStream;

	char delimeter;
	std::vector<std::string> header;
};
