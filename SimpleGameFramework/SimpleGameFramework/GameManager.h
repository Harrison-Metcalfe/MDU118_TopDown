#pragma once

#include "GameFramework.h"
#include "GameObject.h"

#include <list>

class GameManager
{
public:
	static GameManager& Instance();

	/** BeginPlay is called when the game first launches. It is only called once per launch. */
	void BeginPlay();

	/** EndPlay is called when the game is closing down. It is only called once and only on exit. */
	void EndPlay();

	/**
	 * Update is called every frame. Update is always called before render
	 *
	 * @param deltaTime The time in seconds since Update was last called.
	 */
	void Update(double deltaTime);

	/**
	 * Render is called every frame after Update is called. All drawing must happen in render.
	 *
	 * @param [in,out] canvas The canvas.
	 * @param clientRect	  The rectangle representing the drawable area.
	 */
	void Render(Gdiplus::Graphics& canvas, const CRect& clientRect);

	void LeftButtonDown(const Vector2i& point);

	void MovementHappened(const Vector2i& input);

	std::vector<std::vector<int>> data;

	int selectedObject = 1;

	GameObject* playerInLevel = nullptr;

	bool isPlayMode;

private:
	GameManager();
	~GameManager();

	GameObject* objectPtr;

	std::list<GameObject*> levelObjects;

	Vector2i levelOffset;
};

/**
 * Retrieves the GameManagerInstance for the game.
 *
 * @return The game manager instance
 */
#define GameManagerInstance (GameManager::Instance())
