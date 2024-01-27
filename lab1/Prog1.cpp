#include "Prog1.h"

#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <stdexcept>

namespace Prog1 {

    template<class T>
    T getNum(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
        T a;
        while(true) {
            std::cin >> a;
            if(std::cin.eof()) // обнаружен конец файла
                throw std::runtime_error("Failed to read number: EOF");
            else if(std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            // прочие ошибки (неправильный формат ввода) либо число не входит в заданный диапазон
            else if(std::cin.fail() || a < min || a > max) {
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else // успешный ввод
                return a;
        }
    }
    
    Matrix input() {
        Matrix matrix;
    
        try {
            // вводим количество строк
            std::cout << "Enter number of lines: ";
            int m = getNum<int>(0);
    
            // выделяем память под массив структур - строк матрицы
            matrix.lines.resize(m);
    
            for (int i = 0; i < m; i++) {
                // запоминаем ссылку на обрабатываемую строку
                Line &line = matrix.lines[i];
    
                // для каждой строки матрицы вводим количество столбцов
                // в симметричной матрице количество столбцов равно индексу строки + 1
                int n = i + 1;
    
                // выделение необходимой памяти под элемент строки
                line.elements.resize(n);
    
                // ввод элементов строки матрицы
                std::cout << "Enter elements for matrix " << (i + 1) << " line :" << std::endl;
                for (int j = 0; j < n; j++) {
                    line.elements[j] = getNum<int>(0);
                }
            }
        } catch (...) // в случае любого исключения
        {
            // очищаем уже выделенную память
            matrix.lines.clear();
            throw; // перекидываем то же исключение дальше
        }
        return matrix;
    }
    void output(const char *msg, const Matrix &matrix) {
        std::cout << msg << ":\n";
        for (int i = 0; i < matrix.lines.size(); i++) {
            for (int j = 0; j < matrix.lines.size(); j++) {
                if (j <= i) { // Элементы выше или на главной диагонали
                    std::cout << matrix.lines[i].elements[j] << " ";
                } else { // Элементы ниже главной диагонали
                    std::cout << matrix.lines[j].elements[i] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    std::vector<int> result(const Matrix &matrix){
        std::vector<int> res;
        int count, max_count = 0;
        int number;
        for (int i = 0; i < matrix.lines.size(); i++) {
            max_count = 0;
            for (int j = 0; j < matrix.lines.size(); j++) {
                count = 0;
                if (j <= i) { // Элементы выше или на главной диагонали
                    number = matrix.lines[i].elements[j];
                } else { // Элементы ниже главной диагонали
                    number = matrix.lines[j].elements[i];
                }
                for(int x = 0; x < matrix.lines.size(); x++){
                    if (x <= i) { // Элементы выше или на главной диагонали
                        if(number == matrix.lines[i].elements[x]) count++;
                    } else { // Элементы ниже главной диагонали
                        if(number == matrix.lines[x].elements[i]) count++;
                    }
                }
                if (count > max_count) max_count = count;
            }
            res.push_back(max_count);
        }
        return res;
    }
    void vectoroutput(const char *msg, std::vector<int> res){
        std::cout << msg << ":\n";
        for (int i = 0; i < res.size(); i++){
            std::cout << res[i] << " ";
        }
        std::cout << std:: endl;
    }
}