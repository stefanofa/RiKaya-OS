#include "const.h"
#include "listx.h"
#include <umps/libumps.h>
#include <umps/arch.h>

#include "pcb.h"
#include "init.h"
#include "scheduler.h"

pcb_t *proc[3];

extern void addokbuf(char *strp);
extern void test1();
extern void test2();
extern void test3();

unsigned int makeMask () {
 //unsigned int tmp =(KM_EN_MASK & VM_DIS_MASK & INT_DIS_MASK & ~TMR_EN_MASK );
 //tmp |= CP0_EN_MASK;
    return ((STATUS_IEc & STATUS_VMc & STATUS_KUc & ~STATUS_TE)| STATUS_CU0) ;

}

int main () {

    //Popolo le New Areas nel ROM Reserved Frame
    populateNewAreas();
    addokbuf("NEW AREAS popolate\n");

    //Istanzio la lista dei PCB
    initPcbs();
	addokbuf("Process Control Blocks inizializzati\n");

    //creo la maschera utilizzata per inizializzare il campo status dei processi
    unsigned int mask = makeMask();

    //Alloco i 3 processi, inizializzando i PCB relativi ed assegnando
    //ad ognuno di essi il puntatore all'area di memoria della loro funzione
    proc[0] = allocAndSet ((memaddr)test1, 1, mask);
    proc[1] = allocAndSet ((memaddr)test2, 2, mask);
    proc[2] = allocAndSet ((memaddr)test3, 3, mask);
    addokbuf("PCB allocati\n");

    mkEmptyProcQ (&ready_queue_h);

    //inserisco i 3 PCB precedentemente creati nella lista dei PCB
    insertProcQ (&ready_queue_h, proc[0]);
    insertProcQ (&ready_queue_h, proc[1]);
    insertProcQ (&ready_queue_h, proc[2]);
    //salvataggio delle priorità iniziali nel campo original_priority

    addokbuf("Inizio esecuzione\n");

    //inizio esecuzione
    scheduler();

    return 0;
}
