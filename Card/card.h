// -------------------------start header gaurds------------------------------
#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
// --------------------including system libraries-----------------------------
#include <stdio.h>
#include <stdint.h>
// -------------------create a structure for data-----------------------
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;
// ----------------------important names-----------------------
typedef enum EN_cardError_t
{
    CARD_OK = 0,               // 0
    WRONG_NAME,              // 1
    WRONG_EXP_DATE,        // 2
    WRONG_PAN                 // 3
}EN_cardError_t;
// ----------------card functions decleration------------------------------
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);
// -------------------------end header gaurds------------------------------
#endif // CARD_H_INCLUDED
