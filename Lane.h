#ifndef _LANE_H__
#define _LANE_H__

#include "TrafficLight.h"
#include "Vehicle.h"
#include <algorithm>
using namespace std;

class Lane {
	private:
		TrafficLight* light;
		int length;
		bool isSpace(Vehicle* v);
	public:
		vector<Vehicle*> lane;
		Lane(TrafficLight* light, int length);
		~Lane();
		vector<VehicleBase*> pointerLane();
		void addVehicle(Vehicle* v);
		void removeVehicle();
		void removeVehicle(int i);
		void insertVehicle(Vehicle* v);
		bool crossSafely(Vehicle* v, int t, int tyellow);
		bool isSafeToMove(Vehicle* v, int index, int t, int tyellow);
};

#endif
