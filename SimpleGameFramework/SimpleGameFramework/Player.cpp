#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	GameFrameworkInstance.LoadImageResource(
		AppConfigInstance.GetResourcePath("Images/spawn.png"),
		"Spawn");

	imageID = "Spawn";

	
}


Player::~Player()
{
}

void Player::Move(float moveSpeed)
{

}

void Player::Move_Blink()
{
}

void Player::Attack(float atkStrength)
{
}

void Player::PickUpItem()
{
}

void Player::OpenDoor()
{
}

void Player::Die(float currHealth)
{
}
