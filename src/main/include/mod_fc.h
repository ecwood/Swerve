#ifndef MODFC
#define MODFC

#include <iostream>
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include <frc/Joystick.h>
#include <string>
#include <joyan.h>

using namespace frc;

class ModFC {
	public:
		ModFC (TalonSRX *talon_rotate, TalonSRX *talon_wheel, Joystick *joystick, JoystickAnalysis *joyan, int clockwise_motor) : talon_rotate(talon_rotate), talon_wheel(talon_wheel), joystick(joystick), joyan(joyan), clockwise_motor(clockwise_motor) {};
		void SetPosition();

		void SetWheelVelocity();

		int CurrentPosition();
		int CurrentDegrees();
		int DegreesToRotate();
		int PositionToRotate();
		void Rotate(int velocity, std::string name);
		int DegreesToRotateRange(int velocity);

	private:
		TalonSRX *talon_rotate, *talon_wheel;
		Joystick *joystick;
		JoystickAnalysis *joyan;
		int clockwise_motor;

		const int encPerRev = 279;
};

#endif