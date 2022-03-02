
    EXTERN currentSP
    EXTERN scheduler
    EXTERN PrintHex

    PUBLIC TaskSwitch

EXC_RETURN_THREAD_MODE EQU 0xFFFFFFF9

    SECTION .text:CODE:REORDER:NOROOT(2)
    THUMB


/*
 *  Context switching interrupt handler.
 *
 *  This is the handler for the PendSV exception.
 *
 *  Expected state on entry:
 *
 *      The Cortex-M4 exception handling hardware has pushed the 
 *      following on the stack using the Main stack pointer:
 *      
 *        xPSR
 *        PC
 *        LR
 *        R12
 *        R3
 *        R2
 *        R1
 *        R0 <-- SP_Main
 *   
 */
TaskSwitch
    //Experiment: I want to see if TaskSwitch gets called
    //this is important because it proves that SysTick is causing
    //an interrupt which results in TaskSwitch being called
    //MOV R0,#8
    //BL PrintHex
    
    // Disable interrupts
    CPSID I
    
    // Save registers R4-R11 using register SP
    PUSH {R4-R11}
    
    // Set up argument for procedure call by copying SP to R0
    MOV R0,R13
    
    // Call scheduler(uint_32 sp) to save the current SP and determine the next
    // value of currentSP. It takes its input argument sp from R0.
    BL scheduler
    
    // Load address of currentSP into R0
    LDR R0,=currentSP
    //MOV R0,R1
    
    
    // Load the value of currentSP into SP
    LDR R13,[R0]
    
    // Load registers R4-R11 using SP
    POP {R4-R11}
    
    // Ensure that we return from exception Handler Mode to Thread Mode by 
    // loading the value EXC_RETURN_THREAD_MODE into LR
    MOV R14, #0xFFFFFFF9
    
    // Enable interrupts
    CPSIE I
    
    // Branch using LR to return from exception while atomically restoring 
    // registers R0-R3, R12, LR, PC and xPSR
    BX LR
    

    END
