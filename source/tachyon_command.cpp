

namespace tyon
{
    extern command_context* g_command = nullptr;

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

    PROC command_ansi_control( ansi_control type, i32 arg = 0 ) -> void
    {
        /** NOTE: Windows supports only the \x1b ANSI escape code and Linux supports both that and \033 */
        fstring code;
        // Windows is insanely slow and ansi clear line causes flickering
        fstring line_clear_entire_code;
        if constexpr (REFLECTION_PLATFORM_LINUX)
        {   code = "\x1b[2K";}
        else
        {   code = "\r                                                                                "; }

        switch (type)
        {
            case ansi_control::none: break;
            case ansi_control::any: break;
            case ansi_control::line_clear_after: break;
            case ansi_control::line_clear_before: break;
            case ansi_control::line_clear_entire: code = line_clear_entire_code; break;
            case ansi_control::cursor_move_home: break;
            case ansi_control::cursor_move_end: break;
            case ansi_control::cursor_save_store: break;
            case ansi_control::cursor_move_store: break;
            default: break;
        }
        command_print_q( code );
    }

    PROC command_read_console() -> void
    {
        fstring& input = g_command->line_contents;
        fstring& input_raw = g_command->line_contents_raw;
        char buf[1024] {};

        bool debug_run_always = false;
        // TODO: do input polling with _khbit() / poll() for performance
        // bool unread_input = console_input_available();
        i32 unread_input = _kbhit();
        i32 events_processed = 0;
        while (unread_input)
        {
            buf[ events_processed ] = char(_getch());
            // NOTE: Borked on windows when using _kbhit
            // fgets( buf, 100, stdin );
            // NOTE: Not needed
            // NOTE: Extremely slow compared to fgets.
            // int read_bytes = read( STDIN_FILENO, buf.data(), 100 );

            unread_input = _kbhit();
            ++events_processed;
        }
        if (events_processed == 0)
        {   return; }
        // Append read input to line editor
        input_raw += buf;
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

        // command_print_q( "Echo: {}", input );
        // command_print_q( "\x1b[1F" );
        // command_print_q( "\x1b[2K" );
        // command_print_q( "Echo: {} ASCII: {}", input.back(), int(input.back()) );
        // command_print_q( "\x1b[1E" );

        // print_q( "\x1b[0E" );
        // print_q( "\x1b[2K" );
        // erase whole line
        command_ansi_control( ansi_control::line_clear_entire );
        // Save cursor position
        command_print_q( "\x1b 7" );
        // Move beginning of line
        command_print_q( "\x1b[0E" );
        // NOTE: Don't echo input when not in console mode, it messes up the terminal so much
        if (g_command->console_input_mode)
        {
            fmt::print(  TYON_COMMAND_ANSI_COLOR "> {}" TYON_COMMAND_ANSI_RESET, input );
        }
        // Restore cursor
        command_print_q( "\x1b 8" );

        bool useful_input = (input_raw.size() > 0);
        if (useful_input)
        {
            bool temp_shared_log_window = true;
            bool do_backspace = (input_raw.size() > 1 && input_raw.back() == 127);
            bool submit_command = (g_command->console_input_mode &&
                                   (input_raw.back() == '\n' || input_raw.back() == '\r'));
            bool start_new_command = ( ! g_command->console_input_mode &&
                                       (input_raw.back() == '\r' ||
                                       input_raw.back() == '\n'));

            if (start_new_command)
            {
                g_command->console_input_mode = true;
                command_print_q( "Please Enter Your Command: \n\r" );

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

                // Restore logger state
                g_logger->console_output_enabled = g_command->prev_console_output_enabled;
                // Go back to non-input mode
                g_command->console_input_mode = false;
            }
        }
    }
}
