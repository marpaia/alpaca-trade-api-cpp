workspace(name = "alpaca_trade_api_cpp")

################################################################################
# General Initialization
################################################################################

# The native http_archive rule is deprecated. This is a drop-in replacement.
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

################################################################################
# C++ Dependencies
################################################################################

# Abseil is an open-source collection of C++ code (compliant to C++11) designed
# to augment the C++ standard library.
http_archive(
    name = "com_google_absl",
    strip_prefix = "abseil-cpp-20200225.1",
    urls = ["https://github.com/abseil/abseil-cpp/archive/20200225.1.tar.gz"],
)

# googletest is a testing framework developed by Google.
http_archive(
    name = "com_google_googletest",
    strip_prefix = "googletest-release-1.10.0",
    urls = ["https://github.com/google/googletest/archive/release-1.10.0.tar.gz"],
)

# gflags is a C++ library that implements commandline flags processing.
http_archive(
    name = "com_github_gflags_gflags",
    strip_prefix = "gflags-2.2.2",
    urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
)

# glog is a C++ implementation of the Google logging module.
http_archive(
    name = "com_github_google_glog",
    strip_prefix = "glog-0.4.0",
    urls = ["https://github.com/google/glog/archive/v0.4.0.tar.gz"],
)

# RapidJSON is a fast JSON parser/generator for C++ with both SAX/DOM style API.
http_archive(
    name = "com_github_tencent_rapidjson",
    strip_prefix = "rapidjson-1.1.0",
    urls = ["https://github.com/Tencent/rapidjson/archive/v1.1.0.tar.gz"],
    build_file = "@alpaca_trade_api_cpp//third_party/rapidjson:BUILD",
)

# cpp-httplib is a C++ header-only HTTP/HTTPS server and client library.
http_archive(
    name = "com_github_yhirose_cpp-httplib",
    strip_prefix = "cpp-httplib-0.5.7",
    urls = ["https://github.com/yhirose/cpp-httplib/archive/v0.5.7.tar.gz"],
    build_file = "@alpaca_trade_api_cpp//third_party/cpp-httplib:BUILD"
)