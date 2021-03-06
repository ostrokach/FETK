/* ./src_f77/cgegv.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static complex c_b1 = {0.f,0.f};
static complex c_b2 = {1.f,0.f};
static integer c__1 = 1;
static integer c_n1 = -1;
static real c_b29 = 1.f;

/* Subroutine */ int cgegv_(char *jobvl, char *jobvr, integer *n, complex *a, 
	integer *lda, complex *b, integer *ldb, complex *alpha, complex *beta,
	 complex *vl, integer *ldvl, complex *vr, integer *ldvr, complex *
	work, integer *lwork, real *rwork, integer *info, ftnlen jobvl_len, 
	ftnlen jobvr_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, vl_dim1, vl_offset, vr_dim1, 
	    vr_offset, i__1, i__2, i__3, i__4;
    real r__1, r__2, r__3, r__4;
    complex q__1, q__2;

    /* Builtin functions */
    double r_imag(complex *);

    /* Local variables */
    static integer jc, nb, in, jr, nb1, nb2, nb3, ihi, ilo;
    static real eps;
    static logical ilv;
    static real absb, anrm, bnrm;
    static integer itau;
    static real temp;
    static logical ilvl, ilvr;
    static integer lopt;
    static real anrm1, anrm2, bnrm1, bnrm2, absai, scale, absar, sbeta;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    static integer ileft, iinfo, icols, iwork, irows;
    extern /* Subroutine */ int cggbak_(char *, char *, integer *, integer *, 
	    integer *, real *, real *, integer *, complex *, integer *, 
	    integer *, ftnlen, ftnlen), cggbal_(char *, integer *, complex *, 
	    integer *, complex *, integer *, integer *, integer *, real *, 
	    real *, real *, integer *, ftnlen);
    extern doublereal clange_(char *, integer *, integer *, complex *, 
	    integer *, real *, ftnlen);
    extern /* Subroutine */ int cgghrd_(char *, char *, integer *, integer *, 
	    integer *, complex *, integer *, complex *, integer *, complex *, 
	    integer *, complex *, integer *, integer *, ftnlen, ftnlen);
    static real salfai;
    extern /* Subroutine */ int clascl_(char *, integer *, integer *, real *, 
	    real *, integer *, integer *, complex *, integer *, integer *, 
	    ftnlen), cgeqrf_(integer *, integer *, complex *, integer *, 
	    complex *, complex *, integer *, integer *);
    static real salfar;
    extern doublereal slamch_(char *, ftnlen);
    extern /* Subroutine */ int clacpy_(char *, integer *, integer *, complex 
	    *, integer *, complex *, integer *, ftnlen), claset_(char *, 
	    integer *, integer *, complex *, complex *, complex *, integer *, 
	    ftnlen);
    static real safmin;
    extern /* Subroutine */ int ctgevc_(char *, char *, logical *, integer *, 
	    complex *, integer *, complex *, integer *, complex *, integer *, 
	    complex *, integer *, integer *, integer *, complex *, real *, 
	    integer *, ftnlen, ftnlen);
    static real safmax;
    static char chtemp[1];
    static logical ldumma[1];
    extern /* Subroutine */ int chgeqz_(char *, char *, char *, integer *, 
	    integer *, integer *, complex *, integer *, complex *, integer *, 
	    complex *, complex *, complex *, integer *, complex *, integer *, 
	    complex *, integer *, real *, integer *, ftnlen, ftnlen, ftnlen), 
	    xerbla_(char *, integer *, ftnlen);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    static integer ijobvl, iright;
    static logical ilimit;
    static integer ijobvr;
    extern /* Subroutine */ int cungqr_(integer *, integer *, integer *, 
	    complex *, integer *, complex *, complex *, integer *, integer *);
    static integer lwkmin;
    extern /* Subroutine */ int cunmqr_(char *, char *, integer *, integer *, 
	    integer *, complex *, integer *, complex *, complex *, integer *, 
	    complex *, integer *, integer *, ftnlen, ftnlen);
    static integer irwork, lwkopt;
    static logical lquery;


/*  -- LAPACK driver routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     June 30, 1999 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  This routine is deprecated and has been replaced by routine CGGEV. */

/*  CGEGV computes for a pair of N-by-N complex nonsymmetric matrices A */
/*  and B, the generalized eigenvalues (alpha, beta), and optionally, */
/*  the left and/or right generalized eigenvectors (VL and VR). */

/*  A generalized eigenvalue for a pair of matrices (A,B) is, roughly */
/*  speaking, a scalar w or a ratio  alpha/beta = w, such that  A - w*B */
/*  is singular.  It is usually represented as the pair (alpha,beta), */
/*  as there is a reasonable interpretation for beta=0, and even for */
/*  both being zero.  A good beginning reference is the book, "Matrix */
/*  Computations", by G. Golub & C. van Loan (Johns Hopkins U. Press) */

/*  A right generalized eigenvector corresponding to a generalized */
/*  eigenvalue  w  for a pair of matrices (A,B) is a vector  r  such */
/*  that  (A - w B) r = 0 .  A left generalized eigenvector is a vector */
/*  l such that l**H * (A - w B) = 0, where l**H is the */
/*  conjugate-transpose of l. */

/*  Note: this routine performs "full balancing" on A and B -- see */
/*  "Further Details", below. */

/*  Arguments */
/*  ========= */

/*  JOBVL   (input) CHARACTER*1 */
/*          = 'N':  do not compute the left generalized eigenvectors; */
/*          = 'V':  compute the left generalized eigenvectors. */

/*  JOBVR   (input) CHARACTER*1 */
/*          = 'N':  do not compute the right generalized eigenvectors; */
/*          = 'V':  compute the right generalized eigenvectors. */

/*  N       (input) INTEGER */
/*          The order of the matrices A, B, VL, and VR.  N >= 0. */

/*  A       (input/output) COMPLEX array, dimension (LDA, N) */
/*          On entry, the first of the pair of matrices whose */
/*          generalized eigenvalues and (optionally) generalized */
/*          eigenvectors are to be computed. */
/*          On exit, the contents will have been destroyed.  (For a */
/*          description of the contents of A on exit, see "Further */
/*          Details", below.) */

/*  LDA     (input) INTEGER */
/*          The leading dimension of A.  LDA >= max(1,N). */

/*  B       (input/output) COMPLEX array, dimension (LDB, N) */
/*          On entry, the second of the pair of matrices whose */
/*          generalized eigenvalues and (optionally) generalized */
/*          eigenvectors are to be computed. */
/*          On exit, the contents will have been destroyed.  (For a */
/*          description of the contents of B on exit, see "Further */
/*          Details", below.) */

/*  LDB     (input) INTEGER */
/*          The leading dimension of B.  LDB >= max(1,N). */

/*  ALPHA   (output) COMPLEX array, dimension (N) */
/*  BETA    (output) COMPLEX array, dimension (N) */
/*          On exit, ALPHA(j)/BETA(j), j=1,...,N, will be the */
/*          generalized eigenvalues. */

/*          Note: the quotients ALPHA(j)/BETA(j) may easily over- or */
/*          underflow, and BETA(j) may even be zero.  Thus, the user */
/*          should avoid naively computing the ratio alpha/beta. */
/*          However, ALPHA will be always less than and usually */
/*          comparable with norm(A) in magnitude, and BETA always less */
/*          than and usually comparable with norm(B). */

/*  VL      (output) COMPLEX array, dimension (LDVL,N) */
/*          If JOBVL = 'V', the left generalized eigenvectors.  (See */
/*          "Purpose", above.) */
/*          Each eigenvector will be scaled so the largest component */
/*          will have abs(real part) + abs(imag. part) = 1, *except* */
/*          that for eigenvalues with alpha=beta=0, a zero vector will */
/*          be returned as the corresponding eigenvector. */
/*          Not referenced if JOBVL = 'N'. */

/*  LDVL    (input) INTEGER */
/*          The leading dimension of the matrix VL. LDVL >= 1, and */
/*          if JOBVL = 'V', LDVL >= N. */

/*  VR      (output) COMPLEX array, dimension (LDVR,N) */
/*          If JOBVR = 'V', the right generalized eigenvectors.  (See */
/*          "Purpose", above.) */
/*          Each eigenvector will be scaled so the largest component */
/*          will have abs(real part) + abs(imag. part) = 1, *except* */
/*          that for eigenvalues with alpha=beta=0, a zero vector will */
/*          be returned as the corresponding eigenvector. */
/*          Not referenced if JOBVR = 'N'. */

/*  LDVR    (input) INTEGER */
/*          The leading dimension of the matrix VR. LDVR >= 1, and */
/*          if JOBVR = 'V', LDVR >= N. */

/*  WORK    (workspace/output) COMPLEX array, dimension (LWORK) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK.  LWORK >= max(1,2*N). */
/*          For good performance, LWORK must generally be larger. */
/*          To compute the optimal value of LWORK, call ILAENV to get */
/*          blocksizes (for CGEQRF, CUNMQR, and CUNGQR.)  Then compute: */
/*          NB  -- MAX of the blocksizes for CGEQRF, CUNMQR, and CUNGQR; */
/*          The optimal LWORK is  MAX( 2*N, N*(NB+1) ). */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  RWORK   (workspace/output) REAL array, dimension (8*N) */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value. */
/*          =1,...,N: */
/*                The QZ iteration failed.  No eigenvectors have been */
/*                calculated, but ALPHA(j) and BETA(j) should be */
/*                correct for j=INFO+1,...,N. */
/*          > N:  errors that usually indicate LAPACK problems: */
/*                =N+1: error return from CGGBAL */
/*                =N+2: error return from CGEQRF */
/*                =N+3: error return from CUNMQR */
/*                =N+4: error return from CUNGQR */
/*                =N+5: error return from CGGHRD */
/*                =N+6: error return from CHGEQZ (other than failed */
/*                                               iteration) */
/*                =N+7: error return from CTGEVC */
/*                =N+8: error return from CGGBAK (computing VL) */
/*                =N+9: error return from CGGBAK (computing VR) */
/*                =N+10: error return from CLASCL (various calls) */

/*  Further Details */
/*  =============== */

/*  Balancing */
/*  --------- */

/*  This driver calls CGGBAL to both permute and scale rows and columns */
/*  of A and B.  The permutations PL and PR are chosen so that PL*A*PR */
/*  and PL*B*R will be upper triangular except for the diagonal blocks */
/*  A(i:j,i:j) and B(i:j,i:j), with i and j as close together as */
/*  possible.  The diagonal scaling matrices DL and DR are chosen so */
/*  that the pair  DL*PL*A*PR*DR, DL*PL*B*PR*DR have elements close to */
/*  one (except for the elements that start out zero.) */

/*  After the eigenvalues and eigenvectors of the balanced matrices */
/*  have been computed, CGGBAK transforms the eigenvectors back to what */
/*  they would have been (in perfect arithmetic) if they had not been */
/*  balanced. */

/*  Contents of A and B on Exit */
/*  -------- -- - --- - -- ---- */

/*  If any eigenvectors are computed (either JOBVL='V' or JOBVR='V' or */
/*  both), then on exit the arrays A and B will contain the complex Schur */
/*  form[*] of the "balanced" versions of A and B.  If no eigenvectors */
/*  are computed, then only the diagonal blocks will be correct. */

/*  [*] In other words, upper triangular form. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Statement Functions .. */
/*     .. */
/*     .. Statement Function definitions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Decode the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    --alpha;
    --beta;
    vl_dim1 = *ldvl;
    vl_offset = 1 + vl_dim1;
    vl -= vl_offset;
    vr_dim1 = *ldvr;
    vr_offset = 1 + vr_dim1;
    vr -= vr_offset;
    --work;
    --rwork;

    /* Function Body */
    if (lsame_(jobvl, "N", (ftnlen)1, (ftnlen)1)) {
	ijobvl = 1;
	ilvl = FALSE_;
    } else if (lsame_(jobvl, "V", (ftnlen)1, (ftnlen)1)) {
	ijobvl = 2;
	ilvl = TRUE_;
    } else {
	ijobvl = -1;
	ilvl = FALSE_;
    }

    if (lsame_(jobvr, "N", (ftnlen)1, (ftnlen)1)) {
	ijobvr = 1;
	ilvr = FALSE_;
    } else if (lsame_(jobvr, "V", (ftnlen)1, (ftnlen)1)) {
	ijobvr = 2;
	ilvr = TRUE_;
    } else {
	ijobvr = -1;
	ilvr = FALSE_;
    }
    ilv = ilvl || ilvr;

/*     Test the input arguments */

/* Computing MAX */
    i__1 = *n << 1;
    lwkmin = max(i__1,1);
    lwkopt = lwkmin;
    work[1].r = (real) lwkopt, work[1].i = 0.f;
    lquery = *lwork == -1;
    *info = 0;
    if (ijobvl <= 0) {
	*info = -1;
    } else if (ijobvr <= 0) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*lda < max(1,*n)) {
	*info = -5;
    } else if (*ldb < max(1,*n)) {
	*info = -7;
    } else if (*ldvl < 1 || ilvl && *ldvl < *n) {
	*info = -11;
    } else if (*ldvr < 1 || ilvr && *ldvr < *n) {
	*info = -13;
    } else if (*lwork < lwkmin && ! lquery) {
	*info = -15;
    }

    if (*info == 0) {
	nb1 = ilaenv_(&c__1, "CGEQRF", " ", n, n, &c_n1, &c_n1, (ftnlen)6, (
		ftnlen)1);
	nb2 = ilaenv_(&c__1, "CUNMQR", " ", n, n, n, &c_n1, (ftnlen)6, (
		ftnlen)1);
	nb3 = ilaenv_(&c__1, "CUNGQR", " ", n, n, n, &c_n1, (ftnlen)6, (
		ftnlen)1);
/* Computing MAX */
	i__1 = max(nb1,nb2);
	nb = max(i__1,nb3);
/* Computing MAX */
	i__1 = *n << 1, i__2 = *n * (nb + 1);
	lopt = max(i__1,i__2);
	work[1].r = (real) lopt, work[1].i = 0.f;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CGEGV ", &i__1, (ftnlen)6);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

/*     Get machine constants */

    eps = slamch_("E", (ftnlen)1) * slamch_("B", (ftnlen)1);
    safmin = slamch_("S", (ftnlen)1);
    safmin += safmin;
    safmax = 1.f / safmin;

/*     Scale A */

    anrm = clange_("M", n, n, &a[a_offset], lda, &rwork[1], (ftnlen)1);
    anrm1 = anrm;
    anrm2 = 1.f;
    if (anrm < 1.f) {
	if (safmax * anrm < 1.f) {
	    anrm1 = safmin;
	    anrm2 = safmax * anrm;
	}
    }

    if (anrm > 0.f) {
	clascl_("G", &c_n1, &c_n1, &anrm, &c_b29, n, n, &a[a_offset], lda, &
		iinfo, (ftnlen)1);
	if (iinfo != 0) {
	    *info = *n + 10;
	    return 0;
	}
    }

/*     Scale B */

    bnrm = clange_("M", n, n, &b[b_offset], ldb, &rwork[1], (ftnlen)1);
    bnrm1 = bnrm;
    bnrm2 = 1.f;
    if (bnrm < 1.f) {
	if (safmax * bnrm < 1.f) {
	    bnrm1 = safmin;
	    bnrm2 = safmax * bnrm;
	}
    }

    if (bnrm > 0.f) {
	clascl_("G", &c_n1, &c_n1, &bnrm, &c_b29, n, n, &b[b_offset], ldb, &
		iinfo, (ftnlen)1);
	if (iinfo != 0) {
	    *info = *n + 10;
	    return 0;
	}
    }

/*     Permute the matrix to make it more nearly triangular */
/*     Also "balance" the matrix. */

    ileft = 1;
    iright = *n + 1;
    irwork = iright + *n;
    cggbal_("P", n, &a[a_offset], lda, &b[b_offset], ldb, &ilo, &ihi, &rwork[
	    ileft], &rwork[iright], &rwork[irwork], &iinfo, (ftnlen)1);
    if (iinfo != 0) {
	*info = *n + 1;
	goto L80;
    }

/*     Reduce B to triangular form, and initialize VL and/or VR */

    irows = ihi + 1 - ilo;
    if (ilv) {
	icols = *n + 1 - ilo;
    } else {
	icols = irows;
    }
    itau = 1;
    iwork = itau + irows;
    i__1 = *lwork + 1 - iwork;
    cgeqrf_(&irows, &icols, &b[ilo + ilo * b_dim1], ldb, &work[itau], &work[
	    iwork], &i__1, &iinfo);
    if (iinfo >= 0) {
/* Computing MAX */
	i__3 = iwork;
	i__1 = lwkopt, i__2 = (integer) work[i__3].r + iwork - 1;
	lwkopt = max(i__1,i__2);
    }
    if (iinfo != 0) {
	*info = *n + 2;
	goto L80;
    }

    i__1 = *lwork + 1 - iwork;
    cunmqr_("L", "C", &irows, &icols, &irows, &b[ilo + ilo * b_dim1], ldb, &
	    work[itau], &a[ilo + ilo * a_dim1], lda, &work[iwork], &i__1, &
	    iinfo, (ftnlen)1, (ftnlen)1);
    if (iinfo >= 0) {
/* Computing MAX */
	i__3 = iwork;
	i__1 = lwkopt, i__2 = (integer) work[i__3].r + iwork - 1;
	lwkopt = max(i__1,i__2);
    }
    if (iinfo != 0) {
	*info = *n + 3;
	goto L80;
    }

    if (ilvl) {
	claset_("Full", n, n, &c_b1, &c_b2, &vl[vl_offset], ldvl, (ftnlen)4);
	i__1 = irows - 1;
	i__2 = irows - 1;
	clacpy_("L", &i__1, &i__2, &b[ilo + 1 + ilo * b_dim1], ldb, &vl[ilo + 
		1 + ilo * vl_dim1], ldvl, (ftnlen)1);
	i__1 = *lwork + 1 - iwork;
	cungqr_(&irows, &irows, &irows, &vl[ilo + ilo * vl_dim1], ldvl, &work[
		itau], &work[iwork], &i__1, &iinfo);
	if (iinfo >= 0) {
/* Computing MAX */
	    i__3 = iwork;
	    i__1 = lwkopt, i__2 = (integer) work[i__3].r + iwork - 1;
	    lwkopt = max(i__1,i__2);
	}
	if (iinfo != 0) {
	    *info = *n + 4;
	    goto L80;
	}
    }

    if (ilvr) {
	claset_("Full", n, n, &c_b1, &c_b2, &vr[vr_offset], ldvr, (ftnlen)4);
    }

/*     Reduce to generalized Hessenberg form */

    if (ilv) {

/*        Eigenvectors requested -- work on whole matrix. */

	cgghrd_(jobvl, jobvr, n, &ilo, &ihi, &a[a_offset], lda, &b[b_offset], 
		ldb, &vl[vl_offset], ldvl, &vr[vr_offset], ldvr, &iinfo, (
		ftnlen)1, (ftnlen)1);
    } else {
	cgghrd_("N", "N", &irows, &c__1, &irows, &a[ilo + ilo * a_dim1], lda, 
		&b[ilo + ilo * b_dim1], ldb, &vl[vl_offset], ldvl, &vr[
		vr_offset], ldvr, &iinfo, (ftnlen)1, (ftnlen)1);
    }
    if (iinfo != 0) {
	*info = *n + 5;
	goto L80;
    }

/*     Perform QZ algorithm */

    iwork = itau;
    if (ilv) {
	*(unsigned char *)chtemp = 'S';
    } else {
	*(unsigned char *)chtemp = 'E';
    }
    i__1 = *lwork + 1 - iwork;
    chgeqz_(chtemp, jobvl, jobvr, n, &ilo, &ihi, &a[a_offset], lda, &b[
	    b_offset], ldb, &alpha[1], &beta[1], &vl[vl_offset], ldvl, &vr[
	    vr_offset], ldvr, &work[iwork], &i__1, &rwork[irwork], &iinfo, (
	    ftnlen)1, (ftnlen)1, (ftnlen)1);
    if (iinfo >= 0) {
/* Computing MAX */
	i__3 = iwork;
	i__1 = lwkopt, i__2 = (integer) work[i__3].r + iwork - 1;
	lwkopt = max(i__1,i__2);
    }
    if (iinfo != 0) {
	if (iinfo > 0 && iinfo <= *n) {
	    *info = iinfo;
	} else if (iinfo > *n && iinfo <= *n << 1) {
	    *info = iinfo - *n;
	} else {
	    *info = *n + 6;
	}
	goto L80;
    }

    if (ilv) {

/*        Compute Eigenvectors */

	if (ilvl) {
	    if (ilvr) {
		*(unsigned char *)chtemp = 'B';
	    } else {
		*(unsigned char *)chtemp = 'L';
	    }
	} else {
	    *(unsigned char *)chtemp = 'R';
	}

	ctgevc_(chtemp, "B", ldumma, n, &a[a_offset], lda, &b[b_offset], ldb, 
		&vl[vl_offset], ldvl, &vr[vr_offset], ldvr, n, &in, &work[
		iwork], &rwork[irwork], &iinfo, (ftnlen)1, (ftnlen)1);
	if (iinfo != 0) {
	    *info = *n + 7;
	    goto L80;
	}

/*        Undo balancing on VL and VR, rescale */

	if (ilvl) {
	    cggbak_("P", "L", n, &ilo, &ihi, &rwork[ileft], &rwork[iright], n,
		     &vl[vl_offset], ldvl, &iinfo, (ftnlen)1, (ftnlen)1);
	    if (iinfo != 0) {
		*info = *n + 8;
		goto L80;
	    }
	    i__1 = *n;
	    for (jc = 1; jc <= i__1; ++jc) {
		temp = 0.f;
		i__2 = *n;
		for (jr = 1; jr <= i__2; ++jr) {
/* Computing MAX */
		    i__3 = jr + jc * vl_dim1;
		    r__3 = temp, r__4 = (r__1 = vl[i__3].r, dabs(r__1)) + (
			    r__2 = r_imag(&vl[jr + jc * vl_dim1]), dabs(r__2))
			    ;
		    temp = dmax(r__3,r__4);
/* L10: */
		}
		if (temp < safmin) {
		    goto L30;
		}
		temp = 1.f / temp;
		i__2 = *n;
		for (jr = 1; jr <= i__2; ++jr) {
		    i__3 = jr + jc * vl_dim1;
		    i__4 = jr + jc * vl_dim1;
		    q__1.r = temp * vl[i__4].r, q__1.i = temp * vl[i__4].i;
		    vl[i__3].r = q__1.r, vl[i__3].i = q__1.i;
/* L20: */
		}
L30:
		;
	    }
	}
	if (ilvr) {
	    cggbak_("P", "R", n, &ilo, &ihi, &rwork[ileft], &rwork[iright], n,
		     &vr[vr_offset], ldvr, &iinfo, (ftnlen)1, (ftnlen)1);
	    if (iinfo != 0) {
		*info = *n + 9;
		goto L80;
	    }
	    i__1 = *n;
	    for (jc = 1; jc <= i__1; ++jc) {
		temp = 0.f;
		i__2 = *n;
		for (jr = 1; jr <= i__2; ++jr) {
/* Computing MAX */
		    i__3 = jr + jc * vr_dim1;
		    r__3 = temp, r__4 = (r__1 = vr[i__3].r, dabs(r__1)) + (
			    r__2 = r_imag(&vr[jr + jc * vr_dim1]), dabs(r__2))
			    ;
		    temp = dmax(r__3,r__4);
/* L40: */
		}
		if (temp < safmin) {
		    goto L60;
		}
		temp = 1.f / temp;
		i__2 = *n;
		for (jr = 1; jr <= i__2; ++jr) {
		    i__3 = jr + jc * vr_dim1;
		    i__4 = jr + jc * vr_dim1;
		    q__1.r = temp * vr[i__4].r, q__1.i = temp * vr[i__4].i;
		    vr[i__3].r = q__1.r, vr[i__3].i = q__1.i;
/* L50: */
		}
L60:
		;
	    }
	}

/*        End of eigenvector calculation */

    }

/*     Undo scaling in alpha, beta */

/*     Note: this does not give the alpha and beta for the unscaled */
/*     problem. */

/*     Un-scaling is limited to avoid underflow in alpha and beta */
/*     if they are significant. */

    i__1 = *n;
    for (jc = 1; jc <= i__1; ++jc) {
	i__2 = jc;
	absar = (r__1 = alpha[i__2].r, dabs(r__1));
	absai = (r__1 = r_imag(&alpha[jc]), dabs(r__1));
	i__2 = jc;
	absb = (r__1 = beta[i__2].r, dabs(r__1));
	i__2 = jc;
	salfar = anrm * alpha[i__2].r;
	salfai = anrm * r_imag(&alpha[jc]);
	i__2 = jc;
	sbeta = bnrm * beta[i__2].r;
	ilimit = FALSE_;
	scale = 1.f;

/*        Check for significant underflow in imaginary part of ALPHA */

/* Computing MAX */
	r__1 = safmin, r__2 = eps * absar, r__1 = max(r__1,r__2), r__2 = eps *
		 absb;
	if (dabs(salfai) < safmin && absai >= dmax(r__1,r__2)) {
	    ilimit = TRUE_;
/* Computing MAX */
	    r__1 = safmin, r__2 = anrm2 * absai;
	    scale = safmin / anrm1 / dmax(r__1,r__2);
	}

/*        Check for significant underflow in real part of ALPHA */

/* Computing MAX */
	r__1 = safmin, r__2 = eps * absai, r__1 = max(r__1,r__2), r__2 = eps *
		 absb;
	if (dabs(salfar) < safmin && absar >= dmax(r__1,r__2)) {
	    ilimit = TRUE_;
/* Computing MAX */
/* Computing MAX */
	    r__3 = safmin, r__4 = anrm2 * absar;
	    r__1 = scale, r__2 = safmin / anrm1 / dmax(r__3,r__4);
	    scale = dmax(r__1,r__2);
	}

/*        Check for significant underflow in BETA */

/* Computing MAX */
	r__1 = safmin, r__2 = eps * absar, r__1 = max(r__1,r__2), r__2 = eps *
		 absai;
	if (dabs(sbeta) < safmin && absb >= dmax(r__1,r__2)) {
	    ilimit = TRUE_;
/* Computing MAX */
/* Computing MAX */
	    r__3 = safmin, r__4 = bnrm2 * absb;
	    r__1 = scale, r__2 = safmin / bnrm1 / dmax(r__3,r__4);
	    scale = dmax(r__1,r__2);
	}

/*        Check for possible overflow when limiting scaling */

	if (ilimit) {
/* Computing MAX */
	    r__1 = dabs(salfar), r__2 = dabs(salfai), r__1 = max(r__1,r__2), 
		    r__2 = dabs(sbeta);
	    temp = scale * safmin * dmax(r__1,r__2);
	    if (temp > 1.f) {
		scale /= temp;
	    }
	    if (scale < 1.f) {
		ilimit = FALSE_;
	    }
	}

/*        Recompute un-scaled ALPHA, BETA if necessary. */

	if (ilimit) {
	    i__2 = jc;
	    salfar = scale * alpha[i__2].r * anrm;
	    salfai = scale * r_imag(&alpha[jc]) * anrm;
	    i__2 = jc;
	    q__2.r = scale * beta[i__2].r, q__2.i = scale * beta[i__2].i;
	    q__1.r = bnrm * q__2.r, q__1.i = bnrm * q__2.i;
	    sbeta = q__1.r;
	}
	i__2 = jc;
	q__1.r = salfar, q__1.i = salfai;
	alpha[i__2].r = q__1.r, alpha[i__2].i = q__1.i;
	i__2 = jc;
	beta[i__2].r = sbeta, beta[i__2].i = 0.f;
/* L70: */
    }

L80:
    work[1].r = (real) lwkopt, work[1].i = 0.f;

    return 0;

/*     End of CGEGV */

} /* cgegv_ */

