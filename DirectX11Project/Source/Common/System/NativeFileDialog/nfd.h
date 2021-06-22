/*
  Native File Dialog

  User API

  http://www.frogtoss.com/labs
 */
#pragma once
#include <string>
#include <stddef.h>

namespace nfd
{
    /* denotes UTF-8 char */
    typedef char nfdchar_t;

    /* opaque data structure -- see NFD_PathSet_* */
    struct nfdpathset_t {
        nfdchar_t* buf;
        size_t* indices; /* byte offsets into buf */
        size_t count;    /* number of indices into buf */
    };

    enum nfdresult_t {
        NFD_ERROR,       /* programmatic error */
        NFD_OKAY,        /* user pressed okay, or successful return */
        NFD_CANCEL       /* user pressed cancel */
    };

    /* single file open dialog */
    nfdresult_t OpenDialog(std::wstring& outPath_wchar, const nfdchar_t* filterList = "png,jpg", const nfdchar_t* defaultPath = nullptr);

    /* multiple file open dialog */
    nfdresult_t OpenDialogMultiple(const nfdchar_t* filterList, const nfdchar_t* defaultPath, nfdpathset_t* outPaths);

    /* save dialog */
    nfdresult_t SaveDialog(std::wstring& outPath_wchar, const nfdchar_t* filterList = "png,jpg", const nfdchar_t* defaultPath = nullptr);

    /* select folder dialog */
    nfdresult_t PickFolder(std::wstring& outPath_wchar, const nfdchar_t* defaultPath = nullptr);

    /* get last error -- set when nfdresult_t returns NFD_ERROR */
    const char* NFD_GetError(void);
    /* get the number of entries stored in pathSet */
    size_t NFD_PathSet_GetCount(const nfdpathset_t* pathSet);
    /* Get the UTF-8 path at offset index */
    nfdchar_t* NFD_PathSet_GetPath(const nfdpathset_t* pathSet, size_t index);
    /* Free the pathSet */
    void NFD_PathSet_Free(nfdpathset_t* pathSet);
}
