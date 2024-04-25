# Zad2
 
1. **Algorytmy ewolucyjne i hill climbing**:
Algorytmy ewolucyjne są efektywne w eksplorowaniu przestrzeni rozwiązań dzięki operacjom takim jak selekcja, krzyżowanie i mutacja, ale mogą mieć trudności z precyzyjnym lokalnym dostosowywaniem. Hill climbing, który jest prostym algorytmem lokalnej optymalizacji, skupia się na iteracyjnym polepszaniu obecnego rozwiązania przez przeszukiwanie jego sąsiedztwa. Możemy połączyć te dwa algorytmy tak, że każdy osobnik w populacji algorytmu ewolucyjnego podlegałby dodatkowemu ulepszaniu przez hill climbing. To pozwoli na bardziej precyzyjne dostosowanie poszczególnych rozwiązań, potencjalnie prowadząc do szybszego znalezienia optymalnych rozwiązań.
 
2. **A∗ oraz local beam search**:
A∗ to algorytm przeszukiwania informowanego, który używa funkcji kosztu (łącząc rzeczywisty koszt ścieżki i heurystyczną ocenę do celu) do optymalizacji procesu wyszukiwania. Local beam search jest algorytmem, który utrzymuje k najlepszych stanów w każdym kroku. Połączenie tych dwóch algorytmów mogłoby polegać na stosowaniu funkcji kosztu z A∗ do wyboru k najlepszych stanów w local beam search, co pozwoliłoby na bardziej zinformatyzowane i celowane przeszukiwanie przestrzeni stanów.
 
3. **Symulowane wyżarzanie i algorytmy ewolucyjne**:
Symulowane wyżarzanie wykorzystuje temperaturę do kontrolowania prawdopodobieństwa akceptacji gorszych rozwiązań, co pomaga w uniknięciu lokalnych minimum. W połączeniu z algorytmami ewolucyjnymi można by zastosować ideę "temperatury" do regulowania prawdopodobieństwa mutacji w algorytmie ewolucyjnym — wyższa "temperatura" mogłaby zwiększać prawdopodobieństwo bardziej radykalnych mutacji, co pomagałoby w eksploracji przestrzeni rozwiązań, a niższa promowałaby bardziej subtelne, lokalne dostosowania.
 
4. **Taboo search z algorytmami ewolucyjnymi**:
Taboo search to algorytm, który utrzymuje listę "taboo" (zakazanych) ruchów, co zapobiega cyklicznemu powrotowi do tych samych rozwiązań. W połączeniu z algorytmami ewolucyjnymi, lista taboo mogłaby być wykorzystana do zapobiegania ponownemu krzyżowaniu lub mutacji tych samych cech, które wcześniej nie prowadziły do polepszenia wyników. To mogłoby przyspieszyć konwergencję algorytmu ewolucyjnego poprzez eliminację nieefektywnych kierunków poszukiwań i zwiększenie różnorodności genetycznej populacji.