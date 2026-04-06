

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

        bool debug_run_always = true;
        // TODO: do input polling with _khbit() / poll() for performance
        if (debug_run_always)
        {
            fgets( buf, 100, stdin );
            // NOTE: Not needed
            // NOTE: Extremely slow compared to fgets.
            // int read_bytes = read( STDIN_FILENO, buf.data(), 100 );

            input += buf;
        }

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

        bool do_backspace = (input.back() == 127);
        bool submit_command = (input.size() > 1 && input.back() == 10);
        if (do_backspace)
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
        }
    }
}
