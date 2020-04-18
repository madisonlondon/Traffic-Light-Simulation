#include "Roadway.h"
#include "Lane.h"
using namespace std;
/*
 *This is the constructor for the Roadway class. It takes two traffic lights
 as parameters: one for north and south, and one for east and west. It also takes
  the length of the road before the intersection. 
  An instance of Roadway has 4 instances of lane, one for each direction of travel.
 */
Roadway::Roadway(TrafficLight* lightns, TrafficLight* lightew, int length)
{
	northbound = new Lane(lightns, length);
	southbound = new Lane(lightns, length);
	eastbound = new Lane(lightew, length);
	westbound = new Lane(lightew, length);
	this->length = length;
}

// Destructor for Roadway
Roadway::~Roadway() 
{
}

/*
 * This method determines if a vehicle is in the intersection.
 * Because of how we implemented the turnRight method, the only
 * relevant position in the intersection for a vehicle is the first
 * position in its lane. At this point, the vehicle either continues
 * straight or turns right. So, this method checks if the front of 
 * the vehicle is at that position in the intersection.
 */
bool Roadway::isIntersection(Vehicle* v)
{
	switch (v->getDirection())
	{
		case Direction::north:
			if (v->getFrontYPos() == length)
			{
				return true;
			}
			break;
		case Direction::south:
			if (v->getFrontYPos() == length + 1)
			{
				return true;
			}
			break;
		case Direction::east:
			if (v->getFrontXPos() == length)
			{
				return true;
			}
			break;
		case Direction::west:
			if (v->getFrontXPos() == length + 1)
			{
				return true;
			}
			break;
	}
	return false;

}

