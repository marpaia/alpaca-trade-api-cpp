package(default_visibility = ["//visibility:public"])

cc_library(
    name = "rapidjson",
    hdrs = glob([
        "include/rapidjson/*.h",
        "include/rapidjson/*/*.h",
    ]),
    copts = [
        "-Wno-non-virtual-dtor",
        "-Wno-unused-variable",
        "-Wno-implicit-fallthrough",
    ],
    includes = ["include"],
)
