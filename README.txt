Project by Berke Nuri, Maddie London, Eric Goetz

1. how to compile your program (which should be just 'make')
We have a Makefile for compiling all of the classes and to create and executable of our driver  class. Typing “make” on the terminal is enough.
2. how to execute your program (be detailed)
Given the executable testSimulation (after compiling using the Makefile), run a command following the format below:
./testSimulation [name of input file] [boolean value]
The user will provide a boolean value indicating whether or not the computer will be in charge of progressing the simulation. If the user enters true, they will need to press enter to iterate through to simulation. If the user enters false, the computer will progress the simulation. 
3. traffic-related design decisions (e.g., how you handled progressing through traffic light, how you handled turns, etc.)
Used four vectors to represent the four lanes of traffic, each lane has a vector of vehicles.
There is a method in the Lane class which determines if a vehicle can get past the intersection when the traffic light is yellow. If there is enough time, the vehicle will continue to the intersection to go straight or to turn right when the light is yellow.
When we try to create a new vehicle at each clock tick, if there’s no space, vehicle doesn’t enter. 
Vehicles will determine what their intersection behavior is when they are created, the vehicle constructor have the parameters: vehicle type, their front and back position x-y coordinates, their current direction, and a boolean value representing if they are going to turn right or not in the intersection. The size of the car will be determined in the constructor depending on the vehicle type(car, SUV, truck).
Going straight and turning right methods are implemented in the vehicle class. Going straight is a straightforward method: it updates the x-y coordinates of the vehicle depending on the car’s direction. On the other hand, turn right method has some logical flaws because vehicles will slightly teleport (take the turn really fast) instead of turning index by index on turns. Since we have control over only the front and back x-y coordinates of the vehicle, and we update the new direction of the vehicle after turning right: if a vehicle which turns index by index, when we call the method go again to make it continue moving away from the intersection, the front position would be on the correct lane; however, back position of the vehicle would move out of pound of the roadway. 
Four instances of TrafficLight (south and west are copies) to be more realistic
North/south lanes will get a green light first
4. OOP design decisions (class structure, how classes interface, etc.) 
TrafficLight  
- Intersection will be controlled by TrafficLight in each of the four directions
- Light will be green, yellow, and red for a period of time
- Length of red for north/south will be the sum of the lengths of green and yellow for east/west and vice versa
Vehicle 
- Inherits from the VehicleBase class
- Three types of vehicles: car, SUV, truck
- Will have a certain probability of proceeding straight or turning right in the intersection
Roadway
- Will keep instances of lane
Lane 
- Will keep a vector representing the lane that holds instances of Vehicle
Time
- At each clock tick the vehicles must attempt to advance one section, TrafficLights will update
- Probability of new vehicle in each of the lanes
