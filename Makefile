OUTPUT = install
SOURCEDIR = ./source
ROOTDIR = .
DIR1 = ./installer/source
DEPOBJDIR = ./depsAndObjects
INCDIRS = ./include ./installer/header
CPPC = g++
C++standart = -std=c++23
OPT = -O2
DEPFLAGS = -MP -MD
GENERALFLAGS = $(C++standart) -g3

CFLAGS = $(GENERALFLAGS) $(OPT) $(DEPFLAGS)

CFILES = $(wildcard $(ROOTDIR)/*.cpp) $(wildcard $(SOURCEDIR)/*.cpp) $(wildcard $(DIR1)/*.cpp)

OBJECTS = $(patsubst %.cpp,$(DEPOBJDIR)/%.o,$(notdir $(CFILES)))
DEPFILES = $(patsubst %.o,%.d,$(OBJECTS))

all: $(OUTPUT)
	@echo ========= SUCCES ==========

run: $(OUTPUT)
	@./$(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CPPC) $^ -Wl,--defsym=main=main -o $@

mrproper:
	rm -rf $(OUTPUT) $(DEPOBJDIR)/*.o $(DEPOBJDIR)/*.d

$(DEPOBJDIR)/%.o:$(ROOTDIR)/%.cpp
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIRS),-I$(D)) -c -o $@ $<

$(DEPOBJDIR)/%.o:$(SOURCEDIR)/%.cpp
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIRS),-I$(D)) -c -o $@ $<

$(DEPOBJDIR)/%.o:$(DIR1)/%.cpp
	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIRS),-I$(D)) -c -o $@ $<

-include $(DEPFILES)