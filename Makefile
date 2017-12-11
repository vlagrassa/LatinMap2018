include config.mk

$(MAIN): $(OBJS) | $(BUILDDIR)
	$(LINK.cpp) $(OUTPUT_OPTION) $^ $(LOADLIBES) $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS) | $(OBJDIR) $(OBJSUBDIRS)
	$(COMPILE.cpp) $(OUTPUT_OPTION) $< 

$(BUILDDIR) $(OBJDIR) $(OBJSUBDIRS):
	mkdir -p $@

.DEFAULT: run
.PHONY:   run
run: $(MAIN)
	./$<

.PHONY: clean
clean:
	$(RM) $(OBJDIR) $(BUILDDIR) $(GCHS)
