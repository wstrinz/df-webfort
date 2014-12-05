#ifndef __WF_CONFIG_HPP__
#define __WF_CONFIG_HPP__

#include <cstdint>

extern bool INGAME_TIME;
extern bool AUTOSAVE_WHILE_IDLE;
extern int32_t TURNTIME;
extern uint32_t MAX_CLIENTS;
extern uint16_t PORT;

bool load_config();

#endif
