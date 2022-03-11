/************************************************** 
 * @Author: shuren
 * @Date: 2022-03-04 14:14:03
 * @LastEditTime: 2022-03-04 20:36:25
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_bsp\bsp_fmc.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "base_typle.h"
#include "gd32f30x.h"
#include "disp.h"
#include "my_print.h"

typedef enum {FAILED = 0, PASSED = !FAILED} test_state;
#define FLASH_PAGE_SIZE ((uint16_t)0x800)
#define FMC_PAGES_PROTECTED (OB_WP_6 | OB_WP_7)

#define BANK0_WRITE_START_ADDR  ((uint32_t)0x0803F000)
#define BANK0_WRITE_END_ADDR    ((uint32_t)0x0803FFFF)

uint32_t erase_counter = 0x0, Address = 0x0;
uint32_t wp_value = 0xFFFFFFFF, protected_pages = 0x0;
uint32_t page_num;
__IO fmc_state_enum fmc_state = FMC_READY;
__IO test_state program_state = PASSED;

union store_2k_s
{
    struct 
    {
        uint32_t lock;
        struct data_bin_s time;
        struct data_bin_s accum_yield;
        struct data_bin_s prev_glue_up;
        struct data_bin_s cur_yield_front;
        struct data_bin_s prev_glue_dowm;
        struct data_bin_s tem;
        struct data_bin_s hum;
        struct data_bin_s cur_yield_rear;
        struct data_bin_s next_glue_up;
        struct data_bin_s next_glue_dowm;
        struct data_bin_s bank;
    }data;
    uint32_t bin32[1024];
};
union store_2k_s store;
void write_store()
{
    int i;
    /* unlock the flash program/erase controller */
    fmc_unlock();
    ob_unlock();
    /* Get pages write protection status */
    wp_value = ob_write_protection_get();
    /* Get the number of pages to be erased */
    page_num = (BANK0_WRITE_END_ADDR - BANK0_WRITE_START_ADDR) / FLASH_PAGE_SIZE;

    /* The selected pages are not write protected */
    if((wp_value & FMC_PAGES_PROTECTED) != 0x00){
        /* Clear All pending flags */
        fmc_flag_clear(FMC_FLAG_BANK0_END);
        fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
        fmc_flag_clear(FMC_FLAG_BANK0_PGERR);

        /* erase the FLASH pages */
        for(erase_counter = 0; (erase_counter < page_num) && (fmc_state == FMC_READY); erase_counter++){
            fmc_state = fmc_page_erase(BANK0_WRITE_START_ADDR + (FLASH_PAGE_SIZE * erase_counter));
        }

        /* FLASH Half Word program of data 0x1753 at addresses defined by BANK1_WRITE_START_ADDR and BANK1_WRITE_END_ADDR */
        Address = BANK0_WRITE_START_ADDR;
        i = 0;
        while((Address < BANK0_WRITE_END_ADDR)&&(fmc_state == FMC_READY) &&(i<2048/4)){
            fmc_state = fmc_word_program(Address, store.bin32[i]);
            i++;
            Address = Address + 4;
        }
    }
}
uint8_t read_store()
{
    int16_t i;
    /* Check the correctness of written data */
    Address = BANK0_WRITE_START_ADDR;
    i = 0;
    do {
		store.bin32[i] = (*(__IO uint32_t*) Address);
        if(store.data.lock == 0XFFFFFFFF)return FALSE;
        Address += 4;      
        i++; 
    }while((Address < BANK0_WRITE_END_ADDR)&&(i<2048/4));
    return TRUE;  
}

void disp_read_store()
{
    uint8_t flag;
    flag = read_store();
    if(flag == FALSE){
        PRINT("link no store");
        return;
    }
    memcpy(&time, &store.data.time, sizeof(DATA_BIN_S));
    memcpy(&accum_yield, &store.data.accum_yield, sizeof(DATA_BIN_S));
    memcpy(&prev_glue_up, &store.data.prev_glue_up, sizeof(DATA_BIN_S));
    memcpy(&cur_yield_front, &store.data.cur_yield_front, sizeof(DATA_BIN_S));
    memcpy(&prev_glue_dowm, &store.data.prev_glue_dowm, sizeof(DATA_BIN_S));
    memcpy(&tem, &store.data.tem, sizeof(DATA_BIN_S));
    memcpy(&hum, &store.data.hum, sizeof(DATA_BIN_S));
    memcpy(&cur_yield_rear, &store.data.cur_yield_rear, sizeof(DATA_BIN_S));
    memcpy(&next_glue_up, &store.data.next_glue_up, sizeof(DATA_BIN_S));
    memcpy(&next_glue_dowm, &store.data.next_glue_dowm, sizeof(DATA_BIN_S));
    memcpy(&bank, &store.data.bank, sizeof(DATA_BIN_S));
}
void disp_write_store()
{
		store.data.lock = 0X5A5A5A5A;
    memcpy(&store.data.time, &time, sizeof(DATA_BIN_S));
    memcpy(&store.data.accum_yield, &accum_yield, sizeof(DATA_BIN_S));
    memcpy(&store.data.prev_glue_up, &prev_glue_up, sizeof(DATA_BIN_S));
    memcpy(&store.data.cur_yield_front, &cur_yield_front, sizeof(DATA_BIN_S));
    memcpy(&store.data.prev_glue_dowm, &prev_glue_dowm, sizeof(DATA_BIN_S));
    memcpy(&store.data.tem, &tem, sizeof(DATA_BIN_S));
    memcpy(&store.data.hum, &hum, sizeof(DATA_BIN_S));
    memcpy(&store.data.cur_yield_rear, &cur_yield_rear, sizeof(DATA_BIN_S));
    memcpy(&store.data.next_glue_up, &next_glue_up, sizeof(DATA_BIN_S));
    memcpy(&store.data.next_glue_dowm, &next_glue_dowm, sizeof(DATA_BIN_S));
    memcpy(&store.data.bank, &bank, sizeof(DATA_BIN_S)); 
    write_store();   
}