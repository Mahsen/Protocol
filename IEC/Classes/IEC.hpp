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
/* String of everything head */
#include <string.h>
#include "../Interface/Media.hpp"
#include "../Interface/Status.hpp"
#include "../Interface/State.hpp"
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
class IEC {
    public:
        Media* _Media;
        void (*_Wait)(uint32_t);
        char _Address[16];

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
            Fault_TimeOut
        };
        Status<Messages> status;
        const char* Status2String[5] = {"Success", "Fault", "Fault_Media", "Fault_TimeOut"};

        void ShowStatus() {
            cout << "ShowStatus(" << Status2String[(int)status.Get()] << ")" << endl;
        }

        IEC(Media* P_Media, void (*P_Wait)(uint32_t)) {
            state.Set(States::UnInited);
            _Media = P_Media;
            _Wait = P_Wait;
        };
};
/*--------------------------------------------------------------------------------------------------------------------*/
class ClientIEC : private IEC {
    public:
        ClientIEC(Media* P_Media, void (*P_Wait)(uint32_t)) : IEC(P_Media, P_Wait) {};

        Status<Messages>* SetAddress(char *Address);
        Status<Messages>* Connect();
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