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
/************************************************** Defineds **********************************************************/
#define SERIAL_COM_PORT_NAME "\\\\.\\COM9"
/************************************************** Names *************************************************************/
/* Using std */
using namespace std;
/************************************************** Variables *********************************************************/
Serial *Serial::_Instance = nullptr;
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
/* This function open media */
bool Serial::Open() {

    if(_Port != nullptr) {
        status.Set(Messages::Fault); 
        return false;
    }

    DWORD byteswritten;
    _Port = CreateFile(
        SERIAL_COM_PORT_NAME,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (_Port == INVALID_HANDLE_VALUE)
    {
        status.Set(Messages::Fault_Find);
        return false;
    }

    COMMTIMEOUTS comTimeOut;
    GetCommTimeouts(_Port, &comTimeOut);
    comTimeOut.ReadIntervalTimeout = 1;
    comTimeOut.ReadTotalTimeoutMultiplier = 1;
    comTimeOut.ReadTotalTimeoutConstant = 1;
    SetCommTimeouts(_Port, &comTimeOut);

    SetCommMask(_Port, EV_RXCHAR);

    status.Set(Messages::Success);

    return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* This function update setting media */
bool Serial::Update(uint32_t Speed) {     

    if(_Port == nullptr) {
        status.Set(Messages::Fault_Find);
        return false;
    }

    DCB dcb;

    if (!GetCommState(_Port, &dcb)) {
        status.Set(Messages::Fault_Update);
        return false;
    }

    dcb.BaudRate = Speed;
    dcb.ByteSize = 7;
    dcb.Parity = EVENPARITY;
    dcb.StopBits = ONESTOPBIT;

    if (!SetCommState(_Port, &dcb)) {
        status.Set(Messages::Fault_Update);
        return false;
    }
    
    status.Set(Messages::Success);

    return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* This function rewrite media function for body of send*/
bool Serial::Send(uint8_t *Message, uint32_t Length) {

    if(_Port == nullptr) {
        status.Set(Messages::Fault_Find); 
        return false;
    }

    DWORD byteswritten;
    WriteFile(_Port, (PCVOID)Message, 1, &byteswritten, NULL);

    if(byteswritten != Length) {
        status.Set(Messages::Fault_Send);
        return false;
    }

    status.Set(Messages::Success);

    return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* This function rewrite media function for body of receive*/
bool Serial::Receive(uint8_t *Message, uint32_t *Length) {
    status.Set(Messages::Fault_Find); 

    if(_Port == nullptr) {
        return false;
    }   

    DWORD   My_Status;
    LPDWORD My_Length = 0;
    *Length = 0;

    //WaitCommEvent(_Port, &My_Status, 0);
    if(!ReadFile( _Port, (LPVOID)Message,  1024, My_Length, NULL)) {
        status.Set(Messages::Fault_Receive);
        return false;
    }
    
    if(My_Length) {
        *Length = *My_Length;
    }
    status.Set(Messages::Success);

    return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* This function close media */
bool Serial::Close() {
    status.Set(Messages::Fault_Find); 

    if(_Port == nullptr) {
        return false;
    }    

    CloseHandle(_Port);
    _Port == nullptr;

    status.Set(Messages::Success);

    return true;
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