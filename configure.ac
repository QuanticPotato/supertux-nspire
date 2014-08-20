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

AC_COPYRIGHT([This project comes from the original game SuperTux.
		To get more information, refer to the README.md file.
		This project is licensed under the GPL license. (c.f. COPYING)
		
		The original author of this adaptation is 
			CHAUVIN Barnabé	(barnabe.chauvin@gmail.com)])

AC_CONFIG_SRCDIR([INSTALL])

dnl ========== Check for programs ============================================

AC_PROG_CC
AC_PROG_CXX
AC_PROG_LN_S

dnl  Check for the nspire C compiler

AC_MSG_CHECKING([--with-nspire-cc argument])
AC_ARG_WITH([nspire-cc], 
	[  --with-nspire-cc=PATH     which nspire C compiler to use (default : nspire-gcc)],
	[NSPIRE_CC="$withval" ; AC_MSG_RESULT($NSPIRE_CC)],
	[NSPIRE_CC="nspire-gcc" ; AC_MSG_RESULT([no  (default is $NSPIRE_CC)])])

AC_CHECK_PROG(has_nspire_cc, "$NSPIRE_CC", "yes", "no")
if test "$has_nspire_cc" = no ; then
	AC_MSG_ERROR([ no nspire C compiler found !
		(You can specify one with the --with-nspire-cc argument)])
fi

dnl  Check for the nspire C++ compiler

AC_MSG_CHECKING([--with-nspire-cxx argument])
AC_ARG_WITH([nspire-cxx], 
	[  --with-nspire-cxx=PATH     which nspire C++ compiler to use (default : nspire-g++)],
	[NSPIRE_CXX="$withval" ; AC_MSG_RESULT($NSPIRE_CXX)],
	[NSPIRE_CXX="nspire-g++" ; AC_MSG_RESULT([no  (default is $NSPIRE_CXX)])])


AC_CHECK_PROG(has_nspire_cxx, "$NSPIRE_CXX", "yes", "no")
if test  "$has_nspire_cxx" = no ; then
	AC_MSG_ERROR([ no nspire C++ compiler found !
		(You can specify one with the --with-nspire-cxx argument)])
fi

dnl Check for the nspire linker

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


AC_OUTPUT

echo ""
echo "configure ran successful !"
echo "=========================="
echo ""
echo "You can now build the game with :"
echo "	make"
echo ""
