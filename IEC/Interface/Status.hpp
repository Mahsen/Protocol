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
class Status {

    public:

        /* All possible messages */
        enum class Message {
            Success,
            Fault,
            Fault_Media
        };

        /* Set current message from outside */
        void SetMessage(Message _Message) {
            this->_Message = _Message;
        }

        /* Set current message */
        Message GetMessage() {
            return _Message;
        }

        /* Show current message on console */
        virtual void ShowMessage() = 0;

    private:

        /* The variable holding the current message */
        Message _Message;
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