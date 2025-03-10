#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using namespace std;

const u16 ROM_START = 0x200; 

struct Registers;

void put_value_in_Vreg(int regNum, u8 value, Registers& registers);
u8 get_value_in_Vreg(int regNum, Registers& registers);
string get_u8reg_string(int reg_num, Registers& registers);
string get_u8hex_string(u8 value);
string get_u16hex_string(u16 value);

struct Registers{
    // general registers
    union {
        struct {
            u8 v0;
            u8 v1;
        };
        u16 v0v1;
    };

    union {
        struct {
            u8 v2;
            u8 v3;
        };
        u16 v2v3;
    };

    union {
        struct {
            u8 v4;
            u8 v5;
        };
        u16 v4v5;
    };

    union {
        struct {
            u8 v6;
            u8 v7;
        };
        u16 v6v7;
    };

    union {
        struct {
            u8 v8;
            u8 v9;
        };
        u16 v8v9;
    };

    union {
        struct {
            u8 vA;
            u8 vB;
        };
        u16 vAvB;
    };

    union {
        struct {
            u8 vC;
            u8 vD;
        };
        u16 vCvD;
    };

    union {
        struct {
            u8 vE;
            u8 vF;
        };
        u16 vEvF;
    };

    // specific registers
    u16 sp;
    u16 pc;
    u16 I; 
    u8 delay_timer;
    u8 sound_timer;

    Registers() {
        pc = ROM_START;
        sp = 0x0000;
        sound_timer = 0;
        delay_timer = 0;
    }

};

#endif 