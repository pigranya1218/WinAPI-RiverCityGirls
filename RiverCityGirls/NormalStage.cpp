#include "stdafx.h"
#include "NormalStage.h"

void NormalStage::init(Image * background, float bgScale)
{
	Stage::init(background, bgScale);
}

void NormalStage::enter()
{
}

void NormalStage::exit()
{
}

Stage * NormalStage::update()
{
	return nullptr;
}

void NormalStage::render()
{
	Stage::render();

	// TODO :: 적들 그리기

}
