### Лабораторная работа номер 9
----------------------------------

Критериями выполнения базовой части являются:
- Реализация программы, возможность ее запуска, ее взаимодействие с пользователем.
- Выполнение всех пунктов без указанного в скобках слова "Усложненный вариант".

Критериями усложненного варианта является:
- Реализация пункта с припиской "Усложненный вариант".
- Все действия реализованы в виде отдельных функций с описанием их документационных строк.

### Вариант 3

Требуется разработать класс для хранения квадратного уровнения в общей форме.
- Класс коэффициенты уровнения и сами корни должны быть комплексными числами.
- Конструктор класса принимает все коэффициенты уровавнения и находит корни уравнения.
- Изменять коэффициенты и корни после создания объекта класса нельзя.

1) Сгенерировать N объектов класса, записав их в контейнер.
2) Перегрузить дружественную функцию - оператор вывода данных в поток (использовать* std::copy), и вывести все объекты из контейнера.
3) С использованием стандартного алгоритма реализовать метод, который проверяет, есть ли среди корней введенное пользователем число.
4) С использованием стандартного алгоритма реализовать метод, который проверяет количество корней, которые меньше заданного пользователем числа. Использовать лямбда-выражение.
5) (Усложненный вариант) Сделать функцию которая переберая все объекты в котнейнере, формирует вектор уникальных корней с использованием методов стандартной библиотеки.
6) (Усложненный вариант) Сделать функцию которая сортирует уравнения в котейнере по возрастанию корней суммы корней.
