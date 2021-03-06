#
# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

################################################################################
#
# Look for MY_STUFF below to customize this Makefile. There's no need to change
# anything else.
#
#################################################################################

# GRPC

HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11
ifeq ($(SYSTEM),Darwin)
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc`\
           -lgrpc++_reflection\
           -ldl
else
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc`\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl
endif
PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`
PROTOS_PATH = service_spec
vpath %.proto $(PROTOS_PATH)

# Opencog

CXXFLAGS += -I/usr/include/guile/2.2 -DHAVE_GUILE
CXXFLAGS += -I/usr/local/include/opencog/
CXXFLAGS += $(shell curl-config --cflags)
LDFLAGS += -L/usr/local/lib/opencog -L/usr/local/lib/opencog/modules -L/usr/local/lib
LDFLAGS += $(shell ls /usr/local/lib/opencog | grep "\.so" | sed "s/lib/-l/" | sed "s/\.so//")
LDFLAGS += $(shell ls /usr/local/lib/opencog/modules | grep "\.so" | sed "s/lib/-l/" | sed "s/\.so//")
LDFLAGS += -lcogutil
LDFLAGS += -lboost_system
LDFLAGS += $(shell curl-config --libs)
SERVICES = $(shell ls cpp-services/*.cc | sed "s/\.cc/\.o/")

#################################################################################
#
# MY_STUFF - begin
#
#################################################################################

all: guileSession server client runTests

server: $(SERVICES) Session.o GuileSessionManager.o OpencogSNETServiceFactory.o SCMService.o OpencogSNETService.o opencog.pb.o opencog.grpc.pb.o server.o utils.o 
	$(CXX) $^ $(LDFLAGS) -o ../bin/$@

guileSession: guileSession.o
	$(CXX) $^ $(LDFLAGS) -o ../bin/$@

client: opencog.pb.o opencog.grpc.pb.o client.o
	$(CXX) $^ $(LDFLAGS) -o ../bin/$@

runTests: runTests.o
	$(CXX) $^ $(LDFLAGS) -o ../bin/$@

clean:
	rm -f *.o $(SERVICES) *.pb.cc *.pb.h ../bin/server ../bin/client ../bin/runTests

#################################################################################
#
# MY_STUFF - end
#
#################################################################################

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<

