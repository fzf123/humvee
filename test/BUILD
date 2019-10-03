cc_binary(
    name = 'test',
    srcs = ['queue_test.cc'],
    deps = [
        '//queue:queue'
    ],
    linkopts = ['-pthread'],
)

cc_binary(
    name = 'threadpool_test',
    srcs = ['threadpool_test.cc'],
    deps = [
        '//thread_pool:thread_pool'
    ],
    linkopts = ['-pthread'],
)
