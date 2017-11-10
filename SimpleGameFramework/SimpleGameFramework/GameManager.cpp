#include "stdafx.h"
#include "GameManager.h"
#include "Wall.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

GameManager& GameManager::Instance()
{
	static GameManager instance;

	return instance;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::BeginPlay()
{
	////////////////////////////////////////////////////////////////////////////////
	// Begin example code

	// Load the image file Untitled.png from the Images folder. Give it the unique name of Image1
	GameFrameworkInstance.LoadImageResource(
		AppConfigInstance.GetResourcePath("Images/wall.png"), 
		"Art");

	objectPtr = new GameObject();
	objectPtr->location = Vector2i(100, 100);

	// End example code
	////////////////////////////////////////////////////////////////////////////////

	// Load level on start
	std::ifstream loadFile("level.csv");
	std::string value;
	while (loadFile.good()) {
		getline(loadFile, value, ',');
		if (value == "1") {
			// Creates new gameobject at 0,0 in corner
			GameObject* newObjectPtr = new GameObject();

			newObjectPtr->location = 0;

			levelObjects.push_back(newObjectPtr);
		}
	}
}

void GameManager::EndPlay()
{
	// Save file type
	std::ofstream saveFile("level.csv");

	// Entries in file
	saveFile << "1, 1, 1, 1, 1, 1, 1, 1" << std::endl;
	saveFile << "0, 1, 0, 0, 0, 0, 0, 1" << std::endl;
	saveFile << "0, 1, 1, 1, 1, 1, 1, 1" << std::endl;

	saveFile.close();

	delete objectPtr;
}

void GameManager::Update(double deltaTime)
{

}

void GameManager::Render(Gdiplus::Graphics& canvas, const CRect& clientRect)
{
	// Save the current transformation of the scene
	Gdiplus::Matrix transform;
	canvas.GetTransform(&transform);

	canvas.TranslateTransform((Gdiplus::REAL) levelOffset.X,
							  (Gdiplus::REAL) levelOffset.Y);

	// draw all of the level objects
	for (GameObject* objToDraw : levelObjects)
	{
		objToDraw->Draw(canvas);
	}

	// Restore the transformation of the scene
	canvas.SetTransform(&transform);

	// Draw UI here so it doesn't move! 
}

void GameManager::LeftButtonDown(const Vector2i & point)
{
	Vector2i snappedLocation;
	snappedLocation.X = 32 * ((point.X - levelOffset.X) / 32);
	snappedLocation.Y = 32 * ((point.Y - levelOffset.Y) / 32);
	DebugLog("Snapped location is " << snappedLocation.X << "," << snappedLocation.Y);

	// check if we've clicked on any level object
	GameObject* foundObject = nullptr;
	for (GameObject* objToTest : levelObjects)
	{
		// construct our bounds for the click
		// NOTE: these values are hacky!
		// please please please use proper ones

		AABBi bounds(objToTest->location-Vector2i(16, 16),
			objToTest->location + Vector2i(16, 16));

		// did we click in the bounds of the object?
		if (bounds.Contains(snappedLocation))
		{
			foundObject = objToTest;
			break;
		}
	}

	// clicked on a thing?
	if (foundObject)
	{
		levelObjects.remove(foundObject);
		delete foundObject;
		return;
	}

	GameObject* newObjectPtr = new GameObject();

	newObjectPtr->location = snappedLocation;

	levelObjects.push_back(newObjectPtr);
}

void GameManager::MovementHappened(const Vector2i & input)
{
	levelOffset -= input;
}
