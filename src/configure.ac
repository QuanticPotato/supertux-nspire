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
		
		The original author of this adaptation is 
			CHAUVIN Barnabé	(barnabe.chauvin@gmail.com)])

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
	[  --with-nspire-linker=PATH     which nspire linker to use (default : nspire-ld-bflt)],
	[NSPIRE_LD="$withval" ; AC_MSG_RESULT($NSPIRE_LD)],
	[NSPIRE_LD="nspire-ld-bflt" ; AC_MSG_RESULT([no  (default is $NSPIRE_LD)])])

AC_CHECK_PROG(has_nspire_ld, "$NSPIRE_LD", "yes", "no")
if test "$has_nspire_ld" = no ; then
	AC_MSG_ERROR([ no nspire linker found !
		(You can specify one with the --with-nspire-ld argument)])
fi

AC_SUBST([NSPIRE_LD], $NSPIRE_LD)

AC_OUTPUT

echo ""
echo "configure ran successful !"
echo "=========================="
echo ""
echo "You can now build the game with :"
echo "	make"
echo ""
