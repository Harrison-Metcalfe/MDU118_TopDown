#include "stdafx.h"
#include "GameManager.h"

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
		AppConfigInstance.GetResourcePath("Images/Untitled.png"), 
		"Art");

	objectPtr = new GameObject();
	objectPtr->location = Vector2i(100, 100);

	// End example code
	////////////////////////////////////////////////////////////////////////////////
}

void GameManager::EndPlay()
{
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

	objectPtr->Draw(canvas);

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
	snappedLocation.X = 20 * ((point.X - levelOffset.X) / 20);
	snappedLocation.Y = 20 * ((point.Y - levelOffset.Y) / 20);

	// check if we've clicked on any level object
	GameObject* foundObject = nullptr;
	for (GameObject* objToTest : levelObjects)
	{
		// construct our bounds for the click
		// NOTE: these values are hacky!
		// please please please use proper ones

		AABBi bounds(objToTest->location-Vector2i(10, 10),
			objToTest->location + Vector2i(10, 10));

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
