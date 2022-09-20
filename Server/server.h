#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
// -------------------------------------------------------------------------------------------------
#include "../Card/card.h"
#include "../Terminal/terminal.h"
// -------------------------------------------------------------------------------------------------
typedef enum EN_transState_t
{
    APPROVED = 11,                          // 11
    DECLINED_INSUFFECIENT_FUND,   // 12
    DECLINED_STOLEN_CARD,            // 13
    FRAUD_CARD,                             // 14
    INTERNAL_SERVER_ERROR           // 15
}EN_transState_t;
// ------------------------------------------------- ------------------------------------------------
typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;
// -------------------------------------------------------------------------------------------------
typedef enum EN_serverError_t
{
    SERVER_OK = 16,                          // 16
    SAVING_FAILED,                            // 17
    TRANSACTION_NOT_FOUND,            // 18
    ACCOUNT_NOT_FOUND,                  // 19
    LOW_BALANCE,                             // 20
    BLOCKED_ACCOUNT                       // 21
}EN_serverError_t ;
// -------------------------------------------------------------------------------------------------
typedef enum EN_accountState_t
{
    RUNNING = 22,            // 22
    BLOCKED             // 23
}EN_accountState_t;
// -------------------------------------------------------------------------------------------------
typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;
// -------------------------------------------------------------------------------------------------
EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);
// -------------------------------------------------------------------------------------------------
extern ST_accountsDB_t valid_accounts_database[255];
extern ST_transaction_t accounts_transactions_database[255];
// -------------------------------------------------------------------------------------------------
#endif // SERVER_H_INCLUDED
