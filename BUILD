
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")


cc_library(
    name = "tachyon_library",
    srcs =
    glob( [
    # "source/**/*.cpp",
     "**/*.h",
    # "source/*.cpp"
    "source/build_control/tachyon_lib_unity_core.cpp",
    "external/fmt/include/fmt/*.h",

    ] ),
    hdrs =
    glob( [    'external/fmt/include/fmt/*',
               # Hack to allow unity builds
           "source/*.cpp"]
         ),
    includes = [
        "source",
        "source/build_control",
        # 'external/fmt/include',
        # # Not needed in unity build
        # 'external/catch2/src/'
    ],
    defines = [
        "TYON_REFLECTION_BAZEL_BUILD"
    ],
    copts = [
    "-std=c++20",
    "-Wno-c++11-compat"
    ]
)
