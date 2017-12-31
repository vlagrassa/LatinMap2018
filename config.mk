SRCDIR   ?= src
OBJDIR   ?= obj
BUILDDIR ?= build
MAIN     ?= main

RM        += -r

# Begin the warnings
override WARNINGS += all
override WARNINGS += extra
# Everything under here is probably overkill
# I'll sort it by important-ness
override WARNINGS += no-unused-variable 
override WARNINGS += no-unused-parameter
override WARNINGS += pedantic
override WARNINGS += effc++ 
override WARNINGS += cast-align
override WARNINGS += cast-qual
override WARNINGS += ctor-dtor-privacy 
override WARNINGS += disabled-optimization 
override WARNINGS += format=2 
override WARNINGS += init-self 
override WARNINGS += missing-declarations 
override WARNINGS += missing-include-dirs 
override WARNINGS += old-style-cast 
override WARNINGS += overloaded-virtual 
override WARNINGS += redundant-decls 
override WARNINGS += shadow 
override WARNINGS += sign-promo 
override WARNINGS += strict-overflow=5 
override WARNINGS += switch-default 
override WARNINGS += undef 
override WARNINGS += sign-conversion 
#override WARNINGS += error 

override CXXFLAGS   += -std=c++11
override CXXFLAGS   += $(addprefix -W,$(WARNINGS))

CPPFLAGS   := $(shell pkg-config sfml-all --cflags)
CPPFLAGS   := $(subst -I,-isystem, $(CPPFLAGS))

LDLIBS     := $(shell pkg-config sfml-all --libs)

SRCSUBDIRS := $(shell find $(SRCDIR) -mindepth 1 -type d)
SRCS       := $(shell find $(SRCDIR) -type f -name '*.cpp')
HDRS       := $(shell find $(SRCDIR) -type f -name '*.hpp')

OBJSUBDIRS := $(subst $(SRCDIR),$(OBJDIR),$(SRCSUBDIRS))
OBJS       := $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.cpp=.o))

override MAIN := $(addprefix $(BUILDDIR)/,$(MAIN))
