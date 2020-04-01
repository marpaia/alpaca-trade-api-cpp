package(default_visibility = ["//visibility:private"])

cc_library(
    name = "alpaca",
    srcs = [
        "account.cpp",
        "client.cpp",
        "config.cpp",
        "order.cpp",
        "position.cpp",
    ],
    hdrs = [
        "account.h",
        "alpaca.h",
        "client.h",
        "config.h",
        "documentation.h",
        "json.h",
        "order.h",
        "position.h",
        "status.h",
    ],
    defines = [
        "CPPHTTPLIB_OPENSSL_SUPPORT",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@com_github_google_boringssl//:ssl",
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
