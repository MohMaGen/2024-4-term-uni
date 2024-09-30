#pragma once

/*
    Создайте класс Кот, Собака, Вомбат со свойствами:
        имя, возраст, сытость (от 0 до 100), усталость.

    Создайте класс Животное, который будет хранить указатель на пустоту,
    за которым скрывается конкретное животное, а так же его тип.

    Создайте класс Контактный зоопарк, который будет хранить в себе массив животных.

    Заполните зоопарк случайными животными в количестве введенным пользователем, так что
    бы было хотя бы по одному животному одного вида.

    Добавьте методы у зоопарка для добавления нового одного животного которого введет пользователь.

    (Усложнение) Смоделируйте работу смотрителя зоопарка в течении одного рабочего дня(12 часов),
    задача которого наблюдать за животными, в случае если животное утомилось (усталость > 80),
    он отправляет его в отдельный вольер спать(скорость восстановления определяется типом животного),
    если животное хочет кушать, он отправляется на фиксированное время так же в отдельный вольер.
    Наработка усталости и уменьшения сытости обоих параметров определяется типом животного и
    интенсивностью посещения зоопарка в текущий момент. Интенсивность меняется каждый час
    работы в диапазоне от 0 до 1.
*/


namespace lab4 {
    void runLab4(void);
}