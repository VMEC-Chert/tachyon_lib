
load("@bazel_skylib//rules:common_settings.bzl", "bool_flag")

def config_bool(name, default = True):
    bool_flag(
        name = name,
        build_setting_default = default,
    )
    native.config_setting(
        name = "config_" + name,
        flag_values = {":" + name: "True"},
    )

def config_enable_list(flag_name, enabled_list ):
    return select({
        "config_" +flag_name: enabled_list,
        "//conditions:default": [],
    })
