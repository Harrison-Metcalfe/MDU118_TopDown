#include "stdafx.h"
#include "GameManager.h"
#include "Wall.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>

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
	std::string line;

	if (loadFile.good()) {
		while (std::getline(loadFile, line)) {
			std::stringstream lineStream(line);
			std::string cell;
			std::vector<int> row;

			while (std::getline(lineStream, cell, ',')) {
				row.push_back(std::stoi(cell));
			}

			data.push_back(row);
		}
	}

	std::vector<std::vector<std::string>>::size_type row; 
	std::vector<std::string>::size_type cell; 
	for (row = 0; row != data.size(); row++) {
		for (cell = 0; cell != data[row].size(); cell++) {
			if (data[row][cell] == 0) {
				continue;
			}
			GameObject* newObjectPtr = new GameObject();

			newObjectPtr->location = Vector2i(cell * 32, row * 32);

			levelObjects.push_back(newObjectPtr);
		}
	}
}

void GameManager::EndPlay()
{
	// Save file type
	std::ofstream saveFile("level.csv");

	// Entries in file
	for (size_t row = 0; row != data.size(); row++) {

		std::ostringstream stream;

		//Copy all the elements from the beginning of the array, to the end of the array
		//Then dumps all the elements to the "stream" parameter with the delimeter of "," in between each element
		std::copy(data[row].begin(), data[row].end(), std::ostream_iterator<int>(stream, ","));

		std::string rowStr = stream.str(); //Convert the stream to an actual string that can be used
		stream.clear();

		rowStr.erase(rowStr.length() - 1); //Clean up the last trailing ","

		saveFile << rowStr << std::endl; //Write it to the file
	}

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
		// Get foundObject X and Y
		int foundObjectX = snappedLocation.X / 32;
		int foundObjectY = snappedLocation.Y / 32;

		// find the entry in the 2D array that corresponds to that (Y is the row, X is the column)
		DebugLog(snappedLocation.X / 32 << "," << snappedLocation.Y / 32);
		
		data[foundObjectY][foundObjectX] = 0; // Set that entry to 0

		levelObjects.remove(foundObject);
		delete foundObject;
		return;
	}

	//Use the snapped location and work out the index coordinates for the csv
	Vector2i indexCoords = Vector2i(snappedLocation.X / 32, snappedLocation.Y / 32);

	GameObject* newObjectPtr = new GameObject();

	newObjectPtr->location = snappedLocation;

	levelObjects.push_back(newObjectPtr);

	//Code for adding to the 2D array
	//Figure out the last index of the cell on the appropriate row
	if (indexCoords.Y < (int)data.size()) {
		//The row already exists in the array
		std::vector<int> cells = data[indexCoords.Y];
		int lastInd = cells.size() - 1; //Last index
		DebugLog(lastInd);

		if (indexCoords.X > lastInd) {
			//Work out the difference between the index of the new object and the last element
			int diff = std::abs(indexCoords.X - lastInd); 
			DebugLog(diff);

			//Pad out the array based on the difference
			for (int i = 0; i < diff; i++) cells.push_back(0); //0 = Empty/Void
			DebugLog(cells.size());
		}

		cells[indexCoords.X] = 1; //1 = Wall
		data[indexCoords.Y] = cells;
	}
	else {
		//The row doesn't exist in the array -> Work out the difference
		DebugLog(data.size() - 1);
		int rowDiff = std::abs(indexCoords.Y - ((int)data.size() - 1));
		DebugLog(rowDiff);
		DebugLog(data.size());

		//Pad out the array again
		for (int i = 0; i < rowDiff; i++) data.push_back(std::vector<int>{ 0 });
		std::vector<int> cells = data[data.size() - 1];
		DebugLog(data.size());

		int cellDiff = std::abs(indexCoords.X - ((int)cells.size() - 1)); //Seems to be always one cell off, so adding one just in case
		for (int i = 0; i < cellDiff; i++) cells.push_back(0);
		DebugLog(cellDiff);

		DebugLog(indexCoords.X);
		DebugLog(cells.size());
		cells[cells.size() - 1] = 1;
		data[indexCoords.Y] = cells;
	}
}

void GameManager::MovementHappened(const Vector2i & input)
{
	levelOffset -= input;
}
