load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

ALPACA_DEPS = [
    "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
] + ALPACA_INTERNAL_DEPS

ALPACA_INTERNAL_DEPS = [
    "@com_github_google_boringssl//:ssl",
    "@com_github_google_glog//:glog",
    "@com_github_tencent_rapidjson//:rapidjson",
    "@com_github_yhirose_cpp_httplib//:httplib",
    "@com_github_unetworking_uwebsockets//:uwebsockets",
]

ALPACA_DEFINES = [
    "CPPHTTPLIB_OPENSSL_SUPPORT",
]

def alpaca_deps():
    """Loads dependencies need to compile and test with the alpaca library."""

    # googletest is a testing framework developed by Google.
    if "com_github_google_gooogletest" not in native.existing_rules():
        http_archive(
            name = "com_github_google_googletest",
            strip_prefix = "googletest-release-1.10.0",
            urls = ["https://github.com/google/googletest/archive/release-1.10.0.tar.gz"],
        )

    # gflags is a C++ library that implements commandline flags processing.
    if "com_github_gflags_gflags" not in native.existing_rules():
        http_archive(
            name = "com_github_gflags_gflags",
            strip_prefix = "gflags-2.2.2",
            urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
        )

    # glog is a C++ implementation of the Google logging module.
    if "com_github_google_glog" not in native.existing_rules():
        http_archive(
            name = "com_github_google_glog",
            strip_prefix = "glog-0.4.0",
            urls = ["https://github.com/google/glog/archive/v0.4.0.tar.gz"],
        )

    # RapidJSON is a fast JSON parser/generator for C++ with both SAX/DOM style API.
    if "com_github_tencent_rapidjson" not in native.existing_rules():
        http_archive(
            name = "com_github_tencent_rapidjson",
            strip_prefix = "rapidjson-1.1.0",
            urls = ["https://github.com/Tencent/rapidjson/archive/v1.1.0.tar.gz"],
            build_file = "@com_github_marpaia_alpaca_trade_api_cpp//third_party/rapidjson:BUILD",
        )

    # cpp-httplib is a C++ header-only HTTP/HTTPS server and client library.
    if "com_github_yhirose_cpp-httplib" not in native.existing_rules():
        http_archive(
            name = "com_github_yhirose_cpp_httplib",
            strip_prefix = "cpp-httplib-0.5.7",
            urls = ["https://github.com/yhirose/cpp-httplib/archive/v0.5.7.tar.gz"],
            build_file = "@com_github_marpaia_alpaca_trade_api_cpp//third_party/cpphttplib:BUILD"
        )

    # BoringSSL is a fork of OpenSSL that is designed to meet Google's needs.
    if "com_github_google_boringssl" not in native.existing_rules():
        http_archive(
            name = "com_github_google_boringssl",
            strip_prefix = "boringssl-master-with-bazel",
            urls = ["https://github.com/google/boringssl/archive/master-with-bazel.tar.gz"],
        )

    # zlib is a general purpose data compression library.
    if "com_github_madler_zlib" not in native.existing_rules():
        http_archive(
            name = "com_github_madler_zlib",
            strip_prefix = "zlib-1.2.11",
            urls = ["https://github.com/madler/zlib/archive/v1.2.11.tar.gz"],
            build_file = "@com_github_marpaia_alpaca_trade_api_cpp//third_party/zlib:BUILD",
        )

    # libuv is a multi-platform support library with a focus on asynchronous I/O.
    if "com_github_libuv_libuv" not in native.existing_rules():
        http_archive(
            name = "com_github_libuv_libuv",
            strip_prefix = "libuv-1.23.2",
            urls = ["https://github.com/libuv/libuv/archive/v1.23.2.tar.gz"],
            build_file = "@com_github_marpaia_alpaca_trade_api_cpp//third_party/libuv:BUILD",
        )

    # uWebsockets is a simple, secure & standards compliant web I/O library.
    if "com_github_unetworking_uwebsockets" not in native.existing_rules():
        http_archive(
            name = "com_github_unetworking_uwebsockets",
            strip_prefix = "uWebSockets-0.14.8",
            urls = ["https://github.com/uNetworking/uWebSockets/archive/v0.14.8.tar.gz"],
            build_file = "@com_github_marpaia_alpaca_trade_api_cpp//third_party/uwebsockets:BUILD",
        )