#include <bits/stdc++.h> //includina visas bibliotekas

using namespace std;

struct skiers //slidininkai
{
    string name;
    int seconds;
};

void sort_skiers(skiers * finisher, int index);
void write(skiers * finisher, ofstream &out, int index);

int main()
{
    ifstream in("U2.txt");
    ofstream out("U2.rez");

    string name_of_participant; //slidininko identifikatorius
    int index = 0; //reikalingas sukurti galutiniam masyvui be skyliu
    int h, m, s;
    int starting_participants; // duotas kiekit zaideju
    int finished_participants; // duotas kiekis likusiu zaideju
    skiers starter[30]; // pradiniai zaidejai
    skiers finisher[30]; //like zaidejai
    in>>starting_participants;

    for(int i = 0; i<starting_participants; i++)
    {
        name_of_participant.resize(20); //string tapo 20 char ilgio
        in.read(&name_of_participant[0], 1); // neformatuojanti c++ funkcija read() palieka bit'ą \n, nuskaicius zaideju kiekio kintamojį, tad ji laikinai irasau
        in.read(&name_of_participant[0], 20); //i kintamasi irasau 20 char ilgio string
        starter[i].name = name_of_participant;
        in>>h>>m>>s;
        starter[i].seconds = h*3600 + m*60 + s; // pasiverciu viską sekundem
    }

    in>>finished_participants;

    for(int i= 0; i<finished_participants; i++)
    {
        name_of_participant.resize(20);
        in.read(&name_of_participant[0], 1);
        in.read(&name_of_participant[0], 20);
        finisher[index].name = name_of_participant;
        in>>h>>m>>s;
        finisher[index].seconds = h*3600 + m*60 + s; //tas pats irasymas, tik vengiant skyliu finisher masyve naudoju index ir ji padidinu tik randant finisavusi ir nediskvalifikuota zaideja
        for(int j=0; j<starting_participants; j++) // prasuku kiekvienam finisavusiam visus pradedanciuosius
        {
            if(finisher[index].name == starter[j].name) // jei randa ta pati varda
            {
                if(finisher[index].seconds - starter[j].seconds < 3600) // tikrina ar nereikia diskvalifikuot del virsitos valandos
                {
                    finisher[index].seconds -= starter[j].seconds; // jei nereikia, tai iraso i index varda, sekundes ir didina index
                    index++;
                }
            }
        }

    }
    sort_skiers(finisher, index); //rusiuoja
    write(finisher, out, index); // iraso i faila

    return 0;
}
void sort_skiers(skiers * finisher, int index)
{
    for(int i= 0; i<index-1; i++) //prasuka kiekvienam elementui iskyrus paskutiniui, kad nesikartotu
    {
        for(int j= i+1; j<index; j++) // bet pradeda nuo tolimesnio skaiciaus, kad taupytų resursus
        {
            if(finisher[i].seconds>finisher[j].seconds){ // jei randa didesni skaiciu auksciau, tai apmaino vietom
                swap(finisher[i], finisher[j]);
            }else if(finisher[i].seconds==finisher[j].seconds){ // jei randa lygius
                if(finisher[i].name>finisher[j].name){ // tai apmaino pagal abecele
                    swap(finisher[i], finisher[j]);
                }
            }
        }
    }
}
void write(skiers * finisher, ofstream &out, int index){
    for(int i=0; i<index; i++) //iraso
    {
        out<<finisher[i].name<<" "<<finisher[i].seconds/60<<" "<<finisher[i].seconds%60<<endl;
    }
}
