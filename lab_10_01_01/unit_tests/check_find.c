#include "check_find.h"
#include "linked_list.h"
#include <string.h>
#include <stdlib.h>

static int str_comp(const void *pl, const void *pr)
{
    return strcmp((char *) pl, (char *) pr);
}

START_TEST(test_one_elem_in_list)
{
    node_t *head;
    node_alloc(&head);
    head->data = "one";
    head->next = NULL;

    node_t *finded = find(head, "one", str_comp);

    ck_assert_int_eq(finded == head, 1);

    free(head);
}
END_TEST

START_TEST(test_not_finded_elem)
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

    node_t *finded = find(head, "four", str_comp);

    ck_assert_int_eq(finded == NULL, 1);

    node_t *next;
    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}
END_TEST

START_TEST(test_find_elem_in_list)
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

    node_t *finded = find(head, "two", str_comp);

    ck_assert_str_eq((char *)finded->data, "two");

    node_t *next;
    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}
END_TEST

Suite *find_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("find");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_one_elem_in_list);
    tcase_add_test(tc_pos, test_not_finded_elem);
    tcase_add_test(tc_pos, test_find_elem_in_list);
    suite_add_tcase(s, tc_pos);
    return s;
}


