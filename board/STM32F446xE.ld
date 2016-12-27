/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * ST32F446xE memory setup.
 * Note: Use of ram1 and ram2 is mutually exclusive with use of ram0.
 */
MEMORY
{
    flash0  : org = 0x08000000, len = 16k		/* Sector 0 (16kB) */
    flash1  : org = 0x00004000, len = 16k		/* Sector 1 (16kB) */
    flash2  : org = 0x00008000, len = 16k		/* Sector 2 (16kB) */
    flash3  : org = 0x0000C000, len = 464k		/* Sector 3 (16kB) + Sector 4 (64kB) + Sector 5-7 (3*128kB) */
    flash4  : org = 0x00000000, len = 0
    flash5  : org = 0x00000000, len = 0
    flash6  : org = 0x00000000, len = 0
    flash7  : org = 0x00000000, len = 0
    ram0    : org = 0x20000000, len = 128k    /* SRAM1 + SRAM2 */
    ram1    : org = 0x20000000, len = 112k    /* SRAM1 */
    ram2    : org = 0x00000000, len = 16k     /* SRAM2 */
    ram3    : org = 0x00000000, len = 0
    ram4    : org = 0x00000000, len = 0
    ram5    : org = 0x00000000, len = 0
    ram6    : org = 0x00000000, len = 0
    ram7    : org = 0x00000000, len = 0
}

/* For each data/text section two region are defined, a virtual region
   and a load region (_LMA suffix).*/

/* Flash region for booting and then jumping to flash3. */
REGION_ALIAS("BOOT_FLASH", flash0);
REGION_ALIAS("BOOT_FLASH_LMA", flash0);

/* Flash region 1 for EEPROM emulation. */
REGION_ALIAS("EEPROM_FLASH1", flash1);
REGION_ALIAS("EEPROM_FLASH1_LMA", flash1);

/* Flash region 2 for EEPROM emulation. */
REGION_ALIAS("EEPROM_FLASH2", flash2);
REGION_ALIAS("EEPROM_FLASH2_LMA", flash2);

/* Flash region to be used for exception vectors.*/
REGION_ALIAS("VECTORS_FLASH", flash3);
REGION_ALIAS("VECTORS_FLASH_LMA", flash3);

/* Flash region to be used for constructors and destructors.*/
REGION_ALIAS("XTORS_FLASH", flash3);
REGION_ALIAS("XTORS_FLASH_LMA", flash3);

/* Flash region to be used for code text.*/
REGION_ALIAS("TEXT_FLASH", flash3);
REGION_ALIAS("TEXT_FLASH_LMA", flash3);

/* Flash region to be used for read only data.*/
REGION_ALIAS("RODATA_FLASH", flash3);
REGION_ALIAS("RODATA_FLASH_LMA", flash3);

/* Flash region to be used for various.*/
REGION_ALIAS("VARIOUS_FLASH", flash3);
REGION_ALIAS("VARIOUS_FLASH_LMA", flash3);

/* Flash region to be used for RAM(n) initialization data.*/
REGION_ALIAS("RAM_INIT_FLASH_LMA", flash3);

/* RAM region to be used for Main stack. This stack accommodates the processing
   of all exceptions and interrupts.*/
REGION_ALIAS("MAIN_STACK_RAM", ram0);

/* RAM region to be used for the process stack. This is the stack used by
   the main() function.*/
REGION_ALIAS("PROCESS_STACK_RAM", ram0);

/* RAM region to be used for data segment.*/
REGION_ALIAS("DATA_RAM", ram0);
REGION_ALIAS("DATA_RAM_LMA", flash3);

/* RAM region to be used for BSS segment.*/
REGION_ALIAS("BSS_RAM", ram0);

/* RAM region to be used for the default heap.*/
REGION_ALIAS("HEAP_RAM", ram0);

/* Generic rules inclusion.*/
INCLUDE rules.ld
