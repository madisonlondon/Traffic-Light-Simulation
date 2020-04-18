#include "TrafficLight.h"

TrafficLight::TrafficLight(){
	// Default constructor 
	gLength = -1;
	yLength = -1;
	rLength = -1;
	currentState = Color::undefined;
	myDirection = TrafficLightDirection::undefined;
	cycleTime = -1;
}

TrafficLight::TrafficLight(int green, int yellow, int red, Color state, TrafficLightDirection direct){
	// Creates an instance of TrafficLigth with pass by value arguments
	gLength = green;
	yLength = yellow;
	rLength = red;
	currentState = state;
	myDirection = direct;
	// The total cycle time will be the time needed for a TrafficLight to turn green, yellow, and red
	cycleTime = green + yellow + red;
}

TrafficLight::TrafficLight(const TrafficLight& other){
	// Copy constructor
	gLength = other.gLength;
	yLength = other.yLength;
	rLength = other.rLength;
	currentState = other.currentState;
	myDirection = other.myDirection;
	cycleTime = other.cycleTime;
}

TrafficLight::~TrafficLight(){
	// Destructor
}

Color TrafficLight::getColor(){
	// Return the current color of the TrafficLight
	return currentState;
}

void TrafficLight::updateState(int time){
	// Update the state of the TrafficLight given the current time of the simulation
	int currentTime = time % cycleTime;

	switch(myDirection){
		case TrafficLightDirection::north_south:
		// In the case that the traffic light being updated is for the north or south lanes
			if(currentTime >= 0 && currentTime < gLength){
				// The north/south lanes first have a green ligth
				currentState = Color::green;
			}
			else if(currentTime >= gLength && currentTime < gLength + yLength){
				//
				currentState = Color::yellow;
			}
			else if(currentTime >= gLength + yLength && currentTime < cycleTime){
				currentState = Color::red;
			}
			break;
		case TrafficLightDirection::east_west: 
		// In the case that the traffic light being updated is for the east or west lanes
			if(currentTime >= rLength + gLength && currentTime < cycleTime){
				currentState = Color::yellow;
			}
			else if(currentTime >= rLength && currentTime < rLength + gLength){
				currentState = Color::green;
			}
			else if(currentTime >= 0 && currentTime < rLength){
				currentState = Color::red;
			}
				break;
		case TrafficLightDirection::undefined: 
		// Do nothing 
			break;
	}
}

int TrafficLight::getTimeRemaining(int time){
	// Return the time remaining before the color changes given the current state of 
    // the TrafficLight and the current time of the simulation
	int currentTime = time % cycleTime;

	switch(myDirection){
		case TrafficLightDirection::north_south:
			if(currentState == Color::green){
				return gLength - 1 - currentTime;
			}
			else if(currentState == Color::yellow){
				return gLength + yLength - 1 - currentTime;
			}
			else if(currentState == Color::red){
				return cycleTime - 1 - currentTime;
			}
		case TrafficLightDirection::east_west:
			if(currentState == Color::green){
				return rLength + gLength - 1 - currentTime;
			}
			else if(currentState == Color::yellow){
				return cycleTime - 1 - currentTime;
			}
			else if(currentState == Color::red){
				return gLength + yLength - 1 - currentTime;
			}
		case TrafficLightDirection::undefined:
		// Return -1 and leave 
			return -1;
	}
	return -1;
}
