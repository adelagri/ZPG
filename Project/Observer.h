/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once

class Camera;

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Update(Camera& camera) = 0;
};

