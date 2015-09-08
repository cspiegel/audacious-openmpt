ifeq ($(CXX), g++)
CXXFLAGS+=	-Wall -std=c++11 -pedantic
endif

ifeq ($(CXX), clang++)
CXXFLAGS+=	-Wall -Wunused-macros -std=c++11 -pedantic
endif

ifeq ($(shell basename $(CXX)), c++-analyzer)
CXXFLAGS+=	-std=c++11
endif

ifneq ($(CXXHOST),)
CXX:=	$(CXXHOST)-$(CXX)
endif
