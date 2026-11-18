#include "include_tachyon_lib_core.h"

namespace tyon
{

PROC config_file_load_strings( fstring config_filename ) -> array<config_pair>
{
    push_allocator _allocator_1 { g_thread->scratch };
    file config_file = file_load_binary( config_filename );

    // Search through newlines
    array<config_pair> config_options;
    config_options.change_allocation( 100 );
    array<i32> i_newlines;
    raw_pointer data = config_file.memory.data;

    char x_char = 0;
    fstring x_string;
    config_pair x_option;
    i64 i_line = 0;
    // assignment operator detected, a key will be provided
    bool assignment_flag = false;
    bool line_ignored_flag = false;
    i64 i_limit = config_file.memory.size;
    // The index in the line the char is. 0 indexed
    i64 i_line_char = 0;
    for (i64 i = 0; i < i_limit; ++i)
    {
        x_char = data[i];
        i_line = (i_newlines.size() + 1);
        bool end_of_line = (x_char == '\n');
        bool end_of_file = (i == i_limit -1);
        if (end_of_line || end_of_file)
        {
            if (line_ignored_flag == false)
            {
                x_option.value = x_string;
                config_options.push_tail( x_option );
            }
            // Reset all loop variables
            x_string = "";
            x_option = {};
            i_line_char = 0;
            assignment_flag = false;
            line_ignored_flag = false;
            i_newlines.push_tail( i );

            // DEBUG: logging
            // TYON_LOGF( "Config File Parsed: Name: '{}' Value: '{}'", x_option.name, x_option.value );
            continue;
        }
        bool ignored_char = (line_ignored_flag || x_char == ' ' || x_char == '\r');
        bool assignment_operator = (x_char == '=');
        bool near_line_start = (i_line_char < 3);
        bool comment_char = (x_char == '#' || x_char == ';');
        bool line_is_comment = (near_line_start && comment_char);
        // Increment be here to avoid being skipped by continue
        ++i_line_char;
        if (ignored_char)
        {   continue; }
        if (assignment_operator)
        {
            if (assignment_flag)
            {
                TYON_LOGF(
                    "Parse Error: On character {} line {} of file {}", i, i_line, config_filename );
                TYON_LOG( "Error: two assignment operators '=' in the same line, skipping line" );
                line_ignored_flag = true;
                continue;
            }
            // Everything left of assignment must be a name, so save it into 'x_option'
            assignment_flag = true;
            x_option.name = x_string;
            x_string = "";
            continue;
        }
        if (line_is_comment)
        {
            // DEBUG: logging
            // TYON_LOGF( "Line {} is a comment", i_line );
            line_ignored_flag = true;
            continue;
        }
        // Good char, add it to the back
        x_string.push_back( x_char );
    }
    // Restore parent allocator
    return config_options;
}

}
