#include "stdafx.h"
#include "MiddleStage.h"

void MiddleStage::init(Image * background, float bgScale)
{
	Stage::init(background, bgScale);
}

void MiddleStage::enter()
{

}

void MiddleStage::exit()
{
	Stage::exit();
}

Stage * MiddleStage::update()
{
	return nullptr;
}

void MiddleStage::render()
{

}
