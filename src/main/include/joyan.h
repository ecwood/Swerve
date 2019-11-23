#ifndef MODULE
#define MODULE

#include <iostream>
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include <frc/Joystick.h>
#include <string>

using namespace frc;

class JoystickAnalysis {
	public:
		JoystickAnalysis (Joystick *joystick) : talon_rotate(talon_rotate), talon_wheel(talon_wheel), joystick(joystick) {};

		int GetJoystickDegrees();
		float GetJoystickRadians();
		float GetJoystickMagnitude();

		float Velocity(int max_velocity);
		int GetJoystickRegion();

		float RadiusOfNoEffect();

	private:
		TalonSRX *talon_rotate, *talon_wheel;
		Joystick *joystick;
		const float radiusOfNoEffect = 0.1;
};

#endif