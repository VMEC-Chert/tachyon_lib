

namespace tyon
{

struct config_option
{
    fstring name = "";
    fstring value = "";
    e_primitive type = e_primitive::none;
};

/** Internal struct for storing parsed strings from a config file */
struct config_pair
{
    fstring name;
    fstring value;
};

PROC config_file_load_strings( fstring config_filename ) -> array<config_pair>;

}
