# zad 1

---

#### perplexity 
perplexity mowi jak bardzo model jetset zagubiony przy generowaniu kolejnych słów.
Im mniejsze perplexity tym lepiej model przewiduje sowa w tekście.

czyli model liczy rozkład prawdopodobieństwa następnego słowo.
$w_i$ - prawdziwe słowo
$p(w_i)$ - prawdopodobieństwo prawdziwego słowa w rozkładzie prawdopodobieństwa modelu
$N$ - liczba słów 

$$
    PPL = e^{ -\frac{1}{N}\sum_{i = 1}^N log \ p(w_i)}
$$

e do średnej z perzewidywań poprawnego słowa

#### czemu to mogło by działać
* modele są trenowane w taki sposób, by minimalizować perplexity

* ludzie często piszą chaotyczne teksty z błedami - wiec mają duże preplexity

#### czemu to raczej nie zadziała
* ludzie piszą czesto przewidywalne proste teksty np. instrukcje, proste maile

* ludzie który by wiedzieli o tej metodzie mogli by próbować specjalnie pisać przewidywalnie, by minimalizować perplexity i zmylić badaczy 

#### jak kotrolować perplexity wygenerowanego tekstu
* można ręcznie zredagować tekst który wypluł model
* można zmienić templerature na wyższą która sprawi że w wygenerowanym tekście będzie więcej losowości -> większe perplexity
* można odpowiednio napisać propt prosąc o bardziej nietypową odpowiedz w nienaturalnym stylu 
