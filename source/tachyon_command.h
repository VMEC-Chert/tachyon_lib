
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
        cursor_move_store
    };

    struct command_property
    {
        uid id;
        dynamic_primitive value;
        pointer<byte> custom_data;
    };

    struct command_property_user
    {
    };

    struct command_context
    {
        array<command_property> properties;
        array<fstring> command_string_queue;
    };

    PROC command_init() -> fresult;

    /** Non-blocking stdin processing */
    PROC command_read_console() -> void;

    extern command_context* g_command;
}
