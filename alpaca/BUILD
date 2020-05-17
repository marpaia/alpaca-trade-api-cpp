package(default_visibility = ["//visibility:private"])

cc_library(
    name = "alpaca",
    hdrs = [
        "account.h",
        "asset.h",
        "alpaca.h",
        "bars.h",
        "calendar.h",
        "client.h",
        "clock.h",
        "config.h",
        "documentation.h",
        "json.h",
        "order.h",
        "portfolio.h",
        "position.h",
        "quote.h",
        "status.h",
        "streaming.h",
        "trade.h",
        "watchlist.h",
    ],
    srcs = [
        "account.cpp",
        "asset.cpp",
        "bars.cpp",
        "calendar.cpp",
        "client.cpp",
        "clock.cpp",
        "config.cpp",
        "order.cpp",
        "portfolio.cpp",
        "position.cpp",
        "quote.cpp",
        "status.cpp",
        "streaming.cpp",
        "trade.cpp",
        "watchlist.cpp",
    ],
    visibility = ["//visibility:public"],
    defines = [
        "CPPHTTPLIB_OPENSSL_SUPPORT",
    ],
    deps = [
        "@com_github_google_boringssl//:ssl",
        "@com_github_google_glog//:glog",
        "@com_github_tencent_rapidjson//:rapidjson",
        "@com_github_yhirose_cpp_httplib//:httplib",
        "@com_github_unetworking_uwebsockets//:uwebsockets",
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
        "@com_github_google_googletest//:gtest",
    ],
)

cc_test(
    name = "account_test",
    size = "small",
    srcs = [
        "account_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "asset_test",
    size = "small",
    srcs = [
        "asset_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "bars_test",
    size = "small",
    srcs = [
        "bars_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "calendar_test",
    size = "small",
    srcs = [
        "calendar_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "client_test",
    size = "large",
    srcs = [
        "client_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "clock_test",
    size = "small",
    srcs = [
        "clock_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "order_test",
    size = "small",
    srcs = [
        "order_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "portfolio_test",
    size = "small",
    srcs = [
        "portfolio_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "position_test",
    size = "small",
    srcs = [
        "position_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "quote_test",
    size = "small",
    srcs = [
        "quote_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
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
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "streaming_test",
    size = "small",
    srcs = [
        "streaming_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "trade_test",
    size = "small",
    srcs = [
        "trade_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "watchlist_test",
    size = "small",
    srcs = [
        "watchlist_test.cpp",
    ],
    deps = [
        ":alpaca",
        ":test_helpers",
        "@com_github_google_googletest//:gtest_main",
    ],
)