///////////////////////////////////////////////////////////////////////////////////
//
//  Header file inclusion
//
//////////////////////////////////////////////////////////////////////////////////


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

///////////////////////////////////////////////////////////////////////////////////
//
// User Defined Macros
//
//////////////////////////////////////////////////////////////////////////////////

//Maximun file size that we are allowed in project
#define MAXFILESIZE 50

#define MAXOPENFILES 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2


#define EXECUTE_SUCCESS 0  

///////////////////////////////////////////////////////////////////////////////////
//
// User Defined Strutures
//
//////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
//
// Structure name:BootBlock
// Description   :Holds the information to boot the OS
//
//////////////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

///////////////////////////////////////////////////////////////////////////////////
//
// Structure name:SuperBlock
// Description   :Holds the information about the file System
//
//////////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

///////////////////////////////////////////////////////////////////////////////////
//
// Structure name:Inode
// Description   :Holds the information about the file
//
//////////////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int ReferenceCount;
    int Permission;
    char *Buffer;

    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;
//////////////////////////////////////////////////////////////////////////////////
//
// Structure name:FileTable
// Description   :Holds the information about opened file
//
//////////////////////////////////////////////////////////////////////////////////
 
 struct FileTable
 {
    int ReadOffset;
    int WriteOffset;
    int Mode;                 
    PINODE ptrinode;          
 };


typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

//////////////////////////////////////////////////////////////////////////////////
//
// Structure name:UAREA
// Description   :Holds the information about the process
//
//////////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};


//////////////////////////////////////////////////////////////////////////////////
//
// Global Varible or object used in the project
//
//////////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head=NULL;                  

//////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IntializeUREA
// Description  : It is used to intialise UAREA  memebers
// Author       : Pradnya Bhausaheb Wani
// Date         : 13/1/2026
//
///////////////////////////////////////////////////////////////////////////////// 

void InitialiseUREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i=0;
    for(i=0;i<MAXOPENFILES;i++)
    {
        uareaobj.UFDT[i]=NULL;
    }
    printf("Marvellous CVFS:Uarea gets intialised succesfully\n");
}

//////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IntializeSuperBlock
// Description  : It is used to intialise USuperBlock  memebers
// Author       : Pradnya Bhausaheb Wani
// Date         : 13/1/2026
//
/////////////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes=MAXINODE;
    superobj.FreeInodes=MAXINODE;

    printf("Marvellous CVFS:Super Block gets intialised succesfully\n");
} 

//////////////////////////////////////////////////////////////////////////////////
//
// Function Name: CreateDILB
// Description  : It is used to create link list of inodes
// Author       : Pradnya Bhausaheb Wani
// Date         : 13/1/2026
//
/////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i=1;
    PINODE newn=NULL;
    PINODE temp=head;


    for(i=1;i<=MAXINODE;i++)
    {
        newn=(PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName,"\0");
        newn->InodeNumber=i;
        newn->FileSize=0;
        newn->ActualFileSize=0;
        newn->ReferenceCount=0;
        newn->Permission=0;
        newn->Buffer=NULL;
        newn->next=NULL;

        if(temp==NULL)//LL is empty
        {
            head=newn;
            temp=head;
        }
        else         //At least one node
        {
            temp->next=newn;
            temp=temp->next;
        }
    }
    printf("Marvellous CVFS:DILB created succesfully\n");
}

//////////////////////////////////////////////////////////////////////////////////
//
// Function Name: StartAuxillaryDataIntiltisation
// Description  : It is used to call all such fuction which are which are used intialise auxillary data
// Author       : Pradnya Bhausaheb Wani
// Date         : 13/1/2026
//
/////////////////////////////////////////////////////////////////////////////////
 

void StartAuxillaryDataIntiltisation()             
{
    strcpy(bootobj.Information,"Botting process of marvellous CVFS is done\n");

    printf("%s\n",bootobj.Information);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUREA();

    printf("Marvelluos CVFS :Auxillary data intialise succesfully\n");
} 

///////////////////////////////////////////////////////////////////////////////////
//
// Entry point Function of the project 
//
//////////////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80]={'\0'};
    char Command[5][20]={{'\0'}};
    int iCount=0;

    StartAuxillaryDataIntiltisation();

    printf("------------------------------------------------------------------------\n");
    printf("---------------------Marvellous CVFS stated sucessfully-----------------\n");
    printf("------------------------------------------------------------------------\n");

    //infinte listening shell
    while(1)                //Unconditional Loop 
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\n Marvellous CVFS: > ");
        fgets(str,sizeof(str),stdin);      //scanf("%S\n",str)

        iCount=sscanf(str,"%s %s %s %s %s",Command[0],Command[1],Command[2],Command[3],Command[4]);

       

        fflush(stdin);

        if(iCount==1)
        {
            if(strcmp("exit",Command[0])==0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            else if(strcmp("ls",Command[0])==0)
            {
                printf("Inside ls\n");
            }
        }//end of else if 1
        else if(iCount==2)
        {

        }//end of else if 2
        else if(iCount==3)
        {

        }//end of else if 3
        else if(iCount==4)
        {

        }//end of else if 4
        else
        {
            printf("Command not Found\n");
            printf("Please refer help option to get more information\n");
        }//end of else

        


    }//end of while

    return 0;
}//end of main
