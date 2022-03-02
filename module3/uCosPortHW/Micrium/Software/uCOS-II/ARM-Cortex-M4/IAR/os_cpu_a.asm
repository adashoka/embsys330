;
;********************************************************************************************************
;                                                uC/OS-II
;                                          The Real-Time Kernel
;
;
;                         (c) Copyright 2009-2013; Micrium, Inc.; Weston, FL
;                    All rights reserved.  Protected by international copyright laws.
;
;                                           ARM Cortex-M4 Port
;
; File      : OS_CPU_A.ASM
; Version   : V2.92.09
; By        : JJL
;             BAN
;             JBL
;
; For       : ARMv7 Cortex-M4
; Mode      : Thumb-2 ISA
; Toolchain : IAR EWARM
;
; Modified 2016 for University of Washington uCOS port
;********************************************************************************************************
;

;********************************************************************************************************
;                                          PUBLIC FUNCTIONS
;********************************************************************************************************

    EXTERN  OSRunning                                           ; External references
    EXTERN  OSIntExit
    EXTERN  OSTaskSwHook
    EXTERN  OS_CPU_ExceptStkBase
    EXTERN  OSPrioCur
    EXTERN  OSPrioHighRdy
    EXTERN  OSTCBCur
    EXTERN  OSTCBHighRdy

    PUBLIC  OS_CPU_SR_Save                                      ; Functions declared in this file
    PUBLIC  OS_CPU_SR_Restore
    PUBLIC  OSStartHighRdy
    PUBLIC  OSCtxSw
    PUBLIC  OSIntCtxSw
    PUBLIC  ContextSwitch



;********************************************************************************************************
;                                               EQUATES
;********************************************************************************************************

NVIC_INT_CTRL      EQU     0xE000ED04                              ; Interrupt control state register.
NVIC_SYSPRI14      EQU     0xE000ED22                              ; System priority register (priority 14).
NVIC_PENDSV_PRI    EQU           0xFF                              ; PendSV priority value (lowest).
NVIC_PENDSVSET     EQU     0x10000000                              ; Value to trigger PendSV exception.
EXC_RET_MSP_THREAD EQU     0xFFFFFFF9                              ; Exception return to Main stack thread mode


;********************************************************************************************************
;                                     CODE GENERATION DIRECTIVES
;********************************************************************************************************

    RSEG CODE:CODE:NOROOT(2)
    THUMB



;********************************************************************************************************
;                                   CRITICAL SECTION METHOD 3 FUNCTIONS
;
; Description: Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
;              would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
;              disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
;              disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
;              into the CPU's status register.
;
; Prototypes :     OS_CPU_SR  OS_CPU_SR_Save(void);
;                  void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
;
;
; Note(s)    : 1) These functions are used in general like this:
;
;                 void Task (void *p_arg)
;                 {
;                 #if OS_CRITICAL_METHOD == 3          /* Allocate storage for CPU status register */
;                     OS_CPU_SR  cpu_sr;
;                 #endif
;
;                          :
;                          :
;                     OS_ENTER_CRITICAL();             /* cpu_sr = OS_CPU_SaveSR();                */
;                          :
;                          :
;                     OS_EXIT_CRITICAL();              /* OS_CPU_RestoreSR(cpu_sr);                */
;                          :
;                          :
;                 }
;********************************************************************************************************

OS_CPU_SR_Save
    // Capture current interrupt enable/disable status (PRIMASK)
    // <Your code here>
    MRS R0,PRIMASK
    
    // Disable interrupts
    // <Your code here>
    CPSID I
    
    // Return captured interrupt enable/disable status
    // <Your code here>
    BX LR

OS_CPU_SR_Restore
    // Restore argument in R0 to PRIMASK
    // <Your code here>
    MSR PRIMASK,R0
    
    // Return
    // <Your code here>
    BX LR


;********************************************************************************************************
;                                         START MULTITASKING
;                                      void OSStartHighRdy(void)
;
; Note(s) : 1) This function triggers a PendSV exception (essentially, causes a context switch) to cause
;              the first task to start.
;
;           2) OSStartHighRdy() MUST:
;              a) Setup PendSV exception priority to lowest;
;              b) Set initial PSP to 0, to tell context switcher this is first run;
;              c) Set the main stack to OS_CPU_ExceptStkBase
;              d) Set OSRunning to TRUE;
;              e) Trigger PendSV exception;
;              f) Enable interrupts (tasks will run with interrupts enabled).
;********************************************************************************************************

OSStartHighRdy
    
    LDR     R0, =OS_CPU_ExceptStkBase                           ; Initialize the SP to the OS_CPU_ExceptStkBase
    LDR     R1, [R0]
    MOV     SP, R1    

    LDR     R0, =OSRunning                                      ; OSRunning = TRUE
    MOVS    R1, #1
    STRB    R1, [R0]

    LDR     R0, =NVIC_INT_CTRL                                  ; Trigger the PendSV exception (causes context switch)
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]

    MOVS    R0, #4                                              ; PSP = 4 will tell PendSV handler to not save context
    MSR     PSP, R0

    CPSIE   I                                                   ; Enable interrupts at processor level

OSStartHang
    B       OSStartHang                                         ; Should never get here


;********************************************************************************************************
;                       PERFORM A CONTEXT SWITCH (From task level) - OSCtxSw()
;
; Note(s) : 1) OSCtxSw() is called when OS wants to perform a task context switch.  This function
;              triggers the PendSV exception which is where the real work is done.
;********************************************************************************************************

OSCtxSw
    LDR     R0, =NVIC_INT_CTRL                                  ; Trigger the PendSV exception (causes context switch)
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]
    BX      LR


;********************************************************************************************************
;                   PERFORM A CONTEXT SWITCH (From interrupt level) - OSIntCtxSw()
;
; Note(s) : 1) OSIntCtxSw() is called by OSIntExit() when it determines a context switch is needed as
;              the result of an interrupt.  This function simply triggers a PendSV exception which will
;              be handled when there are no more interrupts active and interrupts are enabled.
;********************************************************************************************************

OSIntCtxSw
    LDR     R0, =NVIC_INT_CTRL                                  ; Trigger the PendSV exception (causes context switch)
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]
    BX      LR



// ContextSwitch
// Performs a context switch.
//
// SP_Main is used throughout this uCOS port in both Thread mode and 
// Handler mode. 
//
// SP_Process is not used for anything but as a flag to indicate the initial 
// context switch that kicks off multitasking.

ContextSwitch
    // Disable interrupts
    // <Your code here>
    CPSID I
    
    // For the initial context switch we must not save the context.
    // To ensure this, PSP is used as a flag to indicate the initial context 
    // switch.
    // See OSStartHighRdy for flag setup.
    
    // Copy process stack pointer to R0
    // <Your code here>
    MRS R0, PSP
    
    // Subtract 4 and set APSR flags
    // <Your code here>
    SUBS R0,R0,#4
    
    // If R0==0 (that is PSP is 4; Z flag set to 0) use conditional execution to set PSP to 0 and branch to 
    // ContextSwitch_AfterSave
    // <Your code here>
    ITT EQ
    MSREQ PSP,R0
    BLEQ ContextSwitch_AfterSave

    // Save R4-R11 to main stack
    // <Your code here>
    PUSH {R4-R11}

    //OSTCBCur->OSTCBStkPtr = SP
    //<Your code here>
    LDR R0,=OSTCBCur
    LDR R0,[R0]
    LDR R0,[R0] //???
    STR SP,[R0] //store Stack Pointer value into address pointed by R0. R0 contains the address of first element 
    //OsTCBCur struct.
    
    // At this point, entire context of task has been saved
    
ContextSwitch_AfterSave

    // Call OSTaskSwHook();
    // <Your code here>
    BL OSTaskSwHook

    // OSPrioCur = OSPrioHighRdy;
    // <Your code here>
    LDR R0,=OSPrioHighRdy
    LDR R0,[R0] //value of OSPrioHighRdy
    LDR R1,=OSPrioCur
    STR R0,[R1]

    // OSTCBCur = OSTCBHighRdy;
    // <Your code here>
    LDR R0,=OSTCBHighRdy
    LDR R0,[R0]
    LDR R1,=OSTCBCur
    STR R0,[R1]

    // SP = OSTCBHighRdy->OSTCBStkPtr;
    // <Your code here>
    LDR R0,=OSTCBHighRdy
    LDR R0,[R0]
    LDR R0,[R0]
    MOV SP,R0
    
    
    // Restore R4-R11
    // <Your code here>
    POP {R4-R11}
    
    // Ensure exception returns to Thread Mode and MSP
    MOV     LR, #EXC_RET_MSP_THREAD
    
    // Enable interrupts
    CPSIE   I
    
    // Return from exception
    BX      LR

    END
