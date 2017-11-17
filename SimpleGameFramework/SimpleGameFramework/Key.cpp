#include "stdafx.h"
#include "Key.h"


Key::Key()
{
	GameFrameworkInstance.LoadImageResource(
		AppConfigInstance.GetResourcePath("Images/key.png"),
		"Key");

	imageID = "Key";
}


Key::~Key()
{
}
