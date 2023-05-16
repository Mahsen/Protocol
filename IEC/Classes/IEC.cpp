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
    Last Update : 2023/5/16
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
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
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
Status<IEC::Messages>* ClientIEC::SetAddress(char *Address) {
    if(strcmp(Address, _Address) != 0) {
            DisConnect();
    }

    strcpy(_Address, Address);

    status.Set(Messages::Success);
    return &status;
}  
/*--------------------------------------------------------------------------------------------------------------------*/
Status<IEC::Messages>* ClientIEC::Connect() {

    uint8_t Data[1024];
    uint32_t Length=0;

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
    sprintf((char*)Data, "/?%s!\r\n", _Address);
    _Media->Send(Data, strlen((char*)Data));

    if(!_Media->Receive(&Data[Length], &Length)) {
        if(DisConnect()->Get() == Messages::Success)
        {
            status.Set(Messages::Fault_TimeOut);
        }
        return &status;
    } 

    
    state.Set(States::Connected);

    status.Set(Messages::Success);
    return &status;
}
/*--------------------------------------------------------------------------------------------------------------------*/
Status<IEC::Messages>* ClientIEC::Execute(char *Data, uint32_t Length) {
    if(state.Get() != States::Connected) {
        if(Connect()->Get() != Messages::Success) {
            return &status;
        }
    }

    state.Set(States::Executeing);
    
    cout << Data << endl;

    state.Set(States::Connected);


    status.Set(Messages::Success);
    return &status;
}
/*--------------------------------------------------------------------------------------------------------------------*/
Status<IEC::Messages>* ClientIEC::DisConnect() {

    if(state.Get() == States::DisConnected) {
        status.Set(Messages::Success);
        return &status;
    }

    if(state.Get() == States::Connected) {
        _Media->Send((uint8_t*)"exit\r\n", 6);
    }

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