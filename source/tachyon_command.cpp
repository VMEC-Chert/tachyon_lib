

namespace tyon
{
    extern command_context* g_command = nullptr;

    // NOTE: Green color by default
    #define TYON_COMMAND_ANSI_COLOR "\x1b[32m"
    #define TYON_COMMAND_ANSI_RESET "\x1b[0m"

    PROC command_print_q( fstring message ) -> void
    {
        fmt::print( TYON_COMMAND_ANSI_COLOR "{}" TYON_COMMAND_ANSI_RESET, message );
    }

    PROC command_init() -> fresult
    {
        g_command = memory_allocate<command_context>(1);
        if (g_command == nullptr)
        {   TYON_ERROR( "Failed to initialize command subsystem" );
            return false;
        }

        g_command->command_string_queue.change_allocation( 50 );
        return true;
    }

    PROC command_add( command* arg ) -> uid
    {
        arg->id = uuid_generate();
        g_command->command_list.push_tail( *arg );
        return arg->id;
    }

    PROC command_ansi_control( ansi_control type, i32 arg = 0 ) -> void
    {
        /** NOTE: Windows supports only the \x1b ANSI escape code and Linux supports both that and \033 */
        fstring code;
        // Windows is insanely slow and ansi clear line causes flickering
        fstring line_clear_entire_code;
        if constexpr (REFLECTION_PLATFORM_LINUX)
        {   line_clear_entire_code = "\x1b[2K";}
        else
        {   line_clear_entire_code = "\r                                                                                \r"; }

        switch (type)
        {
            case ansi_control::none: break;
            case ansi_control::any: break;
            case ansi_control::line_clear_after: break;
            case ansi_control::line_clear_before: break;
            case ansi_control::line_clear_entire: code = line_clear_entire_code; break;
            case ansi_control::cursor_move_home: code = "\x1b[0E"; break;
            case ansi_control::cursor_move_end: break;
            case ansi_control::cursor_save_store: break;
            case ansi_control::cursor_move_store: break;
            case ansi_control::cursor_move_forwards: code = fmt::format( "\x1b[{}C", arg ); break;
            case ansi_control::cursor_move_backwards: code = fmt::format( "\x1b[{}D", arg ); break;
            case ansi_control::cursor_move_up: code = fmt::format( "\x1b[{}A", arg ); break;
            case ansi_control::cursor_move_down: code = fmt::format( "\x1b[{}B", arg ); break;
            default: break;
        }
        command_print_q( code );
    }

    PROC command_read_console() -> void
    {
        PROFILE_SCOPE_FUNCTION();
        fstring& input = g_command->line_contents;
        fstring& input_raw = g_command->line_contents_raw;

        bool debug_run_always = false;
        monad<fstring> read_result = console_read_input_nonblocking();
        g_command->console_input = read_result.copy_default({});

        if (read_result.error)
        {   return; }
        // Append read input to line editor
        input_raw += g_command->console_input;
        input.clear();

        // Normalize non-raw input before doing anything else
        fstring tmp = input_raw;
        char x_char = 0;
        for (i32 i=0; i < input_raw.size(); ++i )
        {
            x_char = input_raw[i];
            // Skip anything that is irrelevant input or interferes output printing
            if (x_char == '\n' || x_char == '\r')
            {   continue; }

           // We must have a good character so we can add it to the string
            input.push_back( x_char );
        }

        bool useful_input = (input_raw.size() > 0);
        if (useful_input)
        {
            // NOTE: Don't forget windows uses "\n\r" for line endings

            bool temp_shared_log_window = true;
            bool do_backspace = (input_raw.size() > 1 && input_raw.back() == e_ascii::delete_);
            bool submit_command = (g_command->console_input_mode &&
                                   (input_raw.back() == '\n' || input_raw.back() == '\r'));
            bool exit_command_mode = (g_command->console_input_mode && input_raw.back() == e_ascii::escape);
            bool enter_command_mode = ( ! g_command->console_input_mode &&
                                       (input_raw.back() == '\r' ||
                                       input_raw.back() == '\n'));
            if (exit_command_mode)
            {
                // Go back to non-input mode
                g_command->console_input_mode = false;
                // Restore logger state
                g_logger->console_output_enabled = g_command->prev_console_output_enabled;
                // TODO: We should probably dump lost logs into the terminal here.

                input.clear();
                input_raw.clear();
                command_print_q( "\n------------------------------\n" );
                command_print_q( "Exiting Command Mode\n" );
                return;
            }
            else if (enter_command_mode)
            {
                g_command->console_input_mode = true;
                command_print_q( "Command Mode: Please Enter Your Command: \n\r" );

                // Pause logging if it's being vommited in the same console as standard inptu
                if (temp_shared_log_window)
                {   g_command->prev_console_output_enabled = g_logger->console_output_enabled;
                    g_logger->console_output_enabled = false;
                }
                // NOTE: Remember to clear input on new command started, I forgot to do this before
                // And it left crud from the non-command input
                input.clear();
                input_raw.clear();
            }
            else if (do_backspace)
            {   // Take off the backspace + 1 character
                bool short_string_special_case = (input_raw.size() < 2);

                i64 raw_size = input_raw.size();
                i64 stripped_size = raw_size;
                char x_char = 0;
                for (i32 i=0; i < input_raw.size(); ++i)
                {
                   x_char = input_raw[ raw_size - i - 1 ];
                   bool invisible_char = (x_char == e_ascii::delete_ ||
                                          x_char == e_ascii::carriage_return ||
                                          x_char == e_ascii::line_feed);
                   if (invisible_char)
                   {    --stripped_size; }
                }
                size_t new_size = (short_string_special_case ? 0 : (input_raw.size() - 2));
                input_raw.resize( new_size );
            }
            else if (submit_command)
            {
                // Need newline on windows
                command_print_q( "\n" );
                fmt::print(  TYON_COMMAND_ANSI_COLOR "Command Submitted: {}\n\r" TYON_COMMAND_ANSI_RESET,
                             input );
                // NOTE: I stripped newline here previously but we just strip the whole command now
                g_command->command_string_queue.push_tail( input );
                input.clear();
                input_raw.clear();

                // NOTE: We used to exit command mode but it's more useful to stay in command mode
            }

        // Normalize non-raw input before doing anything else
        tmp = input_raw;
        input.clear();
        char x_char = 0;
        for (i32 i=0; i < input_raw.size(); ++i )
        {
            x_char = input_raw[i];
            // Skip anything that is irrelevant input or interferes output printing
            if (x_char == '\n' || x_char == '\r')
            {   continue; }

            // We must have a good character so we can add it to the string
            input.push_back( x_char );
        }

        command_ansi_control( ansi_control::line_clear_entire );
        // Move beginning of line
        command_ansi_control( ansi_control::cursor_move_home );
        // NOTE: Don't echo input when not in console mode, it messes up the terminal so much
        if (g_command->console_input_mode)
        {
            fmt::print(  TYON_COMMAND_ANSI_COLOR "> {}" TYON_COMMAND_ANSI_RESET, input );
        }
        // Restore cursor position
        // go to home then move foward by visible input size + 2 for command start visuals
        command_ansi_control( ansi_control::cursor_move_home );
        command_ansi_control( ansi_control::cursor_move_forwards, input.size() + 2);
        // fflush( stdout );

        }
    }

    PROC command_proccess_commands() -> void
    {
        i64 i_limit = g_command->command_string_queue.size();
        fstring x_command;
        x_command.reserve( 100 );
        string x_split;
        command_submitted x_submit;
        for (i64 i=0; i < i_limit; ++i)
        {
            TYON_LOG( "Processing commands", i );
            x_submit = {};
            x_command = g_command->command_string_queue[i];
            x_split = x_command;
            x_split = x_split.split_whitespace();

            x_submit.unprocessed = x_split;
            // TODO: read each string part and figure out what type of input it is
            auto command_s = entity_search_name_array(
                g_command->command_list, x_split.parts[0].data );
            if (command_s.match_found)
            {
                TYON_LOGF( "Command Exists: {}", command_s.match->name );
            }
            // TYON_LOGF( "Command Processed: {}", x_split.parts[0].data );
        }

        // We can clear this list now
        g_command->command_string_queue.reset();
    }
}
