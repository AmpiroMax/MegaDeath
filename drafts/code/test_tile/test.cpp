#include "pch.h"


TEST(TestTile, TestIsKnown)
{
	Tile tile1; 
	ASSERT_FALSE(tile1.isKnown());
	
	Tile tile2(0xFFFC);
	ASSERT_FALSE(tile2.isKnown());

	Tile tile3(0x15E8);
	ASSERT_FALSE(tile3.isKnown());

	Tile tile4(0x000F);
	ASSERT_TRUE(tile4.isKnown());

	Tile tile5(0x8FAA);
	ASSERT_TRUE(tile5.isKnown());

	Tile tile6(0x5BD6);
	ASSERT_TRUE(tile6.isKnown());
}


TEST(TestTile, TestIsPassible)
{
	Tile tile1;
	ASSERT_FALSE(tile1.isPassible());

	Tile tile2(0x7FFC);
	ASSERT_FALSE(tile2.isPassible());

	Tile tile3(0x15E8);
	ASSERT_FALSE(tile3.isPassible());

	Tile tile4(0xA00F);
	ASSERT_TRUE(tile4.isPassible());

	Tile tile5(0x8FAA);
	ASSERT_TRUE(tile5.isPassible());

	Tile tile6(0xFBD6);
	ASSERT_TRUE(tile6.isPassible());
}


TEST(TestTile, TestGetTextureId)
{
	Tile tile1;
	ASSERT_EQ(0, tile1.getTextureId());

	Tile tile2(TEXTURE_ID_MASK);
	ASSERT_EQ(0x03FF, tile2.getTextureId());

	Tile tile3(0x8FAA);
	ASSERT_EQ(0x007D, tile3.getTextureId());

	Tile tile4(0xA00F);
	ASSERT_EQ(0x0100, tile4.getTextureId());
}


TEST(TestTile, TestIlluminationLevel)
{
	Tile tile1;
	ASSERT_EQ(0, tile1.getIlluminationLevel());

	Tile tile2(ILLUMINATION_MASK);
	ASSERT_EQ(7, tile2.getIlluminationLevel());

	Tile tile3(0x8FAA);
	ASSERT_EQ(2, tile3.getIlluminationLevel());

	Tile tile4(0xA00F);
	ASSERT_EQ(3, tile4.getIlluminationLevel());
}
