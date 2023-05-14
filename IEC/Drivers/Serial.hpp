#ifndef SERIAL_HPP
#define SERIAL_HPP
/************************************************** Description *******************************************************/
/*
    File : Serial.hpp
    Programmer : Mohammad Lotfi
    Used : Using
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
#include "../Interface/Media.hpp"
#include "../Interface/Status.hpp"
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
/*--------------------------------------------------------------------------------------------------------------------*/
/* Sample of media to useing RS485 (the RS485 is media with specific voltage levels used in industry) */
class Serial : public Media {    
    private: 

        /* Instance for single use */
        static Serial *Instance;
        Serial() {};
        Status status;
        /* All message explanations */
        const string Message2String[3] = {"Success", "Fault", "Fault_Media"};

    public: 
        /* All possible messages */
        enum class Message {
            Success,
            Fault,
            Fault_Media
        };

        /* Show current message on console */
        void ShowMessage() {
            cout << "Message : " << Message2String[(int)status.GetMessage()] << endl;
        }

        static Serial *getInstance() {
            if(Instance == nullptr) {
                Instance = new Serial();
            }

            return Instance;
        }

        Status* Send(string Message, uint32_t Length) override;
        Status* Receive(string *Message, uint32_t *Length) override;
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