//include whatever needed files.

struct pcb* pcb_create(char* name, char* class, char* priority){

    //pcb_setup() to create a pcb

    //insert into the appropriate queue with pcb_insert()
    
    //ERROR HANDLING:
        //name must be unique and valis, class and priority must be valid

    return 0;
}

//delete
void pcb_delete(char* name){

    //find process and remove from queue w/ pcb_remove()

    //free all associated mem with pcb_free()


    //ERROR HANDLING:
        //valid name
        //cannot be a system process

    return 0;
}

//block
void pcb_block(char* name){

    //puts process in blocked state

    //move to appropriate queue

    //ERROR HANDLING:
        //must be valid name
    
    return 0;
}

//unblock
void pcb_unblock(char* name){
    //put process in ready (unblocked) state
    //move to appropriate queue

    //ERROR HANDLING:
        //Name must be valid

    return 0;
}

//suspend
void pcb_suspend(char* name){
    //put process in suspended state
    //move to appropriate queue

    //ERROR HANDLING:
        //name must be valid
        //must NOT be a system process
}
//resume
void pcb_resume(char* name){
    //put a process not in the suspended state
    //moves it to the appropriate queue

    //ERROR HANDLING:
        //name must be valid
}

//set priority

//show PCB

//show ready

//show blocked

//show all
