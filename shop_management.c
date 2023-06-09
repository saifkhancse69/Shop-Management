/* Online shop management software .
In this project you will make a software for online shop.
 The software you will develop will have two types of user namely admin and customer.
 Admins can add products detail (product id, name, price, quantity etc.) by login to their account
using their email and password. On the other hand the customers can buy those products.
You should be able to generate payment receipt for every customer.
Products' quantity should be decreased if customers buy from the shop and quantity should be increased
if admins add more quantity to that product using its product id. Add more features to make this project
more usable and intuitive. Please check SHAWPNO, AGORA, MEENA BAZAR, etc.
for better understanding and incorporate all features.*/
//Use admin and admin for admin login!
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>
#include<time.h>
#define PROGRESS_BAR_SIZE 40
typedef struct product
{
    int item_code,item_quantity;
    char item_name[50];
    float item_price;
} product;
typedef struct user
{

    char user_name[50];
    char user_email[50];
    char user_pass[50];
    char user_add[50];

} user;

void regis();
// ADMIN FUNCTIONS
void headerf();
void admin_login();
void admin_panel();
void reset_create();
void add_product();
void inventory();
void total_product();
void search();
void update();
void delete_rec();
void sort_by_name();
void sort_by_quantity();
void delete_rec();
//CUSTOMER FUNCTIONS
void customer_menu(char *username);
void browse_product();
void customer_menu2(char *username);
void cust_sort_by_name();
void cust_sort_by_price();
void addtoshow_cart(char *username);
void show_cart(char *username);
void cart_menu(char *username);
void checkout(char *username);
void receipt1(char card_name[10],char *username);
void exit_menu(char *username);
void delete_cart_item();
void update_after_del(int code,int tempp);


int main()
{
    system("COLOR 70");
    headerf();
    user s1;
    FILE *fp;
    char email[100], password[100];
    char code[50],pass[50],username[50];
    int ch;


cp1:
    printf("           Login To Start Shopping!\n");
    printf("           [1]Login.\n");
    printf("           [2]Register\n           -> ");
    scanf("%d",&ch);

    if(ch==1)
        {
cp2:
        printf("          E-mail : ");
        scanf("%s",&code);
        printf("          Password : ");
        scanf("%s",&pass);
        if(strcmp(code,"admin")==0 && strcmp(pass,"admin")==0)
            {
            system("cls");
            admin_panel();
            }
        fp = fopen("user.txt","r");
        while(fread(&s1,sizeof(user),1,fp))
            {
            if(strcmp(code,s1.user_email)==0 && strcmp(pass,s1.user_pass)==0)
                {
                system("cls");
                customer_menu(s1.user_name);
                }
            }

        }
    else if(ch==2)
        {
        system("cls");
        regis();
        }
    else
        {
        system("cls");
        printf("           INVALID INPUT!\n");
        goto cp2;
        }
    system("cls");
    printf("           INVALID INPUT!\n");
    goto cp2;

    fclose(fp);
}

void regis()
{
    user u[100];
    FILE *fp;
    int n,i,j;

    fp = fopen("user.txt","a");
    printf("          User Registration Menu:\n          Please provide the following information:\n");
    for(i=0; i<1; i++)
        {
        printf("          Name: ");
        fflush(stdin);
        gets( u[i].user_name );
        printf("          E-mail: ");
        gets( u[i].user_email );
        printf("          Address: ");
        gets( u[i].user_add );
        printf("          Password: ");
        gets( u[i].user_pass );
        fwrite(u+i,sizeof(user),1,fp);
        }
    fclose(fp);
    printf("          REGISTRATION SUCCESSFUL!\n");
    system("cls");
    main();
}
void customer_menu(char *username)
{
    headerf();
    int ch;
    printf("          Welcome, %s!\n",username);
    printf("          WHAT DO YOU WANT TO DO?\n");
    printf("          ->[1].BROWSE PRODUCTS.\n");
    printf("          ->[2].SHOW CART.\n");
    printf("          ->[0].LOGOUT.\n");
    printf("\n        Enter Your Choice : ");
    scanf("%d",&ch);
    switch(ch)
        {
        case 1:
            system("cls");
            browse_product();
            customer_menu2(username);
            break;
        case 2:
            system("cls");
            show_cart(username);
            cart_menu(username);
            break;
        case 0:
            system("cls");
            main();
            break;
        default:
            system("cls");
            printf("Invalid input!");
            customer_menu( username);
        }
}
void browse_product()//
{
    product s1;
    FILE *fp;
    printf("          Availabe products:\n");
    printf("          %-21s%-15s%-15s\n","Product Code","Name","Price(Unit/KG)");
    fp = fopen("products.txt","r");
    while(fread(&s1,sizeof(product),1,fp))
        {
        printf("          %-21d",s1.item_code);
        printf("%-15s",s1.item_name);
        printf("%-15.2f\n",s1.item_price);
        }
    fclose(fp);
}

void customer_menu2(char *username)
{
    int ch;

    printf("\n          ->[1].ADD TO CART.\n");
    printf("          ->[2].SHOW CART.\n");
    printf("          ->[3].SHORT BY NAME.\n");
    printf("          ->[4].SHORT BY PRICE.\n");
    printf("          ->[0].GO BACK.\n");
    printf("\n        Enter Your Choice : ");
    scanf("%d",&ch);
    switch(ch)
        {
        case 1:

            system("cls");
            browse_product();
            addtoshow_cart(username);
            customer_menu2(username);
            break;
        case 2:
            system("cls");
            show_cart(username);
            break;
        case 3:
            system("cls");
            cust_sort_by_name();
            customer_menu2(username);
            break;
        case 4:
            system("cls");
            cust_sort_by_price();
            customer_menu2(username);
            break;
        case 0:
            system("cls");
            customer_menu(username);
            break;
        default:
            system("cls");
            printf("Invalid input!");
            customer_menu(username);
        }
}
void cust_sort_by_name()
{
    product s[100], s1;
    FILE *fp;
    fp = fopen("products.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(product);
    int i,j;
    rewind(fp);
    for(i=0; i<n; i++)
        fread(&s[i],sizeof(product),1,fp);

    for(i=0; i<n; i++)
        {
        for(j=i+1; j<n; j++)
            {
            if(strcmp(s[i].item_name,s[j].item_name)>0)
                {
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
                }
            }
        }
    printf("          %-21s%-15s%-15s\n","Product Code","Name","Price");
    for(i=0; i<n; i++)
        {
        printf("          %-21d%-15s%-15.2f\n",s[i].item_code,s[i].item_name,s[i].item_price);
        }
    fclose(fp);
}
void cust_sort_by_price()
{
    product s[100], s1;
    FILE *fp;
    fp = fopen("products.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(product);
    int i,j;
    rewind(fp);
    for(i=0; i<n; i++)
        fread(&s[i],sizeof(product),1,fp);

    for(i=0; i<n; i++)
        {
        for(j=i+1; j<n; j++)
            {
            if(s[i].item_price>s[j].item_price)
                {
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
                }
            }
        }
    printf("          %-21s%-15s%-15s\n","Product Code","Name","Price");
    for(i=0; i<n; i++)
        {
        printf("          %-21d%-15s%-15.2f\n",s[i].item_code,s[i].item_name,s[i].item_price);
        }
    fclose(fp);
}

void addtoshow_cart(char *username)
{
    int i, j, found=0;
    product s1;
    FILE *fp, *fp1,*fp2;
    int code,quan,tempq;

    printf("          Enter Code to Add it to Your Cart: ");
    scanf("%d",&code);

    fp = fopen("products.txt","r");
    fp1 = fopen("temp.txt","w");
    fp2= fopen("cart.txt","a");
    while(fread(&s1,sizeof(product),1,fp))
        {
        if(s1.item_code == code)
            {
            printf("          Code: %d Item: %s is available!\n",s1.item_code,s1.item_name);
            printf("          Enter Unit/KG: ");
            scanf("%d",&quan);
            if(s1.item_quantity<quan)
                {
                printf("          Sorry We have only %d UNIT/KG of %s.\n",s1.item_quantity,s1.item_name);
                break;
                }
            else
                {
                found = 1;
                tempq=s1.item_quantity;
                s1.item_quantity=quan;
                fwrite(&s1,sizeof(product),1,fp2);
                s1.item_quantity=tempq-quan;
                }
            }
        fwrite(&s1,sizeof(product),1,fp1);
        }
    fclose(fp);
    fclose(fp1);
    fclose(fp2);

    if(found)
        {
        fp = fopen("products.txt","w");
        fp1 = fopen("temp.txt","r");

        while(fread(&s1,sizeof(product),1,fp1))
            {
            fwrite(&s1,sizeof(product),1,fp);
            }
        fclose(fp);
        fclose(fp1);
        system("cls");
        printf("          PRODUCT ADDED TO CART SUCCESSFULLY!\n");
        }
    else
        printf("\n          Not Found.....\n");
    remove("temp.txt");


    browse_product();
    customer_menu2(username);
}
void show_cart(char *username)
{
    float total=0,sum=0;
    product s1;
    FILE *fp;
    printf("          Your Selected Items: \n");
    printf("          %-21s%-15s%-15s%-15s\n","Product Code","Name","Quantity","Price");
    fp = fopen("cart.txt","r");
    while(fread(&s1,sizeof(product),1,fp))
        {
        printf("          %-21d",s1.item_code);
        printf("%-15s",s1.item_name);
        printf("%-15d",s1.item_quantity);
        printf("%-15.2f\n",s1.item_price*(float)s1.item_quantity);


        total+=s1.item_quantity*s1.item_price;
        }
    fclose(fp);
    printf("          ---------------------------------------------------------\n");
    printf("%57s%10.2f","Total:",total);
    FILE *fp2;
    fp2 = fopen("total.txt","w");
    fprintf(fp2,"%.2f",total);
    fclose(fp2);
}
void cart_menu(char *username)
{

    int ch;
cp1:

    printf("\n         [1].CHECKOUT.");
    printf("\n         [2].REMOVE FROM CART.");
    printf("\n         [0].RETURN TO MENU.");
    printf("\n         Enter Your Choice : ");
    scanf("%d",&ch);
    switch(ch)
        {
        case 1:
            system("cls");
            checkout(username);
            break;
        case 2:
            delete_cart_item();
            show_cart(username);
            cart_menu(username);
            break;
        case 0:
            system("cls");
            browse_product();
            customer_menu2(username);
            break;
        default:
            system("cls");
            printf("Invalid input!");
            show_cart(username);
            cart_menu(username);
        }
}
void checkout(char *username)
{

    system("cls");
    float total;
    FILE *fp2;
    fp2 = fopen("total.txt","r");
    fscanf(fp2,"%f",&total);
    fclose(fp2);

    show_cart(username);
    int ch,ch2;
    long int cardno,cardpin,otp;
    char card_name[10];

    printf("\n         [1].SELECT PAYMENT METHOD.");
    printf("\n         [2].CONTINUE SHOPPING.");
    printf("\n         [0].RETURN TO MENU.");
    printf("\n         Enter Your Choice : ");
    scanf("%d",&ch);
    switch(ch)
        {
        case 1:
            system("cls");
            printf("\n         [1].CARD.");
            printf("\n         [2].MOBILE BANKING.");
            printf("\n         [0].RETURN TO MENU.");
            printf("\n         Enter Your Choice : ");
            scanf("%d",&ch2);
            if(ch2==1)
                {
                printf("         PLEASE ENTER YOUR CARD NAME: ");
                fflush(stdin);
                gets(card_name);
                printf("         PLEASE ENTER YOUR CARD NUMBER: ");
                scanf("%d",&cardno);
                printf("         PLEASE ENTER YOUR CARD PIN NUMBER: ");
                scanf("%d",&cardpin);

                system("cls");
                printf("\n         PLEASE BE PATIENT AS WE PROCESS YOUR PAYMENT!\n");
                loading();
                system("cls");
                printf("\n                    YOUR PAYMENT WAS SUCCESFULL!\n");
                printf("\n                        HERE IS YOUR RECEIPT.   \n");
                receipt1(card_name,username);
                }
            else if(ch2==2)
                {
                printf("         PLEASE ENTER YOUR MOBILE BANKING SERVICE'S NAME: ");
                fflush(stdin);
                gets(card_name);
                printf("         PLEASE ENTER YOUR PHONE NUMBER: ");
                scanf("%d",&cardno);

                printf("         PLEASE ENTER YOUR PIN NUMBER: ");
                scanf("%d",&cardpin);
                printf("         PLEASE ENTER OTP : ");
                scanf("%d",&otp);
                system("cls");
                printf("\n         PLEASE BE PATIENT AS WE PROCESS YOUR PAYMENT!\n");
                loading();
                system("cls");
                printf("\n                 YOUR PAYMENT WAS SUCCESFULL!\n\n");
                printf("\n                 HERE IS YOUR RECIEPT!\n\n");
                receipt1(card_name,username);
                }
            break;
        case 2:
            system("cls");
            customer_menu(username);
            break;
        case 0:
            system("cls");
            cart_menu(username);
            break;
        default:
            system("cls");
            printf("Invalid input!");
            show_cart(username);
            checkout(username);
        }

}
void receipt1(char card_name[10],char *username )
{
    system("COLOR F0");
    int ti;
    ti=total_cart_product();
    time_t t;
    time(&t);
    float total=0,sum=0;
    FILE *fp,*fp2;
    fp = fopen("cart.txt","r");
    fp2 = fopen("reciept.txt","w");
    FILE *fp3;
    fp3 = fopen("total.txt","w");
    product s1;

    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    printf("          |              EWU ONLINE SHOP             |\n");
    fprintf(fp2,"          |              EWU ONLINE SHOP             |\n");
    printf("          |                  RECIEPT                 |\n");
    fprintf(fp2,"          |                  RECIEPT                 |\n");
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    printf("          |%s%27s|\n","CUSTOMER NAME: ",username);
    fprintf(fp2,"          |%s%27s|\n","CUSTOMER NAME: ",username,"|");
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    printf("          |%s%s","TIME: ",ctime(&t));
    fprintf(fp2,"          |%s%s","TIME: ",ctime(&t));
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    printf("          |%-10s%10s%22s|\n","NAME","QTY","PRICE");
    fprintf(fp2,"          |%-10s%10s%22s|\n","NAME","QTY","PRICE");
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");

    while(fread(&s1,sizeof(product),1,fp))
        {

        printf("          |%-10s",s1.item_name);
        fprintf(fp2,"          |%-10s",s1.item_name);
        printf("%10d",s1.item_quantity);
        fprintf(fp2,"%10d",s1.item_quantity);
        printf("%22.2f|\n",s1.item_price*(float)s1.item_quantity);
        fprintf(fp2,"%22.2f|\n",s1.item_price*(float)s1.item_quantity);
        total+=s1.item_quantity*s1.item_price;
        }
    fclose(fp);

    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
         printf("          |%32s%10d|\n","TOTAL ITEM:",ti);
    fprintf(fp2,"          |%32s%10d|\n","TOTAL ITEM:",ti);
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    printf("          |%32s%10.2f|\n","SUB TOTAL:",total);
    fprintf(fp2,"          |%32s%10.2f|\n","SUB TOTAL:",total);
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    printf("          |%32s%10.2f|\n","Tax(7.5%):",total*0.075);
    fprintf(fp2,"          |%32s%10.2f|\n","Tax(7.5%):",total*0.075);
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    printf("          |%32s%10.2f|\n","TOTAL:",total+(total*0.075));
    fprintf(fp2,"          |%32s%10.2f|\n","TOTAL:",total+(total*0.075));
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    printf("          |%32s%10s|\n","Payment Method:","CARD");
    fprintf(fp2,"          |%32s%10s|\n","Payment Method:","CARD");
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    printf("          |%32s%10s|\n","CARD NAME:",card_name);
    fprintf(fp2,"          |%32s%10s|\n","CARD NAME:",card_name);
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    printf("          |         THANKS FOR SHOPPING WITH US!     |\n");
    fprintf(fp2,"          |         THANKS FOR SHOPPING WITH US!     |\n");
    printf("          |                                          |\n");
    fprintf(fp2,"          |                                          |\n");
    printf("          |            HOPE TO SEE YOU AGAIN!        |\n");
    fprintf(fp2,"          |            HOPE TO SEE YOU AGAIN!        |\n");
    printf("          |                                          |\n");
    fprintf(fp2,"          |                                          |\n");
    printf("          |------------------------------------------|\n");
    fprintf(fp2,"          |------------------------------------------|\n");
    exit_menu(username);
    fclose(fp2);
}
void exit_menu(char *username)
{
    printf("\n          YOUR RECIEPT IS AVAILABLE.\n          PLEASE CHECK reciept.txt FOLDER");
    int ch;
cp1:
    printf("\n         [1].CONTINUE SHOPPING?.");
    printf("\n         [2].LOGOUT.");
    printf("\n         Enter Your Choice : ");
    scanf("%d",&ch);
    switch(ch)
        {
        case 1:
            system("cls");
            remove("cart.txt");
            remove("total.txt");
            remove("reciept.txt");
            customer_menu(username);
            break;
        case 2:
            system("cls");
            remove("cart.txt");
            remove("reciept.txt");
            remove("total.txt");
            main();
            break;
        default:
            system("cls");
            goto cp1;
        }

}
void total_cart_product()//
{
    product s1;
    FILE *fp;
    fp = fopen("cart.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(product);
    return n;
    fclose(fp);
}
void delete_cart_item()
{
    int i, j, found=0;
    int tempp;
    product s1;
    FILE *fp, *fp1;
    int code;
    printf("          Enter Product Code to Delete From Cart: ");
    scanf("%d",&code);
    fp = fopen("cart.txt","r");
    fp1 = fopen("temp.txt","w");
    while(fread(&s1,sizeof(product),1,fp))
        {
        if(s1.item_code == code)
            {
            found = 1;
            tempp=s1.item_quantity;
            update_after_del(code,tempp);
            }
        else
            fwrite(&s1,sizeof(product),1,fp1);
        }
    fclose(fp);
    fclose(fp1);


    if(found)
        {
        fp = fopen("cart.txt","w");
        fp1 = fopen("temp.txt","r");

        while(fread(&s1,sizeof(product),1,fp1))
            {
            fwrite(&s1,sizeof(product),1,fp);
            }
        fclose(fp);
        fclose(fp1);
        system("cls");
        printf("\n         Item was Removed From Cart!\n");
        }
    else
        {
        printf("\n          Not Found.....\n");
        }


    remove("temp.txt");

}
void update_after_del(int code,int tempp)
{
    int i, j, found=0;
    product s1;
    FILE *fp, *fp1;
    fp = fopen("products.txt","r");
    fp1 = fopen("temp2.txt","w");
    while(fread(&s1,sizeof(product),1,fp))
        {
        if(s1.item_code == code)
            {
            found = 1;
            s1.item_quantity=s1.item_quantity+tempp;
            }
        fwrite(&s1,sizeof(product),1,fp1);
        }
    fclose(fp);
    fclose(fp1);

    if(found)
        {
        fp = fopen("products.txt","w");
        fp1 = fopen("temp2.txt","r");

        while(fread(&s1,sizeof(product),1,fp1))
            {
            fwrite(&s1,sizeof(product),1,fp);
            }
        fclose(fp);
        fclose(fp1);
        }
    else
        printf("\n          Not Found.....\n");
    remove("temp2.txt");
}
void admin_panel()//
{
    int ch;
cp1:
    printf("           Welcome to Admin Menu!\n");
    printf("           [1].CREATE & RESET [WARNING!]");
    printf("\n           [2].ADD PRODUCT.");
    printf("\n           [3].DISPLAY INVENTORY.");
    printf("\n           [4].NO OF RECORDS.");
    printf("\n           [5].SEARCH.");
    printf("\n           [6].UPDATE.");
    printf("\n           [7].DELETE.");
    printf("\n           [8].SORT ON SCREEN BY NAME.");
    printf("\n           [9].SORT ON SCREEN BY QUANTITY.");
    printf("\n           [10].SORT ON SCREEN BY PRICE.");
    printf("\n           [0].LOGOUT.");
    printf("\n           Enter Your Choice : ");
    scanf("%d",&ch);
    switch(ch)
        {
        case 1:
            system("cls");
            remove("carts.txt");
            remove("products.txt");
            remove("total.txt");
            reset_create();
            break;
        case 2:
            system("cls");
            add_product();
            break;
        case 3:
            system("cls");
            inventory();
            break;
        case 4:
            system("cls");
            total_product();
            break;
        case 5:
            system("cls");
            inventory();
            search();
            break;
        case 6:
            system("cls");
            inventory();
            update();
            break;
        case 7:
            system("cls");
            inventory();
            delete_rec();
            break;
        case 8:
            system("cls");

            sort_by_name();
            break;
        case 9:
            system("cls");
            sort_by_quantity();
            break;
        case 10:
            system("cls");
            sort_by_price();
            break;
        case 0:
            system("cls");
            main();
        }
    goto cp1;
}

void reset_create()//
{
    product s[100];
    FILE *fp;
    int n,i,j;

    printf("          How many item data do you want to entry?\n          -> ");
    scanf("%d",&n);
    fp = fopen("products.txt","w+");

    for(i=0; i<n; i++)
        {
        printf("          Item[%d] Code: ",i+1);
        scanf("%d",&s[i].item_code);

        printf("          Item[%d] Name: ",i+1);
        fflush(stdin);
        gets( s[i].item_name );

        printf("          Item[%d] Quantity: ",i+1);
        scanf("%d",&s[i].item_quantity);

        printf("          Item[%d] Price: ",i+1);
        scanf("%f",&s[i].item_price);

        printf("\n");

        fwrite(s+i,sizeof(product),1,fp);
        }
    fclose(fp);
    system("cls");
    printf("          PRODUCT ADDED SUCCESSFULLY!\n");
}
void inventory()//
{
    product s1;
    FILE *fp;
    printf("\n          INVENTORY: \n");
    printf("          %-21s%-15s%-15s%-15s\n","Product Code","Name","Quantity","Price");
    fp = fopen("products.txt","r");
    while(fread(&s1,sizeof(product),1,fp))
        {
        printf("          %-21d",s1.item_code);
        printf("%-15s",s1.item_name);
        printf("%-15d",s1.item_quantity);
        printf("%-15.2f\n",s1.item_price);
        }
    fclose(fp);
    printf("\n");
}
void update()//
{
    int i, j, found=0;
    product s1;
    FILE *fp, *fp1;
    int code;
    printf("          Enter Code to Update : ");
    scanf("%d",&code);

    fp = fopen("products.txt","r");
    fp1 = fopen("temp.txt","w");
    while(fread(&s1,sizeof(product),1,fp))
        {
        if(s1.item_code == code)
            {
            found = 1;

            printf("          Enter New Quantity : ");
            scanf("%d",&s1.item_quantity);
            printf("          Enter New Price : ");
            scanf("%f",&s1.item_price);
            }
        fwrite(&s1,sizeof(product),1,fp1);
        }
    fclose(fp);
    fclose(fp1);

    if(found)
        {
        fp = fopen("products.txt","w");
        fp1 = fopen("temp.txt","r");

        while(fread(&s1,sizeof(product),1,fp1))
            {
            fwrite(&s1,sizeof(product),1,fp);
            }
        fclose(fp);
        fclose(fp1);
        system("cls");
        printf("          PRODUCT UPDATED SUCCESSFULLY!\n");
        }
    else
        {
        system("cls");
        printf("          Not Found.....\n");
        }


}

void delete_rec()//
{
    int i, j, found=0;
    product s1;
    FILE *fp, *fp1;
    int code;
    printf("          Enter Product Code to Delete : ");
    scanf("%d",&code);

    fp = fopen("products.txt","r");
    fp1 = fopen("temp.txt","w");
    while(fread(&s1,sizeof(product),1,fp))
        {
        if(s1.item_code == code)
            {
            found = 1;
            }
        else
            fwrite(&s1,sizeof(product),1,fp1);
        }
    fclose(fp);
    fclose(fp1);


    if(found)
        {
        fp = fopen("products.txt","w");
        fp1 = fopen("temp.txt","r");

        while(fread(&s1,sizeof(product),1,fp1))
            {
            fwrite(&s1,sizeof(product),1,fp);
            }
        fclose(fp);
        fclose(fp1);
        system("cls");
        printf("          PRODUCT DELETED SUCCESSFULLY!\n");
        }
    else
        {
        printf("\n          Not Found.....\n");
        }

}
void add_product()//
{
    product s[100];
    FILE *fp;
    int n,i,j;

    printf("          How many item data do you want to entry?\n          -> ");
    scanf("%d",&n);
    fp = fopen("products.txt","a");

    for(i=0; i<n; i++)
        {
        printf("          Item[%d] Code: ",i+1);
        scanf("%d",&s[i].item_code);


        printf("          Item[%d] Name: ",i+1);
        fflush(stdin);
        gets( s[i].item_name );

        printf("          Item[%d] Quantity: ",i+1);
        scanf("%d",&s[i].item_quantity);

        printf("          Item[%d] Price: ",i+1);
        scanf("%f",&s[i].item_price);

        printf("\n");

        fwrite(s+i,sizeof(product),1,fp);
        }
    fclose(fp);
}
void search()//
{
    system("cls");
    int i, j, found=0;
    product s1;
    FILE *fp;
    int code;
    printf("          Enter Product Code to Search : ");
    scanf("%d",&code);

    fp = fopen("products.txt","r");
    printf("          %-21s%-15s%-15s%-15s\n","Product Code","Name","Quantity","Price");
    while(fread(&s1,sizeof(product),1,fp))
        {
        if(s1.item_code == code)
            {
            found = 1;
            printf("          %-21d%-15s%-15d%-15.2f\n",s1.item_code,s1.item_name,s1.item_quantity,s1.item_price);
            }
        }
    if(!found)
        printf("\n          Not Found.....\n");
    fclose(fp);
}
void total_product()//
{
    product s1;
    FILE *fp;
    fp = fopen("products.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(product);
    printf("\n          No of Records = %d\n",n);
    fclose(fp);
}
void sort_by_name()//
{
    product s[100], s1;
    FILE *fp;
    fp = fopen("products.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(product);
    int i,j;
    rewind(fp);
    for(i=0; i<n; i++)
        fread(&s[i],sizeof(product),1,fp);

    for(i=0; i<n; i++)
        {
        for(j=i+1; j<n; j++)
            {
            if(strcmp(s[i].item_name,s[j].item_name)>0)
                {
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
                }
            }
        }
    printf("          %-21s%-15s%-15s%-15s\n","Product Code","Name","Quantity","Price");
    for(i=0; i<n; i++)
        {
        printf("          %-21d%-15s%-15d%-15.2f\n",s[i].item_code,s[i].item_name,s[i].item_quantity,s[i].item_price);
        }
    fclose(fp);
}
void sort_by_quantity()//
{
    product s[100], s1;
    FILE *fp;
    fp = fopen("products.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(product);
    int i,j;
    rewind(fp);
    for(i=0; i<n; i++)
        fread(&s[i],sizeof(product),1,fp);

    for(i=0; i<n; i++)
        {
        for(j=i+1; j<n; j++)
            {
            if(s[i].item_quantity<s[j].item_quantity)
                {
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
                }
            }
        }
    printf("          %-21s%-15s%-15s%-15s\n","Product Code","Name","Quantity","Price");
    for(i=0; i<n; i++)
        {
        printf("          %-21d%-15s%-15d%-15.2f\n",s[i].item_code,s[i].item_name,s[i].item_quantity,s[i].item_price);
        }
    fclose(fp);
}
void sort_by_price()
{
    product s[100], s1;
    FILE *fp;
    fp = fopen("products.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(product);
    int i,j;
    rewind(fp);
    for(i=0; i<n; i++)
        fread(&s[i],sizeof(product),1,fp);

    for(i=0; i<n; i++)
        {
        for(j=i+1; j<n; j++)
            {
            if(s[i].item_price>s[j].item_price)
                {
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
                }
            }
        }
    printf("          %-21s%-15s%-15s%-15s\n","Product Code","Name","Quantity","Price");
    for(i=0; i<n; i++)
        {
        printf("          %-21d%-15s%-15d%-15.2f\n",s[i].item_code,s[i].item_name,s[i].item_quantity,s[i].item_price);
        }
    fclose(fp);
}
void headerf()//
{
    printf("          |-----------------|\n");
    printf("          |   WELLCOME TO   |\n");
    printf("          | EWU ONLINE SHOP |\n");
    printf("          |-----------------|\n");
}

int loading()
{
    int p;
    printf("          ");
    for (p = 0; p <= 100; ++p)
        {
        putchar('\r');
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar('[');
        print_n_chars(PROGRESS_BAR_SIZE * p / 100, '|');
        print_n_chars(PROGRESS_BAR_SIZE - PROGRESS_BAR_SIZE * p / 100, ' ');
        putchar(']');
        Sleep(10);

        }

}
void print_n_chars(int n, int c)
{
    while (n-- > 0) putchar(c);
}



