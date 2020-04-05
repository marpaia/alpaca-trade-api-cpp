package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "streaming",
    srcs = ["streaming.cpp"],
    deps = [
        "//alpaca:alpaca",
        "@com_github_unetworking_uwebsockets//:uwebsockets",
    ],
)

cc_binary(
    name = "buy",
    srcs = ["buy.cpp"],
    deps = ["//alpaca:alpaca"],
)

cc_binary(
    name = "toggle_shorting",
    srcs = ["toggle_shorting.cpp"],
    deps = ["//alpaca:alpaca"],
)