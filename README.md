# Lab #3 MISPI

## The task:
 Cценарий **должен реализовывать** следующие **цели (targets):**
>   
    1. compile -- компиляция исходных кодов проекта.
    2. build -- компиляция исходных кодов проекта и их упаковка в исполняемый jar-архив. Компиляцию исходных кодов реализовать посредством вызова цели compile.
    3. clean -- удаление скомпилированных классов проекта и всех временных файлов (если они есть).
    4. test -- запуск junit-тестов проекта. Перед запуском тестов необходимо осуществить сборку проекта (цель build).
    5. scp - перемещение собранного проекта по scp на выбранный сервер по завершению сборки. Предварительно необходимо выполнить сборку проекта (цель build)
    6. env - осуществляет сборку и запуск программы в альтернативных окружениях; окружение задается версией java и набором аргументов виртуальной машины в файле параметров.
    7. music - осуществляет проигравание музыки по завершению сборки (цель build)
(make LAB1DEBUG=1 and change compiler to g++ ???)

## Steps:
These are the steps taken in order to finish this lab:

>
    1. Learn basic CMake syntax.
    2. Replace jar-archives and all java-related bullshit with a normal programing language (C was chosen in particular)
    3. Find out how scp is meant to work and implement it in CMake.
    4. Get 3 libraries from Gleb and Drew.
    5. Find out how unit-tests can be handled with C and CMake:
        1. Choose the framework:
            1. check.h 
            2. kuya???
            3. smthng else
        2. Learn the syntax for it. 
        3. Write code.
    6. Write a report. 
    7. Download Pismak photo and make a notification with him after build starts

## Unit Testing
Testing will work the following way:

>
    1. We will be testing the dynamic library "ipv4"
    2. Units for testing:
        1. convert_to_IPv4() func
        2. 
## How to run it?
>

    1. $ cmake .
    2. make compile/build/clean/test/scp/env

## Tips and tricks:
>

    1. delete.sh - *a small script for deleting all garbage that 'cmake .' creates*


