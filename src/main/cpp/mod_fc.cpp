#include <mod_fc.h>
#define PI 3.1415

void ModFC::SetPosition(){

}

void ModFC::SetWheelVelocity(){
	
}

int ModFC::CurrentPosition(){
	int pos = talon_rotate->GetSelectedSensorPosition(0);
	if (clockwise_motor < 0){
		pos = pos * -1;
	}

	int inRotPos = pos % encPerRev;
	if (clockwise_motor < 0 && inRotPos < 0) inRotPos = inRotPos + 360;

	return inRotPos;
}

int ModFC::CurrentDegrees(){
	return (CurrentPosition() * 1.0 / encPerRev) * (360);
}

int ModFC::DegreesToRotate(){
	int current_angle = CurrentDegrees();
	int new_angle = joyan->GetJoystickRegion();

	bool clockwise;
	int dir1 = std::abs(new_angle - current_angle);
	int dir2 = 360 - std::abs(new_angle - current_angle);

	int deg = std::min(dir1, dir2);

	if (dir1 == deg){
		if (new_angle - current_angle > 0) clockwise = 1;
		else clockwise = 0;
	}
	else{
		if ((current_angle - new_angle)  > 0) clockwise = 1;
		else clockwise = 0;
	}

	int dir;
	if (clockwise) dir = 1 * clockwise_motor;
	else dir = -1 * clockwise_motor;

	return deg * dir;
}

int ModFC::PositionToRotate(){
	//return DegreesToRotate() * (encPerRev / 360.0);
	return DegreesToRotate() * (encPerRev / 360.0);
}

void ModFC::Rotate(int velocity, std::string name){
	if (abs(joyan->GetJoystickMagnitude()) > joyan->RadiusOfNoEffect()){
		int pos = CurrentPosition();
		int target = PositionToRotate();
		if (target < 0){
			//talon_rotate->Set(ControlMode::Velocity, DegreesToRotateRange(-velocity));
			if (abs(DegreesToRotate()) >= 15){
				talon_rotate->Set(ControlMode::Velocity, -velocity);
			}
			else{
				talon_rotate->Set(ControlMode::PercentOutput, 0);
			}
		}
		else {
			//Wheel rotates clockwise
			//std::cout<<"Sub: "<<pos - target<<std::endl;
			if (abs(DegreesToRotate()) >= 15){
				talon_rotate->Set(ControlMode::Velocity, velocity);
			}
			else{
				talon_rotate->Set(ControlMode::PercentOutput, 0);
			}
			//talon_rotate->Set(ControlMode::Velocity, DegreesToRotateRange(velocity));
		}
	}
	else{
		talon_rotate->Set(ControlMode::PercentOutput, 0);
	}

	//std::cout<<name<<" Position: "<<CurrentPosition()<<std::endl;
	std::cout<<name<<" DegreesToRotate Range: "<<DegreesToRotateRange(velocity)<<std::endl;
	std::cout<<name<<" Current Degrees: "<<CurrentDegrees()<<std::endl;
	//std::cout<<name<<" Degrees to Rotate: "<<DegreesToRotate()<<std::endl;
	//std::cout<<name<<" Position to Go: "<<PositionToRotate()<<std::endl;
	std::cout<<"\t"<<name<<" Position: "<<talon_rotate->GetSelectedSensorPosition(0)<<std::endl;
}

int ModFC::DegreesToRotateRange(int velocity){
	if (abs(DegreesToRotate()) >= 20) return velocity;
	if (abs(DegreesToRotate()) >= 10) return velocity / 2;
	if (abs(DegreesToRotate()) >= 5) return velocity / 3;
	return 0;

}

/* Need a way to make motors all arrive at the same time
	- Boolean that checks if motor is in right degree range before wheel can move
	- Have a separate function to do the wheel rotation countaract to the module rotation
	- One rotation of module = 1/2 rotation of wheel
	-

*/