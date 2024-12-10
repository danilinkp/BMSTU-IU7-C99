#include "check_pop_back.h"
#include "linked_list.h"
#include <stdlib.h>

START_TEST(test_pop_empty_list)
{
    node_t *head = NULL;
    void *data = pop_back(&head);

    ck_assert_ptr_eq(data, NULL);
}
END_TEST

START_TEST(test_pop_list_with_one_el)
{
    node_t *head;
    node_alloc(&head);
    head->data = "one";
    head->next = NULL;

    char *data = (char *) pop_back(&head);

    ck_assert_str_eq("one", data);
    ck_assert_ptr_eq(head, NULL);
}
END_TEST

START_TEST(test_pop_list_with_few_elems)
{
    node_t *head = NULL;
    char *strs[] = { "one", "two" };
    for (size_t i = 0; i < 2; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = strs[i];
        node->next = NULL;
        head = push_back(head, node);
    }

    char *data = (char *) pop_back(&head);

    ck_assert_str_eq("two", data);
    ck_assert_ptr_eq(head->next, NULL);

    free(head);
}
END_TEST

START_TEST(test_pop_until_list_empty)
{
    node_t *head = NULL;
    char *strs[] = { "one", "two" };
    for (size_t i = 0; i < 2; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = strs[i];
        node->next = NULL;
        head = push_back(head, node);
    }

    char *data1 = (char *) pop_back(&head);
    ck_assert_str_eq("two", data1);
    ck_assert_ptr_eq(head->next, NULL);

    char *data2 = (char *) pop_back(&head);
    ck_assert_str_eq("one", data2);
    ck_assert_ptr_eq(head, NULL);
}
END_TEST

Suite *pop_back_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("pop_back");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_pop_empty_list);
    tcase_add_test(tc_pos, test_pop_list_with_one_el);
    tcase_add_test(tc_pos, test_pop_list_with_few_elems);
    tcase_add_test(tc_pos, test_pop_until_list_empty);
    suite_add_tcase(s, tc_pos);
    return s;
}
