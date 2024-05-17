cc_library(
    name = "wc_lib",
    srcs = ["src/wc.cpp"],
    hdrs = ["include/wc.h"]
)

cc_binary(
    name = "wc",
    srcs = ["src/main.cpp"],
    deps = [":wc_lib"],
    copts = select({
        "//conditions:default": [],
        "//build:debug": ["-g", "-O0"],
        "//build:releasee": ["-O3"],
    }),
)