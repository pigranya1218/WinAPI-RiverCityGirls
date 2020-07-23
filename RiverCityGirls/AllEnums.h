#pragma once

enum class OBJECT_TEAM : int
{
	PLAYER,
	ENEMY,
	OBJECT
};

enum class DIRECTION : int
{
	RIGHT,
	LEFT
};

enum class ATTACK_TYPE : int
{
	HIT,
	KNOCKDOWN
};

enum class DEBUG_TYPE : int
{
	PLAYER = 0,
	ENEMY = 1,
	OBJECT = 2,
	STAGE = 3,
	END = 4
};