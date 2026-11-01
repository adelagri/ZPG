#include "ClockHands.h"
#include <ctime>
#include <glm/glm.hpp>

void ClockHands::Update(ShaderProgram* shader)
{
	time_t now_c = time(nullptr); // get the current time in seconds
	tm local;
	localtime_s(&local, &now_c);	// convert the time to local time and store it in a tm struct

	float sec = (float)local.tm_sec;
	float min = local.tm_min + sec / 60.0f;
	float hour = (local.tm_hour % 12) + min / 60.0f;

	// convert the time to angles in radians for the clock hands
	float secondAngle = -glm::radians(sec * 6.0f);	// 360° / 60 = 6 degrees per second
	float minuteAngle = -glm::radians(min * 6.0f);	// 360° / 60 = 6
	float hourAngle = -glm::radians(hour * 30.0f);	// 360° / 12 = 30

	shader->Use();
	shader->SetUniform("secondAngle", secondAngle);
	shader->SetUniform("minuteAngle", minuteAngle);
	shader->SetUniform("hourAngle", hourAngle);
}
