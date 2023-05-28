
    Paraschiv Andreea-Alina 311AA


-In lanParty.c se afla main-ul
-In tasks.h se afla functiile folosite pentru fiecare task,
-In player.h se afla structurile pentru jucatori(Player) si pentru echipe(Team) si functiile folosite cu acestea pentru cerinta 1, respectiv cerinta 2
-In stive.h se afla structura pentru stivele(Stack) de catigatori si pierzatori si functiile folosite cu acestea flosite la cerinta 3
-In Top8.h se afla structura pentru listele cu ultimele 8 echipe(Top8) si functiile folosite cu acestea pentru cerintele 4 si 5
-In BST.h se afla structura pentru graf(Graph) si functiile folosite pentru bst in cerinta 4
-In AVL.h se afla functiile folosite pentru avl folosite in cerinta 5

player.h
    - se declara 2 liste simplu inlantuite, de tipul Player si Team
        -> int calculateNMax(int num) : calculeaza numarul x maxim mai mic ca numarul de echipe dat(num) de forma 2^n
        -> int calculateTeamScore(Player *player) : calculeaza suma scorulrilor pentru o echipa, parcurgand lista de player a echipei   respective
        -> Team* calculateALLTeamScore(Team *team) : calculeaza scorul pentru toate echipele
        -> float calculateMinScore(Team *team) : calculeaza scorul minim
        -> void removeTeam(Team **team, float x) : sterge echipa care are un scor dat (scorul minim)

stive.h
    - se declara o lista simplu inlantuita de tipul Stack
        -> void decideWinnersAndLosers(Queue **match,Stack **winners, Stack **losers, Team **A, Team **B) : pentru fiecare meci din coada(match) decide care din cele 2 echipe a castigat si pune echipa castigatoare in winners si cealalta in losers
        -> void displayWinners(Stack *winners, FILE *outputFile) : afiseaza lista de castigatori

cozi.h
    - se declara o lista simplu inlantuita cu 2 echipe de tipul Node si o structura de tip Queue
        -> Queue* createMatches(Queue *match, Team *teams) : creaza coada cu toate meciurile
        -> void displayOpponents(Queue *match, FILE *outputFile) : afiseaza continutul cozii


TASK 1:
    Se creaza o lista cu echipele date de tipul Teams. Citim din fisirul d.in datele si le punem in lista. Dupa citire se pargurge lista pentru a sterge linia noua generata din citirea cu fgets si stergem spatiile in plus care provoaca erori in taskuriile viitoare. La final se afiseaza echipele in ordine inversa citirii acestora.

TASK 2:
    Calculam scorul pentru toate echipele apeland functia calculateALLTeamScore si numarul Nmax maxim de forma 2^n folosind functia calculateNMax. Apoi pana cand numarul de echipe (numOfTeam) este mai mic ca Nmax se va sterge echipa cu scorul minim apeland functia removeTeam.

TASK 3:
    Se creeaza coada de meciuri(match) prin apelarea functiei createMatches. Se afiseaza coada si apoi se decide care sunt catigatorii si pierzatori, adaugandu-i in listele respective de winners and losers. Apoi se afiseaza lista de castigatori, cea de pierzatori se sterge. Din lista de catigatori se creaza coada pentru urmatoarea runda de meciuri. La fiecare pas numarul de echipe devine de 2 ori mai mic. Se continua pana cand se termina echipele. 
    In cazul in care avem ultimele 8 echipe ramase, acestea se adauga in lista de top8 apeland functia createTop8. La final de sterge lista de castigatori si coada de meciuri.

TASK 4:
    Se creaza arborele bst de tip Graph apeland functia createBST care pune echipele din Top 8 in graf dupa regula bst-ului (cele mai mici decat radacina in stanga si cele mai mari in dreapta). Apoi se creaza lista top8ord cu echipele in ordine descrescatoare pe care o vom folosi la task-ul 5 apeland functia inorder. Se parcurge lista si se afiseaza. Se sterge arborele de bst.

TASK 5:
    Se creeaza arborele de avl. Se pargurge lista de top8ord si se introduc echipele in avl, facand rotatiile corespunzatoare. Apoi se afiseaza echipele de pe al 2-lea nivel apeland functia displayLvl2. Se sterge arborele de avl.

La final stergem datele de echipe.