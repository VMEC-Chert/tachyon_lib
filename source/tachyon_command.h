
#pragma once
namespace tyon
{

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
