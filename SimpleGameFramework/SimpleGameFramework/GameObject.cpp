#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	imageID = "Art";
}


GameObject::~GameObject()
{
}

void GameObject::Draw(Gdiplus::Graphics & canvas)
{
	// store the current transform so we can restore it
	Gdiplus::Matrix transform;
	canvas.GetTransform(&transform);

	// offset drawing so we can work in local coordinates
	canvas.TranslateTransform((Gdiplus::REAL)location.X, 
							  (Gdiplus::REAL)location.Y);

	ImageWrapper* image = 
	        GameFrameworkInstance.GetLoadedImage(imageID);
	DebugLog(imageID);
	if (image == nullptr) return;

	GameFrameworkInstance.DrawImage(canvas,
		Vector2i::Zero, image);

	// restore the transform
	canvas.SetTransform(&transform);
}

void GameObject::Update(double deltaTime)
{
}
