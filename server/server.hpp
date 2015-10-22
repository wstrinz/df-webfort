#ifndef __WF_SERVER_HPP_
#define __WF_SERVER_HPP__

/*
 * server.hpp
 * Part of Web Fortress
 *
 * Copyright (c) 2014 mifki, ISC license.
 */

#include <ctime>
#include <map>
#include <string>
#include <websocketpp/server.hpp>
#include <DFHackVersion.h>

typedef struct {
    std::string addr;
    std::string nick;
    unsigned char mod[256*256];
    time_t atime;
	bool is_admin;
} Client;

namespace ws = websocketpp;
// FIXME: use unique_ptr or the boost equivalent
typedef ws::connection_hdl conn_hdl;

static std::owner_less<conn_hdl> conn_lt;
inline bool operator==(const conn_hdl& p, const conn_hdl& q)
{
    return (!conn_lt(p, q) && !conn_lt(q, p));
}
inline bool operator!=(const conn_hdl& p, const conn_hdl& q)
{
    return conn_lt(p, q) || conn_lt(q, p);
}

typedef std::map<conn_hdl, Client*, std::owner_less<conn_hdl>> conn_map;
extern conn_map clients;

void wsthreadmain(void*);

#endif
