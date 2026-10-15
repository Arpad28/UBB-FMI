*Laborator 1 MAP*

# 1. Sabloane de Proiectare

Factory Pattern -ascunde logica de creare a obiectelor si centralizeaza acest proces intr un singur loc,ajutand pentru delegarea responsabilitatii
		-se foloseste in clasa OperationFactory
		-clasa ExpressionParser nu trebuie sa apeleze direct constructorul specific pentru tipul de operatie,el pur si simplu apeleaza functia OperationFactory.getOperation(operator) nestiind cum ii implementat in spate
		-ajuta pentru abstractizarea codului,daca vreau sa adaug operatii noi nu trebuie sa modific tot codul

# 2. Principii SOLID

**Single Responsibility Principle** 
		-fiecare clasa are o singura responsabilitate
		-ComplexNumber gestioneaza numai datele,ExpressionParser strict de parsare si validare,iar clasele care implementeaza interfata ComplexOperation se ocupa strict de logica matematica

**Open/Closed Principle**
		-clasele ar trebui sa fie deschise pentru extensie si inchise pentru modificare
		-datorita interfetei ComplexOperation daca va trebui sa adaugam o functie de ridicare la putere sau de radical vom crea pur si simplu o clasa noua care implementeaza acest lucru restul codului ramanand neschimbat,fiind necesara o mica schimbare numai in OperationFactory

**Dependency Inversion Principle**
		-modulele de nivel inalt nu ar trebui sa depinda de modulele  de nivel scazut,ambele depinzand numai de abstractizare(interfete,clase abstracte)
		-ExpressionParser depinde de abstractia ComplexOperation nu de clasele concrete (Addition,Substraction...)Pentru a nu crea direct instante de tip ComplexOperation in cadrul ExpressionParser se utilizeaza OperationFactory astfel este decuplat de fiecare operatie in parte