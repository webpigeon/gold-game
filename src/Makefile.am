## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(GOLD_IGGI_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gold_iggi

gold_iggi_SOURCES = \
	main.cc

gold_iggi_LDFLAGS = 

gold_iggi_LDADD = $(GOLD_IGGI_LIBS)


if NATIVE_WIN32
gold_iggi_LDFLAGS += -mwindows
endif
