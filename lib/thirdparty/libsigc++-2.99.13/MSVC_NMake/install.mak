# NMake Makefile snippet for copying the built libraries, utilities and headers to
# a path under $(PREFIX).

install: all
	@if not exist $(PREFIX)\bin\ mkdir $(PREFIX)\bin
	@if not exist $(PREFIX)\lib\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\include\ mkdir $(PREFIX)\lib\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\include
	@if not exist $(PREFIX)\include\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\sigc++\adaptors\ @mkdir $(PREFIX)\include\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\sigc++\adaptors
	@if not exist $(PREFIX)\include\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\sigc++\functors\ @mkdir $(PREFIX)\include\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\sigc++\functors
	@if not exist $(PREFIX)\include\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\sigc++\tuple-utils\ @mkdir $(PREFIX)\include\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\sigc++\tuple-utils
	@copy /b $(CFG)\$(PLAT)\$(LIBSIGC_LIBNAME).dll $(PREFIX)\bin
	@copy /b $(CFG)\$(PLAT)\$(LIBSIGC_LIBNAME).pdb $(PREFIX)\bin
	@copy /b $(CFG)\$(PLAT)\$(LIBSIGC_LIBNAME).lib $(PREFIX)\lib
	@for %h in ($(LIBSIGC_INT_HDRS)) do @copy "..\sigc++\%h" "$(PREFIX)\include\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\sigc++\%h"
	@copy "sigc++config.h" "$(PREFIX)\lib\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\include\"
