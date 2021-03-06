/* YCDWriter.cpp
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 07/29/2013
 * Last Modified    : 07/29/2013
 * 
 */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Dependencies
#include "../../Public/CompilerSettings.h"
#include "../../Public/AlignedMalloc.h"
#include "../../Public/Exception.h"
#include "../Globals.h"
#include "YCDFileWriter.h"
#include "YCDWriter.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace DigitViewer{
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Helpers
void YCDWriter::create_file(uiL_t fileid){
    std::wstring full_path(path);
    full_path += name;
    full_path += L" - ";
    full_path += std::to_wstring(fileid);
    full_path += L".ycd";

    file = YCDFileWriter(full_path,first_digits,digits_per_file,fileid,radix);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
YCDWriter::YCDWriter(
    std::wstring path_,
    std::wstring name_,
    std::string first_digits,
    uiL_t digits_per_file_,
    uiL_t start_fileid,
    int radix_,
    upL_t buffer_size,
    u64_t* buffer,
    void (*deallocator)(void*)
)
    : path(std::move(path_))
    , name(std::move(name_))
    , radix(radix_)
    , first_digits(std::move(first_digits))
    , digits_per_file(digits_per_file_)
    , fileid(start_fileid)
    , fp_free(deallocator)
{
    if (buffer_size < 4096)
        throw ym_exception("Requested buffer size is too small.",YCR_DIO_ERROR_INVALID_PARAMETERS);

    switch (radix){
        case 16: break;
        case 10: break;
        default:
            throw ym_exception("Unsupported Radix",YCR_DIO_ERROR_INVALID_BASE);
    }

    //  Make sure path ends in a slash.
    if (path.size() != 0){
        wchar_t back = path.back();
        if (back != '/' && back != '\\')
            path += '/';
    }

    //  Multiple files, create a folder for them.
    if (digits_per_file != (uiL_t)0 - 1){
        path += name;
        path += '/';
        FileIO::MakeDirectory(path.c_str());
    }

    bin_buffer_L = buffer_size / sizeof(u64_t);
    if (buffer == NULL){
        external_buffer = false;
        bin_buffer = (u64_t*)AlignedMalloc(bin_buffer_L * sizeof(u64_t),2*sizeof(u64_t));
    }else{
        external_buffer = true;
        bin_buffer = buffer;
    }
}
YCDWriter::~YCDWriter(){
    //  Internally allocated.
    if (!external_buffer)
        AlignedFree(bin_buffer);

    //  Preallocated with manual deallocator.
    if (fp_free != NULL)
        fp_free(bin_buffer);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void YCDWriter::write(char* str,upL_t digits){
    while (true){
        //  No file is opened.
        if (!file.isValid()){
            create_file(fileid++);
        }

        //  Write digits
        upL_t written = file.write_chars(str,digits,bin_buffer,bin_buffer_L);
        if (written == digits)
            return;

        digits -= written;
        str    += written;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
}
