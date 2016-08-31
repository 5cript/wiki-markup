#include "dllmain.h"

#include "page.hpp"
#include "parser/page_parser.hpp"

#include <cstring>

//#####################################################################################################################
char* allocateCString(std::string const& str)
{
    char* cstr = new char[str.length() + 1];
    std::memcpy(cstr, str.c_str(), str.length());
    cstr[str.length()] = '\0';
    return cstr;
}
//---------------------------------------------------------------------------------------------------------------------
extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE /* hinstDLL */, DWORD /* fdwReason */, LPVOID /* lpvReserved */)
{
    return TRUE; // succesful
}
//---------------------------------------------------------------------------------------------------------------------
C_LINKAGE DLL_EXPORT void free_buffer(char* buffer)
{
    delete buffer;
}
//---------------------------------------------------------------------------------------------------------------------
C_LINKAGE DLL_EXPORT void markup_to_json(const char* markup, char** json)
{
    WikiMarkup::PageParser parser{{markup}};
    parser.parse();
    auto jsonString = parser.getPage().toJson();

    // convert string
    *json = allocateCString(jsonString);
}
//---------------------------------------------------------------------------------------------------------------------
C_LINKAGE DLL_EXPORT void json_to_markup(const char* json, char** markup)
{
    WikiMarkup::Page page;
    page.fromJson(json);
    auto markupString = page.toMarkup();

    // convert string
    *markup = allocateCString(markupString);
}
//#####################################################################################################################
