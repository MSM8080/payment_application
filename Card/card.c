// --------------------including system libraries-----------------------------
#include <string.h>
// --------------------including application libraries-------------------
#include "card.h"
// ------------------functions getCardHolderName-----------------------
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    printf("Enter Card Holder Name: ");
    gets(cardData->cardHolderName);

    if (cardData->cardHolderName == NULL)
    {
        strcpy(cardData->cardHolderName, "\0");
        return WRONG_NAME;
    }
    else if ((strlen(cardData->cardHolderName) > 24) || (strlen(cardData->cardHolderName) < 20))
    {
        strcpy(cardData->cardHolderName, "\0");
        return WRONG_NAME;
    }
    else
        return CARD_OK;
}
// ------------------functions getCardExpiryDate-----------------------
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    printf("Enter Card Expiry Date: ");
    gets(cardData->cardExpirationDate);

    // good format (MM/YY)
    if (cardData->cardExpirationDate == NULL) // check null date
    {
        strcpy(cardData->cardExpirationDate, "\0");
        return WRONG_EXP_DATE;
    }
    else if (strlen(cardData->cardExpirationDate) != 5) // check date formate length
    {
        strcpy(cardData->cardExpirationDate, "\0");
        return WRONG_EXP_DATE;
    }
    else if ((cardData->cardExpirationDate[0] == 48) && (cardData->cardExpirationDate[1] == 48)) // check MM = 00
    {
        strcpy(cardData->cardExpirationDate, "\0");
        return WRONG_EXP_DATE;
    }
    else if ((cardData->cardExpirationDate[0] < 48) || (cardData->cardExpirationDate[0] > 49)) // first M should be (0:1)
    {
        strcpy(cardData->cardExpirationDate, "\0");
        return WRONG_EXP_DATE;
    }
    else if ((cardData->cardExpirationDate[1] < 49) || (cardData->cardExpirationDate[1] > 57)) // second M should be (1:9)
    {
        strcpy(cardData->cardExpirationDate, "\0");
        return WRONG_EXP_DATE;
    }
    else if ((cardData->cardExpirationDate[0] == 49) && (cardData->cardExpirationDate[1] > 50)) // no month over 12
    {
        strcpy(cardData->cardExpirationDate, "\0");
        return WRONG_EXP_DATE;
    }
    else if ((cardData->cardExpirationDate[3] < 48) || (cardData->cardExpirationDate[3] > 57)) // first Y should be (0:9)
    {
        strcpy(cardData->cardExpirationDate, "\0");
        return WRONG_EXP_DATE;
    }
    else if ((cardData->cardExpirationDate[4] < 48) || (cardData->cardExpirationDate[4] > 57)) // second Y should be (0:9)
    {
        strcpy(cardData->cardExpirationDate, "\0");
        return WRONG_EXP_DATE;
    }
    else
        return CARD_OK; // valid card holder name
}
// ------------------functions getCardPAN-----------------------
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    printf("Enter Card PAN: ");
    gets(cardData->primaryAccountNumber);

    if (cardData->primaryAccountNumber == NULL)
    {
        return WRONG_PAN;
    }
    else if ((strlen(cardData->primaryAccountNumber) > 19) || (strlen(cardData->primaryAccountNumber) < 16))
    {
        return WRONG_PAN;
    }
    else
        return CARD_OK; // valid card holder name
}
