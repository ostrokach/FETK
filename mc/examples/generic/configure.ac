dnl ##########################################################################
dnl MC = < Manifold Code >
dnl Copyright (C) 1994-- Michael Holst 
dnl
dnl This library is free software; you can redistribute it and/or 
dnl modify it under the terms of the GNU Lesser General Public 
dnl License as published by the Free Software Foundation; either 
dnl version 2.1 of the License, or (at your option) any later version. 
dnl
dnl This library is distributed in the hope that it will be useful, 
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of             
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
dnl Lesser General Public License for more details. 
dnl 
dnl You should have received a copy of the GNU Lesser General Public 
dnl License along with this library; if not, write to the Free Software  
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   
dnl
dnl rcsid="INTENTIONALLY LEFT BLANK"
dnl ##########################################################################

dnl ##########################################################################
dnl File:    configure.ac
dnl
dnl Purpose: configure.ac script for a typical MC application.
dnl
dnl Author:  Michael Holst
dnl ##########################################################################

dnl 0. autoconf initialization
AC_INIT(mcapp, 1.0, mholst@math.ucsd.edu)
AC_CONFIG_SRCDIR(main.c)
AC_CONFIG_AUX_DIR(config)
AC_PREFIX_DEFAULT(${HOME})
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

dnl 1. automake initialization (uncomment only if rebuilding Makefile.in's)
AM_INIT_AUTOMAKE([foreign])
FETK_VERSION="1:0:0"
AC_SUBST(FETK_VERSION)
AM_MAINTAINER_MODE

dnl 2. checks for programs
AC_LANG_C
AC_PROG_CC
AC_PROG_CPP

dnl 3. checks for libraries
AC_CHECK_LIB(m,pow,[math_lib="-lm"],[math_lib=""])
AC_SUBST(math_lib)
AC_CHECK_LIB(iberty,strerrno,[liberty_lib="-liberty"],[liberty_lib=""])
AC_SUBST(liberty_lib)
nsl_lib="";
AC_CHECK_FUNC(gethostbyname,[try_nsl=""],[try_nsl="yes"])
if test -n "${try_nsl}"; then
    AC_CHECK_LIB(nsl,gethostbyname,[nsl_lib="-lnsl"],[nsl_lib=""])
fi
AC_SUBST(nsl_lib)
socket_lib="";
AC_CHECK_FUNC(connect,[try_socket=""],[try_socket="yes"])
if test -n "${try_socket}"; then
    AC_CHECK_LIB(socket,connect,[socket_lib="-lsocket"],[socket_lib=""])
fi
AC_SUBST(socket_lib)
thread_lib="";
AC_CHECK_FUNC(thr_create,[try_thread=""],[try_thread="yes"])
if test -n "${try_thread}"; then
    AC_CHECK_LIB(thread,thr_create,[thread_lib="-lthread"],[thread_lib=""])
fi
AC_SUBST(thread_lib)

dnl 4. checks for header files
dnl 5. checks for typedefs
dnl 6. checks for structures
dnl 7. checks for compiler characteristics
dnl 8. checks for library functions
dnl 9. checks for system services
dnl 10. checks for anything else

dnl # ------------------------------------------------
dnl # CHECK WHETHER TO DISABLE CPU-VENDOR-HOST TRIPLET
dnl # ------------------------------------------------
fetk_cpu_vendor_os="";
AC_MSG_CHECKING([whether you want to disable the CPU-VENDOR-OS install triplet])
AC_ARG_ENABLE(triplet,
    [  --disable-triplet       disable CPU-VENDOR-OS install triplet [[default=no]]],
    [ triplet_kill="yes"],
    [ triplet_kill="" ]
)
if test "${triplet_kill}" = yes; then
    AC_MSG_RESULT([yes])
    fetk_cpu_vendor_os="";
else
    AC_MSG_RESULT([no])
    fetk_cpu_vendor_os="${host_cpu}-${host_vendor}-${host_os}";
fi
AC_SUBST(fetk_cpu_vendor_os)

dnl # ---------------------------
dnl # HANDLE THE READLINE LIBRARY
dnl # ---------------------------
rl_lib="";
AC_MSG_CHECKING([whether your environment defines FETK_RL_LIBRARY])
if test -n "${FETK_RL_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    rl_lib_path="-L${FETK_RL_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    rl_lib_path="";
fi
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${rl_lib_path};
AC_CHECK_LIB(ncurses,tgetnum,
    [ncurses_lib="-lncurses"],
    [ncurses_lib=""],
    [${math_lib}])
AC_CHECK_LIB(readline,readline,
    [rl_use="yes";rl_lib="${rl_lib_path}-lreadline ${ncurses_lib}"],
    [rl_use="";rl_lib=""],
    [${rl_lib_path} ${ncurses_lib} ${math_lib}])
if test -n "${rl_use}"; then
    AC_CHECK_LIB(readline,add_history,
        [rl_use="yes";rl_lib="${rl_lib_path}-lreadline ${ncurses_lib}"],
        [rl_use="";rl_lib=""],
        [${rl_lib_path} ${ncurses_lib} ${math_lib}])
fi
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(rl_lib)

dnl # ----------------------
dnl # HANDLE THE MPI LIBRARY
dnl # ----------------------
mpi_lib="";
AC_MSG_CHECKING([whether your environment defines FETK_MPI_LIBRARY])
if test -n "${FETK_MPI_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    mpi_lib_path="-L${FETK_MPI_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    mpi_lib_path="";
fi
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${mpi_lib_path};
mpi_use="";
AC_CHECK_LIB(mpi,main,
    [mpi_use="yes";mpi_lib="${mpi_lib_path}-lmpi"],
    [mpi_use="";mpi_lib=""],${mpi_lib_path})
if test -z "${mpi_use}"; then
    AC_CHECK_LIB(mpich,main,
        [mpi_use="yes";mpi_lib="${mpi_lib_path}-lmpich"],
        [mpi_use="";mpi_lib=""],${mpi_lib_path})
fi
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(mpi_lib)

dnl # -----------------------
dnl # HANDLE THE FETK LIBRARY
dnl # -----------------------
fetk_lib="";
AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
if test -n "${FETK_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    fetk_lib="${FETK_LIBRARY}";
else
    AC_MSG_RESULT([no])
    fetk_lib="${HOME}/lib/${fetk_cpu_vendor_os}"
fi
AC_SUBST(fetk_lib)
fetk_inc="";
AC_MSG_CHECKING([whether your environment defines FETK_INCLUDE])
if test -n "${FETK_INCLUDE}"; then
    AC_MSG_RESULT([yes])
    fetk_inc="${FETK_INCLUDE}";
else
    AC_MSG_RESULT([no])
    fetk_inc="${HOME}/include";
fi
AC_SUBST(fetk_inc)

dnl # -----------------------
dnl # HANDLE THE VF2C LIBRARY
dnl # -----------------------
vf2c_lib="";
AC_MSG_CHECKING([whether your environment defines FETK_VF2C_LIBRARY])
if test -n "${FETK_VF2C_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    vf2c_lib_path="-L${FETK_VF2C_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
    if test -n "${FETK_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        vf2c_lib_path="-L${FETK_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        vf2c_lib_path="-L${HOME}/lib ";
    fi
fi
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${vf2c_lib_path};
vf2c_use="";
AC_CHECK_LIB(vf2c,d_abs,
    [vf2c_use="yes";vf2c_lib="${vf2c_lib_path}-lvf2c"],
    [vf2c_use="";vf2c_lib=""],
    [${vf2c_lib_path}-lvf2c ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(vf2c_lib)

dnl # -----------------------
dnl # HANDLE THE BLAS LIBRARY
dnl # -----------------------
blas_lib="";
AC_MSG_CHECKING([whether your environment defines FETK_BLAS_LIBRARY])
if test -n "${FETK_BLAS_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    blas_lib_path="-L${FETK_BLAS_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
    if test -n "${FETK_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        blas_lib_path="-L${FETK_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        blas_lib_path="-L${HOME}/lib ";
    fi
fi
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${blas_lib_path};
blas_use="";
AC_CHECK_LIB(blas,dscal_,
    [blas_use="yes";blas_lib="${blas_lib_path}-lblas"],
    [blas_use="";blas_lib=""],
    [${blas_lib_path}-lblas ${vf2c_lib} ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(blas_lib)

dnl # --------------------------
dnl # HANDLE THE AMD LIBRARY
dnl # --------------------------
amd_lib="";
AC_MSG_CHECKING([whether your environment defines FETK_AMD_LIBRARY])
if test -n "${FETK_AMD_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    amd_lib_path="-L${FETK_AMD_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
    if test -n "${FETK_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        amd_lib_path="-L${FETK_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        amd_lib_path="-L${HOME}/lib ";
    fi
fi
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${amd_lib_path};
amd_use="";
AC_CHECK_LIB(amd,amd_order,
    [amd_use="yes";amd_lib="${amd_lib_path}-lamd"],
    [amd_use="";amd_lib=""],
    [${amd_lib_path}-lamd ${blas_lib} ${vf2c_lib} ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(amd_lib)

dnl # --------------------------
dnl # HANDLE THE UMFPACK LIBRARY
dnl # --------------------------
umfpack_lib="";
AC_MSG_CHECKING([whether your environment defines FETK_UMFPACK_LIBRARY])
if test -n "${FETK_UMFPACK_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    umfpack_lib_path="-L${FETK_UMFPACK_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
    if test -n "${FETK_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        umfpack_lib_path="-L${FETK_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        umfpack_lib_path="-L${HOME}/lib ";
    fi
fi
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${umfpack_lib_path};
umfpack_use="";
AC_CHECK_LIB(umfpack,umfpack_di_free_numeric,
    [umfpack_use="yes";umfpack_lib="${umfpack_lib_path}-lumfpack"],
    [umfpack_use="";umfpack_lib=""],
    [${umfpack_lib_path}-lumfpack ${amd_lib} ${blas_lib} ${vf2c_lib} ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(umfpack_lib)

dnl # --------------------------
dnl # HANDLE THE SUPERLU LIBRARY
dnl # --------------------------
superlu_lib="";
AC_MSG_CHECKING([whether your environment defines FETK_SUPERLU_LIBRARY])
if test -n "${FETK_SUPERLU_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    superlu_lib_path="-L${FETK_SUPERLU_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
    if test -n "${FETK_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        superlu_lib_path="-L${FETK_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        superlu_lib_path="-L${HOME}/lib ";
    fi
fi
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${superlu_lib_path};
superlu_use="";
AC_CHECK_LIB(superlu,Destroy_SuperMatrix_Store,
    [superlu_use="yes";superlu_lib="${superlu_lib_path}-lsuperlu"],
    [superlu_use="";superlu_lib=""],
    [${superlu_lib_path}-lsuperlu ${amd_lib} ${blas_lib} ${vf2c_lib} ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(superlu_lib)

AC_MSG_RESULT([----------- begin processing APP configure options ---------])

dnl # --------------------------------
dnl # HANDLE ANSI/PEDANTIC COMPILATION
dnl # --------------------------------
AC_MSG_CHECKING([whether you want pedantic ANSI compilation])
AC_ARG_ENABLE(pansi,
    [  --enable-pansi          enable pedantic ANSI compilation],
    [ pansi_use="yes" ],
    [ pansi_use=""    ]
)
if test -z "${pansi_use}"; then
    AC_MSG_RESULT([no])
    wall=""
    wall_pedantic=""
    wall_pedantic_ansi=""
    pedantic_ansi=""
else
    AC_MSG_RESULT([yes])
    wall="-Wall"
    wall_pedantic="-Wall -pedantic"
    wall_pedantic_ansi="-Wall -pedantic -ansi"
    pedantic_ansi="-pedantic -ansi"
fi
AC_SUBST(wall)
AC_SUBST(wall_pedantic)
AC_SUBST(wall_pedantic_ansi)
AC_SUBST(pedantic_ansi)

dnl # ----------------
dnl # HANDLE PROFILING
dnl # ----------------
AC_MSG_CHECKING([whether you want profiling])
AC_ARG_ENABLE(gprof,
    [  --enable-gprof          enable gprof profiling [default=no]],
    [ gprof_use="yes" ],
    [ gprof_use=""    ]
)
if test -z "${gprof_use}"; then
    AC_MSG_RESULT([no])
    profile=""
    profile_lib=""
else
    AC_MSG_RESULT([yes])
    profile="-pg"
    profile_lib="-pg"
fi
AC_SUBST(profile)
AC_SUBST(profile_lib)

dnl # ---------------------------------
dnl # HANDLE THE ELECTRIC FENCE LIBRARY
dnl # ---------------------------------
AC_MSG_CHECKING([whether you want ElectricFence])
AC_ARG_ENABLE(efence,
    [  --enable-efence         enable ElectricFence malloc lib [default=no]],
    [ efence_use="yes" ],
    [ efence_use=""    ]
)
if test -z "${efence_use}"; then
    AC_MSG_RESULT([no])
    zfence="";
    zfence_lib="";
else
    AC_MSG_RESULT([yes ...poking around for it])
    AC_CHECK_LIB(efence,main,
        [efence_use="yes";zfence="zfence";zfence_lib="-lefence"],
        [efence_use="";zfence="";zfence_lib=""])
fi
AC_SUBST(zfence)
AC_SUBST(zfence_lib)

dnl # -----------------------------
dnl # HANDLE BUILDING LIBRARY TESTS
dnl # -----------------------------
AC_MSG_CHECKING([whether you want to build library test programs])
AC_ARG_ENABLE(vtst,
    [  --enable-vtst           enable building of library tests [default=no]],
    [ vtst="tests";AC_MSG_RESULT([yes]) ],
    [ vtst="";AC_MSG_RESULT([no]) ]
)
AC_SUBST(vtst)

AC_MSG_RESULT([------------ end processing APP configure options ----------])

AC_MSG_RESULT([---------- begin configuring for MALOC linkage ------------])

dnl # ------------------------
dnl # HANDLE THE MALOC LIBRARY
dnl # ------------------------

dnl # MALOC header location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_INCLUDE])
if test -n "${FETK_INCLUDE}"; then
    AC_MSG_RESULT([yes])
    maloc_inc_path="-I${FETK_INCLUDE} ";
else
    AC_MSG_RESULT([no])
    maloc_inc_path="-I${HOME}/include ";
fi

dnl # MALOC library location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
if test -n "${FETK_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    maloc_lib_path="-L${FETK_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    maloc_lib_path="-L${HOME}/lib ";
fi

dnl # Setup temp LDFLAGS and look for MALOC library/header
LDFLAGS_SAVE=${LDFLAGS};
CPPFLAGS_SAVE=${CPPFLAGS};
LDFLAGS=${maloc_lib_path};
CPPFLAGS=${maloc_inc_path};
maloc_found="";
AC_CHECK_HEADER(maloc/maloc.h,
    [maloc_found="yes";maloc_inc="${maloc_inc_path}"],
    [maloc_found="";maloc_inc=""])
if test -n "${maloc_found}"; then
    AC_CHECK_LIB(maloc,maloc_link,
        [maloc_found="yes";maloc_lib="${maloc_lib_path}-lmaloc"],
        [maloc_found="";maloc_lib=""],
        [${maloc_lib_path}-lmaloc ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])
fi
if test -z "${maloc_found}"; then
    AC_MSG_ERROR([MALOC libraries OR headers missing ...EXITING ON ERROR])
else
    AC_MSG_RESULT([MALOC libraries AND headers were found ...rocking on...])
fi

dnl # Return LDFLAGS and CPPFLAGS to normal
LDFLAGS=${LDFLAGS_SAVE};
CPPFLAGS=${CPPFLAGS_SAVE};
AC_SUBST(maloc_lib)
AC_SUBST(maloc_inc)

dnl # Check whether MALOC actually needs the READLINE library
AC_CHECK_LIB(maloc,maloc_needs_rl,
    [rl_use="yes"],
    [rl_use=""],
    [${maloc_lib} ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])

dnl # Check whether MALOC actually needs the MPI library
AC_CHECK_LIB(maloc,maloc_needs_mpi,
    [mpi_use="yes"],
    [mpi_use=""],
    [${maloc_lib} ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])

AC_MSG_RESULT([---------- end configuring for MALOC linkage --------------])

AC_MSG_RESULT([---------- begin configuring for PUNC linkage ------------])

dnl # PUNC header location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_INCLUDE])
if test -n "${FETK_INCLUDE}"; then
    AC_MSG_RESULT([yes])
    punc_inc_path="-I${FETK_INCLUDE} ";
else
    AC_MSG_RESULT([no])
    punc_inc_path="-I${HOME}/include ";
fi

dnl # PUNC library location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
if test -n "${FETK_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    punc_lib_path="-L${FETK_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    punc_lib_path="-L${HOME}/lib ";
fi

dnl # Setup temp LDFLAGS and look for PUNC library/header
LDFLAGS_SAVE=${LDFLAGS};
CPPFLAGS_SAVE=${CPPFLAGS};
LDFLAGS=${punc_lib_path};
CPPFLAGS=${punc_inc_path};
punc_found="";
AC_CHECK_HEADER(punc/punc.h,
    [punc_found="yes";punc_inc="${punc_inc_path}"],
    [punc_found="";punc_inc=""])
if test -n "${punc_found}"; then
    AC_CHECK_LIB(punc,punc_link,
        [punc_found="yes";punc_lib="${punc_lib_path}-lpunc"],
        [punc_found="";punc_lib=""],
        [${punc_lib_path}-lpunc ${maloc_lib} ${umfpack_lib} ${superlu_lib} ${amd_lib} ${blas_lib} ${vf2c_lib} ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])
fi
if test -z "${punc_found}"; then
    AC_MSG_ERROR([PUNC libraries OR headers missing ...EXITING ON ERROR])
else
    AC_MSG_RESULT([PUNC libraries AND headers were found ...rocking on...])
fi

dnl # Return LDFLAGS and CPPFLAGS to normal
LDFLAGS=${LDFLAGS_SAVE};
CPPFLAGS=${CPPFLAGS_SAVE};
AC_SUBST(punc_lib)
AC_SUBST(punc_inc)

AC_MSG_RESULT([---------- end configuring for PUNC linkage --------------])

AC_MSG_RESULT([---------- begin configuring for MC linkage ---------------])

dnl # -----------------------
dnl # HANDLE THE MC LIBRARIES
dnl # -----------------------
dnl # MC header location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_INCLUDE])
if test -n "${FETK_INCLUDE}"; then
    AC_MSG_RESULT([yes])
    mc_inc_path="-I${FETK_INCLUDE} ";
else
    AC_MSG_RESULT([no])
    mc_inc_path="-I${HOME}/include ";
fi

dnl # MC library location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
if test -n "${FETK_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    mc_lib_path="-L${FETK_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    mc_lib_path="-L${HOME}/lib ";
fi

dnl # Setup temp LDFLAGS and look for MC library/header
LDFLAGS_SAVE=${LDFLAGS};
CPPFLAGS_SAVE=${CPPFLAGS};
LDFLAGS=${mc_lib_path};
CPPFLAGS=${mc_inc_path};
mc_found="";
AC_CHECK_HEADER(mc/mc.h,
    [mc_found="yes";mc_inc="${mc_inc_path}"],
    [mc_found="";mc_inc=""])
if test -n "${mc_found}"; then
    AC_CHECK_LIB(mc,mc_link,
        [mc_found="yes";mc_lib="${mc_lib_path}-lmc"],
        [mc_found="";mc_lib=""],
        [${mc_lib_path}-lmc ${punc_lib} ${maloc_lib} ${umfpack_lib} ${superlu_lib} ${amd_lib} ${blas_lib} ${vf2c_lib} ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])
fi
if test -z "${mc_found}"; then
    AC_MSG_ERROR([MC libraries OR headers missing ...EXITING ON ERROR])
else
    AC_MSG_RESULT([MC libraries AND headers were found ...rocking on...])
fi

dnl # Return LDFLAGS and CPPFLAGS to normal
LDFLAGS=${LDFLAGS_SAVE};
CPPFLAGS=${CPPFLAGS_SAVE};
AC_SUBST(mc_lib)
AC_SUBST(mc_inc)

AC_MSG_RESULT([---------- end configuring for MC linkage -----------------])

dnl 11. generate the makefiles
AC_OUTPUT([
    Makefile
])

