/* DigitWriter.cpp - File Writer Object Interface
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 04/03/2012
 * Last Modified    : 07/28/2013
 * 
 */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Dependencies
#include "../../Public/AlignedMalloc.h"
#include "DigitWriter.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace DigitViewer{
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DigitWriter::DigitWriter()
    : buffer(NULL)
    , buffer_L(0)
    , iter_f_offset(0)
    , iter_b_offset(buffer_L)
{
}
DigitWriter::~DigitWriter(){
    AlignedFree(buffer);
}
void DigitWriter::push(const char* str,upL_t digits){
    while (digits > 0){
        //  Buffer is full
        if (iter_b_offset == buffer_L){
            flush();
        }

        upL_t block = buffer_L - iter_b_offset;
        if (block > digits)
            block = digits;

        memcpy(&buffer[0] + iter_b_offset,str,block);
        
        iter_f_offset += block;
        iter_b_offset += block;
        str += block;
        digits -= block;
    }
}
void DigitWriter::flush(){
    //  Buffer isn't initialized yet.
    if (buffer_L == 0){
        upL_t buffer_size = YC_DIGITWRITER_DEFAULT_BUFFER;
        buffer = (char*)AlignedMalloc(buffer_size,2*sizeof(u64_t));

        //  Do this assignment last - just in case the above throws.
        buffer_L = buffer_size;
    }else{
        //  Write
        write(buffer,iter_b_offset);
    }

    //  Clear the buffer
    iter_b_offset = 0;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
}
