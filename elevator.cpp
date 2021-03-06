//
// Created by Abdel Nasser on 2/18/22.
//

// UMBC - CMSC 341 - Spring 2022 - Proj1
#include "elevator.h"
Elevator::Elevator(){
    m_ground = nullptr;
    m_top = nullptr;
}
Elevator::~Elevator(){
    Floor * curr = m_ground;
    Floor * temp;
    while (curr != nullptr){
        temp = curr->m_next;
        delete curr;
        curr = temp;
    }
}
void Elevator::clear(){
    Elevator::~Elevator();
}
bool Elevator::insertAtHead(int floor, string passenger){
  // if there are no nodes at ground
  if (m_ground == nullptr) {

    // allocate a new node and set the ground and top to that node
    Floor * floorToAppend = new Floor(floor, passenger);
    m_ground = floorToAppend;
    m_top = floorToAppend;
    return true;
  }

  // else try to append at ground
  else {

    // should only apppend at the ground if th floor is smaller then the ground floor
    if (m_ground->m_floorNum > floor) {
      Floor *floorToAppend = new Floor(floor, passenger); // allocate a new node
      m_ground->m_previous = floorToAppend; // set the ground previous to that new ground floor
      floorToAppend->m_next = m_ground;// set its next to the ground floor
      m_ground = floorToAppend; //set the new ground floor to that new node
      return true;
    }
  }

  return false;

}
bool Elevator::insertAtTail(int floor, string passenger){
    if (m_top == nullptr) {
    // allocate a new node and set the ground and top to that node                                                                                                               
      Floor * floorToAppend = new Floor(floor, passenger);
        m_ground = floorToAppend;
        m_top = floorToAppend;
        return true;
    }
    else {
        if (m_top->m_floorNum < floor) {
            Floor *floorToAppend = new Floor(floor, passenger);
            m_top->m_next = floorToAppend; // set the tops floor next to the new top floor
            floorToAppend->m_previous = m_top; //set the new floors previous to the old top
            m_top = floorToAppend; //set the new top to the new top floor
            return true;
        }
    }
  
    return false;
}
bool Elevator::removeFloor(int floor){
  // if there are no floorts at all return false
  if (m_ground == nullptr or m_top == nullptr)
        return false;

  // if floor is out of bounds
  if (floor < m_ground->m_floorNum or floor > m_top->m_floorNum){
    throw out_of_range("This is out of bounds!");}

  int ground = floor - m_ground->m_floorNum; // finds the difference between floor to remove and the bottom floor
  int top = m_top->m_floorNum - floor; // finds the difference between the floor to remove and the top floor

    // if the remove floor is on the top half of the floors or at half
    if (top <= ground) {
        Floor *curr = m_top;

        if (int(curr->m_floorNum)== floor and curr->m_previous == nullptr) {
            delete curr;
            m_ground = nullptr;
            m_top = nullptr;
            return true;
        }

        // if the top floor is the floor to remove
        else if (curr->m_floorNum == floor) {
            // set the top floor to the next floor
            m_top = m_top->m_previous;

            // remove and delete the top floor
            delete m_top->m_next;
            m_top->m_next = nullptr;
            return true;
        }
        else {
            // get the second floor from the top
            curr = curr->m_previous;
            while (curr->m_previous != nullptr) {
                if (curr->m_floorNum == floor) {
                    // set the previous floor nexts pointer to the curr nexts pointer
                    curr->m_previous->m_next = curr->m_next;
                    curr->m_next->m_previous = curr->m_previous;
                    delete curr;
                    curr = nullptr;
                    return true;
                }
                curr = curr->m_previous;
            }
        }
    }
    // if its bottom half
    else{
        Floor *curr = m_ground;

        if (curr->m_floorNum == floor and m_ground->m_next == nullptr) {
            delete curr;
            curr = nullptr;
            m_top = nullptr;
            return true;
        }

        // if the ground floor is the floor to remove
        else if (curr->m_floorNum == floor) {
            // set the ground floor to the next floor
            m_ground = m_ground->m_next;


            // remove and delete the OG ground floor
            delete m_ground->m_previous;
            m_ground->m_previous = nullptr;
            return true;
        }
        else {
            curr = curr->m_next;
            while (curr->m_next != nullptr) {
                if (curr->m_floorNum == floor) {
                    // removes the middle mans and updates the pointers next and previous
                    curr->m_previous->m_next = curr->m_next;
                    curr->m_next->m_previous = curr->m_previous;
                    delete curr;
                    curr = nullptr;
                    return true;
                }
                curr = curr->m_next;
            }

        }
    }
    return false;

}
bool Elevator::insertFloor(int floor){
  if (floor < m_ground->m_floorNum or floor > m_top->m_floorNum){
    throw out_of_range("This is out of bounds!");} 


    int ground = floor - m_ground->m_floorNum; 
    int top = m_top->m_floorNum - floor; 

    
    if (top <= ground) { //-4 < 6
        Floor *curr = m_top;

        while (curr->m_previous != nullptr) {
	 
	  if (curr->m_floorNum > floor and curr->m_previous->m_floorNum < floor) {

	        Floor *floorToInsert = new Floor(floor);
	        //set the floor to Insert next's to curr
                floorToInsert->m_next = curr;

                // set the floor to inserts previous to previous floor of the current floor
                floorToInsert->m_previous = curr->m_previous;

                // Set the curr previous next to floor to Insert
                curr->m_previous->m_next = floorToInsert;

                //floorToInsert->m_previous->m_next = floorToInsert;
                // set the curr previous to floor to Insert
                curr->m_previous = floorToInsert;
                return true;
            }
            curr = curr->m_previous;
        }
    }
    else{
        Floor *curr = m_ground;

        while (curr->m_next != nullptr) {

	  if (curr->m_floorNum < floor and curr->m_next->m_floorNum > floor) {

	        Floor *floorToInsert = new Floor(floor);
                //set the floor to Insert previous to curr
                floorToInsert->m_previous = curr;

                // set the floor to inserts next to next floor of the current floor
                floorToInsert->m_next = curr->m_next;

                // Set the curr next previous to floor to Insert
                curr->m_next->m_previous = floorToInsert;

                // set the curr next to floor to Insert
                curr->m_next = floorToInsert;
                return true;
            }
            curr = curr->m_next;
        }
    }
    return false;

}
bool Elevator::checkFloor(int floor){
    if (floor < m_ground->m_floorNum or floor > m_top->m_floorNum)
        throw out_of_range("This is out of bounds!");

    Floor *temp = m_ground;
    while (temp != nullptr) {
        if (temp->m_floorNum == floor)
            return true;
        temp = temp->m_next;
    }

    return false;
}
bool Elevator::move(int origin, int destination){
    if (m_ground == nullptr or m_top == nullptr)
        return false;

    if (origin < m_ground->m_floorNum or origin > m_top->m_floorNum){
        throw origin;
    }

    if (destination < m_ground->m_floorNum or destination > m_top->m_floorNum)
        throw destination;

    int direction = destination - origin;
    Floor *originFloor = nullptr;
    Floor *destinationFloor = nullptr;

    // if destination is positive we are going up
    if (direction > 0) {
        Floor *curr = m_ground;

        while (curr != nullptr) {
            // if we found the floor the origin floor and there is someone there
            if (curr->m_floorNum == origin and curr->m_passenger != "") {
                originFloor = curr;
            }
                // if we found the destination floor and there are no passenger
            else if (curr->m_floorNum == destination and curr->m_passenger == "") {
                destinationFloor = curr;
            }
            curr = curr->m_next;
        }
        // if both floors dont equal nullptr, then we can move passanger
        if (destinationFloor != nullptr and originFloor != nullptr) {
            destinationFloor->m_passenger = originFloor->m_passenger;
            originFloor->m_passenger = "";
            return true;
        }
    }

    // if we are going down
    else {
        Floor *curr = m_top;

        while (curr != nullptr) {
            // if we found the origin floor and there is a passanger there
            if (curr->m_floorNum == origin and curr->m_passenger != "") {
                originFloor = curr;
            }
                // if we found the destination floor and there are no passenger
            else if (curr->m_floorNum == destination and curr->m_passenger == "") {
                destinationFloor = curr;
            }
            curr = curr->m_previous;
        }
        if (destinationFloor != nullptr and originFloor != nullptr) {
            destinationFloor->m_passenger = originFloor->m_passenger;
            originFloor->m_passenger = "";
            return true;
        }
    }
        return false;
}
string Elevator::exit(int floor, string passenger){
    if (floor < m_ground->m_floorNum or floor > m_top->m_floorNum)
        throw floor;

    Floor *curr = m_top;

    // iterate towards the floor to exit
    while (curr != nullptr) {

      // if that floor is equal to the exit floor and there is a passanger
      if (curr->m_floorNum == floor and curr->m_passenger != "") {
            string pass = curr->m_passenger;
            curr->m_passenger = ""; // set the passanger string to empty
            return pass; // return passanger
        }
      // if the passanger is empty and 
      if (curr->m_floorNum == floor and curr->m_passenger == "")
            return "";

        curr = curr->m_previous;
    }
    return "";
}
bool Elevator::enter(int floor, string passenger) {

    if (floor < m_ground->m_floorNum or floor > m_top->m_floorNum) {
      throw out_of_range("This is out of bounds");
    }
    int top = m_top->m_floorNum - floor;
    int ground = floor - m_ground->m_floorNum;

    // iterates backward
    if (top <= ground) {
        Floor *curr = m_top;

	// iterate to the wanted floor
	while (curr != nullptr) {
	  // if its the floor we want and ther is no passanger return fasle
	    if (curr->m_floorNum == floor and curr->m_passenger != "") {
                return false;
            }
	    // if its the floor we want and there is a passanger, set that floor passanger to the string passsed in and return true
	    if (curr->m_floorNum == floor and curr->m_passenger == ""){
                curr->m_passenger = passenger;
		return true;
	    }
            curr = curr->m_previous;
        }
    }

    // iterates forward
    else {
        Floor *curr = m_ground;
        while (curr != nullptr) {
            if (curr->m_floorNum == floor and curr->m_passenger != "") {
                return false;
            }
            if (curr->m_floorNum == floor and curr->m_passenger == ""){
                curr->m_passenger = passenger;
                return true;
	    }
            curr = curr->m_next;

        }
    }
    return false;
}
Elevator::Elevator(const Elevator & rhs){
  // inalizes the private variables
  Floor * curr = rhs.m_ground;// takes in the og ground floor to be used to ieterate over
    m_top = nullptr;
    m_ground = nullptr;

    // copies all the nodes over
    while (curr != nullptr){
        insertAtTail(curr->m_floorNum,curr->m_passenger);
        curr = curr->m_next;
    }
}

const Elevator & Elevator::operator=(const Elevator & rhs){

    Floor * curr = rhs.m_ground;
    m_top = nullptr;
    m_ground = nullptr;
    while (curr != nullptr){
        insertAtTail(curr->m_floorNum,curr->m_passenger);
        curr = curr->m_next;
    }
    return *this;
}
void Elevator::dump(){
    if (m_top != nullptr){
        Floor *temp = m_top;
        cout << "Top Floor " ;
        while(temp->m_previous != nullptr){
            cout << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
            temp = temp->m_previous;
        }
        cout << "Ground Floor " << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
    }
}

