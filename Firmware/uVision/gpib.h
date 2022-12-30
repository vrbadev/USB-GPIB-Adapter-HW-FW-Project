#ifndef GPIB_H_
#define GPIB_H_

#include "stm32f103x6.h"

/* callback timeout function returns TRUE when gpib transfer timed out */
typedef bool (*gpibtimeout_t)(void);

extern bool gpib_timedout; /* TRUE, if a writedat transfer timed out */

/* check, if a GPIB device is physically connected or not*/
bool gpib_is_connected(void);

void gpib_init(void); /* init gpib, do remote enable and send clear interface instruction */
void gpib_interface_clear(void);
void gpib_ren(bool enable);

/* assign/deassign talker or listener role */
bool gpib_make_talker(uint8_t addr, gpibtimeout_t ptimeoutfunc);
bool gpib_make_listener(uint8_t addr, gpibtimeout_t ptimeoutfunc);
bool gpib_untalk_unlisten(gpibtimeout_t ptimeoutfunc);

/* read/write single bytes */
uint8_t gpib_readdat(bool *pEoi, bool *ptimedout, gpibtimeout_t ptimeoutfunc); /* reads a character. Eoi is TRUE if the last byte was received */ 
bool gpib_writedat(uint8_t dat, bool Eoi, gpibtimeout_t ptimeoutfunc); /* send a character to device, returns TRUE if timed out  */

bool gpib_ATN_HIGH(void);

uint8_t gpib_search(void);

void gpib_set_readtermination(char terminator);



/* read status byte using serial poll */
uint8_t gpib_readStatusByte(uint8_t addr, gpibtimeout_t ptimeoutfunc);

/* local lockout of all connected GPIB devices (turn of LOCAL button) */
bool gpib_localLockout(gpibtimeout_t ptimeoutfunc);

/* goto local */
bool gpib_gotoLocal(uint8_t addr, gpibtimeout_t ptimeoutfunc);

/* trigger instrument */
bool gpib_trigger(uint8_t addr, gpibtimeout_t ptimeoutfunc);



#endif /* INCFILE1_H_ */
