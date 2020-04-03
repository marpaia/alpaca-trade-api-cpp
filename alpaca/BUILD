package(default_visibility = ["//visibility:private"])

cc_library(
    name = "alpaca",
    srcs = [
        "account.cpp",
        "asset.cpp",
        "client.cpp",
        "clock.cpp",
        "config.cpp",
        "order.cpp",
        "position.cpp",
        "status.cpp",
        "watchlist.cpp",
    ],
    hdrs = [
        "account.h",
        "asset.h",
        "alpaca.h",
        "client.h",
        "clock.h",
        "config.h",
        "documentation.h",
        "json.h",
        "order.h",
        "position.h",
        "status.h",
        "watchlist.h",
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

cc_library(
    name = "test_helpers",
    srcs = [
        "testing.cpp",
    ],
    hdrs = [
        "testing.h",
    ],
    deps = [
        ":alpaca",
        "@com_google_googletest//:gtest",
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
        ":test_helpers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "client_test",
    size = "medium",
    srcs = [
        "client_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_google_googletest//:gtest_main",
    ],
)