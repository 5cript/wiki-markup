#include "dll.h"

#include <stdint.h>

typedef int32_t result_type;

/**
 *  Used to free buffers, that were allocated by this library.
 *
 *  @param buffer A string buffer to deallocate.
 */
C_LINKAGE DLL_EXPORT void free_buffer(char* buffer);

/**
 *  Converts wiki markup to json.
 *
 *  @param markup A null terminated string of valid markup.
 *  @param json Will allocate memory and place a json string at its location.
 */
C_LINKAGE DLL_EXPORT void markup_to_json(const char* markup, char** json);

/**
 *  Converts json to wiki markup.
 *
 *  @param json A null terminated string of json.
 *  @param markup Will allocate memory and place a markup string at its location.
 */
C_LINKAGE DLL_EXPORT void json_to_markup(const char* json, char** markup);
