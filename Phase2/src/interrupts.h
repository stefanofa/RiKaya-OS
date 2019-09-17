#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "scheduler.h"
#include "syscalls.h"
#include "handler.h"

int semDev[MAX_DEVICES];//array utilizzato per inizializzare i semafori dei devices correttamente
semdev semDevices;//semdev è la struttura dati contenente i semafori dei devices
int pseudoclock;//serve per inizializzare e allocare il semaforo della wait clock
semd_t pseudoclock_sem;//semaforo della wait clock
state_t *old_area;//puntatore alla INT_OLDAREA nel caso curr_proc = NULL
pcb_t *wakeup_proc;//processo risvegliato da una V quando un device completa l'operazione di I/O

void Interrupt_Handler();
int getDevice(int line_no, int dev_no);
void IO_request(U32 command, U32 * reg, U32 term_command);

#endif
