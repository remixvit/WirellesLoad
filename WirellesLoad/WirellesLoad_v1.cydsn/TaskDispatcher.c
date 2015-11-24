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

#include "TaskDispatcher.h"

inline void TaskManager(void) //Диспетчер задач
{
    uint8      index=0;
    TPTR   GoToTask = Idle;      // Инициализируем переменные
 
        // Как видишь, тут есть указатель Idle - ведущий на процедуру простоя ядра.
        // На нее можно повесить что нибудь совсем фоновое, например отладочные примочки =)  
        // И локальная переменная-указатель GoToTask куда мы будем жрать адреса переходов
 
    CyGlobalIntDisable;
        // Запрещаем прерывания!!! Это макрос. Поэтому без ; в конце. 
        // Почему не CLI()? Это команда AVR, а я хотел сделать максимально
        // платформонезависимый диспетчер. Прерывания надо запрещать потому, что
        // Идет обращение к глобальной очереди диспетчера. Ее могут менять и прерывания
        // Поэтому заботимся об атомарности операции. 
 
    GoToTask = TaskQueue[0];	// Хватаем первое значение из очереди
 
    if (GoToTask==Idle)		// Если там пусто
	{
	    CyGlobalIntEnable;		// Разрешаем прерывания
	    (Idle)();			// Переходим на обработку пустого цикла
    }
    else
   	{
       	for(index=0;index!=TaskQueueSize;index++)	// В противном случае сдвигаем всю очередь
  		{
    		TaskQueue[index]=TaskQueue[index+1];
		}
        TaskQueue[TaskQueueSize]= Idle;	// В последнюю запись пихаем затычку Idle
     
    	CyGlobalIntEnable;		// Разрешаем прерывания
    	(GoToTask)();		// Переходим к задаче
       	}
}


void SetTask(TPTR TS)
{
    uint8		index = 0;
    uint8   	nointerrupted = 0;

    	CyGlobalIntDisable;
    	nointerrupted = 1;					// И ставим флаг, что мы не в прерывании. 
    	

    while(TaskQueue[index]!=Idle) 			// Прочесываем очередь задач на предмет свободной ячейки
    	{									// с значением Idle - конец очереди.
    	index++;
    	if (index==TaskQueueSize+1) 		// Если очередь переполнена то выходим не солоно хлебавши
    		{
    		if (nointerrupted)	CyGlobalIntEnable; 	// Если мы не в прерывании, то разрешаем прерывания
    		return;									// Раньше функция возвращала код ошибки - очередь переполнена. Пока убрал.
    		}
    	}
    												// Если нашли свободное место, то
    TaskQueue[index] = TS;							// Записываем в очередь задачу
    if (nointerrupted) CyGlobalIntEnable;			// И включаем прерывания если не в обработчике прерывания.
}

//Функция установки задачи по таймеру. Передаваемые параметры - указатель на функцию, 
// Время выдержки в тиках системного таймера. Возвращет код ошибки.
void SetTimerTask(TPTR TS, uint32 NewTime)
{
    uint8		index=0;
    uint8		nointerrupted = 0;

	CyGlobalIntDisable;
	nointerrupted = 1;
	
    for(index=0;index!=MainTimerQueueSize+1;++index)	//Прочесываем очередь таймеров
    	{
    	    if(MainTimer[index].GoToTask == TS)				// Если уже есть запись с таким адресом
    	    {
		        MainTimer[index].Time = NewTime;			// Перезаписываем ей выдержку
		        if (nointerrupted) 	CyGlobalIntEnable;		// Разрешаем прерывания если не были запрещены.
		        return;										// Выходим. Раньше был код успешной операции. Пока убрал
            }
        }
	

    for(index=0;index!=MainTimerQueueSize+1;++index)	// Если не находим похожий таймер, то ищем любой пустой	
	{
    	if (MainTimer[index].GoToTask == Idle)		
    	{
    		MainTimer[index].GoToTask = TS;			// Заполняем поле перехода задачи
    		MainTimer[index].Time = NewTime;		// И поле выдержки времени
    		if (nointerrupted) 	CyGlobalIntEnable;	// Разрешаем прерывания
    		return;									// Выход. 
    	}
		
	}												// тут можно сделать return c кодом ошибки - нет свободных таймеров
}


inline void InitRTOS(void)
{
    uint8	index;

    for(index=0;index!=TaskQueueSize+1;index++)	// Во все позиции записываем Idle
    	{
    	TaskQueue[index] = Idle;
    	}


    for(index=0;index!=MainTimerQueueSize+1;index++) // Обнуляем все таймеры.
    	{
    	MainTimer[index].GoToTask = Idle;
    	MainTimer[index].Time = 0;
    	}
}

inline void RTOS_Start()
{
    InitRTOS();
    Timer_RTOS_ISR_StartEx(TaskDispatcher_ISR);
}

inline void  Idle(void)
{
    
}

/*
Служба таймеров ядра. Должна вызываться из прерывания раз в 1мс. Хотя время можно варьировать в зависимости от задачи

To DO: Привести к возможности загружать произвольную очередь таймеров. Тогда можно будет создавать их целую прорву. 
А также использовать эту функцию произвольным образом. 
В этом случае не забыть добавить проверку прерывания. 
*/
inline void TimerService(void)
{
    uint8 index;

    for(index=0;index!=MainTimerQueueSize+1;index++)		// Прочесываем очередь таймеров
    	{
    	if(MainTimer[index].GoToTask == Idle) continue;		// Если нашли пустышку - щелкаем следующую итерацию

    	if(MainTimer[index].Time !=1)						// Если таймер не выщелкал, то щелкаем еще раз. 
    		{												// To Do: Вычислить по тактам, что лучше !=1 или !=0. 
    		MainTimer[index].Time --;						// Уменьшаем число в ячейке если не конец.
    		}
    	else
    		{
    		SetTask(MainTimer[index].GoToTask);				// Дощелкали до нуля? Пихаем в очередь задачу
    		MainTimer[index].GoToTask = Idle;				// А в ячейку пишем затычку
    		}
    	}
}



CY_ISR(TaskDispatcher_ISR)
{
    TimerService();
    //RTC_Update();
}

/* [] END OF FILE */
