# Comment this line if running on a UNIX system
SHELL := cmd.exe

CXX := g++
CXXOPT := -O3
CXXFLAGS := -Wall -Wextra $(CXXOPT) -std=c++17
CPPFLAGS := -I.

MAIN := test.cpp
OBJDIR := obj
EXEC := $(patsubst %.cpp, %.exe, $(MAIN))

SRCS := Calculators.cpp Manager.cpp $(MAIN) utilities.cpp
HEADS := TypeTraits.hpp KmlInterface.hpp Data.hpp Calculator.hpp Manager.hpp utilities.hpp
OBJS := $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRCS))

$(EXEC): $(OBJS)
	$(CXX) $^ -o $@



# Pattern rules
$(OBJDIR)/%.o: %.cpp 
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
