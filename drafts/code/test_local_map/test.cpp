#include "pch.h"

TEST(TestGetCentredMap, StandardCases) 
{
	IntMatrix matrix;

	for (int i = 0; i < 4; ++i)
	{
		std::vector<int> line;

		for (int j = 0; j < 4; ++j)
			line.push_back(i + j);

		matrix.push_back(line);
	}

	Map map(matrix);

	IntMatrix local1 = map.getCentredLocalMap({ 0, 0 }, 2, 2);
	IntMatrix answer1 = { {0, 1}, {1, 2} };

	IntMatrix local2 = map.getCentredLocalMap({ 2, 1 }, 2, 2);
	IntMatrix answer2 = { {0, 1, 2}, {1, 2, 3}, {2, 3, 4}, {3, 4, 5} };

	IntMatrix local3 = map.getCentredLocalMap({ 5, 8 }, 2, 2);
	IntMatrix answer3;

	IntMatrix local4 = map.getCentredLocalMap({ 1, 2 }, 0, 0);

	IntMatrix local5 = map.getCentredLocalMap({2, 2}, 2, 3 );

	ASSERT_EQ(local1, answer1);
	ASSERT_EQ(local2, answer2);
	ASSERT_EQ(local3, answer3);
	ASSERT_EQ(local4, answer3);
	ASSERT_EQ(local5, matrix);
}


TEST(TestGetLocalMap, StandardCases)
{
	IntMatrix matrix;

	for (int i = 0; i < 4; ++i)
	{
		std::vector<int> line;

		for (int j = 0; j < 4; ++j)
			line.push_back(i + j);

		matrix.push_back(line);
	}

	Map map(matrix);

	IntMatrix local1 = map.getLocalMap({ 0, 0 }, 1, 2, 1, 3);
	IntMatrix answer1 = { {0, 1, 2} };

	IntMatrix local2 = map.getLocalMap({ 2, 1 }, 1, 1, 0, 3);
	IntMatrix answer2 = { {2, 3, 4}, {3, 4, 5} };

	IntMatrix local3 = map.getLocalMap({ 5, 8 }, 2, 2, 2, 2);
	IntMatrix answer3;

	IntMatrix local4 = map.getLocalMap({ 1, 2 }, 0, 0, 0, 0);

	IntMatrix local5 = map.getLocalMap({ 2, 2 }, 2, 2, 2, 2);

	IntMatrix local6 = map.getLocalMap({ 3, 3 }, 1, 0, 0, 1);
	IntMatrix answer6 = { {6} };

	ASSERT_EQ(local1, answer1);
	ASSERT_EQ(local2, answer2);
	ASSERT_EQ(local3, answer3);
	ASSERT_EQ(local4, answer3);
	ASSERT_EQ(local5, matrix);
	ASSERT_EQ(local6, answer6);
}
