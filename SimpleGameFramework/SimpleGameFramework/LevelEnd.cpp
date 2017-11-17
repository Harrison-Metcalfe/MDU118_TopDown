#include "stdafx.h"
#include "LevelEnd.h"


LevelEnd::LevelEnd()
{
	GameFrameworkInstance.LoadImageResource(
		AppConfigInstance.GetResourcePath("Images/end.png"),
		"End");

	imageID = "End";
}


LevelEnd::~LevelEnd()
{
}

void LevelEnd::LevelFinish()
{
}
