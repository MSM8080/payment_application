// --------------------including system libraries-----------------------------
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
// --------------------including application libraries-----------------------------
#include "terminal.h"
// ------------------function getTransactionDate-----------------------
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    strcpy(termData->transactionDate, "");
    char dd[11];
    char mm[11];
    char yyyy[11];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(dd, "%02d", tm.tm_mday);
    strcat(termData->transactionDate, dd);
    strcat(termData->transactionDate, "/");
    sprintf(mm, "%02d", (tm.tm_mon + 1));
    strcat(termData->transactionDate, mm);
    strcat(termData->transactionDate, "/");
    sprintf(yyyy, "%d", (tm.tm_year + 1900));
    strcat(termData->transactionDate, yyyy);

    printf("local date: ");
    puts(termData->transactionDate);

    // good formate (DD/MM/YYYY)
    if (termData->transactionDate == NULL)
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if (strlen(termData->transactionDate) < 10)
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[0] < 48) || (termData->transactionDate[0] > 57)) // first D should be (0:9)
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[1] < 48) || (termData->transactionDate[1] > 57)) // second D should be (0:9)
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if (termData->transactionDate[2] != 47) // check '/' position
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[3] < 48) || (termData->transactionDate[3] > 57)) // first M should be (0:9)
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[4] < 48) || (termData->transactionDate[4] > 57)) // second M should be (0:9)
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if (termData->transactionDate[5] != 47) // check '/' position
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[6] < 48) || (termData->transactionDate[6] > 57)) // first Y should be (0:9)
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[7] < 48) || (termData->transactionDate[7] > 57)) // second Y should be (0:9)
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[8] < 48) || (termData->transactionDate[8] > 57)) // third M should be (0:9)
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[9] < 48) || (termData->transactionDate[9] > 57)) // fourth M should be (0:9)
    {
        strcpy(termData->transactionDate, "\0");
        return WRONG_DATE;
    }
    else
        return TERMINAL_OK;
}
// ------------------function isCardExpired-----------------------
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    printf("is Card Expired: \n");

    // card(MM/YY) , terminal(DD/MM/YYYY)
    if ((termData.transactionDate == NULL) || (cardData.cardExpirationDate == NULL))
        return EXPIRED_CARD;
    else if (termData.transactionDate[8] > cardData.cardExpirationDate[3]) //ten's of years
      return EXPIRED_CARD;
    else if (termData.transactionDate[8] == cardData.cardExpirationDate[3])
    {
        if (termData.transactionDate[9] > cardData.cardExpirationDate[4]) //one's of years
            return EXPIRED_CARD;
        else if (termData.transactionDate[9] == cardData.cardExpirationDate[4])
        {
            if (termData.transactionDate[3] > cardData.cardExpirationDate[0]) // ten's of months
                return EXPIRED_CARD;
            else if (termData.transactionDate[3] == cardData.cardExpirationDate[0])
            {
                if (termData.transactionDate[4] > cardData.cardExpirationDate[1]) // one's of months
                    return EXPIRED_CARD;
                else
                    return TERMINAL_OK;
            }
            else
                return TERMINAL_OK;
        }
        else
            return TERMINAL_OK;
    }
    else
        return TERMINAL_OK;
}
// ------------------function getTransactionAmount-----------------------
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    char str_amount [20];
    strcpy(str_amount, "\0");
    printf("Enter Transaction Amount: ");
    gets(str_amount);
    termData->transAmount = atof(str_amount);

    if (termData->transAmount <= 0)
        return INVALID_AMOUNT;
    else
        return TERMINAL_OK;
}
// ------------------function isBelowMaxAmount-----------------------
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    printf("is Below Max Amount: \n");

    if ((termData->transAmount) > (termData->maxTransAmount))
        return EXCEED_MAX_AMOUNT;
    else
        return TERMINAL_OK;
}
// ------------------function setMaxAmount-----------------------
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
    termData->maxTransAmount = 50000;
    printf("Max Transiction Amount: (%f)\n", termData->maxTransAmount);

    if (termData->maxTransAmount <= 0)
        return INVALID_MAX_AMOUNT;
    else
        return TERMINAL_OK;
}
