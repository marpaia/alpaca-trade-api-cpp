package(default_visibility = ["//visibility:private"])

cc_library(
    name = "alpaca",
    srcs = [],
    hdrs = [
        "documentation.h",
        "status.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@com_google_absl//absl/strings",
        "@com_github_google_glog//:glog",
        "@com_github_tencent_rapidjson//:rapidjson",
        "@com_github_yhirose_cpp-httplib//:httplib",
    ],
)

cc_test(
    name = "status_test",
    size = "small",
    srcs = [
        "status_test.cpp",
    ],
    deps = [
        ":alpaca",
        "@com_google_googletest//:gtest_main",
    ],
)
