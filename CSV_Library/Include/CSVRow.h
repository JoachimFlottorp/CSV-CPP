#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

class CSVRow
{
public:
	CSVRow(std::vector<std::string> const& header, std::vector<std::string> const& row);

	std::string const& GetColumn(std::string const& column_name) const;

private:
	std::vector<std::string> header;
	std::vector<std::string> row;
};
