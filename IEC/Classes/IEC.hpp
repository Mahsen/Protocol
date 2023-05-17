#ifndef IEC_HPP
#define IEC_HPP
/************************************************** Description *******************************************************/
/*
    File : IEC.hpp
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
/* String of everything head */
#include <string.h>
/* Media class is there */
#include "../Interface/Media.hpp"
/* Status class is there */
#include "../Interface/Status.hpp"
/* State class is there */
#include "../Interface/State.hpp"
/************************************************** Defineds **********************************************************/
#define IEC_CHAR_SOH ""
#define IEC_CHAR_STX ""
#define IEC_CHAR_ETX ""
#define IEC_CHAR_EOT ""
#define IEC_CHAR_ACK ""
#define IEC_CHAR_NAK ""
/************************************************** Names *************************************************************/
/* Using std */
using namespace std;
/************************************************** Variables *********************************************************/
const uint32_t IEC_Table_BoadRate[] = {305, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
/************************************************** Opjects ***********************************************************/
class IEC {
    public:
        Media* _Media;
        void (*_Wait)(uint32_t);
        char _Address[16];
        char _Mode;
        uint8_t _Data[1024];
        uint32_t _Length;

        /* All possible states */
        enum class States {
            UnInited,
            Initing,
            Inited,
            Connecting,
            Connected,
            Executeing,
            DisConnecting,
            DisConnected
        };
        State<States> state;
    
        /* All possible messages */
        enum class Messages {
            Success,
            Fault,
            Fault_Media,
            Fault_TimeOut,
            Fault_Data,
            Fault_Speed
        };
        Status<Messages> status;
        const char* Status2String[6] = {"Success", "Fault", "Fault_Media", "Fault_TimeOut", "Fault_Data", "Fault_Speed"};

        void ShowStatus() {
            cout << "ShowStatus(" << Status2String[(int)status.Get()] << ")" << endl;
        }

        IEC(Media* P_Media, void (*P_Wait)(uint32_t)) {
            state.Set(States::UnInited);
            _Media = P_Media;
            _Wait = P_Wait;
            memset(_Data, 0, sizeof(_Data));
            _Length = 0;
        };
        uint8_t GetBCC(uint8_t *Data, uint32_t Length);
};
/*--------------------------------------------------------------------------------------------------------------------*/
class ClientIEC : private IEC {
    public:
        ClientIEC(Media* P_Media, void (*P_Wait)(uint32_t)) : IEC(P_Media, P_Wait) { SetAddress(""); SetMode('0'); };

        Status<Messages>* SetAddress(char *Address);
        Status<Messages>* SetMode(char Mode);
        Status<Messages>* GetData(char* Data, uint32_t Length);
        Status<Messages>* Connect();
        Status<Messages>* Connect(char *Address);
        Status<Messages>* Connect(char *Address, char Mode);
        Status<Messages>* Execute(char *Data, uint32_t Length, void (*CallBack)(char *Data, uint32_t Length));
        Status<Messages>* Execute(char *Data, uint32_t Length);
        Status<Messages>* DisConnect();
};
/************************************************** Functions *********************************************************/
/*
    Nothing
*/
/************************************************** Tasks *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
#endif