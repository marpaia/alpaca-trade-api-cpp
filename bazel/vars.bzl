ALPACA_DEPS = [
    "@com_github_google_boringssl//:ssl",
    "@com_github_google_glog//:glog",
    "@com_github_tencent_rapidjson//:rapidjson",
    "@com_github_yhirose_cpp-httplib//:httplib",
    "@com_github_unetworking_uwebsockets//:uwebsockets",
]

ALPACA_DEFINES = [
    "CPPHTTPLIB_OPENSSL_SUPPORT",
]