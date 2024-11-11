#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint-gcc.h>
#include<time.h>
int count_account=1,max_account=100;


 struct Account{
 int account_number;
 float balance;
 char name[50];
struct Account* next;};

 void dummy_account(struct Account* account){
 account->account_number=1;
 account->balance=40.0;
 strcpy(account->name,"");
 account->next=NULL;


 }
int Authentication(struct Account* account){
  int pass;
printf("Enter the account number : ");
scanf("%d", &pass);
while(account!=NULL){
if(account->account_number==pass){
    printf("Loading");
    for(int i=0;i<5;i++){
        printf(".");
           usleep(500000);
    }
    return pass;
    }
    account=account->next;}


    printf("wrong password \n Try again");
     return 0;

}
void open_account(struct Account* account){
if (count_account == max_account) {
        max_account *= 2;
    }
     struct Account* new_account=(struct Account*)malloc(sizeof(struct Account));

    while (getchar() != '\n');

   printf("Enter the name : ");

   fgets(new_account->name, sizeof(new_account->name), stdin);

  size_t len = strlen(new_account->name);
    if (len > 0 && new_account->name[len - 1] == '\n') {
        new_account->name[len - 1] = '\0';
    }
    count_account++;
    new_account->account_number=count_account;
    new_account->balance=0;
    account->next=new_account;
    account=new_account;

      FILE* ptr = fopen("input.txt", "w");
      if(ptr==NULL){
        printf("Error in Opening");
        return;
      }
      fprintf(new_account->name,ptr);
      fprintf(ptr,"%f\n",new_account->balance);
      fprintf(ptr,"%d\n",new_account->account_number);
      fclose(ptr);

   printf("your account is successfully activated\n");
   printf("your account number: %d\n", new_account->account_number);
   printf("your currently available balance: %d\n", new_account->balance);

}
void close_account(struct Account* account){

     struct Account* temp=account;
int result= Authentication(account);
if(result==0){
}
else{
    if(temp->account_number==result){
           count_account--;
           strcpy(temp->name,"");
    temp->account_number=count_account;
    temp->balance=0;
    }
    else{
      temp=temp->next;
    }
}
printf("your account has been deleted");
}
void add_amount(struct Account* account){
       struct Account* temp=account;
       int amount;
       printf("Enter the amount you want to deposit : ");
       scanf("%d", &amount);
int result=Authentication(account);
if(result==0){
}

    while(temp!=NULL){
      if(temp->account_number==result){
        temp->balance+=amount;
        printf("your available balance is %f\n",temp->balance);
        return;
      }
      temp=temp->next;
    }

}
void Withdraw_amount(struct Account* account){
   struct Account* temp=account;
        int amount;
       printf("Enter the amount you want to withdraw\n");
       scanf("%d", &amount);
int result=Authentication(account);
if(result==0){
        return;
}
    while(temp!=NULL){
      if(temp->account_number==result){
            if(temp->balance>=amount){
        temp->balance=temp->balance-amount;
        printf("your available balance is : %f\n",temp->balance);
      }
      else{
        printf("insufficient balance");
      }}
      temp=temp->next;
    }


}

 int main(){


 struct Account* account= (struct Account*)malloc(sizeof(struct Account));
dummy_account(&account);
 int choice;
 printf("----------banking system----------\n\n");
 printf("1. open an account\n");
 printf("2. close an account\n");
 printf("3. add amount to your account\n");
 printf("4. withdraw amount from your account\n");
 printf("5. Display Transaction\n");
 printf("5.updation of any information\n");
 scanf("%d", &choice);

switch(choice){
case 1:
    open_account(&account);
    break;
case 2:
    close_account(&account);
    break;
case 3:
    add_amount(&account);
    break;
case 4:
    Withdraw_amount(&account);
    break;

 }
 return 0;}
