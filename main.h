#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

// Estrutura para armazenar os dados dos médicos
struct Medico {
    int id;
    set<int> diasDisponiveis;
    set<int> diasFerias;  // Dias de férias escolhidos pelo médico
};

// Declaração das funções
bool atribuirMedico(map<int, int>& atribuicao, vector<Medico>& medicos, int dia, int medicoId, int c);
bool encontrarAtribuicao(vector<int>& feriados, vector<Medico>& medicos, map<int, int>& atribuicao, int idx, int c);
void modoUsuario();
void executarTestes();

#endif // MAIN_H
