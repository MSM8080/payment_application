#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// -------------------------------------------------------------------------------------------------
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"
// -------------------------------------------------------------------------------------------------
extern ST_accountsDB_t valid_accounts_database[255] =
{
    {10000,RUNNING,"1234567891234567"},
    {20000,BLOCKED,"2345678912345678"},
    {30000,RUNNING,"3456789123456789"},
    {40000,BLOCKED,"4567891234567891"},
    {50000,RUNNING,"5678912345678912"},
    {60000,BLOCKED,"6789123456789123"},
    {70000,RUNNING,"7891234567891234"},
    {80000,BLOCKED,"8912345678912345"},
    {90000,RUNNING,"9123456789123456"},
    {100000,BLOCKED,"0123456789012345"},
};
// -------------------------------------------------------------------------------------------------
extern ST_transaction_t accounts_transactions_database[255] = {0};
// -------------------------------------------------------------------------------------------------
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
    int c;
    c = getCardHolderName(cardData);
    get_enum_name(c);
    c = getCardExpiryDate(cardData);
    get_enum_name(c);
    c = getCardPAN (cardData);
    get_enum_name(c);

    for (int i = 0; i < 255; i++)
    {
        if (strcmp(cardData->primaryAccountNumber , valid_accounts_database[i].primaryAccountNumber) == 0) // 1: found
            {
                accountRefrence->state = valid_accounts_database[i].state;
                strcpy(accountRefrence->primaryAccountNumber ,valid_accounts_database[i].primaryAccountNumber);
                accountRefrence->balance = valid_accounts_database[i].balance;
                return SERVER_OK;
            }
        else
            continue;
    }
    return ACCOUNT_NOT_FOUND;
}
// -------------------------------------------------------------------------------------------------
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
     if (accountRefrence->state == BLOCKED)
        return BLOCKED;
    else
        return RUNNING;
}
// -------------------------------------------------------------------------------------------------
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t accountRefrence)
{
    int c;
    c = setMaxAmount(termData);
    get_enum_name(c);
    c = getTransactionAmount(termData);
    get_enum_name(c);
    c = isBelowMaxAmount(termData);
    get_enum_name(c);

    if(termData->transAmount > accountRefrence.balance)
        return LOW_BALANCE;
    else
        return SERVER_OK;
}
// -------------------------------------------------------------------------------------------------
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
     char a[5];
     int c;

     // account refrence
     ST_accountsDB_t DB1;

    // card info
     c = isValidAccount(&transData->cardHolderData,&DB1);
     printf("\nIs Valid Account: \n");
     get_enum_name(c);
     if(c == ACCOUNT_NOT_FOUND)
            return FRAUD_CARD;

     c = getTransactionDate(&transData->terminalData);
     get_enum_name(c);
     c = isCardExpired(transData->cardHolderData, transData->terminalData);
     get_enum_name(c);
     if(c == EXPIRED_CARD)
            return EXPIRED_CARD;

     c = isBlockedAccount(&DB1);
     printf("\nIs Blocked Account: \n");
     get_enum_name(c);

    // asking for blocking the account
     if (c == RUNNING)
     {
         printf("Want to block your account? (y/n)\n");
         gets(a);
         if(strcmp(a,"y")==0)
         {
            DB1.state == BLOCKED ;
            return BLOCKED;
         }
     }
     else if(c == BLOCKED)
            return DECLINED_STOLEN_CARD;

    // show account refrence
     printf("\nOld account data base:");
     printf("\nBalance: %f $",DB1.balance);
     printf("\nPAN: %s\n",DB1.primaryAccountNumber);
     get_enum_name(DB1.state);

    // terminal info
     c = isAmountAvailable(&transData->terminalData,DB1);
     printf("\nIs Amount Available: \n");
     get_enum_name(c);
     if (c == LOW_BALANCE)
            return DECLINED_INSUFFECIENT_FUND;
/*
     if a transaction can't be saved will return INTERNAL_SERVER_ERROR and will not save the transaction
     can't saved due bad internet connection
*/

    // update account data base & reference (balance & state)
    for (int i = 0; i < 255; i++)
    {
        if (strcmp(transData->cardHolderData.primaryAccountNumber , valid_accounts_database[i].primaryAccountNumber) == 0) // 1: found
            {
                printf("\nUpdate account data base:");
                DB1.balance -= transData->terminalData.transAmount;
                valid_accounts_database[i].balance -= transData->terminalData.transAmount;
                printf("\nBalance: %f $",DB1.balance);
                printf("\nPAN: %s\n",DB1.primaryAccountNumber);
                get_enum_name(DB1.state);
            }
        else
            continue;
    }
    return APPROVED;
}
// -------------------------------------------------------------------------------------------------
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    int c;
    for (int i = 0; i<255; i++)
    {
        if (accounts_transactions_database[i].transactionSequenceNumber == 0)
        {
            // save card transaction
            strcpy(accounts_transactions_database[i].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
            strcpy(accounts_transactions_database[i].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
            strcpy(accounts_transactions_database[i].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);

            // save terminal transaction
            strcpy(accounts_transactions_database[i].terminalData.transactionDate, transData->terminalData.transactionDate);
            accounts_transactions_database[i].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
            accounts_transactions_database[i].terminalData.transAmount = transData->terminalData.transAmount;

            // save state transaction
            accounts_transactions_database[i].transState = transData->transState;

            // save transaction Sequence Number
            accounts_transactions_database[i].transactionSequenceNumber = i+1;

            // get transaction
            c = getTransaction(accounts_transactions_database[i].transactionSequenceNumber, &transData);
            printf("\nGet transaction: \n");
            get_enum_name(c);

            return SERVER_OK;
        }
        else
            continue;
    }
    return SAVING_FAILED;
}
// -------------------------------------------------------------------------------------------------
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    for(int i =0; i<255; i++)
    {
        if (accounts_transactions_database[i].transactionSequenceNumber == transactionSequenceNumber)
            {
                // get card transaction
                printf("\nCard name: %s",accounts_transactions_database[i].cardHolderData.cardHolderName);
                printf("\nCard expired date: %s",accounts_transactions_database[i].cardHolderData.cardExpirationDate);
                printf("\nCard PAN: %s",accounts_transactions_database[i].cardHolderData.primaryAccountNumber);

                // get terminal transaction
                printf("\nTransaction Date: %s",accounts_transactions_database[i].terminalData.transactionDate);
                printf("\nMax Trans Amount: %f $",accounts_transactions_database[i].terminalData.maxTransAmount);
                printf("\nTrans Amount: %f $",accounts_transactions_database[i].terminalData.transAmount);

                // get transaction Sequence Number
                printf("\nTransaction Sequence Number: %d",accounts_transactions_database[i].transactionSequenceNumber);

                // get state transaction
                printf("\nStatus transaction: ");
                get_enum_name(accounts_transactions_database[i].transState);

                return SERVER_OK;
            }
        else
            continue;
    }
    return TRANSACTION_NOT_FOUND;
}
// -------------------------------------------------------------------------------------------------

