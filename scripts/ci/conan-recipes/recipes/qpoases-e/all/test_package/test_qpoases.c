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

int main(void) {
    real_t now = qpOASES_getCPUtime();
    if (!isfinite(now) || now < 0.0) {
        fprintf(stderr, "qpOASES_e: invalid timer value=%g\n", (double)now);
        return 1;
    }
    real_t lb = 0.0, ub = 1.0;
    return test_bounds(-2.0, &lb, &ub, 1.0) ||
           test_bounds(2.0, &lb, &ub, 0.0) ||
           test_bounds(-2.0, NULL, &ub, 1.0) ||
           test_bounds(2.0, &lb, NULL, 0.0);
}
