# zad 9 

--- 

używanie modelu do przewidywania następnego ruchu w szachach.

papuga nie ma tokenów ilealnie pod szachy np `e4`, `O-O` więc niekoniecznie będzie dobrze sobie radziła z niem następnego ruchu

możemy uczyć nasz model na partiach szachów osób które dobrze w nie grają np 2000+ elo lub napisać silnik szachowy wraz z botek który by nam generował partie.

tokenizjcja na podstawie szachowej notacji algobraicznej: 
* piąki: po prostu e4 -> pionek idzie na e4
* figury: [K / Q / R / B / N][pole docelowe] Nf3 -> skoczek na f3
* bicie: dodajemy x: Nxe5 -> skoczek bije na e5
* roszada: krótka: O-O, długa O-O-O

można też użyć potem model jako heurystycznej funcji ewaluacyjnej w mcts/min-max, patrząc na prawdopodobieństwa tokenów 