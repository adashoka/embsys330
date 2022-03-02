/*
 * University of Washington
 * Certificate in Embedded and Real-Time Systems
 *
 * uDebugger homework
 */


#include "bsp.h"
#include "print.h"


char clr_scrn[] = { 27, 91, 50, 74, 0 };              // esc[2J
/* Public variables ----------------------------------------------------------*/
PRINT_DEFINEBUFFER();           /* required for lightweight sprintf */
/* Private prototype ---------------------------------------------------------*/

void SystemInit(void);

// Generates a fault exception
void GenerateFault()
{
    static int count = 0;

    count++;

    if (count > 10)
    {
        PrintString("\nSuccess!\n");
        SetLED(1);
        while (1);
    }

    /* TODO: Modify the code to cause a data fetch bus fault by reading */
    /* memory at an invalid address. */
    //int *a = (int*) 0x20000000;
    int *a = (int*) 0x30000000;
    int b = *a;
    b = b; // This line just avoids a compiler warning

    PrintString("\nFail! Should not arrive here.\n");
    while (1);
    
}


int MyFunction2(int a,int b,int c)
{
   int ap=a+1;
   int bp=b+1;
   int cp=c+1;
   int value=ap+bp+cp;
   return value;
}

int MyFunction (int a,int b,int c)
{
   //--------------------------------------
   //when you call MyFunction 2 within 
   //My Function; see [num] below
   //--------------------------------------
   //[1]here LR gets pushed
   int ap=a+1;
   int bp=b+1;
   int cp=c+1;
   int value = MyFunction2(ap,bp,cp);
   //int value=ap+bp+cp;
   return(value);
   //[2][a] here LR gets poped into PC
   //or
   //[2] [b] you could pop it back into LR
   //and then execute BX LR
}

 
void main() {
    Hw_init();
    
    int res = MyFunction(1,2,3);
    
    PrintString(clr_scrn); /* Clear entire screen */
    PrintString("University of Washington - Debugger Test Application \n");

    GenerateFault();

    PrintString("\nFail! Should not arrive here.\n");
    while(1);
}


