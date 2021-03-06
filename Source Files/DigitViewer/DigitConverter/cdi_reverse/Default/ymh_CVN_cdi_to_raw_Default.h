/* ymh_CVN_cdi_to_raw_Default.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 01/20/2011
 * Last Modified    : 05/20/2012
 * 
 * 
 *      ymh         =   Helper Function
 *      CVN         =   Format Conversion Unit
 *      cdi_to_raw  =   Compressed Integer -> Raw
 *      Default     =   Default Instruction Set
 * 
 */

#ifndef _ymh_CVN_cdi_to_raw_Default_H
#define _ymh_CVN_cdi_to_raw_Default_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Dependencies
#include "ymi_CVN_cdi_to_rawh_Default.h"
#include "ymi_CVN_cdi_to_rawd_Default.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ymb_CVN_c32i_to_rawh_r(char* T,const u32_t* A,upL_t AL){
    T += AL * 8;
    const u32_t* stopA = A + AL - 1;

    while (A < stopA){
        T -= 16;
        ymi_CVN_c32i_to_rawh_u1_Default(T,A);
        A += 2;
    }
    if (A < stopA + 1){
        T -= 8;
        ymi_CVN_c32i_to_rawh_u0_Default(T,A);
        A += 1;
    }
}
void ymb_CVN_c64i_to_rawh_r(char* T,const u64_t* A,upL_t AL){
    T += AL * 16;
    const u64_t* stopA = A + AL;

    while (A < stopA){
        T -= 16;
        ymi_CVN_c64i_to_rawh_u0_Default(T,A);
        A += 1;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ymb_CVN_c32i_to_rawd_r(char* T,const u32_t* A,upL_t AL){
    T += AL * 9;
    const u32_t* stopA = A + AL - 1;

    while (A < stopA){
        T -= 18;
        ymi_CVN_c32i_to_rawd_u1_Default(T,A);
        A += 2;
    }
    if (A < stopA + 1){
        T -= 9;
        ymi_CVN_c32i_to_rawd_u0_Default(T,A);
        A += 1;
    }
}
void ymb_CVN_c64i_to_rawd_r(char* T,const u64_t* A,upL_t AL){
    T += AL * 19;
    const u64_t* stopA = A + AL - 1;
    
    while (A < stopA){
        T -= 38;
        ymi_CVN_c64i_to_rawd_u1_Default(T,A);
        A += 2;
    }
    if (A < stopA + 1){
        T -= 19;
        ymi_CVN_c64i_to_rawd_u0_Default(T,A);
        A += 1;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
