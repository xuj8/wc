cc_library(
    name = "cpp_wc_lib",
    hdrs = ["cpp/include/wc.h"],
    srcs = ["cpp/src/wc.cpp"],
    includes = ["cpp/include"],
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "cpp_wc",
    hdrs = ["cpp/include/CLI11.hpp"],
    srcs = ["cpp/src/main.cpp"],  # Assuming you have or will create a main.cpp
    includes = ["cpp/include"],
    deps = [":cpp_wc_lib"],
)