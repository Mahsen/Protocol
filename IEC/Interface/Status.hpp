#ifndef CTATUS_HPP
#define CTATUS_HPP
/************************************************** Description *******************************************************/
/*
    File : Status.hpp
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
/*
    Nothing
*/
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
/* All object to return their status need this object */
template <typename T_Message = int>
class Status {

    private:

        /* The variable holding the current message */
        T_Message _Message;

    public:
    
        /* Set current message from outside */
        void Set(T_Message Message) {
            this->_Message = Message;
        }

        /* Set current message */
        T_Message Get() {        
            return this->_Message;
        }

        /* Show current message on console */
        //virtual void ShowMessage() = 0;

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