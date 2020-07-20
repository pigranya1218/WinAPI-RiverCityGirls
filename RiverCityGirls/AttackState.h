#pragma once
#include "Kyoko.h"

class AttackState
{
public:
	virtual AttackState* update(Kyoko& Kyoko);
	virtual void render(Kyoko& Kyoko);
};


