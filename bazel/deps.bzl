load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def alpaca_deps():
    """Loads dependencies need to compile and test with the alpaca library."""

    # googletest is a testing framework developed by Google.
    if "com_github_google_gooogletest" not in native.existing_rules():
        http_archive(
            name = "com_github_google_googletest",
            strip_prefix = "googletest-release-1.10.0",
            urls = ["https://github.com/google/googletest/archive/release-1.10.0.tar.gz"],
            sha256 = "9dc9157a9a1551ec7a7e43daea9a694a0bb5fb8bec81235d8a1e6ef64c716dcb",
        )

    # gflags is a C++ library that implements commandline flags processing.
    if "com_github_gflags_gflags" not in native.existing_rules():
        http_archive(
            name = "com_github_gflags_gflags",
            strip_prefix = "gflags-2.2.2",
            urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
            sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
        )

    # glog is a C++ implementation of the Google logging module.
    if "com_github_google_glog" not in native.existing_rules():
        http_archive(
            name = "com_github_google_glog",
            strip_prefix = "glog-0.4.0",
            urls = ["https://github.com/google/glog/archive/v0.4.0.tar.gz"],
            sha256 = "f28359aeba12f30d73d9e4711ef356dc842886968112162bc73002645139c39c",
        )

    # RapidJSON is a fast JSON parser/generator for C++ with both SAX/DOM style API.
    if "com_github_tencent_rapidjson" not in native.existing_rules():
        http_archive(
            name = "com_github_tencent_rapidjson",
            strip_prefix = "rapidjson-1.1.0",
            urls = ["https://github.com/Tencent/rapidjson/archive/v1.1.0.tar.gz"],
            build_file = "@//bazel/third_party/rapidjson:BUILD",
            sha256 = "bf7ced29704a1e696fbccf2a2b4ea068e7774fa37f6d7dd4039d0787f8bed98e",
        )

    # cpp-httplib is a C++ header-only HTTP/HTTPS server and client library.
    if "com_github_yhirose_cpp-httplib" not in native.existing_rules():
        http_archive(
            name = "com_github_yhirose_cpp_httplib",
            strip_prefix = "cpp-httplib-0.5.7",
            urls = ["https://github.com/yhirose/cpp-httplib/archive/v0.5.7.tar.gz"],
            build_file = "@//bazel/third_party/cpphttplib:BUILD",
            sha256 = "27b7f6346bdeb1ead9d17bd7cea89d9ad491f50f0479081053cc6e5742a89e64",
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
            build_file = "@//bazel/third_party/zlib:BUILD",
            sha256 = "629380c90a77b964d896ed37163f5c3a34f6e6d897311f1df2a7016355c45eff",
        )

    # libuv is a multi-platform support library with a focus on asynchronous I/O.
    if "com_github_libuv_libuv" not in native.existing_rules():
        http_archive(
            name = "com_github_libuv_libuv",
            strip_prefix = "libuv-1.23.2",
            urls = ["https://github.com/libuv/libuv/archive/v1.23.2.tar.gz"],
            build_file = "@//bazel/third_party/libuv:BUILD",
            sha256 = "30af979c4f4b8d1b895ae6d115f7400c751542ccb9e656350fc89fda08d4eabd",
        )

    # uWebsockets is a simple, secure & standards compliant web I/O library.
    if "com_github_unetworking_uwebsockets" not in native.existing_rules():
        http_archive(
            name = "com_github_unetworking_uwebsockets",
            strip_prefix = "uWebSockets-0.14.8",
            urls = ["https://github.com/uNetworking/uWebSockets/archive/v0.14.8.tar.gz"],
            build_file = "@//bazel/third_party/uwebsockets:BUILD",
            sha256 = "663a22b521c8258e215e34e01c7fcdbbd500296aab2c31d36857228424bb7675",
        )