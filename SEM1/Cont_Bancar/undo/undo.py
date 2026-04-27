def undo(lista_istoric,lista):
    """
    Aplica undo pentru ultima operatie
    :param lista_istoric: Lista cu istoricul tranzactiilor
    :param lista: Lista de tranzactii
    :return: Numele ultimei operatie
    """
    if  not lista_istoric:
        raise ValueError ("Nu mai este nicio tranzactie la care se poate face undo")
    operatie=lista_istoric.pop()
    lista.clear()
    lista.extend(operatie)
    return operatie
