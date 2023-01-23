# Parallel-Define-Integrall
Define Integrall by using Trapezoidal Rule and use threads to make it parallel
# Задача
Параллельная реализация вычисления N-мерного интеграла методом прямоугольников или трапеций с заданной точностью. N задаётся в runtime при старте нужного теста.

<h1>Метод трапеций</h1> 
<img src="https://s0.wp.com/latex.php?latex=I%3D%5Cint_0%5E%7B%5Cpi%2F2%7D+%5Cfrac%7B5%7D%7Be%5E%5Cpi-2%7D%5Cexp%282x%29%5Ccos%28x%29dx%3D1.0++&bg=%23ffffff&fg=%23383838&s=2"> <br>
Точность приближения зависит от числа N отрезков, на которые разбивается промежуток интегрирования. Таким образом, длина промежутка:
<br>
<img src="https://s0.wp.com/latex.php?latex=%5CDelta+x+%3D+%5Cfrac%7Bb-a%7D%7BN%7D++&bg=%23ffffff&fg=%23383838&s=2">
<br>
<img src="https://thoughtsoncpp.files.wordpress.com/2019/04/trapezoid-1.png">
<br>
Площадь трапеции может быть вычислена по формуле:
<img src="https://s0.wp.com/latex.php?latex=A%3D%5Cfrac%7Ba%2Bb%7D%7B2%7D%5Ccdot+h++&bg=%23ffffff&fg=%23383838&s=2">
Суммируя все вышесказанное, приближенное значение интеграла вычисляется по формуле:
<img src="https://s0.wp.com/latex.php?latex=%5Cwidetilde%7B+I+%7D+%3D+%5Csum_%7Bi%3D1%7D%5E%7BN%2B1%7D+%5Cfrac%7Bx_i-x_%7Bi%2B1%7D%7D%7B2%7D%28f%28x_i%29%2Bf%28x_%7Bi%2B1%7D%29%29++&bg=%23ffffff&fg=%23383838&s=2">

Функция, вычисляющая интеграл методом трапеций должна принимать следующие параметры:
<ul>
	<li>границы отрезка интегрирования;</li>
	<li>подинтегральную функцию;</li>
	<li>число N промежутков разбиения.</li>
</ul>

<h1>Решение</h1>
<ul>
	<li>Windows-Open MPI (main.cpp)</li>
	<li>Linux-pthreads (pthread.cpp)</li>
</ul>
