#include <stdio.h>
#include <stdlib.h>
// -------------------------------------------------------------------------------------------------
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"
// -------------------------------------------------------------------------------------------------
void appStart(void)
{
    int c;


    ST_transaction_t trans1;

    // recieve transaction
    c = recieveTransactionData(&trans1);
    printf("\nRecieve Transaction Data: \n");
    get_enum_name(c);

    // save transaction
    trans1.transState = c;
    c = saveTransaction(&trans1);
    printf("\nsave Transaction: \n");
    get_enum_name(c);

    return 0;
}
// -------------------------------------------------------------------------------------------------
char get_enum_name(int e)
{
    switch (e)
    {
    case 0: puts("status: CARD_OK\n"); break;
    case 1: puts("status: WRONG_NAME\n"); break;
    case 2: puts("status: WRONG_EXP_DATE\n"); break;
    case 3: puts("status: WRONG_PAN\n"); break;
    case 4: puts("status: TERMINAL_OK\n"); break;
    case 5: puts("status: WRONG_DATE\n"); break;
    case 6: puts("status: EXPIRED_CARD\n"); break;
    case 7: puts("status: INVALID_CARD\n"); break;
    case 8: puts("status: INVALID_AMOUNT\n"); break;
    case 9: puts("status: EXCEED_MAX_AMOUNT\n"); break;
    case 10: puts("status: INVALID_MAX_AMOUNT\n"); break;
    case 11: puts("status: APPROVED\n"); break;
    case 12: puts("status: DECLINED_INSUFFECIENT_FUND\n"); break;
    case 13: puts("status: DECLINED_STOLEN_CARD\n"); break;
    case 14: puts("status: FRAUD_CARD\n"); break;
    case 15: puts("status: INTERNAL_SERVER_ERROR\n"); break;
    case 16: puts("status: SERVER_OK\n"); break;
    case 17: puts("status: SAVING_FAILED\n"); break;
    case 18: puts("status: TRANSACTION_NOT_FOUND\n"); break;
    case 19: puts("status: ACCOUNT_NOT_FOUND\n"); break;
    case 20: puts("status: LOW_BALANCE\n"); break;
    case 21: puts("status: BLOCKED_ACCOUNT\n"); break;
    case 22: puts("status: RUNNING\n"); break;
    case 23: puts("status: BLOCKED\n"); break;
    }
}
// -------------------------------------------------------------------------------------------------
/*
     ST_cardData_t d1;
     ST_accountsDB_t DB1;
     ST_terminalData_t t1;

     // card info
     c = isValidAccount(d1,&DB1);
     printf("\nIs Valid Account: \n");
     get_enum_name(c);
     c = getTransactionDate(&t1);
     get_enum_name(c);
     c = isCardExpired(d1, t1);
     get_enum_name(c);

     printf("\nBalance: %f",DB1.balance);
     printf("\nPAN: %s\n",DB1.primaryAccountNumber);
     get_enum_name(DB1.state);

     // terminal info
     c = isAmountAvailable(&t1,DB1);
     printf("\nIs Amount Available: \n");
     get_enum_name(c);
*/
