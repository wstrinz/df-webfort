#ifndef __WF_CONFIG_HPP__
#define __WF_CONFIG_HPP__

#include <cstdint>
#include <vector>
#include <string>

extern bool INGAME_TIME;
extern bool AUTOSAVE_WHILE_IDLE;
extern int32_t TURNTIME;
extern uint32_t MAX_CLIENTS;
extern uint16_t PORT;
extern std::string SECRET;

bool load_config();
std::vector<std::string> split(const char *str, char c = ' ');

#endif
