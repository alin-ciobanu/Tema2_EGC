Elemente de Grafica pe Calculator - Tema 1
Geometry Wars

Nume: Ciobanu Alin Emanuel
Grupa: 332 CC

Curpins
1. Cerinta
2. Utilizare
3. Implementare
4. Testare
5. Probleme Aparute
6. Continutul Arhivei
7. Functionalitati


1. Cerinta
Tema consta in realizarea unui joc de tip racing in care jucatorul controleaza o masina si trebuie sa se fereasca de 
obstacolele care ii apar in fata.
2. Utilizare

2.1 Consola si fisiere
Executabilul nu primeste parametri la consola.
Nu am folosit fisiere de intrare.

2.2 Input tastatura
Tasta sageata sus se foloseste pentru acceleratie.
Tasta sageata jos se foloseste pentru franare.
Tasta sageasta stanga, respectiv dreapta se folosesc pentru a vira masina.
Tasta ESC inchide programul.
Nicio alta tasta nu mai este folosita.

3 Implementare
IDE: Visual Studio 2012
Sistem de operare: Windows 7 Ultimare Edition (64 bit)
Framework-ul folosit a fost cel din laboratorul 3. Singura modificare a fost adaugarea de listenere 
pentru a asculta la ridicarea unei taste.

3.1 Clase si dependentele dintre ele
Clasele adaugate fata de cele deja existente au fost cele pentru masina (Car) si pentru obstacole (Obstacle).
Clasele nu deriva din nimic. Complexitatea structurii de clase este simpla si intuitiva.
Am folosit o singura clasa pentru a genera toate obstacolele. Constructorul Obstacle primeste un parametru de tip int 
care selecteaza un tip de obstacol. Am folosit 3 tipuri de obstacole: piramida triunghiulara regulata, piramida 
patrulatera si cub.

4. Testare
Tema a fost testata in Visual Studio. 

5. Probleme aparute
Am avut probleme la afisarea perspectiva si, in general, la aranjarea in pagina. 

6. Continutul arhivei

³   files.txt
³   lab2.sln
³   README.txt
³   
----Debug
³       freeglut.dll
³       
----lab2
    ³   Car.cpp
    ³   Car.h
    ³   lab2.vcxproj
    ³   lab2.vcxproj.filters
    ³   main.cpp
    ³   Obstacle.cpp
    ³   Obstacle.h
    ³   
    ----Debug
    ³       lab2.Build.CppClean.log
    ³       lab2.log
    ³       
    ----dependente
    ³       freeglut.dll
    ³       freeglut.h
    ³       freeglut.lib
    ³       freeglut_ext.h
    ³       freeglut_std.h
    ³       glut.h
    ³       Readme_freeglut.txt
    ³       
    ----Framework
            Circle2D.h
            Color.h
            DrawingWindow.cpp
            DrawingWindow.h
            Line2D.h
            Object2D.h
            Object3D.h
            Point2D.h
            Point3D.h
            Polygon2D.h
            Rectangle2d.h
            Text.h
            Transform2D.cpp
            Transform2D.h
            Transform3D.cpp
            Transform3D.h
            Visual2D.cpp
            Visual2D.h
            

            

7. Functionalitati
Functionalitati Standard (ca in enunt):
	miscare masina
	acceleratie/franare
	obstacolele vin spre masina
Functionalitati Bonus:
	oprirea din inertie a masinii (daca nu este apasata acceleratia, masina se opreste in timp)
	