/* YCDFileReader.h - .ycd Reader Object
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 07/13/2013
 * Last Modified    : 07/28/2013
 * 
 * 
 *  This class represents a file handle to a single .ycd file. When constructed,
 *  it parses and holds all the metadata in it.
 * 
 *  An instance of this class allows the user to:
 *      -   Read raw 64-bit words from the file.
 *      -   Read digits from the file.
 * 
 */

#pragma once
#ifndef _ycr_YCDFileReader_H
#define _ycr_YCDFileReader_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Dependencies
#include <string>
#include "../../Public/Types.h"
#include "../../Public/FileIO/FileIO.h"
namespace DigitViewer{
    using namespace ymp;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class YCDFileReader{
public:
    //  Movable
    YCDFileReader(){}
    YCDFileReader(YCDFileReader&&);
    void operator=(YCDFileReader&&);
private:
    //  But not copyable
    YCDFileReader(const YCDFileReader&);
    void operator=(const YCDFileReader&);

public:
    YCDFileReader(std::wstring path);

    void print() const;
    void read_words(ufL_t pos,u64_t* T,upL_t L);
    void read_chars(
        uiL_t pos,char* str,upL_t digits,
        u64_t* buffer,upL_t buffer_L,
        void (*fp_convert)(char*,const u64_t*,upL_t)
    );

private:
    std::wstring path;
    FileIO::BasicFile file;

    std::string file_version;
    int radix;
    std::string first_digits;
    uiL_t total_digits;
    ufL_t digits_per_file;
    uiL_t file_id;

    upL_t digits_per_word;
    ufL_t words_in_this_file;
    ufL_t data_offset;              //  Offset where the actual data blocks begin.

    friend class YCDReader;
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
}
#endif
