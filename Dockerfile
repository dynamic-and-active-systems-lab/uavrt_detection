FROM auterion/ubuntu-mavsdk:v0.44.0 as build-stage

WORKDIR /matlab-extern
COPY matlab-extern .
WORKDIR /uavrt_detection
COPY detector/config/detectorConfig.txt detector/config/detectorConfig.txt
COPY udp.cpp udp.h .
WORKDIR /uavrt_detection/codegen/exe/uavrt_detection
COPY codegen/exe/uavrt_detection .
RUN make -j12 -f uavrt_detection_rtw.mk

FROM arm64v8/ubuntu as release-stage

ARG DEBIAN_FRONTEND=noninteractive

# MAVSDK dependencies
RUN apt-get update \
    && apt-get clean \
    && apt-get install -y --no-install-recommends libgomp1 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=build-stage /uavrt_detection/detector/config/detectorConfig.txt detector/config/detectorConfig.txt
COPY --from=build-stage /uavrt_detection/uavrt_detection /app/

ENTRYPOINT [ "/app/uavrt_detection" ]
