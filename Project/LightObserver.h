/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once

class Light;

class LightObserver
{
	public:
        virtual ~LightObserver() = default;
        virtual void Update(const Light& light) = 0;
};

