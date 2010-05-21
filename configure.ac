dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(bsdpm, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_DEFUN([BSDPM_ADD_FUNCTIONALITY], [
	FUNCTIONALITY="${FUNCTIONALITY} $1"
	AC_SUBST([LTLIB$1], ["libbsdpm_$1.la"])
	AC_SUBST([BSDPM_LDFLAGS], ["${BSDPM_LDFLAGS} -L$1"])
	AC_SUBST([BSDPM_LIBS], ["${BSDPM_LIBS} -lbsdpm_$1"])
])

AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC

AC_ARG_ENABLE(nls,
    [  --enable-nls            enable Native Language Support [[default=yes]]],,
    [enable_nls="yes"])
AM_CONDITIONAL(ENABLE_NLS, [test "${enable_nls}" = "yes"])
if test "${enable_nls}" = "yes"; then
GETTEXT_PACKAGE=bsdpm
	AC_SUBST(GETTEXT_PACKAGE)
	AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
	AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])
	AC_SUBST([BSDPM_LIBS], ["${BSDPM_LIBS} ${INTLLIBS}"])
	AC_CONFIG_FILES([po/Makefile.in])
fi

AM_PROG_LIBTOOL

AC_ARG_VAR(PKG_CONFIG_PATH,
	[Paths where to find .pc not at the default location])
	PKG_PROG_PKG_CONFIG()

PKG_CHECK_MODULES(SQLITE3, [sqlite3 >= 3.6])
PKG_CHECK_MODULES(CURL, [libcurl >= 7.20])

BSDPM_ADD_FUNCTIONALITY([core])
AC_CONFIG_FILES([
src/core/bsdpm.pc
src/core/Makefile
])

AC_ARG_WITH(gtk2,
[  --with-gtk2             enable GTK+ graphical interface])
AM_CONDITIONAL(HAVE_GTK2, [test "${with_gtk2}" = "yes"])
if test "${with_gtk2}" = "yes"; then
	PKG_CHECK_MODULES(GTK2, [gtk+-2.0 >= 2.14])
	AC_DEFINE( HAVE_GTK2, 1, [Define if GTK+ graphical interface will be supported])
	BSDPM_ADD_FUNCTIONALITY([gtk2])
	AC_CONFIG_FILES([src/gtk2/Makefile])
fi

AC_ARG_WITH(qt4,
[  --with-qt4              enable QT4 graphical interface])
AM_CONDITIONAL(HAVE_QT4, [test "${with_qt4}" = "yes"])
if test "${with_qt4}" = "yes"; then
##	PKG_CHECK_MODULES(QT4, [qt4 >= 4.6])
	AC_DEFINE( HAVE_QT4, 1, [Define if QT4 graphical interface will be supported])
##	BSDPM_ADD_FUNCTIONALITY([qt4])
##	AC_CONFIG_FILES([src/qt4/Makefile])
fi

AC_CONFIG_FILES([
src/Makefile
Makefile
])

AC_OUTPUT
