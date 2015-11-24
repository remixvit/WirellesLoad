/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <Project.h>
#include "SysClock.h"

#define TaskQueueSize 10
#define MainTimerQueueSize 20

typedef void (*TPTR)(void); //указатель пустышка

volatile static TPTR TaskQueue[TaskQueueSize+1];// очередь указателей

volatile static struct
                  {
                  TPTR GoToTask;		// Указатель перехода
                  uint32 Time;			// Выдержка в мс
                  }
MainTimer[MainTimerQueueSize+1];   // Очередь таймеров


inline void TaskManager(void);
void SetTask(TPTR TS);
inline void TimerService(void);
void SetTimerTask(TPTR TS, uint32 NewTime);
inline void InitRTOS(void);
inline void RTOS_Start();
inline void  Idle(void);


CY_ISR(TaskDispatcher_ISR);
/* [] END OF FILE */
