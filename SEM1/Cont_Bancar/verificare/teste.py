from servicii.functionalitati import *
from adaugare.tranzactie import creaza_tranzactie
from undo.undo import undo

def teste_creare_tranzictii():
    """Verifică dacă tranzacțiile se creează corect"""
    tranzactie=creaza_tranzactie(31,30,"intrare")
    assert get_zi_tranzactie(tranzactie)==31
    assert get_suma_tranzactie(tranzactie)==30
    assert get_tip_tranzactie(tranzactie)=="intrare"

    try:
        creaza_tranzactie(31, 30, "eroare")
        assert False
    except ValueError:
        assert True

def teste_actualizare_tranzictii():
    """Verifică dacă se actualizează corect tranzacțiile"""
    lista_istoric=[]
    lista_teste= [creaza_tranzactie(31, 30, "intrare"), creaza_tranzactie(20, 500, "iesire")]
    actualizare_tranzactie(lista_istoric,lista_teste,31,500,"intrare")
    actualizare_tranzactie(lista_istoric,lista_teste,20,500,"intrare")
    assert get_suma_tranzactie(lista_teste[0])==500
    assert get_tip_tranzactie(lista_teste[1])=="intrare"

def teste_tranzictii_mai_mari_decat_o_valoare():
    """Verifică dacă se caută corect tranzacțiile mai mari decat o anumită sumă"""
    lista_teste = [creaza_tranzactie(31, 30, "intrare"), creaza_tranzactie(20, 50, "iesire")]
    suma_test=25
    rezultat_test=tranzactii_mai_mari_decat_o_valoare(lista_teste,suma_test)
    assert(len(rezultat_test)==2)
    assert(get_suma_tranzactie(rezultat_test[0])==30)
    assert(get_suma_tranzactie(rezultat_test[1])==50)
    suma_test=500
    rezultat_test = tranzactii_mai_mari_decat_o_valoare(lista_teste, suma_test)
    assert(len(rezultat_test)==0)

def teste_tranzictii_de_un_anumit_tip():
    """Verifică dacă se caută corect tranzacțiile de un anumit tip"""
    lista_teste = [creaza_tranzactie(31, 30, "intrare"), creaza_tranzactie(20, 50, "iesire")]
    tip_test="intrare"
    rezultat_test=tranzactii_de_un_anumit_tip(lista_teste,tip_test)
    assert(len(rezultat_test)==1)
    assert(get_tip_tranzactie(rezultat_test[0])=="intrare")

def teste_calculeaza_suma_de_un_anumit_tip():
    """Verifică dacă se calculează corect suma de tipul dat"""
    lista_teste = [creaza_tranzactie(31, 30, "intrare"), creaza_tranzactie(20, 50, "iesire")]
    suma_test=calculeaza_suma_de_un_anumit_tip(lista_teste,"intrare")
    assert(suma_test==30)
    suma_test = calculeaza_suma_de_un_anumit_tip(lista_teste, "iesire")
    assert (suma_test == 50)

def teste_valideaza_suma():
    """Verifică dacă suma se validază corect"""
    try:
        valideaza_suma("adssd")
        assert False
    except ValueError:
        assert True

    try:
        valideaza_suma("34dssd")
        assert False
    except ValueError:
        assert True

def teste_valideaza_zi():
    """Verifică dacă ziua se validază corect"""
    try:
        valideaza_zi("adssd")
        assert False
    except ValueError:
        assert True

    try:
        valideaza_zi("34.5")
        assert False
    except ValueError:
        assert True

    try:
        valideaza_zi("34")
        assert False
    except ValueError:
        assert True

def teste_tranzactii_efectuate_inainte_de_o_zi_si_mai_mari_de_o_suma():
    """Verifică dacă se caută corect tranzacțiile făcute înainte de o zi și mai mari decât o sumă"""
    lista_teste = [creaza_tranzactie(30, 20, "intrare"), creaza_tranzactie(20, 50, "iesire")]
    rezultat_test=tranzactii_efectuate_inainte_de_o_zi_si_mai_mari_de_o_suma(31,25,lista_teste)

    if len(rezultat_test)==1:
        assert True
    else:
        assert False

    if get_suma_tranzactie(rezultat_test[0])==50:
        assert True
    else:
        assert False

def teste_valideaza_tip():
    """Verifică dacă se validează corect un tip"""
    try:
        valideaza_tip("edfdgt")
        assert False
    except ValueError:
        assert True

    try:
        valideaza_tip("intrare")
        assert True
    except ValueError:
        assert False

def teste_sterge_tranzactii_in_ziua_data():
    """Verifică dacă se șterge corect tranzacțiile din ziua dată"""
    lista_istoric=[]
    lista_teste = [creaza_tranzactie(31, 30, "intrare"), creaza_tranzactie(20, 50, "iesire")]
    lista_teste=sterge_tranzactii_in_ziua_data(lista_istoric,20,lista_teste)
    assert len(lista_teste)==1
    assert get_suma_tranzactie(lista_teste[0]) == 30
    assert get_zi_tranzactie(lista_teste[0])== 31

def teste_sterge_tranzactii_de_la_o_perioada():
    """Verifică dacă se șterge corect tranzacțiile după o perioadă"""
    lista_istoric=[]
    lista_teste = [creaza_tranzactie(31, 30, "intrare"), creaza_tranzactie(20, 50, "iesire")]
    lista_teste = sterge_tranzactii_de_la_o_perioada(lista_istoric,15,20,lista_teste)
    assert len(lista_teste) == 1
    assert get_suma_tranzactie(lista_teste[0]) == 30
    assert get_zi_tranzactie(lista_teste[0])== 31

def teste_sterge_tranzactii_de_un_tip():
    """Verifică dacă se șterge corect tranzacțiile după un tip"""
    lista_istoric=[]
    lista_teste = [creaza_tranzactie(31, 30, "intrare"), creaza_tranzactie(20, 50, "iesire")]
    lista_teste = sterge_tranzactii_de_un_tip(lista_istoric,"intrare",lista_teste)
    assert len(lista_teste) == 1
    assert get_suma_tranzactie(lista_teste[0]) == 50
    assert get_zi_tranzactie(lista_teste[0]) == 20

def teste_calculeaza_soldul_la_o_data():
    """Verifca daca calculeaza bine soldul pana la o data specificata"""
    lista_teste = [creaza_tranzactie(25, 30, "intrare"), creaza_tranzactie(20, 50, "iesire")
        ,creaza_tranzactie(30, 50, "iesire")]
    rez_test=calculeaza_soldul_la_o_data(lista_teste,25)
    assert rez_test==-20

def teste_tranzactii_de_un_anumit_tip_ordonate():
    """Verifca daca se cauta corect toate tranzactiile de un anumit tip si le ordoneaza dupa suma"""
    lista_teste = [creaza_tranzactie(25, 30, "iesire"), creaza_tranzactie(20, 50, "iesire")
        ,creaza_tranzactie(30, 50, "iesire")]
    lista_rez=tranzactii_de_un_anumit_tip_ordonate(lista_teste,"iesire")
    assert len(lista_rez)==3
    assert get_zi_tranzactie(lista_rez[1])== 20
    assert get_zi_tranzactie(lista_rez[2])== 30
    assert get_suma_tranzactie(lista_rez[0])== 30
    assert get_suma_tranzactie(lista_rez[1])== 50

def teste_filtreaza_tranzactii_de_un_anumit_tip():
    """Verifica daca se filtreaza corect toate tranzactiile de un anumit tip"""
    lista_teste = [creaza_tranzactie(25, 30, "iesire"), creaza_tranzactie(20, 50, "intrare")
        , creaza_tranzactie(30, 50, "iesire")]
    lista_rez=filtreaza_tranzactii_de_un_anumit_tip(lista_teste,"iesire")
    assert len(lista_rez)==2
    assert get_zi_tranzactie(lista_rez[1])==30
    assert get_suma_tranzactie(lista_rez[0])==30
    assert get_suma_tranzactie(lista_rez[1])==50

def teste_filtreaza_tranzactii_de_un_anumit_tip_si_mai_mici_decat_o_suma():
    """Verifica daca se filtreaza corect toate tranzactille de un anumit tip si mai mici decat o suma"""
    lista_teste = [creaza_tranzactie(25, 30, "iesire"), creaza_tranzactie(20, 50, "intrare")
        , creaza_tranzactie(30, 50, "iesire")]
    lista_rez=filtreaza_tranzactii_de_un_anumit_tip_si_mai_mici_decat_o_suma(lista_teste,40,"iesire")
    assert len(lista_rez)==1
    assert get_zi_tranzactie(lista_rez[0])==25
    assert get_suma_tranzactie(lista_rez[0])==30

def teste_undo():
    """Verifica functionalitatea functiei undo"""
    lista_teste=[]
    lista_istoric_teste=[]
    tranzactie=creaza_tranzactie(25, 30, "iesire")
    adauga_tranzactie(lista_istoric_teste,lista_teste,tranzactie)
    tranzactie = creaza_tranzactie(15, 300, "intrare")
    adauga_tranzactie(lista_istoric_teste, lista_teste, tranzactie)
    tranzactie = creaza_tranzactie(10, 30, "iesire")
    adauga_tranzactie(lista_istoric_teste, lista_teste, tranzactie)
    undo(lista_istoric_teste,lista_teste)
    assert len(lista_teste)==2
    actualizare_tranzactie(lista_istoric_teste,lista_teste,15,500,"iesire")
    undo(lista_istoric_teste, lista_teste)
    assert get_suma_tranzactie(lista_teste[1])==300
    assert get_tip_tranzactie(lista_teste[1]) == "intrare"
    lista_teste=sterge_tranzactii_de_un_tip(lista_istoric_teste,"intrare",lista_teste)
    assert len(lista_teste) == 1
    undo(lista_istoric_teste,lista_teste)
    assert len(lista_teste) == 2
    lista_teste=sterge_tranzactii_de_la_o_perioada(lista_istoric_teste,13,24,lista_teste)
    assert len(lista_teste) == 1
    undo(lista_istoric_teste,lista_teste)
    assert len(lista_teste)==2
    assert get_zi_tranzactie(lista_teste[1])==15
    lista_teste=sterge_tranzactii_in_ziua_data(lista_istoric_teste,25,lista_teste)
    assert len(lista_teste) == 1
    undo(lista_istoric_teste,lista_teste)
    assert len(lista_teste)== 2
    assert get_zi_tranzactie(lista_teste[0])==25

def ruleaza_toate_testele():
    """Rulează toate testele"""
    teste_calculeaza_suma_de_un_anumit_tip()
    teste_actualizare_tranzictii()
    teste_creare_tranzictii()
    teste_tranzictii_mai_mari_decat_o_valoare()
    teste_tranzictii_de_un_anumit_tip()
    teste_valideaza_suma()
    teste_valideaza_zi()
    teste_tranzactii_efectuate_inainte_de_o_zi_si_mai_mari_de_o_suma()
    teste_valideaza_tip()
    teste_sterge_tranzactii_in_ziua_data()
    teste_sterge_tranzactii_de_la_o_perioada()
    teste_sterge_tranzactii_de_un_tip()
    teste_calculeaza_soldul_la_o_data()
    teste_tranzactii_de_un_anumit_tip_ordonate()
    teste_filtreaza_tranzactii_de_un_anumit_tip()
    teste_filtreaza_tranzactii_de_un_anumit_tip_si_mai_mici_decat_o_suma()
    teste_undo()
