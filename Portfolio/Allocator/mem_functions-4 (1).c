#include "mem.h"
extern BLOCK_HEADER* first_header;


int getSize(BLOCK_HEADER* current){
    int blockSize = 0;
    blockSize = current->size_alloc & 0xFFFFFFFE;    
    return blockSize; 
}

int isAlloc(BLOCK_HEADER* current){
    int alloc = 0;
    alloc = current->size_alloc &1;
    return alloc;
}




// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size){
    int blockSize = 0;
    int alloc = 0;
   // int payload = 0;
    int padding = 0;
    int newPadding = 0;
    int newBlockSize = 0;
    int payload = 0;
  void *userPointer;
 //  void *nextUserPointer;
    BLOCK_HEADER *nextHeader;
    BLOCK_HEADER *current = first_header; 
        
        while(1) {
           // alloc = current->size_alloc & 1;
           // blockSize = current->size_alloc & 0xFFFFFFFE;
           alloc = isAlloc(current); 
           blockSize = getSize(current);


            if (!alloc) {
                payload = current->payload;
                if (payload >= size) {
                  //  size++;
                   // current->size_alloc = size+8; 
               
                current->size_alloc = blockSize | 1;
                current -> payload = size;
                padding = blockSize - 8 - size ;



                if (padding >=16) {
                    newPadding = padding%16; 
                    newBlockSize = size + 8 + newPadding;
                    current ->size_alloc = newBlockSize | 1;
                    current-> payload = size;
                    userPointer = (void *)((unsigned long)current+8);  

                    nextHeader = (BLOCK_HEADER *)((unsigned long)current+newBlockSize);
                    nextHeader->size_alloc = blockSize - newBlockSize;
                    nextHeader->payload = blockSize - newBlockSize - 8;
                  // nextUserPointer = (void *)((unsigned long)current+newBlockSize+8);
                     //split
                     
}
                  return userPointer;  //allocate block
}
                
}



 if (current->size_alloc == 1)  {return NULL;}  

        current = (BLOCK_HEADER *)((unsigned long)current + blockSize);

}

}


 // find a free block that's big enough

    // return NULL if we didn't find a block

    // allocate the block

    // split if necessary (if padding size is greater than or equal to 16 split the block)

   



// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr){
    int blockSize = 0;
   int afterBlockSize = 0;
    int alloc = 0;
   int alloc2 = 0;
    BLOCK_HEADER *current = first_header;
    BLOCK_HEADER *nextHeader;
    
    void *userPointer;

    while (1) {

    
    blockSize = getSize(current);
    userPointer = (void *)((unsigned long)current+8);
   // alloc = isAlloc(current);


     if (userPointer == ptr) {
    blockSize = getSize(current); 
    current->size_alloc = blockSize;
    current->payload = blockSize - 8;
     
   break;  
} 
if (current->size_alloc == 1) return -1;
    current = (BLOCK_HEADER *)((unsigned long)current + blockSize);

}



current = first_header;
blockSize = getSize(current); 
    while (1) {
 
    nextHeader = (BLOCK_HEADER *)((unsigned long)current+blockSize);
    alloc = isAlloc(current);
    alloc2 = isAlloc (nextHeader);
    


    if (!alloc) {
        if (!alloc2) {
            blockSize = getSize(current);
            afterBlockSize = getSize(nextHeader);
            current->size_alloc = blockSize + afterBlockSize;
            current->payload = blockSize + afterBlockSize - 8;
            return 0;
}

}

if (current->size_alloc == 1) break;
//current = nextHeader;
current = (BLOCK_HEADER *)((unsigned long)current + blockSize);
 
} 
return 0;
}


 
   
 

 

/* if (current->size_alloc == 1) return -1;
 current = (BLOCK_HEADER *)((unsigned long)current + blockSize);

}


while (1) {
    current = first_header; 
    alloc = isAlloc(current);
    blockSize = getSize(current);
    if (!alloc){
         nextHeader = (BLOCK_HEADER *)((unsigned long)current+blockSize);    
         int nextBlockSize = getSize(nextHeader);
         alloc = isAlloc(nextHeader);
         if (!alloc) {
            current->size_alloc = blockSize + nextBlockSize;
            return 0;
}




}
if (current->size_alloc == 1) break;
   current = (BLOCK_HEADER *)((unsigned long)current + blockSize);





}   

  // traverse the list and check all pointers to find the correct block 
    // if you reach the end of the list without finding it return -1
    
    // free the block 

    // coalesce adjacent free blocks

  
}*/



