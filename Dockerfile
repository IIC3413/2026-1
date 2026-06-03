# Build stage
FROM alpine:3.23 AS build

WORKDIR /my_db
RUN apk --no-cache add cmake \
                       make \
                       g++ \
                       boost1.84-dev

COPY src                               src
COPY CMakeLists.txt                    CMakeLists.txt
COPY third_party/antlr4-runtime-4.13.1 third_party/antlr4-runtime-4.13.1


RUN cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./ && \
    cmake --build build -j $(($(getconf _NPROCESSORS_ONLN)-1)) --target install

# Final minimal stage (to minimize image size)
FROM alpine:3.23 AS final
WORKDIR /data

RUN apk --no-cache add libstdc++ \
                       libgcc \
                       bash

COPY --from=build /my_db/build/bin /usr/bin

VOLUME /data
CMD ["bash"]
