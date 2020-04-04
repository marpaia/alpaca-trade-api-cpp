package(default_visibility = ["//visibility:public"])

cc_library(
    name = "uwebsockets",
    hdrs = [
        "src/Backend.h",
        "src/Epoll.h",
        "src/Extensions.h",
        "src/Group.h",
        "src/HTTPSocket.h",
        "src/Hub.h",
        "src/Libuv.h",
        "src/Networking.h",
        "src/Node.h",
        "src/Socket.h",
        "src/WebSocket.h",
        "src/WebSocketProtocol.h",
        "src/uWS.h",
    ],
    srcs = [
        "src/Epoll.cpp",
        "src/Extensions.cpp",
        "src/Group.cpp",
        "src/HTTPSocket.cpp",
        "src/Hub.cpp",
        "src/Networking.cpp",
        "src/Node.cpp",
        "src/Socket.cpp",
        "src/WebSocket.cpp",
    ],
    includes = [
        "src/",
    ],
    deps = [
        "@com_github_google_boringssl//:ssl",
        "@com_github_libuv_libuv//:libuv",
        "@com_github_madler_zlib//:zlib",
    ],
    defines = [],
)