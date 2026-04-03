

namespace tyon
{
    extern command_context* g_command = nullptr;

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


    PROC command_read_console() -> void
    {
        fstring input;
        char buf[1024] {};
        /** NOTE: Breaks if two newlines are input, so we have to clear the newlines in a loop..
            NOTE: This is horrible API design and I hate whoever designed this.
            NOTE: BUT IT DOES WORK, it IS non-blocking */
        while (std::cin.peek() == '\n')
        { std::cin.ignore( 1000000, '\n' ); }
        std::cin.get( buf, 1024 );
        input = buf;

        if (input.size())
        {
            TYON_LOGF( "Echo Input from stdin: '{}'", input );
            g_command->command_string_queue.push_tail( input );
        }
    }
}
