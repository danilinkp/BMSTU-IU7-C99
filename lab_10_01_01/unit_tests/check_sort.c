#include "check_sort.h"
#include "linked_list.h"
#include <stdlib.h>

static int str_comp(const void *pl, const void *pr)
{
    return strcmp((char *) pl, (char *) pr);
}

START_TEST(test_sorted_list)
{
    node_t *head = NULL;
    char *strs[] = { "a", "b", "c", "d" };
    for (size_t i = 0; i < 4; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = strs[i];
        node->next = NULL;
        head = push_back(head, node);
    }

    node_t *result = NULL;
    char *result_strs[] = { "a", "b", "c", "d" };
    for (size_t i = 0; i < 4; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = result_strs[i];
        node->next = NULL;
        result = push_back(result, node);
    }

    node_t *sorted = sort(head, str_comp);

    node_t *curr_1 = sorted;
    node_t *curr_2 = result;
    while (curr_1 && curr_2)
    {
        ck_assert_str_eq((char *) curr_1->data, (char *) curr_2->data);
        curr_1 = curr_1->next;
        curr_2 = curr_2->next;
    }

    node_t *next;
    for (; sorted; sorted = next)
    {
        next = sorted->next;
        free(sorted);
    }

    node_t *next_res;
    for (; result; result = next_res)
    {
        next_res = result->next;
        free(result);
    }
}
END_TEST

START_TEST(test_reversed_sorted_list)
{
    node_t *head = NULL;
    char *strs[] = { "d", "c", "b", "a" };
    for (size_t i = 0; i < 4; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = strs[i];
        node->next = NULL;
        head = push_back(head, node);
    }

    node_t *result = NULL;
    char *result_strs[] = { "a", "b", "c", "d" };
    for (size_t i = 0; i < 4; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = result_strs[i];
        node->next = NULL;
        result = push_back(result, node);
    }

    node_t *sorted = sort(head, str_comp);

    node_t *curr_1 = sorted;
    node_t *curr_2 = result;
    while (curr_1 && curr_2)
    {
        ck_assert_str_eq((char *) curr_1->data, (char *) curr_2->data);
        curr_1 = curr_1->next;
        curr_2 = curr_2->next;
    }

    node_t *next;
    for (; sorted; sorted = next)
    {
        next = sorted->next;
        free(sorted);
    }

    node_t *next_res;
    for (; result; result = next_res)
    {
        next_res = result->next;
        free(result);
    }
}

END_TEST

START_TEST(test_list_with_same_elems)
{
    node_t *head = NULL;
    char *strs[] = { "b", "b", "b", "b" };
    for (size_t i = 0; i < 4; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = strs[i];
        node->next = NULL;
        head = push_back(head, node);
    }

    node_t *result = NULL;
    char *result_strs[] = { "b", "b", "b", "b" };
    for (size_t i = 0; i < 4; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = result_strs[i];
        node->next = NULL;
        result = push_back(result, node);
    }

    node_t *sorted = sort(head, str_comp);

    node_t *curr_1 = sorted;
    node_t *curr_2 = result;
    while (curr_1 && curr_2)
    {
        ck_assert_str_eq((char *) curr_1->data, (char *) curr_2->data);
        curr_1 = curr_1->next;
        curr_2 = curr_2->next;
    }

    node_t *next;
    for (; sorted; sorted = next)
    {
        next = sorted->next;
        free(sorted);
    }

    node_t *next_res;
    for (; result; result = next_res)
    {
        next_res = result->next;
        free(result);
    }
}
END_TEST

START_TEST(test_list_with_one_elem)
{
    node_t *head = NULL;
    node_alloc(&head);
    head->data = "a";
    head->next = NULL;

    node_t *result = NULL;
    node_alloc(&result);
    result->data = "a";
    result->next = NULL;

    node_t *sorted = sort(head, str_comp);

    ck_assert_str_eq((char *) head->data, (char *) result->data);

    free(sorted);
    free(result);
}
END_TEST

START_TEST(test_list_with_random_order)
{
    node_t *head = NULL;
    char *strs[] = { "b", "c", "a", "d" };
    for (size_t i = 0; i < 4; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = strs[i];
        node->next = NULL;
        head = push_back(head, node);
    }

    node_t *result = NULL;
    char *result_strs[] = { "a", "b", "c", "d" };
    for (size_t i = 0; i < 4; i++)
    {
        node_t *node;
        node_alloc(&node);
        node->data = result_strs[i];
        node->next = NULL;
        result = push_back(result, node);
    }

    node_t *sorted = sort(head, str_comp);

    node_t *curr_1 = sorted;
    node_t *curr_2 = result;
    while (curr_1 && curr_2)
    {
        ck_assert_str_eq((char *) curr_1->data, (char *) curr_2->data);
        curr_1 = curr_1->next;
        curr_2 = curr_2->next;
    }

    node_t *next;
    for (; sorted; sorted = next)
    {
        next = sorted->next;
        free(sorted);
    }

    node_t *next_res;
    for (; result; result = next_res)
    {
        next_res = result->next;
        free(result);
    }
}
END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sort");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sorted_list);
    tcase_add_test(tc_pos, test_reversed_sorted_list);
    tcase_add_test(tc_pos, test_list_with_same_elems);
    tcase_add_test(tc_pos, test_list_with_one_elem);
    tcase_add_test(tc_pos, test_list_with_random_order);
    suite_add_tcase(s, tc_pos);
    return s;
}
