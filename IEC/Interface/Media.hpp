#ifndef MEDIA_HPP
#define MEDIA_HPP
/************************************************** Description *******************************************************/
/*
    File : Media.hpp
    Programmer : Mohammad Lotfi
    Used : Use header
    Design Pattern : Nothing
    Types of memory : Nothing
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
#include "Status.hpp"
#include "iostream"
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
/* Media is interface with virtual functions to use other media for example (UART,LAN,RS485,USB,...) and all things that follows this structure */
class Media {    
    public: 
        /* This function for send data*/
        virtual Status* Send(string Message, uint32_t Length) = 0;
        /* This function for receive data*/
        virtual Status* Receive(string *Message, uint32_t *Length) = 0;
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