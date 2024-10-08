#pragma once

/*
# Лабораторная работа номер 3
----------------------------------


Критериями выполнения базовой части являются:
- Реализация программы, возможность ее запуска, ее взаимодействие с пользователем.
- Выполнение двух и более действий взаимодействия со структурами из пункта 4, предложенными в задании вашего варианта.
- Оформление кода в соответствии с соглашением об именовании. 
- Код можно разбивать на функции, а можно не разбивать.

Критериями усложненного варианта является:
- Реализация всех предложенных в задании действий со структурами.
- Генерация набора структур случайными генераторами в рамках адекватных граничных условий (т.е. работник имеет полноценное ФИО и возраст не превышающий 70 лет, генерируется множество разнообразных банкнот, фигуры генерируются существующими, а размеры не превышающими 100 единиц).
- Все действия реализованы в виде отдельных функций с описанием их документационных строк.

#### Вариант 1

Требуется написать программу, в которой:
1. Будет реализована структура "Работник" с полями:
   * ФИО
   * Пол (Используя перечисление)
   * Год рождения (Структура Даты)
2. Пользователь вводит число N.
3. Создан массив хранящий N работников, кол-во считывается с клавиатуры.
4. Cгенерированы N работников.
5. Написаны функции которые:
   1. Проводит поиск по массиву работников и находит работника по частичному совпадению ФИО (Поиск только от начала фио в целом).
   2. Формирует срез работников из массива по году рождения (больше или меньше).
   3. Выводит распределение работников по полу и возрастным группам (группы выбираются с шагом не менее 5 лет).
   4. Сортирует массив работников по возрасту (учитываются все составляющие даты).
*/

namespace lab3 {
    void runLab3(void);
}
