#ifndef SERIAL_HPP
#define SERIAL_HPP
/************************************************** Description *******************************************************/
/*
    File : Serial.hpp
    Programmer : Mohammad Lotfi
    Used : Using send and receive to comport windows
    Design Pattern : Singleton
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2023/5/26
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
#include<iostream>
#include<sstream>
#include<fstream>
#include<windows.h>
#include<string>
#include<thread>
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
/* Sample of media to useing RS485 (the RS485 is media with specific voltage levels used in industry) */
class Serial : public Media {    
    private: 

        /* Instance for single use */
        static Serial *_Instance;
        /* Use serial com port windows */
        HANDLE _Port;
        /* Initialize private variable */
        Serial() {
            _Port = nullptr;
            _Instance = nullptr; 
        }       

    public: 

        /* All possible messages */
        enum class Messages {
            Success,
            Fault,
            Fault_TimeOut,
            Fault_Find,
            Fault_Update,
            Fault_Send,
            Fault_Receive
        };
        Status<Messages> status;        

        static Serial *getInstance() {
            if(_Instance == nullptr) {
                _Instance = new Serial();
            }

            return _Instance;
        }

        bool Open() override;
        bool Update(uint32_t Speed) override;
        bool Send(uint8_t *Message, uint32_t Length) override;
        bool Receive(uint8_t *Message, uint32_t *Length) override;
        bool Clear() override;
        bool Reset() override;
        bool Close() override;
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