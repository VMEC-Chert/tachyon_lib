
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

# TODO: This build file is clumsily written because I'm not show the exact
# function of all the configurations yet.

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
    ],
    defines = [
        "TYON_REFLECTION_BAZEL_BUILD"
    ],
    copts = [
    "-std=c++20",
    "-Wno-c++11-compat",
    ],
    linkopts = [ "-luuid" ],
    deps = [  ]
)

cc_test(
    name = "tachyon_library_test",
    srcs = [
        "source/tests/unity_catch2_core.cpp",
    ]
    + glob( ["source/tests/ai_generated/*.cpp"] ),
    deps = ["//:tachyon_library", '@catch2//:catch2_main'],
    # Don't think I need linkstatic right now
    # linkstatic = True,
    copts = [
    "-Wno-c++11-compat",
    ]
)
