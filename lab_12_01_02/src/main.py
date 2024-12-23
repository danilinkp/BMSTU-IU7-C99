import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout,
                             QHBoxLayout, QLabel, QLineEdit, QPushButton,
                             QTextEdit, QGroupBox)
from PyQt6.QtCore import Qt
from ctypes import CDLL, c_int, POINTER, byref

lib = CDLL("./lib/libarr.so")

# void left_shift(int arr[], int len, int k)
_left_shift = lib.left_shift
_left_shift.argtypes = (POINTER(c_int), c_int, c_int)

# int filter_squares(int src[], int src_len, int dst[], int *dst_len)
_filter_squares = lib.filter_squares
_filter_squares.argtypes = (POINTER(c_int), c_int, POINTER(c_int), POINTER(c_int))

_filter_squares.restype = c_int


def left_shift(arr: list, k: int) -> None:
    arr_len = len(arr)
    _arr = (c_int * arr_len)(*arr)

    _left_shift(_arr, arr_len, k)

    arr[:] = _arr


def filter_squares_predict(arr: list) -> tuple[int, list]:
    src_len = len(arr)
    src = (c_int * src_len)(*arr)
    dst_len = c_int(src_len)
    dst = (c_int * src_len)()

    rc = _filter_squares(src, src_len, dst, byref(dst_len))

    return rc, list(dst)


def filter_squares_by_func(arr: list) -> tuple[int, list]:
    src_len = len(arr)
    src = (c_int * src_len)(*arr)
    dst_len = c_int(0)

    rc = _filter_squares(src, src_len, None, byref(dst_len))
    if rc == 1:
        dst = (c_int * dst_len.value)()
        rc = _filter_squares(src, src_len, dst, byref(dst_len))
        return rc, list(dst)
    return rc, list()


class Array(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Обработка массивов")
        self.setGeometry(100, 100, 600, 400)

        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        main_layout = QVBoxLayout(central_widget)

        self.create_input_group(main_layout)
        self.create_shift_group(main_layout)
        self.create_squares_group(main_layout)
        self.create_output_group(main_layout)

    def create_input_group(self, parent_layout):
        input_group = QGroupBox("Ввод данных")
        layout = QVBoxLayout()

        layout.addWidget(QLabel("Введите числа через пробел:"))
        self.input_edit = QLineEdit()
        layout.addWidget(self.input_edit)

        input_group.setLayout(layout)
        parent_layout.addWidget(input_group)

    def create_shift_group(self, paren_layout):
        shift_group = QGroupBox("Циклический сдвиг влево")
        layout = QHBoxLayout()

        layout.addWidget(QLabel("Величина сдвига: "))
        self.shift_edit = QLineEdit()
        layout.addWidget(self.shift_edit)

        shift_button = QPushButton("Выполнить сдвиг")
        shift_button.clicked.connect(self.make_shift)
        layout.addWidget(shift_button)

        shift_group.setLayout(layout)
        paren_layout.addWidget(shift_group)

    def create_squares_group(self, parent_layout):
        squares_group = QGroupBox("Фильтрация массива")
        layout = QVBoxLayout()

        button_layout = QHBoxLayout()

        predict_button = QPushButton("Метод 1 (с запасом)")
        predict_button.setToolTip("Выделение памяти с запасом равным размеру входного массива")
        predict_button.clicked.connect(self.filter_squares_1)
        button_layout.addWidget(predict_button)

        func_button = QPushButton("Метод 2 (динамически)")
        func_button.setToolTip("Динамическое выделение памяти после определения нужного размера")
        func_button.clicked.connect(self.filter_squares_2)
        button_layout.addWidget(func_button)

        layout.addLayout(button_layout)
        squares_group.setLayout(layout)
        parent_layout.addWidget(squares_group)

    def create_output_group(self, parent_layout):
        output_group = QGroupBox("Результат")
        layout = QVBoxLayout()

        self.result_text = QTextEdit()
        self.result_text.setReadOnly(True)
        layout.addWidget(self.result_text)

        output_group.setLayout(layout)
        parent_layout.addWidget(output_group)

    def input_array(self):
        try:
            arr = [int(x) for x in self.input_edit.text().split()]
            return arr
        except ValueError:
            self.show_error("Введите целые числа, разделенные пробелами")
            return None

    def make_shift(self):
        arr = self.input_array()
        if arr is None:
            return
        elif len(arr) == 0:
            self.show_error("Массив пуст")
            return
        try:
            k = int(self.shift_edit.text())
            if k < 0:
                raise Exception
            left_shift(arr, k)
            self.show_result(f"Результат сдвига: {arr}")
            self.input_edit.setText(" ".join(str(i) for i in arr))
        except ValueError:
            self.show_error("Введите целое число для сдвига")
        except Exception:
            self.show_error("Введите положительное число")

    def filter_squares_1(self):
        arr = self.input_array()
        if arr is None:
            return
        elif len(arr) == 0:
            self.show_error("Массив пуст")
            return
        rc, filtered_arr = filter_squares_predict(arr)
        self.show_result(f"Фильтрация первым методом: {filtered_arr}")

    def filter_squares_2(self):
        arr = self.input_array()
        if arr is None:
            return
        elif len(arr) == 0:
            self.show_error("Массив пуст")
            return
        rc, filtered_arr = filter_squares_by_func(arr)
        self.show_result(f"Фильтрация превым методом: {filtered_arr}")

    def show_result(self, text):
        self.result_text.setText(text)

    def show_error(self, message):
        self.result_text.setText(f"Ошибка: {message}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Array()
    window.show()
    sys.exit(app.exec())
