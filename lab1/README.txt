# Лабораторная работа 1 (Задачи 1–3)

## Сборка
В Visual Studio: Сборка → Собрать решение
Или в терминале:
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab1\task1\task1
cl /openmp /EHsc task1.cpp
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab1\task2\task2
cl /openmp /EHsc task2.cpp
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab1\task3\task3
cl /openmp /EHsc task3.cpp

## Запуск

### Задача 1
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab1\task1\x64\Debug
.\task1.exe 8

### Задача 2
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab1\task2\x64\Debug
.\task2.exe 8 static
.\task2.exe 8 dynamic
.\task2.exe 8 guided
.\task2.exe 8 runtime

### Задача 3
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab1\task3\x64\Debug
.\task3.exe 8 1
.\task3.exe 8 2
.\task3.exe 8 3
.\task3.exe 8 4
.\task3.exe 8 5