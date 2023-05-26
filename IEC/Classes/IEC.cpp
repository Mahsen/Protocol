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
    Last Update : 2023/5/17
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
uint8_t IEC::GetBCC  (uint8_t *Data, uint32_t Length)
{
	uint8_t bcc = 0;

	for(uint32_t Index=1; Index<Length; Index++)
	{
		bcc ^= Data[Index];
	}

	return bcc;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* Set address of device that use in connection */
Status<IEC::Messages>* ClientIEC::SetAddress(char *Address) {
    /* Disconnect if current address diffrent with old address */
    if(strcmp(Address, _Address) != 0) {
            DisConnect();
    }
    /* Replace address */
    strcpy(_Address, Address);

    status.Set(Messages::Success);
    return &status;
}  
/*--------------------------------------------------------------------------------------------------------------------*/
/* Set mode of device that use in connection */
Status<IEC::Messages>* ClientIEC::SetMode(char Mode) {
    /* Disconnect if current mode diffrent with old mode */
    if(Mode != _Mode) {
            DisConnect();
    }
    /* Replace Mode */
    _Mode = Mode;

    status.Set(Messages::Success);
    return &status;
}  
/*--------------------------------------------------------------------------------------------------------------------*/
/* Command to connect IEC */
Status<IEC::Messages>* ClientIEC::Connect() {

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
    sprintf((char*)_Data, "/?%s!\r\n", _Address);
    if(!_Media->Send(_Data, strlen((char*)_Data))) {
        status.Set(Messages::Fault_Media);
        return &status;
    }

    memset(_Data, 0, sizeof(_Data));
    _Length = 0;
    if(!_Media->Receive(&_Data[_Length], &_Length)) {
        if(DisConnect()->Get() == Messages::Success)
        {
            status.Set(Messages::Fault_TimeOut);
        }
        return &status;
    } 

    char *Identification = strchr((char*)_Data, '/');
    if(Identification == nullptr) {
        status.Set(Messages::Fault_Data);
        return &status;
    }

    if((Identification[4] - '0') > 9) {
        status.Set(Messages::Fault_Speed);
        return &status;
    }

    /* Change speed line */
    _Wait(50);
    if(!_Media->Update(IEC_Table_BoadRate[Identification[4] - '0'])) {
        status.Set(Messages::Fault_Media);
        return &status;
    }
    _Media->Clear();
    _Wait(50);

    sprintf((char*)_Data, "%c0%c%c\r\n", IEC_CHAR_ACK, Identification[4], _Mode);
    if(!_Media->Send(_Data, strlen((char*)_Data))) {
        status.Set(Messages::Fault_Media);
        return &status;
    }

    memset(_Data, 0, sizeof(_Data));
    _Length = 0;
    if(!_Media->Receive(&_Data[_Length], &_Length)) {
        if(DisConnect()->Get() == Messages::Success)
        {
            status.Set(Messages::Fault_TimeOut);
        }
        return &status;
    } 
    _Media->Clear();

    state.Set(States::Connected);

    status.Set(Messages::Success);
    return &status;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* Command to connect IEC with Address */
Status<IEC::Messages>* ClientIEC::Connect(char *Address) {

    if(SetAddress(Address)->Get() != Messages::Success) {
        return &status;
    }

    return Connect();
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* Command to connect IEC with address and mode */
Status<IEC::Messages>* ClientIEC::Connect(char *Address, char Mode) {

    if(SetMode(Mode)->Get() != Messages::Success) {
        return &status;
    }

    return Connect(Address);
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* Command to connect IEC with Address */
Status<IEC::Messages>* ClientIEC::GetData(char* Data, uint32_t Length) {

    Data = (char*)_Data;
    Length = _Length;

    status.Set(Messages::Success);
    return &status;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* Command to execute data to IEC with callback */
Status<IEC::Messages>* ClientIEC::Execute(char *Data, void (*CallBack)(char *Data, uint32_t Length)) {
    /* Send connect command if IEC is not connected */
    if(state.Get() != States::Connected) {
        if(Connect()->Get() != Messages::Success) {
            return &status;
        }
    }

    state.Set(States::Executeing);
    
    cout << Data << endl;
    
    uint32_t Length = 0;
	char BCC;
	char *pch, *etx;

	pch = NULL;
	etx = NULL;
	
	pch = strtok((char*)Data, (char*)IEC_CHAR_ETX);	
	etx = pch;
	
	if(etx == NULL)
	{
		pch = strtok((char*)Data, (char*)IEC_CHAR_EOT);
	}

	while(pch)
	{
		Length = strlen(pch);

		sprintf((char*)_Data, "%s%c", pch, (etx)?IEC_CHAR_ETX:IEC_CHAR_EOT);
		BCC = GetBCC(_Data, ++Length);
		_Data[Length++] = BCC;

		SendReceive:

        _Media->Clear();
        if(!_Media->Send(_Data, strlen((char*)_Data))) {
            status.Set(Messages::Fault_Media);
            return &status;
        }

        memset(_Data, 0, sizeof(_Data));
        _Length = 0;
        if(!_Media->Receive(&_Data[_Length], &_Length)) {
            if(DisConnect()->Get() == Messages::Success)
            {
                status.Set(Messages::Fault_TimeOut);
            }
            return &status;
        } 

		if(CallBack)
		{
			if(_Length)
			{
				CallBack((char*)_Data, (_Length-1));
			}
		}
		
		if((_Data[_Length-2] == (uint8_t)IEC_CHAR_EOT) || ((_Data[_Length-2] != (uint8_t)IEC_CHAR_ETX) && (_Data[_Length-1] == (uint8_t)IEC_CHAR_EOT)))
		{
			sprintf((char*)_Data, "%c", IEC_CHAR_ACK);
			Length = 1;
			
			goto SendReceive;
		}		
		
		pch = NULL;
		etx = NULL;
		
		pch = strtok(NULL, (char*)IEC_CHAR_ETX);	
		etx = pch;
		
		if(etx == NULL)
		{
			pch = strtok(NULL, (char*)IEC_CHAR_EOT);
		}

	}

    state.Set(States::Connected);

    status.Set(Messages::Success);
    return &status;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* Command to execute data to IEC */
Status<IEC::Messages>* ClientIEC::Execute(char *Data) {
    return Execute(Data, nullptr);
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* Command to disconnect IEC */
Status<IEC::Messages>* ClientIEC::DisConnect() {

    if(state.Get() == States::DisConnected) {
        status.Set(Messages::Success);
        return &status;
    }

    state.Set(States::DisConnecting);
    if(state.Get() == States::Connected) {
        sprintf((char*)_Data, "%cB0%cq", IEC_CHAR_SOH, IEC_CHAR_ETX);
        if(!_Media->Send(_Data, strlen((char*)_Data))) {
            status.Set(Messages::Fault_Media);
            return &status;
        }
    }
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