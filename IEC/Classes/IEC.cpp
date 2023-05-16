/************************************************** Description *******************************************************/
/*
    File : IEC.cpp
    Programmer : Mohammad Lotfi
    Used : Managing IEC Protocol
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
#include "IEC.hpp"
#include "../Interface/Media.hpp"
/************************************************** Defineds **********************************************************/
#define IEC_TIMEOUT_REQUEST 10 //ms
/************************************************** Names *************************************************************/
/*
    Nothing
*/
/************************************************** Variables *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
Status<IEC::Messages>* IEC::Connect() {

    if(state.Get() == States::Connected) {
        status.Set(Messages::Success);
        return &status;
    }

    state.Set(States::Initing);
    if(!_Media->Open()) {
        status.Set(Messages::Fault_Media);
        return &status;
    }
    if(!_Media->Update(300)) {
        status.Set(Messages::Fault_Media);
        return &status;
    }
    
    state.Set(States::Inited);

    state.Set(States::Connecting);
    _Media->Send((uint8_t*)"/?!\r\n", 5);
    uint8_t Data[1024];
    uint32_t Length=0, Length_Feed=0, TimeOut=0;
    do {
        Length_Feed = Length;
        _Wait(IEC_TIMEOUT_REQUEST);
        _Media->Receive(Data, &Length); 
        TimeOut++;     
    } while((Length != Length_Feed) && (TimeOut<10));
    cout << Length << endl;
    state.Set(States::Connected);

    status.Set(Messages::Success);
    return &status;
}
/*--------------------------------------------------------------------------------------------------------------------*/
Status<IEC::Messages>* IEC::DisConnect() {

    if(state.Get() == States::DisConnected) {
        status.Set(Messages::Success);
        return &status;
    }

    _Media->Send((uint8_t*)"exit\r\n", 6);
    state.Set(States::DisConnecting);
    if(!_Media->Close()) {
        status.Set(Messages::Fault_Media);
        return &status;
    }
    state.Set(States::DisConnected);

    status.Set(Messages::Success);
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