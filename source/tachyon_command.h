
#pragma once
namespace tyon
{

    enum class ansi_control : i32
    {
        none = 0,
        any = 1,
        line_clear_after,
        line_clear_before,
        line_clear_entire,
        cursor_move_home,
        cursor_move_end,
        cursor_save_store,
        cursor_move_store,

        cursor_move_forwards,
        cursor_move_backwards,
        cursor_move_up,
        cursor_move_down
    };

    /** Console command types */
    enum class e_command : i32
    {
        none = 0,
        any = 1,
        /** One shot command that can run a function*/
        execute,
        /** Read or Write from a bound variable */
        property
    };

    struct command_property
    {
        uid id;
        dynamic_primitive value;
        pointer<byte> custom_data;
    };

    // ??????
    // TODO: Is this supposed to be a local consumer binding for referencing a bound property? idk
    struct command_property_user
    {
    };

    /** Description of a command that can be called */
    struct command
    {
        uid id;
        e_command type;
        fstring name;
        array<fstring> aliases;

        // State
        bool triggered = false;
        command_property property;
    };

    struct command_submitted
    {
        string name;
        string flags;
        dynamic_primitive value;
        string unprocessed;
    };

    struct command_context
    {
        array<command_property> properties;
        /** Before processing */
        array<fstring> command_string_queue;
        /** After processing */
        array<command_submitted> command_queue;
        array<command> command_list;
        fstring line_contents;
        fstring line_contents_raw;
        /** Temporary contents for console input reading */
        fstring console_input;
        i32 line_cursor = 0;
        i32 cursor_x = 0;
        i32 cursor_y = 0;

        bool console_input_mode = false;
        /** Saves the state of the log variable before modifying it so we can restore it. */
        bool prev_console_output_enabled = true;
    };

    PROC command_init() -> fresult;

    PROC command_add( command* arg ) -> uid;

    /** Non-blocking stdin processing */
    PROC command_read_console() -> void;

    /** After commands are received we can do text processing and other such actions. */
    PROC command_proccess_commands() -> void;

    extern command_context* g_command;
}
