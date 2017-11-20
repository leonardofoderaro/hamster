
AC_INIT([hamster], [0.1], [stratrack79@gmail.com])

AM_INIT_AUTOMAKE

AC_PROG_CC

PKG_CHECK_MODULES([libzmq], [libzmq])
CFLAGS="${libzmq_CFLAGS} ${CFLAGS}"
LIBS="${libzmq_LIBS} ${LIBS}"

AC_CHECK_LIB([fcgi], [FCGX_Accept],,
		AC_MSG_ERROR(libfcgi not found))

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
