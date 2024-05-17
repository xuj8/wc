cc_library(
    name = "wc_lib",
    srcs = ["src/wc.cpp"],
    hdrs = ["include/wc.h", "include/CLI11.hpp"],
    includes = ["include"],
)

cc_binary(
    name = "wc",
    srcs = ["src/main.cpp"],
    deps = [":wc_lib"],
    # copts = select({
    #     "//conditions:default": [],
    #     "//build:debug": ["-g", "-O0"],
    #     "//build:release": ["-O3"],
    # }),
)