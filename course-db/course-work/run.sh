#! /bin/bash


echo "INIT..."
doas -u postgres psql -d course_work -f "./init.sql" -P format=csv -q

echo "FILL..."
doas -u postgres psql -d course_work -f "./fill.sql" -P format=csv -q

echo "DISPLAY..."

echo "   clients:"
doas -u postgres psql -d course_work -c "select * from clients" \
    -P format=csv -q > clients.csv

echo "   cars:"
doas -u postgres psql -d course_work -c "select * from cars" \
    -P format=csv -q > cars.csv

echo "   suppliers:"
doas -u postgres psql -d course_work -c "select * from suppliers" \
    -P format=csv -q > suppliers.csv

echo "   orders:"
doas -u postgres psql -d course_work -c "select * from orders" \
    -P format=csv -q > orders.csv


for req in req*.sql;
do
    res="res${req:3:-4}.csv";
    doas -u postgres psql -d course_work -f $req -P format=csv -q > $res;
done

