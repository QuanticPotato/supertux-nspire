dnl ==========================================================================
dnl
dnl	configure.ac
dnl	Author : CHAUVIN Barnabé   (Choups314)
dnl
dnl	Process this file with autoconf to produce a configure script
dnl
dnl ==========================================================================

AC_PREREQ([2.54])
AC_INIT([SuperTux-nSpire], 0.1)

AC_COPYRIGHT([This project comes from the original game SuperTux.  To get more information, refer to the README.md file.  This project is licensed under the GPL license. (c.f. COPYING)
		
		The original author of this adaptation is CHAUVIN Barnabé	(barnabe.chauvin@gmail.com)])

AC_CONFIG_SRCDIR([main.cpp]) 

AM_INIT_AUTOMAKE

AC_CONFIG_FILES([Makefile])

dnl ========== Check for programs ============================================

dnl  The ndless SDK use a different program as linker, so we have to disable 
dnl  the linker test step.

AC_NO_EXECUTABLES


#  Check for the nspire C compiler

AC_MSG_CHECKING([--with-nspire-cc argument])
AC_ARG_WITH([nspire-cc], 
	[  --with-nspire-cc=PATH     which nspire C compiler to use (default : nspire-gcc)],
	[CC="$withval" ; AC_MSG_RESULT($CC)],
	[CC="nspire-gcc" ; AC_MSG_RESULT([no  (default is $CC)])])

AC_CHECK_PROG(has_nspire_cc, "$CC", "yes", "no")
if test "$has_nspire_cc" = no ; then
	AC_MSG_ERROR([ no nspire C compiler found !
		(You can specify one with the --with-nspire-cc argument)])
fi

AC_PROG_CC


#  Check for the nspire C++ compiler

AC_MSG_CHECKING([--with-nspire-cxx argument])
AC_ARG_WITH([nspire-cxx], 
	[  --with-nspire-cxx=PATH     which nspire C++ compiler to use (default : nspire-g++)],
	[CXX="$withval" ; AC_MSG_RESULT($CXX)],
	[CXX="nspire-g++" ; AC_MSG_RESULT([no  (default is $CXX)])])


AC_CHECK_PROG(has_nspire_cxx, "$CXX", "yes", "no")
if test  "$has_nspire_cxx" = no ; then
	AC_MSG_ERROR([ no nspire C++ compiler found !
		(You can specify one with the --with-nspire-cxx argument)])
fi

AC_PROG_CXX


# Check for the nspire linker

AC_MSG_CHECKING([--with-nspire-linker argument])
AC_ARG_WITH([nspire-linker], 
	[  --with-nspire-linker=PATH     which nspire linker to use (default : nspire-ld)],
	[NSPIRE_LD="$withval" ; AC_MSG_RESULT($NSPIRE_LD)],
	[NSPIRE_LD="nspire-ld" ; AC_MSG_RESULT([no  (default is $NSPIRE_LD)])])

AC_CHECK_PROG(has_nspire_ld, "$NSPIRE_LD", "yes", "no")
if test "$has_nspire_ld" = no ; then
	AC_MSG_ERROR([ no nspire linker found !
		(You can specify one with the --with-nspire-ld argument)])
fi

AC_SUBST([NSPIRE_LD], $NSPIRE_LD)


# Check for the genzehn

AC_MSG_CHECKING([--with-nspire-genzehn argument])
AC_ARG_WITH([nspire-genzehn], 
	[  --with-nspire-genzehn=PATH     which nspire genzehn to use (default : genzehn)],
	[NSPIRE_GENZEHN="$withval" ; AC_MSG_RESULT($NSPIRE_GENZEHN)],
	[NSPIRE_GENZEHN="genzehn" ; AC_MSG_RESULT([no  (default is $NSPIRE_GENZEHN)])])

AC_CHECK_PROG(has_nspire_genzehn, "$NSPIRE_GENZEHN", "yes", "no")
if test "$has_nspire_genzehn" = no ; then
	AC_MSG_ERROR([ no nspire genzhen found !
		(You can specify one with the --with-nspire-genzhen argument)])
fi

AC_SUBST([NSPIRE_GENZEHN], $NSPIRE_GENZEHN)
AC_SUBST([NSPIRE_ZEHN_FLAGS], )


# Check for the make-prg

AC_MSG_CHECKING([--with-nspire-make-prg argument])
AC_ARG_WITH([nspire-make-prg], 
	[  --with-nspire-make-prg=PATH     which nspire make-prg to use (default : make-prg)],
	[NSPIRE_MAKE_PRG="$withval" ; AC_MSG_RESULT($NSPIRE_MAKE_PRG)],
	[NSPIRE_MAKE_PRG="make-prg" ; AC_MSG_RESULT([no  (default is $NSPIRE_MAKE_PRG)])])

AC_CHECK_PROG(has_nspire_make_prg, "$NSPIRE_MAKE_PRG", "yes", "no")
if test "$has_nspire_make_prg" = no ; then
	AC_MSG_ERROR([ no nspire make-prg found !
		(You can specify one with the --with-nspire-make-prg argument)])
fi

AC_SUBST([NSPIRE_MAKE_PRG], $NSPIRE_MAKE_PRG)


dnl ========== Check for build mode ==========================================

# Check for debug mode
AC_MSG_CHECKING(for debug mode)
AC_ARG_ENABLE(debug,
	      AC_HELP_STRING([--enable-debug], [enable debugging mode]),
	      [ENABLE_DEBUG="$enableval"],
	      [ENABLE_DEBUG="no"])
if test "x${ENABLE_DEBUG}" != "xno" ; then
	CXXFLAGS="$CXXFLAGS -DDEBUG -g"
	AC_MSG_RESULT([enabled])
else
	AC_MSG_RESULT([disable])
fi


dnl Constants

output_name=supertux
exe_ext=.tns
elf_ext=.elf
zehn_ext=.zehn
AC_SUBST([OUTPUT_NAME], $output_name)
AC_SUBST([EXE_NAME], $output_name$exe_ext)
AC_SUBST([ELF_NAME], $output_name$elf_ext)
AC_SUBST([ZEHN_NAME], $output_name$zehn_ext)

AC_OUTPUT

echo ""
echo "configure ran successful !"
echo "=========================="
echo ""
echo "You can now build the game with :"
echo "	make"
echo ""
echo "The executable $exe_name will be built ..."
echo ""
