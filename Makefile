appName ?= uavrt_detection
toolsPath = /home/parallels/auterion_developer_tools-v2.5.3/tools
version ?= 1.0.0
architecture ?= arm64
device ?= skynode
deviceIp ?= 10.41.1.1

ifneq ($(artifactPath),)
artifactPath=$(artifactPath)
else
artifactPath=$(shell pwd)/output/$(appName)_$(version).auterionos
endif

build-docker:
	docker build --network=host --platform=$(architecture) . -t $(appName):$(version)

build: build-docker Dockerfile codegen/exe/uavrt_detection/uavrt_detection_rtw.mk
	mkdir -p output
	docker save $(appName):$(version) | gzip > output/$(appName).image
	$(toolsPath)/package_app.sh --app=$(appName) --version=$(version) --device=$(device)

install:
	$(toolsPath)/update.py --artifact $(artifactPath) --device-ip $(deviceIp)
	
remove:
	$(toolsPath)/remove_app.sh -d $(deviceIp) -n $(appName)
