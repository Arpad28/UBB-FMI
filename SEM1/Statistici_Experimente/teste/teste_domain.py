from domain.experiment import Experiment

def teste_domain():
    exp1=Experiment(1,"time travel","physical","Dr.X",3,0)
    exp2=Experiment(2,"study travel","surveys","Dr.Y",3,2)

    assert(exp1.get_nume()=="Dr.X")
    assert (exp2.get_nume() == "Dr.Y")
    assert (exp1.get_id() ==1)
    assert (exp2.get_id() ==2)
    assert (exp1.get_tip() == "physical")
    assert (exp2.get_nr_succese() ==2 )
    assert (exp1.get_nr_repetari() ==3)
    assert (exp1.get_titlu() == "time travel")
    assert (exp2.get_titlu() == "study travel")