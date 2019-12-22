#include <joyan.h>
#define PI 3.1415

int JoystickAnalysis::GetJoystickDegrees(){
	if (EnableZeroStart(zero_start_on)) return 0;
	float y_axis = -1 * joystick->GetRawAxis(1);
	float x_axis = joystick->GetRawAxis(0);

	int ang = atan(y_axis / x_axis) * (180 / PI);
	if (x_axis < 0){
		ang = 360 - ang;
	}
	ang = ang - 90;
	if (ang < 0) ang = ang * -1;

	return ang;
}

float JoystickAnalysis::GetJoystickRadians(){
	return GetJoystickDegrees() * (PI / 180);
}

float JoystickAnalysis::GetJoystickMagnitude(){
	float y_axis = -1 * joystick->GetRawAxis(1);
	float x_axis = joystick->GetRawAxis(0);
	float sqr = sqrt(pow(y_axis, 2) + pow(x_axis, 2));
	int dir = 1;
	if (x_axis < 0) dir = -1;
	if (sqr > 1) return 1 * dir;
	return sqr * dir;
}

float JoystickAnalysis::Velocity(int max_velocity){
	this->max_velocity = max_velocity;
	float mag = GetJoystickMagnitude();
	if (abs(mag) < radiusOfNoEffect) return 0;
	return mag * max_velocity;
}

bool JoystickAnalysis::EnableZeroStart(bool on){
	zero_check = zero_check + abs(GetJoystickMagnitude());
	zero_start_on = on;
	if (zero_check < RadiusOfNoEffect() * max_velocity && on) return true;
	else return false;
}
		
int JoystickAnalysis::GetJoystickRegion(){
	int ang = GetJoystickDegrees();
	switch (ang){
		case 0 ... 22:
			return 0;
		case 23 ... 67:
			return 45;
		case 68 ... 112:
			return 90;		
		case 113 ... 157:
			return 135;
		case 158 ... 202:
			return 180;
		case 203 ... 247:
			return 225;
		case 248 ... 292:
			return 270;
		case 293 ... 337:
			return 315;
		case 338 ... 360:
			return 0;
	}
}

float JoystickAnalysis::RadiusOfNoEffect(){
	return radiusOfNoEffect;
}