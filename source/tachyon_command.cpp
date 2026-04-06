

namespace tyon
{
    extern command_context* g_command = nullptr;

    PROC command_print_q( fstring message ) -> void
    {
        fmt::print( "{}", message );
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
        fstring code;
        switch (type)
        {

            case ansi_control::none: break;
            case ansi_control::any: break;
            case ansi_control::line_clear_after: break;
            case ansi_control::line_clear_before: break;
            case ansi_control::line_clear_entire: code = "\033[2K"; break;

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
        fstring input;
        char buf[1024] {};

        bool debug_run_always = false;
        // TODO: do input polling with _khbit() / poll() for performance
        bool unread_input = console_input_available();
        if (unread_input || debug_run_always)
        {
            fgets( buf, 100, stdin );
            // NOTE: Not needed
            // NOTE: Extremely slow compared to fgets.
            // int read_bytes = read( STDIN_FILENO, buf.data(), 100 );

            input += buf;
        }
        else
        {   return; }

        // command_print_q( "Echo: {}", input );
        // command_print_q( "\033[1F" );
        // command_print_q( "\033[2K" );
        // command_print_q( "Echo: {} ASCII: {}", input.back(), int(input.back()) );
        // command_print_q( "\033[1E" );

        // print_q( "\033[0E" );
        // print_q( "\033[2K" );
        // erase whole line
        command_ansi_control( ansi_control::line_clear_entire );
        // Save cursor position
        command_print_q( "\033 7" );
        // Move beginning of line
        command_print_q( "\033[0E" );
        fmt::print( "{}", input );
        // Restore cursor
        command_print_q( "\033 8" );

        bool useful_input = (input.size() > 0);
        if (useful_input)
        {
            bool temp_shared_log_window = true;
            bool do_backspace = (input.size() > 1 && input.back() == 127);
            bool submit_command = (g_command->console_input_mode && input.back() == 10);
            bool start_new_command = ( ! g_command->console_input_mode && input.back() == '\n');

            if (start_new_command)
            {
                g_command->console_input_mode = true;
                command_print_q( "Please Enter Your Command: \n" );

                // Pause logging if it's being vommited in the same console as standard inptu
                if (temp_shared_log_window)
                {   g_command->prev_console_output_enabled = g_logger->console_output_enabled;
                    g_logger->console_output_enabled = false;
                }
            }
            else if (do_backspace)
            {   // Take off the backspace + 1 character
                bool short_string_special_case = (input.size() < 2);
                size_t new_size = (short_string_special_case ? 0 : (input.size() - 2));
                input.resize( new_size );
            }
            else if (submit_command)
            {
                fmt::print( "Command Submitted: {}", input );
                // Strip last newline
                input.resize( input.size() - 1 );
                g_command->command_string_queue.push_tail( input );
                input.clear();

                // Restore logger state
                g_logger->console_output_enabled = g_command->prev_console_output_enabled;
                // Go back to non-input mode
                g_command->console_input_mode = false;
            }
        }
    }
}
