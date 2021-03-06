// UMBC - CMSC 341 - Spring 2022 - Proj1
#include "elevator.h"
#include <string>
class Tester{
public:
    /******************************************
    * Test function declarations go here! *
    ******************************************/
    bool testInsertAtHeadNormalCase();
    bool testInsertAtHeadErrorCase();

    bool testinsertAtTailNormalCase();
    bool testinsertAtTailErrorCase();

    bool testEnterElevatorNormalCase();
    bool testEnterElevatorErrorCase();
    void testEnterElevatorOutOfBounds();


    bool testRemoveAllFloorsNormalCase();
    bool testRemoveAllFloorsRandomOrderNormalCase();
    bool testRemoveNoneExistantFloorsErrorCase();
    void testRemoveOutOfBoundFloorsEdgeCase();

    void testMoveOutOfBounds();
    bool testMoveNormalCaseMovingUp();
    bool testMoveNormalCaseMovingDown();
    bool testMoveFloorDNE();
    bool testMoveDestinationFullElevators();
    bool testMoveNoPassengerOrigin();
    void TestRandomMoveFunctionEdgeCase();

    bool testCheckFloorNormalCase();
    bool testCheckFloorErrorCase();

    bool testInsertFloorNormalCase();
    bool testInsertFloorErrorCase();

    void testDeepCopyOfCopyConsNormalCase();
    void testDeepCopyOfCopyConsEdgeCase();

    void testDeepCopyOfAssignmentOpeEdgeCase();
    void testDeepCopyOfAssignmentOpeNormalCase();
};


void assertTest(bool, string);
int main(){
    Tester tester;
    
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i=1;i<=10;i++)
        anElev.insertAtTail(i);
    cout << "\nCarrying Alice from 6th floor to 10th floor:\n";
    cout << "\tAlice enters the elevator:\n";
    anElev.enter(6,"Alice");
    anElev.dump();
    cout << "\n\tMoving to 10th floor:\n";
    anElev.move(6,10);
    anElev.dump();
    anElev.exit(10,"Alice");
    cout << "\n\tRemoving the 2nd floor:\n";
    anElev.removeFloor(2);
    anElev.dump();
    
    {
        assertTest(tester.testInsertAtHeadNormalCase(), "For Normal case: Inserting at the head in sequential order");
    }

    {
        assertTest(tester.testInsertAtHeadErrorCase(), "For Error case: Inserting at the head in sequential order");
    }

    {
        assertTest(tester.testinsertAtTailNormalCase(), "For Normal case: Inserting at the Tail in sequential order");
    }

    {
        assertTest(tester.testinsertAtTailErrorCase(), "For Error case: Inserting at the Tail in sequential order");
    }
    {
        assertTest(tester.testEnterElevatorNormalCase(), "For Normal Case: People entering the elevator");
    }

    {
        assertTest(tester.testEnterElevatorErrorCase(), "For error Case: People already in the elevator");
    }
    {
        tester.testEnterElevatorOutOfBounds();
    }

    {
        assertTest(tester.testRemoveAllFloorsNormalCase(), "For Normal Case: Remove all floors");
    }

    {
        assertTest(tester.testRemoveAllFloorsRandomOrderNormalCase()," For Normal Case: Remove all floors in random order");
    }
    {
        assertTest(tester.testRemoveNoneExistantFloorsErrorCase(), "For Error Case: Remove non existant floors");
    }

    {
        tester.testRemoveOutOfBoundFloorsEdgeCase();
    }

    {
        assertTest(tester.testCheckFloorNormalCase(), "Check floor function for Normal");
    }

    {
        assertTest(tester.testCheckFloorErrorCase(), "Check Floor Function For Error Case");
    }

    {
        assertTest(tester.testMoveNormalCaseMovingUp(), "Check Move Function Normal Case moving up");
    }

    {
        assertTest(tester.testMoveNormalCaseMovingDown(), "Check Move Function Normal Case moving down");
    }

    {
        assertTest(tester.testMoveFloorDNE(), "Check Move Function if floors DNE");
    }

    {
        assertTest(tester.testMoveNoPassengerOrigin(), "Check Move Function if there are no passanger" );
    }

    {
        assertTest(tester.testMoveDestinationFullElevators(), "Check Move Function there is a passanger in the destination");
    }

    {
        tester.testMoveOutOfBounds();
    }

    {
        tester.TestRandomMoveFunctionEdgeCase();
    }
    {
        assertTest(tester.testInsertFloorNormalCase(), "Testing Inserting floors after Removing them ");
    }
    
    {
        assertTest(tester.testInsertFloorErrorCase(), "Testing Error Case if floor is already there");
    }

    {
        tester.testDeepCopyOfCopyConsNormalCase();
    }
    {
        tester.testDeepCopyOfCopyConsEdgeCase();
    }

    {
        tester.testDeepCopyOfAssignmentOpeNormalCase();
    }
    {
        tester.testDeepCopyOfAssignmentOpeEdgeCase();
    }
    
    return 0;
}

void assertTest(bool bol, string statment){
    if (bol)
        cout << "Test Passed " << statment << "\n" << endl;
    else
        cout << "Test Failed " << statment << "\n" << endl;
}

// Inserts 300 nodes at Head
bool Tester::testInsertAtHeadNormalCase(){
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i = 300; i>=0; i--) {

        if (!anElev.insertAtHead(i)) {
            return false;
        }
    }
    return true;

}
// tests inserts at the head error case
bool Tester::testInsertAtHeadErrorCase() {
    Elevator anElev;
    anElev.insertAtHead(0);
    for (int i = 1; i <= 10; i++) {
        if (anElev.insertAtHead(i) == true){
            return false;
        }
    }

    return true;

}
// test insert at tail 300 nodes
bool Tester::testinsertAtTailNormalCase(){
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i=1;i<=300;i++)
        if (anElev.insertAtTail(i) == false)
            return false;

    return true;
}

bool Tester::testinsertAtTailErrorCase(){
    Elevator anElev;
    anElev.insertAtTail(11);
    for (int i = 1; i <= 11; i++) {

        if (anElev.insertAtTail(i) == true) {
            return false;
        }
    }
    return true;
}
// test Enter Elevator if there are no people at the floor
bool Tester::testEnterElevatorNormalCase(){
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i);
    }
    for (int i=1;i<=10;i++) {
        if (anElev.enter(i, to_string(i)) == false)
            return false;
    }
    return true;
}
// test enter error case if there are passangers on the floor
bool Tester::testEnterElevatorErrorCase(){
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i, to_string(i));

        if (anElev.enter(i, to_string(i)) == true)
            return false;
    }
    return true;
}
//tests out of bounds for entering elevator
void Tester::testEnterElevatorOutOfBounds(){
    Elevator anElev;
    for (int i = 1; i <= 10; i++) {
        anElev.insertAtTail(i, to_string(i));
    }
    
    cout << "Testing Exception Handling for Entering out of bound floors" << endl;
    try {
        anElev.enter(0,"0");
        assertTest(false,"Exception not thrown for entering out of bound floor");
    }
    catch (...){
        assertTest(true, "exception thrown correctly for entering out of bound floor");

    }

    try {
        anElev.enter(11,"11");
        assertTest(false,"Exception not thrown for entering out of bound floor");
    }
    catch (...){
        assertTest(true, "exception thrown correctly for entering out of bound floor");

    }
}
// test normal case if remove all floor works 
bool Tester::testRemoveAllFloorsNormalCase() {
    Elevator anElev;
    for (int i = 1; i <= 10; i++) {
        anElev.insertAtTail(i, to_string(i));
    }
    for (int i = 1; i <= 10; i++) {
        if (anElev.removeFloor(i) == false)
            return false;
    }

    return true;

}
bool Tester::testRemoveAllFloorsRandomOrderNormalCase() {
    Elevator anElev;
    for (int i = 1; i <= 10; i++) {
        anElev.insertAtTail(i, to_string(i));
    }
    // removes all elevators in different order after all elevators have been placed
    if (anElev.removeFloor(4) == false)
        return false;
    if (anElev.removeFloor(7) == false)
        return false;
    if (anElev.removeFloor(1) == false)
        return false;
    if (anElev.removeFloor(6) == false)
        return false;
    if (anElev.removeFloor(10) == false)
        return false;
    if (anElev.removeFloor(9) == false)
        return false;
    if (anElev.removeFloor(2) == false)
        return false;
    if (anElev.removeFloor(5) == false)
        return false;
    if (anElev.removeFloor(3) == false)
        return false;
    if (anElev.removeFloor(8) == false)
        return false;

    return true;
}


bool Tester::testRemoveNoneExistantFloorsErrorCase(){
    Elevator anElev;
    for (int i = 1; i <= 10; i++) {
        anElev.insertAtTail(i, to_string(i));
        anElev.removeFloor(i);
        if (anElev.removeFloor(i) == true)
            return false;
    }
    return true;
}
void Tester::testRemoveOutOfBoundFloorsEdgeCase(){
    Elevator anElev;
    for (int i = 1; i <= 10; i++) {
        anElev.insertAtTail(i, to_string(i));
}

    cout << "Testing Exception Handling for removing out of bound floors" << endl;
    try {
        anElev.removeFloor(0);
        assertTest(false,"Exception not thrown for removing out of bound floor");
    }
    catch (...){
        assertTest(true, "exception thrown correctly for removing out of bound floor");

    }

    try {
        anElev.removeFloor(11);
        assertTest(false,"Exception not thrown for removing out of bound floor");
    }
    catch (...){
        assertTest(true, "exception thrown correctly for removing out of bound floor");

    }
}

//test moving up normal test case
bool Tester::testMoveNormalCaseMovingUp(){
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i);
    }
    anElev.enter(1,"Abdel");
    anElev.move(1,10);
    if (anElev.m_ground->m_passenger == "" and anElev.m_top->m_passenger == "Abdel")
        return true;
    return false;
}
// test moving down test case
bool Tester::testMoveNormalCaseMovingDown(){
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i);
    }
    anElev.enter(10,"Abdel");
    if (anElev.move(10, 1) and anElev.m_ground->m_passenger == "Abdel" and anElev.m_top->m_passenger == "")
        return true;
    return false;
}
// test if there is a passanger is at detination
bool Tester::testMoveDestinationFullElevators() {
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i);
    }
    anElev.enter(1,"Abdel");
    anElev.enter(10,"del");

    if (anElev.move(1,10) == false)
        return true;
    return false;
}
// test if there are no passanger to move at orgin edge case
bool Tester::testMoveNoPassengerOrigin(){
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i);
    }

    if (anElev.move(1,10) == false)
        return true;
    return false;
}

//test if destination floor DNE edge case
bool Tester::testMoveFloorDNE() {
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i);
    }
    anElev.enter(1,"Abdel");
    anElev.removeFloor(5);

    if (anElev.move(1,5) == true)
        return false;
    return true;
}

void Tester::testMoveOutOfBounds(){
    Elevator anElev;
    for (int i = 1; i <= 10; i++) {
        anElev.insertAtTail(i, to_string(i));
    }
    anElev.enter(1,"Abdel");
    anElev.enter(10,"del");
    cout << "Testing Exception Handling for Moving out of bound floors" << endl;
    try {
        anElev.move(1,11);
        assertTest(false,"Exception not thrown for moving out of bound floor");
    }
    catch (...){
        assertTest(true, "exception thrown correctly for moving out of bound floor");

    }

    try {
        anElev.move(10,0);
        assertTest(false,"Exception not thrown for moving out of bound floor");
    }
    catch (...){
        assertTest(true, "exception thrown correctly for moving out of bound floor");

    }
}
// test check floor normal case
bool Tester::testCheckFloorNormalCase() {

    //Creating an elevator with 10 floors
    Elevator anElev;
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i);
    }
    for (int i=1;i<=10;i++) {
        if (anElev.checkFloor(i) == false)
            return false;
    }
    return true;
}
// test if check floor works when thoses floors dont exist
bool Tester::testCheckFloorErrorCase() {
    Elevator anElev;
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i);
    }

    anElev.removeFloor(3);
    anElev.removeFloor(4);
    anElev.removeFloor(5);

    if (anElev.checkFloor(3))
        return false;
    if (anElev.checkFloor(4))
        return false;
    if (anElev.checkFloor(5))
        return false;

    return true;
}
// test edge case if flors DNE
void Tester::TestRandomMoveFunctionEdgeCase(){
    Elevator anElev;
    assertTest(!anElev.move(1,1), "Edge Case if origin equals destination");
    for (int i=-10;i<=10;i++){
        anElev.insertAtTail(i);
    }

    anElev.enter(-10,"Abdel");
    assertTest(anElev.move(-10,-3), "testing Negative Floors move");
}
// test Inserting floors that have been removed
bool Tester::testInsertFloorNormalCase(){
    Elevator anElev;
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i);
    }

    anElev.removeFloor(3);
    anElev.removeFloor(4);
    anElev.removeFloor(5);

    if (!anElev.insertFloor(3))
        return false;
    if (!anElev.insertFloor(4))
        return false;
    if (!anElev.insertFloor(5))
        return false;

    return true;
}
// test inserting floors that already exist
bool Tester::testInsertFloorErrorCase() {
    Elevator anElev;
    for (int i=1;i<=10;i++){
        anElev.insertAtTail(i);
    }
    if (anElev.insertFloor(3))
        return false;
    if (anElev.insertFloor(4))
        return false;
    if (anElev.insertFloor(5))
        return false;
    
    return true;
}
// test if copy cons creates a deep copy
void Tester::testDeepCopyOfCopyConsNormalCase() {
    Elevator anElev;
    for (int i=1;i<=10;i++) {
        anElev.insertAtTail(i, to_string(i));
    }

    Elevator theElev(anElev);

    cout << "original obj " << anElev.m_top << " copy obj " << theElev.m_top  << endl;
    Floor *theTemp = theElev.m_ground;
    Floor *anTemp = anElev.m_ground;

    for (int i=1;i<=10;i++) {
        if (theTemp == anTemp)
            assertTest(false,"Copy Constr Pointers dont equal each other");
        theTemp = theTemp->m_next;
        anTemp = anTemp->m_next;
    }
    assertTest(true,"Copy Constr Pointers dont equal each other");

    Floor *tempThe = theElev.m_ground;
    Floor *tempAn = anElev.m_ground;
    for (int i=1;i<=10;i++) {
        if (tempThe->m_passenger != tempAn->m_passenger and tempThe->m_floorNum != tempAn->m_floorNum)
            assertTest(false,"Copy Constr Similar Member Varaibles");
        tempThe = tempThe->m_next;
        tempAn = tempAn->m_next;
    }
    assertTest(true,"Copy Constr Similar Member Varaibles");


    for (int i=1;i<=10;i++) {
        anElev.removeFloor(i);

        if (!theElev.checkFloor(i))
            assertTest(false, "Copy Constr Deep copy created");

    }
    assertTest(true, "Copy Constr Deep copy created");

}


// test if copy cons creates a deep copy of 1 and 2 eleveators
void Tester::testDeepCopyOfCopyConsEdgeCase() {
    Elevator anElev;
    anElev.insertAtTail(1);

    Elevator theElev(anElev);

    if (theElev.m_top->m_floorNum == anElev.m_top->m_floorNum)
        assertTest(true,"Copy Constr floor values are the same edge case");
    else
        assertTest(false,"Copy Constr floor values are the same edge case");

    if (anElev.m_top == theElev.m_top)
        assertTest(false, "Copy Constr top floor mem location are different");

    assertTest(true, "Copy Constr top floor mem location are different");
    anElev.insertAtTail(2);

    Elevator twoFloorElev(anElev);

    if ((anElev.m_top->m_floorNum != twoFloorElev.m_top->m_floorNum) or (anElev.m_ground->m_floorNum != twoFloorElev.m_ground->m_floorNum))
        assertTest(false,"Copy Constr floor values are the same for two floors edge case");
    else
        assertTest(true,"Copy Constr floor values are the same for two floors edge case");

    if (twoFloorElev.m_top == anElev.m_top or twoFloorElev.m_ground == anElev.m_ground)
        assertTest(false, "Copy Constr Two floor Mem location are different");

    assertTest(true, "Copy Constr Two floor Mem location are different");

}

void Tester::testDeepCopyOfAssignmentOpeEdgeCase() {
    Elevator anElev;
    anElev.insertAtTail(1);

    Elevator theElev = (anElev);

    if (theElev.m_top->m_floorNum == anElev.m_top->m_floorNum)
        assertTest(true,"Assignment Operator floor values are the same edge case");
    else
        assertTest(false,"Assignment Operator floor values are the same edge case");

    if (anElev.m_top == theElev.m_top)
        assertTest(false, "Assignment Operator top floor mem location are different");

    assertTest(true, "Assignment Operator top floor mem location are different");
    anElev.insertAtTail(2);

    Elevator twoFloorElev = (anElev);

    if ((anElev.m_top->m_floorNum != twoFloorElev.m_top->m_floorNum) or (anElev.m_ground->m_floorNum != twoFloorElev.m_ground->m_floorNum))
        assertTest(false,"Assignment Operator floor values are the same for two floors edge case");
    else
        assertTest(true,"Assignment Operator floor values are the same for two floors edge case");

    if (twoFloorElev.m_top == anElev.m_top or twoFloorElev.m_ground == anElev.m_ground)
        assertTest(false, "Assignment Operator Two floor Mem location are different");

    assertTest(true, "Assignment Operator Two floor Mem location are different");
}

void Tester::testDeepCopyOfAssignmentOpeNormalCase() {
    Elevator anElev;
    for (int i=1;i<=10;i++) {
        anElev.insertAtTail(i, to_string(i));
    }

    Elevator theElev = (anElev);

    cout << "original obj " << anElev.m_top << " copy obj " << theElev.m_top  << endl;
    Floor *theTemp = theElev.m_ground;
    Floor *anTemp = anElev.m_ground;

    for (int i=1;i<=10;i++) {
        if (theTemp == anTemp)
            assertTest(false,"Assignment Operator Pointers dont equal each other");
        theTemp = theTemp->m_next;
        anTemp = anTemp->m_next;
    }
    assertTest(true,"Assignment Operator Pointers dont equal each other");

    Floor *tempThe = theElev.m_ground;
    Floor *tempAn = anElev.m_ground;

    for (int i=1;i<=10;i++) {
        if (tempThe->m_passenger != tempAn->m_passenger and tempThe->m_floorNum != tempAn->m_floorNum)
            assertTest(false,"Assignment Operator Similar Member Varaibles");
        tempThe = tempThe->m_next;
        tempAn = tempAn->m_next;
    }
    assertTest(true,"Assignment Operator Similar Member Varaibles");


    for (int i=1;i<=10;i++) {
        anElev.removeFloor(i);

        if (!theElev.checkFloor(i))
            assertTest(false, "Assignment Operator Deep copy created");

    }
    assertTest(true, "Assignment Operator Deep copy created");
}
