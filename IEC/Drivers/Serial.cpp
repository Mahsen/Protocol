/************************************************** Description *******************************************************/
/*
    File : Serial.cpp
    Programmer : Mohammad Lotfi
    Used : Send & Receive from com port
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
#include "Serial.hpp"
#include "iostream"
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/* Using std */
using namespace std;
/************************************************** Variables *********************************************************/
Serial *Serial::Instance = nullptr;
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
/* This function rewrite media function for body of send*/
Status* Serial::Send(string Message, uint32_t Length) {
    status.SetMessage(Serial::Message::Fault);

    /* This line represents everything in this section */
    cout << "Serial : Send()" << endl;
    status.SetMessage(Serial::Message::Success);

    return &status;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* This function rewrite media function for body of receive*/
Status* Serial::Receive(string *Message, uint32_t *Length) {
    status.SetMessage(Serial::Message::Fault);    

    /* This line represents everything in this section */
    cout << "Serial : Receive()" << endl;
    status.SetMessage(Serial::Message::Success);

    return &status;
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