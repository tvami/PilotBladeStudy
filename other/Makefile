include Makefile.arch

PILOTHISTOMAKERO      = PilotHistoMaker.$(ObjSuf)
PILOTHISTOMAKERS      = PilotHistoMaker.$(SrcSuf)
PILOTHISTOMAKER       = PilotHistoMaker$(ExeSuf)

OBJS          += $(PILOTHISTOMAKERO)
PROGRAMS      += $(PILOTHISTOMAKER)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all:            $(PROGRAMS)

$(PILOTHISTOMAKER):     $(PILOTHISTOMAKERO)
		$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt)$@
		$(MT_EXE)
		@echo "$@ done"

clean:
		@rm -f $(OBJS) core

distclean:      clean
		@rm -f $(PROGRAMS) *Dict.* *.def *.exp \
		   *.root *.ps *.so *.lib *.dll *.d *.log .def so_locations
		@rm -rf cxx_repository

.SUFFIXES: .$(SrcSuf)

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

