cc_library(
    name = "wc_lib",
    srcs = ["src/wc.cpp", "src/buffer_reader.cpp"],
    hdrs = ["include/wc.h", "include/CLI11.hpp", "include/buffer_reader.h", "include/utils.h"],
    includes = ["include"],
    copts = ["-std=c++20"],
)

cc_binary(
    name = "wc",
    srcs = ["src/main.cpp"],
    deps = [":wc_lib"],
    copts = ["-std=c++20"],
    # copts = select({
    #     "//conditions:default": [],
    #     "//build:debug": ["-g", "-O0"],
    #     "//build:release": ["-O3"],
    # }),
)

cc_test(
    name = "wc_test",
    srcs = ["tests/wc_test.cpp"],
    deps = [
        ":wc_lib",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
    copts = ["-std=c++20"],
)