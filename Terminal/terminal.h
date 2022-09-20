// -------------------------start header gaurds------------------------------
#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED
// --------------------including system libraries-----------------------------
#include <stdio.h>
#include <stdint.h>
// --------------------including application libraries-----------------------------
#include "../Card/card.h"
// -------------------create a structure for data-----------------------
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;
// ----------------------important names-----------------------
typedef enum EN_terminalError_t
{
    TERMINAL_OK = 4,         // 4
    WRONG_DATE,              // 5
    EXPIRED_CARD,             // 6
    INVALID_CARD,             // 7
    INVALID_AMOUNT,         // 8
    EXCEED_MAX_AMOUNT,  // 9
    INVALID_MAX_AMOUNT  // 10
}EN_terminalError_t;
// ----------------terminal functions decleration------------------------------
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);
// -------------------------end header gaurds------------------------------
#endif // TERMINAL_H_INCLUDED
