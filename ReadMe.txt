#Лабораторная работа 2

Тема: Разработка многопоточных приложений, технология – встроенные потоки Windows

Подготовить исходные данные: Программа, которая вызывает функцию Calculate(), выполняющую трудоемкие вычисления

Цель: Улучшить отзывчивость программы. Например, предоставить пользователю возможность приостановить вычисления

Способ достижения цели: Разделить по потокам пользовательский интерфейс и трудоемкие вычисления

1. Создание потока

Читать. Функция CreateThread().

Задача. Вызвать функцию Calculate() в отдельном потоке.

2. Завершение потока

Читать. Корректное и некорректное завершение потока, функции WainForSingleObject(), CloseHandle().

Задача. Обеспечить корректное завершение вычислительного потока.

3. Корректное завершение потока по инициативе пользователя

Читать. Глобальная переменная – флаг Terminate.

Задача. После запуска вычислений в отдельном потоке предоставить пользователю возможность продолжить вычисления или завершить вычисления с сохранением промежуточного результата.

4. Передача данных потоку

Читать. Параметры функции потока.

Задача. При запуске потока передать параметры.

Литература

Буза, М.К. Проектирование программ для многоядерных процессоров


========================================================================
       WIN32 APPLICATION : Thr3
========================================================================


AppWizard has created this Thr3 application for you.  

This file contains a summary of what you will find in each of the files that
make up your Thr3 application.

Thr3.cpp
    This is the main application source file.

Thr3.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.
	

/////////////////////////////////////////////////////////////////////////////
AppWizard has created the following resources:

Thr3.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

res\Thr3.ico
    This is an icon file, which is used as the application's icon (32x32).
    This icon is included by the main resource file Thr3.rc.

small.ico
    %%This is an icon file, which contains a smaller version (16x16)
	of the application's icon. This icon is included by the main resource
	file Thr3.rc.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Thr3.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.


/////////////////////////////////////////////////////////////////////////////
