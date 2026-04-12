
#pragma once

#if (REFLECTION_PLATFORM_LINUX)
namespace tyon
{


struct linux_context
{

};

extern linux_context* g_linux;

fresult
file_write_binary_posix( file* arg );

PROC linux_restore_terminal_mode() -> void;

}
#endif // REFLECTION_PLATFORM_LINUX
