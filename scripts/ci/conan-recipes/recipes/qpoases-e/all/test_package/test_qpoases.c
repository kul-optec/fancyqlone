#include <qpOASES_e.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static int test_bounds(real_t g, real_t *lb, real_t *ub, real_t expected) {
    real_t H = 1.0, x = 0.0;
    int nWSR = 10;
    QProblemB *qp = QProblemB_createMemory(1);
    if (!qp) return 1;
    QProblemBCON(qp, 1, HST_POSDEF);
    returnValue status = QProblemB_init(qp, &H, &g, lb, ub, &nWSR, NULL);
    QProblemB_getPrimalSolution(qp, &x);
    int valid_bounds = isfinite(qp->lb[0]) && isfinite(qp->ub[0]);
    free(qp);
    if (status != SUCCESSFUL_RETURN || !valid_bounds ||
        !isfinite(x) || fabs(x - expected) > 1e-8) {
        fprintf(stderr, "qpOASES_e: status=%d, x=%g\n", status, (double)x);
        return 1;
    }
    return 0;
}

static int test_matrix_products(void) {
    real_t values[] = {1.0, 2.0, 3.0, 4.0};
    real_t x[] = {2.0, 3.0, 5.0, 7.0};
    const real_t expected[] = {8.0, 18.0, 19.0, 43.0};
    const real_t expected_trans[] = {11.0, 16.0, 26.0, 38.0};
    real_t storage[4];
    DenseMatrix matrix = {.val = storage};
    DenseMatrixCON(&matrix, 2, 2, 2, values);
    /* Exercise both GEMV (one RHS) and GEMM (multiple RHS). */
    for (int nrhs = 1; nrhs <= 2; ++nrhs) {
        real_t y[4] = {0}, yt[4] = {0};
        if (DenseMatrix_times(&matrix, nrhs, 1.0, x, 2, 0.0, y, 2) != SUCCESSFUL_RETURN ||
            DenseMatrix_transTimes(&matrix, nrhs, 1.0, x, 2, 0.0, yt, 2) != SUCCESSFUL_RETURN)
            return 1;
        for (int i = 0; i < 2 * nrhs; ++i) {
            if (fabs(y[i] - expected[i]) > 1e-8 ||
                fabs(yt[i] - expected_trans[i]) > 1e-8) {
                fprintf(stderr, "qpOASES_e: incorrect matrix product (nrhs=%d)\n", nrhs);
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    real_t now = qpOASES_getCPUtime();
    if (!isfinite(now) || now < 0.0) {
        fprintf(stderr, "qpOASES_e: invalid timer value=%g\n", (double)now);
        return 1;
    }
    real_t lb = 0.0, ub = 1.0;
    return test_matrix_products() ||
           test_bounds(-2.0, &lb, &ub, 1.0) ||
           test_bounds(2.0, &lb, &ub, 0.0) ||
           test_bounds(-2.0, NULL, &ub, 1.0) ||
           test_bounds(2.0, &lb, NULL, 0.0);
}
