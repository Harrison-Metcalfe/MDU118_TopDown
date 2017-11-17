#include "stdafx.h"
#include "Wall.h"


Wall::Wall()
{
	// Load the image file wall.png from the Images folder. Give it the unique name of Wall
	GameFrameworkInstance.LoadImageResource(
		AppConfigInstance.GetResourcePath("Images/wall.png"),
		"Art");

	imageID = "Wall";
}


Wall::~Wall()
{
}

void Wall::Block()
{
}
