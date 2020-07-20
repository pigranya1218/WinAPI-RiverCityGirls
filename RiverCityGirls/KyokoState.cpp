#include "stdafx.h"
#include "KyokoState.h"


void KyokoState::imageEnter(Kyoko & Kyoko)
{
}

//State 부모클래스
KyokoState * KyokoState::update(Kyoko & Kyoko)
{
	return nullptr;
}

void KyokoState::render(Kyoko & Kyoko)
{
}

void IdleState::imageEnter(Kyoko & Kyoko)
{
}

KyokoState * IdleState::update(Kyoko & Kyoko)
{
	return nullptr;
}

void IdleState::render(Kyoko & Kyoko)
{
}

void WalkState::imageEnter(Kyoko & Kyoko)
{
}

KyokoState * WalkState::update(Kyoko & Kyoko)
{
	return nullptr;
}

void WalkState::render(Kyoko & Kyoko)
{
}

void RunningState::imageEnter(Kyoko & Kyoko)
{
}

KyokoState * RunningState::update(Kyoko & Kyoko)
{
	return nullptr;
}

void RunningState::render(Kyoko & Kyoko)
{
}
