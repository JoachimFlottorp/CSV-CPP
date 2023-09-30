#include "CSV.h"
#include "CSVBinder.h"

#include <iostream>
#include <assert.h>

#define PRINT_BEGIN(name) \
std::cout << "========== " << name << " ==========" << std::endl << std::endl << std::endl;

#define PRINT_END \
std::cout << std::endl << std::endl;

struct MyRow
{
	int one;
	std::string two;
	std::string three;

	CSV_BIND_METHOD
	{
		CSV_BIND_MEMBER(one, "One");
		CSV_BIND_MEMBER(two, "Two");
		CSV_BIND_MEMBER(three, "Three");
	};

	void Print()
	{
		std::cout << "One: " << one << ", Two: " << two << ", Three: " << three << std::endl;
	}
};

std::ifstream File()
{
	std::string path("Data\\One.csv");
	std::cout << "Reading " << path << std::endl;

	std::ifstream in(path);

	assert(in.is_open());

	return std::move(in);
}

void ReadRow()
{
	PRINT_BEGIN("Read Row Method");

	std::ifstream in = File();

	CSVReader reader(in);

	std::vector<std::string> cols = { "One", "Two", "Three" };

	{
		std::cout << "---- Header ----" << std::endl;
		auto row = reader.GetHeaderDefinition();
		for (auto const& col : cols)
		{
			std::cout << col << "\t";
		}

		std::cout << std::endl << std::endl;;
	}

	std::cout << "---- Body ----" << std::endl;

	while (true)
	{
		auto row = reader.ReadRow();

		if (row == nullptr)
		{
			break;
		}

		for (auto const& col : cols)
		{
			std::cout << row->GetColumn(col) << "\t";
		}
		std::cout << std::endl;
	}

	PRINT_END;
}

void StructBind()
{
	PRINT_BEGIN("Struct Bind Method");

	std::ifstream in = File();

	CSVReader reader(in);

	do
	{
		MyRow row{};

		reader.BindRow(row);

		row.Print();

	} while (!reader.IsEOF());

	PRINT_END;
}

int main()
{
	ReadRow();
	StructBind();

	return 0;
}