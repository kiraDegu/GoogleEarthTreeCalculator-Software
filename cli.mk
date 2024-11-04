# Comment this line if running on a UNIX system
SHELL := cmd.exe

CXX := g++
CXXOPT := -O3
CXXFLAGS := -Wall -Wextra $(CXXOPT) -std=c++17 -DCLICOMPILE=true
CPPFLAGS := -I.

MAIN := test.cpp
OBJDIR := obj
EXEC := $(patsubst %.cpp, %.exe, $(MAIN))

SRCS := Calculators.cpp Manager.cpp utilities.cpp $(MAIN)
HEADS := TypeTraits.hpp KmlInterface.hpp Data.hpp Calculator.hpp Manager.hpp utilities.hpp
OBJS := $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRCS))

.PHONY: clean distclean

$(EXEC): $(OBJS)
	$(CXX) $^ -o $@

clean:
	@rm $(OBJS)

distclean: clean
	@rmdir $(OBJDIR)
	@rm $(EXEC)

# Pattern rules
$(OBJDIR)/%.o: %.cpp
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
