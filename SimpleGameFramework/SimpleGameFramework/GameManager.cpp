#include "stdafx.h"
#include "GameManager.h"
#include "Wall.h"
#include "Door.h"
#include "Enemy.h"
#include "Player.h"
#include "Key.h"
#include "LevelEnd.h"

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
			if (data[row][cell] == 1) {
				Wall* newObjectPtr = new Wall();

				newObjectPtr->location = Vector2i(cell * 32, row * 32);

				levelObjects.push_back(newObjectPtr);
			}
			if (data[row][cell] == 2) {
				Enemy* newObjectPtr = new Enemy();

				newObjectPtr->location = Vector2i(cell * 32, row * 32);

				levelObjects.push_back(newObjectPtr);
			}
			if (data[row][cell] == 3) {
				Player* newObjectPtr = new Player();

				newObjectPtr->location = Vector2i(cell * 32, row * 32);

				levelObjects.push_back(newObjectPtr);
			}
			if (data[row][cell] == 4) {
				Door* newObjectPtr = new Door();

				newObjectPtr->location = Vector2i(cell * 32, row * 32);

				levelObjects.push_back(newObjectPtr);
			}
			if (data[row][cell] == 5) {
				Key* newObjectPtr = new Key();

				newObjectPtr->location = Vector2i(cell * 32, row * 32);

				levelObjects.push_back(newObjectPtr);
			}
			if (data[row][cell] == 6) {
				LevelEnd* newObjectPtr = new LevelEnd();

				newObjectPtr->location = Vector2i(cell * 32, row * 32);

				levelObjects.push_back(newObjectPtr);
			}
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

	// clean up all of the level objects
	for (GameObject* objToDraw : levelObjects)
	{
		delete objToDraw;
	}

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
	// DebugLog("Snapped location is " << snappedLocation.X << "," << snappedLocation.Y);

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
		// DebugLog(snappedLocation.X / 32 << "," << snappedLocation.Y / 32);
		
		data[foundObjectY][foundObjectX] = 0; // Set that entry to 0

		levelObjects.remove(foundObject);
		delete foundObject;
		return;
	}

	//Use the snapped location and work out the index coordinates for the csv
	Vector2i indexCoords = Vector2i(snappedLocation.X / 32, snappedLocation.Y / 32);

	if (selectedObject == 1) {
		Wall* newObjectPtr = new Wall();

		newObjectPtr->location = snappedLocation;

		levelObjects.push_back(newObjectPtr);
	}
	else if (selectedObject == 2) {
		Enemy* newObjectPtr = new Enemy();

		newObjectPtr->location = snappedLocation;

		levelObjects.push_back(newObjectPtr);
	} 
	else if (selectedObject == 3) {
		Player* newObjectPtr = new Player();

		newObjectPtr->location = snappedLocation;

		levelObjects.push_back(newObjectPtr);
	}
	else if (selectedObject == 4) {
		Door* newObjectPtr = new Door();

		newObjectPtr->location = snappedLocation;

		levelObjects.push_back(newObjectPtr);
	}
	else if (selectedObject == 5) {
		Key* newObjectPtr = new Key();

		newObjectPtr->location = snappedLocation;

		levelObjects.push_back(newObjectPtr);
	}
	else if (selectedObject == 6) {
		LevelEnd* newObjectPtr = new LevelEnd();

		newObjectPtr->location = snappedLocation;

		levelObjects.push_back(newObjectPtr);
	}


	//Code for adding to the 2D array
	//Figure out the last index of the cell on the appropriate row
	if (indexCoords.Y < (int)data.size()) {
		//The row already exists in the array
		std::vector<int> cells = data[indexCoords.Y];
		int lastInd = cells.size() - 1; //Last index
		// DebugLog(lastInd);

		if (indexCoords.X > lastInd) {
			//Work out the difference between the index of the new object and the last element
			int diff = std::abs(indexCoords.X - lastInd); 
			// DebugLog(diff);

			//Pad out the array based on the difference
			for (int i = 0; i < diff; i++) cells.push_back(0); //0 = empty 
			// DebugLog(cells.size());
		}

		cells[indexCoords.X] = selectedObject; //selectedObject fills entry 
		data[indexCoords.Y] = cells;
	}
	else {
		//The row doesn't exist in the array -> Work out the difference
		// DebugLog(data.size() - 1);
		int rowDiff = std::abs(indexCoords.Y - ((int)data.size() - 1));
		// DebugLog(rowDiff);
		// DebugLog(data.size());

		//Pad out the array again
		for (int i = 0; i < rowDiff; i++) data.push_back(std::vector<int>{ 0 });
		std::vector<int> cells = data[data.size() - 1];
		// DebugLog(data.size());

		int cellDiff = std::abs(indexCoords.X - ((int)cells.size() - 1)); //Seems to be always one cell off, so adding one just in case
		for (int i = 0; i < cellDiff; i++) cells.push_back(0);
		// DebugLog(cellDiff);

		// DebugLog(indexCoords.X);
		// DebugLog(cells.size());
		cells[cells.size() - 1] = 1;
		data[indexCoords.Y] = cells;
	}
}

