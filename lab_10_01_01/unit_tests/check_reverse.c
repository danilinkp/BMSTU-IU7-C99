#include "check_reverse.h"
#include "linked_list.h"
#include <stdlib.h>

START_TEST(test_list_with_one_elem)
{
    node_t *head;
    node_alloc(&head);
    head->data = "one";
    head->next = NULL;

    node_t *result;
    node_alloc(&result);
    result->data = "one";
    result->next = NULL;

    node_t *reversed = reverse(head);

    ck_assert_str_eq(reversed->data, result->data);
    free(reversed);
    free(result);
}
END_TEST

START_TEST(test_reverse_list_with_diff_elems)
{
    node_t *head = NULL;
    char *strs[] = { "one", "two", "three" };
    for (size_t i = 0; i < 3; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = strs[i];
        node->next = NULL;
        head = push_back(head, node);
    }

    node_t *result = NULL;
    char *result_strs[] = { "three", "two", "one" };
    for (size_t i = 0; i < 3; i++)
    {
        node_t *node_res = NULL;
        node_alloc(&node_res);
        node_res->data = result_strs[i];
        node_res->next = NULL;
        result = push_back(result, node_res);
    }

    node_t *reversed = reverse(head);

    node_t *curr_1 = reversed;
    node_t *curr_2 = result;
    while (curr_1 && curr_2)
    {
        ck_assert_str_eq(curr_1->data, curr_2->data);
        curr_1 = curr_1->next;
        curr_2 = curr_2->next;
    }

    node_t *next;
    for (; reversed; reversed = next)
    {
        next = reversed->next;
        free(reversed);
    }

    node_t *next_res;
    for (; result; result = next_res)
    {
        next_res = result->next;
        free(result);
    }
}
END_TEST

START_TEST(test_reverse_list_with_same_elems)
{
    node_t *head = NULL;
    char *strs[] = { "two", "two", "two" };
    for (size_t i = 0; i < 3; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = strs[i];
        node->next = NULL;
        head = push_back(head, node);
    }

    node_t *result = NULL;
    char *result_strs[] = { "two", "two", "two" };
    for (size_t i = 0; i < 3; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = result_strs[i];
        node->next = NULL;
        result = push_back(result, node);
    }

    node_t *reversed = reverse(head);

    node_t *curr_1 = reversed;
    node_t *curr_2 = result;
    while (curr_1 && curr_2)
    {
        ck_assert_str_eq((char *) curr_1->data, (char *) curr_2->data);
        curr_1 = curr_1->next;
        curr_2 = curr_2->next;
    }

    node_t *next;
    for (; reversed; reversed = next)
    {
        next = reversed->next;
        free(reversed);
    }

    node_t *next_res;
    for (; result; result = next_res)
    {
        next_res = result->next;
        free(result);
    }
}
END_TEST

Suite *reverse_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("reverse");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_list_with_one_elem);
    tcase_add_test(tc_pos, test_reverse_list_with_diff_elems);
    tcase_add_test(tc_pos, test_reverse_list_with_same_elems);
    suite_add_tcase(s, tc_pos);
    return s;
}
