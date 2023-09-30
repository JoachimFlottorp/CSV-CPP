#include "CSV.h"

CSVRow::CSVRow(std::vector<std::string> const& header, std::vector<std::string> const& row)
	: header(header), row(row)
{
	if (header.size() != row.size())
	{
		throw std::runtime_error("header and row size mismatch");
	}
}

std::string const& CSVRow::GetColumn(std::string const& column_name) const
{
	// find the column name in the header
	auto it = std::find(header.begin(), header.end(), column_name);
	if (it == header.end())
	{
		throw std::runtime_error("column not found");
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
	std::vector<std::string> row = {};

	std::string line;
	std::getline(inStream, line);

	if (inStream.eof() && line.empty())
	{
		return row;
	}

	std::string cell;
	for (char c : line)
	{
		if (c == delimeter)
		{
			row.push_back(cell);
			cell.clear();
		}
		else
		{
			cell += c;
		}
	}
	row.push_back(cell);

	return row;
}