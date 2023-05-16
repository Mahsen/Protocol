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
    private:
        Media* _Media;
        void (*_Wait)(uint32_t);

        /* All possible states */
        enum class States {
            UnInited,
            Initing,
            Inited,
            Connecting,
            Connected,
            DisConnecting,
            DisConnected
        };
        State<States> state;
    public:
        /* All possible messages */
        enum class Messages {
            Success,
            Fault,
            Fault_Media
        };
        Status<Messages> status;
        const string Status2String[5] = {"Success", "Fault", "Fault_Media"};

        void ShowStatus() {
            cout << "ShowStatus(" << Status2String[(int)status.Get()] << ")" << endl;
        }

        IEC(Media* P_Media, void (*P_Wait)(uint32_t)) {
            state.Set(States::UnInited);
            _Media = P_Media;
            _Wait = P_Wait;
        };
        
        Status<Messages>* Connect();
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