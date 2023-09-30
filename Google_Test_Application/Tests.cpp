#include "gtest/gtest.h"

#include <CSV.h>

#include <sstream>

#define X Tests

#define EX_HEADER(...) std::vector<std::string>({__VA_ARGS__})

TEST(X, Basic_With_Header) {
	std::istringstream input("One,Two\n1,2");

	CSVReader reader(input);

	EXPECT_EQ(EX_HEADER("One", "Two"), reader.GetHeaderDefinition());

	auto row = reader.ReadRow();

	ASSERT_NE(nullptr, row);
	ASSERT_EQ(2, row->Size());
	EXPECT_EQ("1", row->GetColumn("One"));

	row = reader.ReadRow();

	ASSERT_EQ(nullptr, row);
}

TEST(X, Can_Escape_Delimiter) {
	std::istringstream input("One,Two\n1,\"2,3\"");

	CSVReader reader(input);

	auto row = reader.ReadRow();

	ASSERT_NE(nullptr, row);
	ASSERT_EQ(2, row->Size());
	EXPECT_EQ("1", row->GetColumn("One"));
	EXPECT_EQ("2,3", row->GetColumn("Two"));

	row = reader.ReadRow();

	ASSERT_EQ(nullptr, row);
}