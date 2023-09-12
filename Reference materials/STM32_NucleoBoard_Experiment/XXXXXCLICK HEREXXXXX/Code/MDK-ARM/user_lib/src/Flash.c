#include "Flash.h"

// starting from 256KB bank - 128KB
uint32_t startAddress = 0x80400000;

/**
 * Define a method to read in a maze from memory
 */
void readFlash(uint16_t ** maze) {
    uint16_t i, j;
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            // read as "maze at i, j is the value at address startAddress +
            // offset as a function of i, j as an unsigned, 16-bit intger."
            maze[i][j] = *(uint16_t *)(startAddress + (i*16 + j) * 2);
        }
    }
}

/**
 * Define a method to write a maze to memory
 */
void writeFlash(uint16_t ** maze) {
    uint16_t i, j;

    // unlock for writing 
    FLASH_Unlock();

    //*FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    
    // we need to erase the entire page before we can start to write to it.
    //*FLASH_ErasePage(startAddress);

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            FLASH_ProgramHalfWord((startAddress + (i * 16 + j) * 2), maze[i][j]);
        }
    }
}