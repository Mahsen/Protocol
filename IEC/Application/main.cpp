/************************************************** Description *******************************************************/
/*
    File : main.cpp
    Programmer : Mohammad Lotfi
    Used : Using IEC class
    Design Pattern : Nothing
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2023/5/13
*/
/************************************************** Warnings **********************************************************/
/*
    Nothing
*/
/************************************************** Wizards ***********************************************************/
/*
    Nothing
*/
/************************************************** Includes **********************************************************/
#include "iostream"
#include "../Drivers/Serial.hpp"
#include "../Classes/IEC.hpp"
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/* Using std */
using namespace std;
/************************************************** Variables *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
void Delay_ms(uint32_t ms) {
    Sleep(ms);
}
/*--------------------------------------------------------------------------------------------------------------------*/
int main() {

    cout << "Start ----------------------- " << endl;

    Serial *_Serial = Serial::getInstance();
    ClientIEC *_ClientIEC = new ClientIEC(_Serial, &Delay_ms);
    
    //IEC::Messages::Fault;
    _ClientIEC->SetAddress((char*)"01");
    _ClientIEC->Connect();
    _ClientIEC->Execute((char*)"11111");
    _ClientIEC->SetAddress((char*)"02");
    _ClientIEC->Execute((char*)"22222");
    _ClientIEC->DisConnect();

    cout << "Finish ----------------------- " << endl;

    return 0;
}
/************************************************** Tasks *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/