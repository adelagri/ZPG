/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once

class Light;

class ILightObserver
{
	public:
        virtual ~ILightObserver() = default;
        virtual void OnLightChanged(const Light& light) = 0;
};

