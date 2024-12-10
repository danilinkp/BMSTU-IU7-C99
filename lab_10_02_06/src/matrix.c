#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void free_matrix(matrix_t *matrix)
{
    if (matrix->head)
        free_list(matrix->head);
}

int matrix_elem_add(matrix_t *matrix, int elem, size_t i, size_t j)
{
    if (matrix->head)
    {
        node_t *current = matrix->head;
        node_t *prev = NULL;
        while (current)
        {
            if (current->row == i && current->col == j)
            {
                current->data += elem;
                if (current->data == 0)
                {
                    if (prev)
                        prev->next = current->next;
                    else
                        matrix->head = current->next;
                    free(current);
                }
                return EXIT_SUCCESS;
            }
            prev = current;
            current = current->next;
        }
    }
    node_t *tmp_node = NULL;
    int rc = node_alloc(&tmp_node);
    if (rc != EXIT_SUCCESS)
        return rc;
    tmp_node->data = elem;
    tmp_node->row = i;
    tmp_node->col = j;
    tmp_node->next = NULL;
    matrix->head = push_back(matrix->head, tmp_node);
    return EXIT_SUCCESS;
}

int read_matrix(matrix_t *matrix)
{
    if (scanf("%zu %zu", &matrix->rows, &matrix->cols) != 2)
        return MATRIX_SIZE_READ_ERROR;
    int tmp_elem;
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols; j++)
        {
            if (scanf("%d", &tmp_elem) != 1)
                return ELEM_READ_ERROR;
            if (tmp_elem != 0)
            {
                int rc = matrix_elem_add(matrix, tmp_elem, i, j);
                if (rc != EXIT_SUCCESS)
                    return rc;
            }
        }
    return EXIT_SUCCESS;
}

int matrix_add(matrix_t *matrix_1, matrix_t *matrix_2, matrix_t *result)
{
    if (!matrix_1->head && !matrix_2->head)
        return MATRIX_EMPTY_ERROR;

    result->rows = matrix_1->rows;
    result->cols = matrix_1->cols;

    node_t *matr_1_elem = matrix_1->head;
    node_t *matr_2_elem = matrix_2->head;

    while (matr_1_elem || matr_2_elem)
    {
        if (matr_1_elem && matr_2_elem)
        {
            if (matr_1_elem->row == matr_2_elem->row && matr_1_elem->col == matr_2_elem->col)
            {
                int sum = matr_1_elem->data + matr_2_elem->data;
                if (sum != 0)
                {
                    int rc = matrix_elem_add(result, sum, matr_1_elem->row, matr_1_elem->col);
                    if (rc != EXIT_SUCCESS)
                        return rc;
                }
                matr_1_elem = matr_1_elem->next;
                matr_2_elem = matr_2_elem->next;
            }
            else if (matr_1_elem->row < matr_2_elem->row || (matr_1_elem->row == matr_2_elem->row && matr_1_elem->col < matr_2_elem->col))
            {
                int rc = matrix_elem_add(result, matr_1_elem->data, matr_1_elem->row, matr_1_elem->col);
                if (rc != EXIT_SUCCESS)
                    return rc;
                matr_1_elem = matr_1_elem->next;
            }
            else
            {
                int rc = matrix_elem_add(result, matr_2_elem->data, matr_2_elem->row, matr_2_elem->col);
                if (rc != EXIT_SUCCESS)
                    return rc;
                matr_2_elem = matr_2_elem->next;
            }
        }
        else if (matr_1_elem && !matr_2_elem)
        {
            int rc = matrix_elem_add(result, matr_1_elem->data, matr_1_elem->row, matr_1_elem->col);
            if (rc != EXIT_SUCCESS)
                return rc;
            matr_1_elem = matr_1_elem->next;
        }
        else if (matr_2_elem && !matr_1_elem)
        {
            int rc = matrix_elem_add(result, matr_2_elem->data, matr_2_elem->row, matr_2_elem->col);
            if (rc != EXIT_SUCCESS)
                return rc;
            matr_2_elem = matr_2_elem->next;
        }
    }
    return EXIT_SUCCESS;
}

int matrix_mul(matrix_t *matrix_1, matrix_t *matrix_2, matrix_t *result)
{
    if (!matrix_1->head || !matrix_2->head)
        return MATRIX_EMPTY_ERROR;

    result->rows = matrix_1->rows;
    result->cols = matrix_2->cols;

    node_t *matr_1_elem = matrix_1->head;
    while (matr_1_elem)
    {
        node_t *matr_2_elem = matrix_2->head;
        while (matr_2_elem)
        {
            if (matr_1_elem->col == matr_2_elem->row)
            {
                int elem = matr_1_elem->data * matr_2_elem->data;
                int rc = matrix_elem_add(result, elem, matr_1_elem->row, matr_2_elem->col);
                if (rc != EXIT_SUCCESS)
                    return rc;
            }
            matr_2_elem = matr_2_elem->next;
        }
        matr_1_elem = matr_1_elem->next;
    }
    return EXIT_SUCCESS;
}

static size_t find_row_with_max_elem(matrix_t *matrix)
{
    int max = matrix->head->data;
    size_t row = 0;
    node_t *curr = matrix->head;
    for (; curr; curr = curr->next)
        if (curr->data > max)
        {
            max = curr->data;
            row = curr->row;
        }
    return row;
}

int matrix_lin(matrix_t *matrix)
{
    if (!matrix->head)
        return MATRIX_EMPTY_ERROR;
    size_t row = find_row_with_max_elem(matrix);
    node_t *curr = matrix->head;
    node_t *prev = NULL;
    while (curr)
    {
        if (curr->row == row)
        {
            if (prev)
                prev->next = curr->next;
            else
                matrix->head = curr->next;
            node_t *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
    return EXIT_SUCCESS;
}

void print_matrix(matrix_t *matrix)
{
    node_t *curr = matrix->head;
    for (; curr; curr = curr->next)
        printf("%zu %zu %d ", curr->row, curr->col, curr->data);
}
