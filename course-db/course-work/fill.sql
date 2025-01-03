INSERT INTO Clients (full_name, id_number, id_issue_date,
                    id_institution, address, phone)
VALUES  ('Краснов Дмитрий Александрович', '4379123456', '2012-2-1', '723-235',
         'г. Москва, ул. Кривая д. 23', '81321232354'),

        ('Зеленов Влад Георгиевич', '4379543456', '2010-5-1', '703-235',
         'г. Москва, ул. Кривая д. 24', '81323432354'),

        ('Пятков Алексей Маркович', '4379543700', '2008-5-1', '703-235',
         'г. Москва, ул. Ленина, д. 1', '89033432354'),

        ('Титова Влада Петрова', '4379543700', '2008-5-1', '703-235',
         'г. Москва, ул. Ленина, д. 1', '89033432354'),

        ('Каролёва Лена Георгиевна', '4379543700', '2008-5-1', '703-235',
         'г. Москва, ул. Ленина, д. 1', '89033432354');


INSERT INTO Cars (VIN, model, milage_km)
VALUES  ('15AD1135931ADB325', 'Ford Focus RS',  40000),
        ('15AD1135ABASDSAK5', 'Ford Focus RS',  401232),

        ('23AD11235DAB1B145', 'Porshe 911',     232124), 
        ('2AS1293BADKAS1235', 'Porshe 911',     220242), 
        ('23AD1121ASBLAS4AB', 'Porshe 911',     208402), 

        ('15AD1135931ADAB49', 'KamAZ-6560',     659493), 
        ('12351135931ADAB49', 'KamAZ-6560',     593912);


INSERT INTO Suppliers (name)
VALUES  ('ООО Машины'), ('ООО КАРСФОРЭВРИВАН'), ('ООО Большие машины');


INSERT INTO Orders (car_VIN, cost, issue_date, return_date,
                                    supplier_id, client_id)
VALUES  ('15AD1135931ADB325', 10000, '2022-11-2', '2022-12-5', 1, 1),

        ('23AD11235DAB1B145', 50000, '2022-5-2',  '2022-12-5', 2, 2),
        ('2AS1293BADKAS1235', 50500, '2023-1-2',  '2023-1-10', 2, 2),
        ('23AD11235DAB1B145', 50100, '2023-2-25', '2023-3-2',  2, 2),

        ('15AD1135931ADAB49', 101000, '2021-2-25', '2021-3-2',  3, 3),
        ('15AD1135931ADAB49', 105000, '2022-2-25', '2022-3-2',  3, 1),
        ('12351135931ADAB49', 105100, '2023-2-25', '2022-3-2',  3, 5),

        ('12351135931ADAB49', 105100, '2023-1-2',  '2023-1-10', 3, 4),

        ('15AD1135931ADAB49', 105000, '2020-6-21', '2020-6-25',  2, 5);
