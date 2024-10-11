cmake_minimum_required(VERSION 3.10)
project(DistributedFileSystem)

set(CMAKE_CXX_STANDARD 17)

# Find Protobuf and gRPC
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# Proto file compilation
set(PROTO_FILES src/grpc_interface.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_FILES})

# Add server and client executables
add_executable(server src/server.cpp src/raft.cpp ${PROTO_SRCS} ${GRPC_SRCS})
add_executable(client src/client.cpp ${PROTO_SRCS} ${GRPC_SRCS})

# Link libraries
target_link_libraries(server gRPC::grpc++ protobuf::libprotobuf)
target_link_libraries(client gRPC::grpc++ protobuf::libprotobuf)
