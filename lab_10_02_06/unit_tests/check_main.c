#include "check_matrix_mul.h"
#include "check_matrix_add.h"
#include "check_matrix_lin.h"

#include <stdlib.h>

int main (void)
{
    int no_failed;
    Suite *s;
    SRunner *runner;

    s = matrix_add_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    s = matrix_mul_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    s = matrix_lin_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

