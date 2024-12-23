#include "check_filter_squares.h"
#include "check_left_shift.h"
#include <stdlib.h>

int main(void)
{
    int no_failed;
    Suite *s;
    SRunner *runner;

    s = filter_square_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    s = left_shift_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}