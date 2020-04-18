#include "Lane.h"

/*
 *Constructor for the Lane class. Takes the length of the lane and the corresponding
 traffic light as parameters.
 */
Lane::Lane(TrafficLight* light, int length)
{
	this->light = light;
	this->length = length;
}

/*
 *This method determines if there is enough space in the lane to 
 add another vehicle. It does this by checking if the current last 
 vehicle in the lane is occupying the last spot in the lane. If it is,
 then there is no room for a new vehicle.
 */
bool Lane::isSpace(Vehicle* v)
{
	int size = v->getSize();
	// If the lane is empty, there is space for a new vehicle
	if (lane.size() == 0)
	{
		return true;
	}
	// Last vehicle in lane
	Vehicle* last_vehicle = lane.back();

	// Checks if last vehicle occupies the last position in the lane.
	// It does this by checking the coordinates of the last vehicle.
	switch(last_vehicle->getDirection())
	{
		case Direction::north:
			if (last_vehicle->getBackYPos() < size)
			{
				return false;
			}
		case Direction::south:
			if (last_vehicle->getBackYPos() > length*2 + 1 - size)
			{
				return false;
			}
		case Direction::east:
			if (last_vehicle->getBackXPos() < size)
			{
				return false;
			}
		case Direction::west:
			if (last_vehicle->getBackXPos() >= length*2 + 1 - size)
			{
				return false;
			}
	}
	return true;
}

/*
 *This method adds a vehicle to a lane if there is space. The vehicle is added to the 
 end of the lane.
 */
void Lane::addVehicle(Vehicle* v)
{
	if (isSpace(v))
	{
		lane.push_back(v);
	}	
}

/*
 *This method adds a vehicle that has made a right turn. It first determines the index
 of the first vehicle in the lane before the intersection. It then adds the new vehicle
 directly in front of that vehicle.
 */
void Lane::insertVehicle(Vehicle* v)
{
	int index = -1;

	// Get index of first vehicle in lane before the light/intersection.	
	switch (v->getDirection())
	{
		case Direction::north:
			for (int i = 0; i < lane.size(); i++)
			{
				if (lane[i]->getFrontYPos() <= length)
				{
					index = i;
					break;
				}
			}
			break;
		case Direction::south:
			for (int i = 0; i < lane.size(); i++)
			{
				if (lane[i]->getFrontYPos() >= length + 2)
				{
					index = i;
					break;
				}
			}
			break;
		case Direction::east:
			for (int i = 0; i < lane.size(); i++)
			{
				if (lane[i]->getFrontXPos() <= length)
				{
					index = i;
					break;
				}
			}
			break;
		case Direction::west:
			for (int i = 0; i < lane.size(); i++)
			{
				if (lane[i]->getFrontXPos() >= length + 2)
				{
					index = i;
					break;
				}
			}
			break;
	}
	// If index is -1, then no vehicles in the lane are before the intersection
	// Therefore, the turning vehicle goes in the back of the lane.
	// If the index is not -1, then the turning vehicle is inserted into the lane
	// at the appropriate spot
	if (index != -1)
	{
		lane.insert(lane.begin() + index, v);
	}
	else
	{
		lane.push_back(v);
	}
}




/*
 *This method removes the first vehicle in the lane from the lane. This method will 
 be called when the vehicle reaches the end of the lane.
 */
void Lane::removeVehicle()
{
	// If no vehicles in lane, cannot remove any vehicles
	if (lane.size() == 0)
	{
		return;
	}
	Vehicle* first = lane[0];
        switch(first->getDirection())
	{
		// Check if vehicle has reached end of lane
		case Direction::north:
			if (first->getFrontYPos() > length*2 + 1)
			{
				lane.erase(lane.begin());
			}
			break;
		case Direction::south:
			if (first->getFrontYPos() < 0)
			{
				lane.erase(lane.begin());
			}
			break;
		case Direction::east:
			if (first->getFrontXPos() > length*2 + 1)
			{
				lane.erase(lane.begin());
			}
			break;
		case Direction::west:
			if (first->getFrontXPos() < 0)
			{
				lane.erase(lane.begin());
			}
			break;
	}

}

/*
 *This method removes a vehicle that made a right turn from the lane. 
 */
void Lane::removeVehicle(int i)
{
	lane.erase(lane.begin() + i);
}

/*
 *This method determines if a vehicle just before the intersection can make 
 it through the intersection safely, before the light turns red.
 The time necessary for the vehicle to travel completely through
 the intersection is different depending on whether the vehicle is
 turning right or going straight.
 */
bool Lane::crossSafely(Vehicle* v, int t, int tyellow)
{
	int size = v->getSize();
	int tn = 0;
	// Determines the number of time steps needed to 
	// make it through the intersection
	if (v->turnsRight())
	{
		tn = 3;
	}
	else
	{
		tn = size + 2;
	}
	// If the light is yellow, the vehicle has until the 
	// light changes to go through the intersection
	if (light->getColor() == Color::yellow)
	{
		if(tn > light->getTimeRemaining(t))
		{
			return false;
		}
	}
	// If the light is green, the vehicle has until the light turns 
	// yellow plus the time that the light will be yellow
	else if (light->getColor() == Color::green)
	{
		if (tn > light->getTimeRemaining(t) + tyellow)
		{
			return false;
		}
	}
	return true;
}

/*
 *This method determines if a vehicle can move. It checks if there is a space in front of the vehicle. 
 If the vehicle is just before the intersection, this method also checks if the light is red or if 
 there is not enough time for the vehicle to make it through the intersection before the light turns
 red. .
 */

bool Lane::isSafeToMove(Vehicle* v, int i, int t, int tyellow)
{
	// If the vehicle is first in the lane, don't need to check any preceding cars
	// Only check if the vehicle is at the light.
	if (i == 0)
	{
		switch (v->getDirection())
		{
			case Direction::north:
				if (v->getFrontYPos() == length - 1)
				{
					if (!crossSafely(v, t, tyellow) or light->getColor() == Color::red)
					{
						return false;
					}
				}
				break;
			case Direction::south:
				if (v->getFrontYPos() == length + 2)
				{
					if (!crossSafely(v, t, tyellow) or light->getColor() == Color::red)
					{
						return false;
					}
				}
				break;
			case Direction::east:
				if (v->getFrontXPos() == length - 1)
				{
					if (!crossSafely(v, t, tyellow) or light->getColor() == Color::red)
					{
						return false;
					}
				}
				break;
			case Direction::west:
				if (v->getFrontXPos() == length + 2)
				{
					if (!crossSafely(v, t, tyellow) or light->getColor() == Color::red)
					{
						return false;
					}
				}
				break;
		}
		return true;
	}
	// If the vehicle is not first in the lane, then we also need to check that its path 
	// is not blocked by any other vehicles.
	Vehicle* previous_vehicle = lane[i-1];
	switch (previous_vehicle->getDirection())
	{
		case Direction::north:
			if (previous_vehicle->getBackYPos() - 1 == v->getFrontYPos())
			{
				return false;
			}
			else if (v->getFrontYPos() == length-1)
			{
				if (!crossSafely(v, t, tyellow) or light->getColor() == Color::red)
				{
					return false;
				}
			}
			break;			
		case Direction::south:
			if (previous_vehicle->getBackYPos() + 1 == v->getFrontYPos())
			{
				return false;
			}
			else if (v->getFrontYPos() == length + 2)
			{
				if (!crossSafely(v,t, tyellow) or light->getColor() == Color::red)
				{
					return false;
				}
			}
			break;
		case Direction::east:
			if (previous_vehicle->getBackXPos() - 1 == v->getFrontXPos())
			{
				return false;
			}
			else if (v->getFrontXPos() == length-1)
			{
				if (!crossSafely(v, t, tyellow) or light->getColor() == Color::red)
				{
					return false;
				}
			}
			break;
		case Direction:: west:
			if (previous_vehicle->getBackXPos() + 1 == v->getFrontXPos())
			{
				return false;
			}
			else if (v->getFrontXPos() == length + 2)
			{
				if (!crossSafely(v, t, tyellow) or light->getColor() == Color::red)
				{
					return false;
				}
			}
			break;
	}
	return true;
}

/*
 * This method returns a vector of vehicle pointers that corresponds to the vector of vehicles lane.
 * This is done because the Animator class requires a vector of vehicle pointers with size 2*length + 2.
 * For each vehicle in the lane, a pointer to that vehicle is placed in each section of the lane that the
 * vehicle occupies.
 */
vector<VehicleBase*> Lane::pointerLane()
{
	vector<VehicleBase*> vp(2*length + 2, nullptr);
	if (lane.size() == 0)
	{
		return vp;
	}
	Vehicle* v = lane[0];
	vector<Vehicle*>::iterator it;
	switch (v->getDirection())
	{
		case Direction::north:
			// For each vehicle in the lane
			for (it = lane.begin(); it != lane.end(); it++)
			{
				Vehicle* w = *it;
				// For each section occupied by the vehicle
				for (int j = w->getBackYPos(); j <= w->getFrontYPos(); j++)
				{
					vp[j] = w;
				}
			}
			break;
		case Direction::south:
			for (it = lane.begin(); it != lane.end(); it++)
			{	
				Vehicle* w = *it;	
				
				for (int j = w->getFrontYPos(); j <= w->getBackYPos(); j++)
				{
					vp[j] = w;
				}
			}
			// We need to reverse the vector because the Animator class will reverse
			// it again. This means that the lane will be going in the correct direction.
			reverse(vp.begin(), vp.end());
			break;
		case Direction::east:
			for (it = lane.begin(); it != lane.end(); it++)
			{
				Vehicle* w = *it;
				
				for (int j = w->getBackXPos(); j <= w->getFrontXPos(); j++)
				{
					vp[j] = w;
				}
			}
			break;
		case Direction::west:
			for (it = lane.begin(); it != lane.end(); it++)
			{
				Vehicle* w = *it;
				
				for (int j = w->getFrontXPos(); j <= w->getBackXPos(); j++)
				{
					vp[j] = w;
				}
			}
			reverse(vp.begin(), vp.end());
			break;
	}
	return vp;	
}














