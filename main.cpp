#include <stdio.h>
#include <windows.h>
#include <string.h>
void display(struct handphone[],int,int,int);//function prototype 6 function
void buy(struct handphone[],int,int,int);
void displaySold(struct handphone product[]);
int compute(struct handphone product[],int,int);
void printReceipt(struct handphone product[],int,int,int,int);//function to calculate receipt
//struct use in C
struct handphone{
       char hpname[20];//structure consist of three types hpname,price,sold
       int price;
       int sold;
};
//array of 12 products
struct handphone product[12]; 
//main function
int main(int price,int totalcashreceived,int totalBalance){
system("cls");//to clear screen in the menu\n
int totalprice=price;
int a;
printf("Welcome to IT MAGIC\n");
printf("Select menu\n");//Display for the menu'
printf("1.Buy item\n");
printf("2.Sell total\n");
printf("Input-->");
scanf("%d", &a);//scan the user input selecting the menu
if(a==1){
         //calling function to display product
        display(product,price,totalcashreceived,totalBalance);
        }else if(a==2){//if user choose 2 will display the total sales menu
              system("cls");
              printf("The total price of sales %d",totalprice-1);
                            printf("\nThe total price of cash received %d",totalcashreceived);
              printf("\nThe total price of cash out %d",totalBalance);//Total balance of cash given back to customer
              printf("\n------------------------");
              printf("\nProduct sold");
              printf("\n------------------------");
             displaySold(product);//function that display the total quantity of product sold
              printf("\n");
              system("pause");
               main(price,totalcashreceived,totalBalance);//back to main function or back to menu in program run  
              }else {//if the user put input diffrent from 1 and 2 exit output this statement
                    printf("Wrong input");
                   }
printf("\n");
   system("pause");//pausing the screen program
return 0;
}
//Display function and initialize from text
void display(struct handphone product[],int price,int totalcashreceived,int totalBalance)
{
     system("cls");
  FILE *ptr_file;//object file for text
char buf[1000];

ptr_file=fopen("handphone_file.txt","r");//open handphone file where the data located from text
if(!ptr_file)//if file not exist error
printf("Error");
int i=0;
while(fgets(buf,1000,ptr_file)!=NULL){//get the file until finish put in variable buffer 
//copy string in array via token
 strcpy(product[i].hpname,strtok(buf,","));
 //convert string into integer via token
product[i].price=atoi(strtok(NULL,","));//convert string from the text file into integer
printf("%d",i+1);//display the product number
printf("  ");
printf("%s",product[i].hpname);//display the product name
printf(" - ");
printf("%d",product[i].price);//display the product price
printf("\n");
i++;//i that use to select the array inside while loop
}
 fclose(ptr_file);//close the file
//function to display buying product
buy(product,price,totalcashreceived,totalBalance);
}
//Select product
void buy(struct handphone product[],int totalprice,int totalcashreceived,int totalBalance){
         int a;//variable for user to choose product
printf("\nPlease select product-->");
scanf("%d",&a);
a=a-1;//-1 because array start from 0
int cashReceived;
int Balance;
 char answer;
static int price=totalprice;//static variable to calculate the total
int selectprice=product[a].price;
printf("\nYou choose %s ",product[a].hpname);
if(a>=0){//if the input ,more than 0 means that the selection number of product will display all of this
       price=compute(product,selectprice,a);
       printf("\nThe total price of the product is -->RM %d",price);
       printf("\nAmount of cash received-->");
       scanf("%d",&cashReceived);//variable to get the cash received
       Balance=cashReceived-price;
       printf("\nBalance-->RM %d",Balance);
static int totalBalance;//static variable to calculate the total balance'
static int totalcashreceived;//static variable to calculate the total cash received
totalprice+=price;//to calculate total price of product
 totalBalance+=Balance;//to calculate total balance
totalcashreceived+=cashReceived;//to calculate total cash received
printf("\n");
 printf("Do you want to print receipt(Y/N)--->");
 scanf("%s",&answer);//variable to get the user if they want a receipt
      if(answer=='Y'|| answer=='y'){//if uppercase Y and lowercase Y it will generate a receipt
                  printReceipt(product,a,totalprice-1,totalcashreceived,totalBalance);//function call to print receipt
                      printf("Receipt Print!\n");
                      system("pause");
                      main(totalprice,totalcashreceived,totalBalance);//back to main function or menu after the print
                      }else {
                     system("\npause");//if the user put other input diffrent from Y that back to menu
                        main(totalprice,totalcashreceived,totalBalance);
                          }    
}else{//if the user input out of range off selected product will generate error output
      printf("\nError not valid");
            }}


int compute(struct handphone product[],int selectprice,int select){//Calculation to calculate the product price
    int quantity;
    int total=0;
    printf("\nHow many quantities do you want-->");
    scanf("%d",&quantity); //variable to get quantity
      product[select].sold=product[select].sold+quantity;//select is put in array to just calculate the selected product only
      total=selectprice*quantity;//the formual to calculate total
            return total;//return total
         
} 
void displaySold(struct handphone product[]){//function to display the speific product that has been sold
for(int i=0;i<12;i++){
        if(product[i].sold>0){    //if there are available product which is 0 then display                        
               printf("\n%s",product[i].hpname);
              printf("  ");
              printf("%d",product[i].sold);
              }else{//if 0 display nothing
              
                    
     }}}
void printReceipt(struct handphone product[],int select,int totalprice,int received,int bal){//function to generate a receipt
     FILE *fp;
     fp=fopen("receipt.txt","w+");//to write a receipt W+
         fprintf(fp,"%s","Receipt - IT MAGIC");
     fprintf(fp,"%s","\n---------------------");
     fprintf(fp,"%s","\nItem purchased");
     for(int i=0;i<12;i++){//looping the 12 available product
                          if(product[i].sold>0){          //if they are product available sold the display                
                                 
     fprintf(fp,"\nHandphone Name:%s",product[i].hpname);
     fprintf(fp,"\nPrice:%d",product[i].price);
        fprintf(fp,"\nQuantity:%d",product[i].sold);
           
        }else{//if nothing are sold display nothing
              }}
         fprintf(fp,"%s","\n---------------------");//output to write on receipt
            fprintf(fp,"\nTotal price :RM%d",totalprice);
            fprintf(fp,"\nCash received :RM%d",received);
              fprintf(fp,"\nCash Back :RM%d",bal);  
     fprintf(fp,"%s","\n---------------------");//output to write on recipt and close the fp objeect
     fprintf(fp,"%s","\nThank You Please come again");
     fclose(fp);
                      
     }
