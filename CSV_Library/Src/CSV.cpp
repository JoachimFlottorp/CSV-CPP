#include "CSV.h"

CSVRow::CSVRow(std::vector<std::string> const& header, std::vector<std::string> const& row)
	: header(header), row(row)
{}

std::string const& CSVRow::GetColumn(std::string const& column_name) const
{
	// find the column name in the header
	auto it = std::find(header.begin(), header.end(), column_name);
	if (it == header.end())
	{
		return "";
	}

	// find the index of the column
	auto index = std::distance(header.begin(), it);

	// return the column
	return row[index];
}


CSVReader::CSVReader(std::istream& inStream, char delm)
	: inStream(inStream), delimeter(delm)
{
	LoadHeaderData();
}

const CSVRow* CSVReader::ReadRow()
{
	auto row = ReadRowData();

	if (row.empty())
	{
		return nullptr;
	}

	return new CSVRow(header, row);
}

const bool CSVReader::IsEOF() const
{
	return inStream.eof();
}

void CSVReader::LoadHeaderData()
{
	auto h = ReadRowData();
	for (auto const& column_name : h)
	{
		header.push_back(column_name);
	}
}

std::vector<std::string> CSVReader::ReadRowData()
{
	constexpr char QUOTE = '"';

	std::vector<std::string> row = {};

	std::string line;
	std::getline(inStream, line);

	if (inStream.eof() && line.empty())
	{
		return row;
	}

	std::string cell;
	for (auto it = line.begin(); it != line.end(); ++it)
	{
		char c = *it;

		if (c == QUOTE)
		{
			++it;
			while (it != line.end() && *it != QUOTE)
			{
				cell.push_back(*it);
				++it;
			}
			continue;
		}
		else if (c == delimeter)
		{
			if (cell.empty())
			{
				continue;
			}
			row.push_back(cell);
			cell.clear();
			continue;
		}

		cell.push_back(c);

	}
	row.push_back(cell);

	return row;
}
