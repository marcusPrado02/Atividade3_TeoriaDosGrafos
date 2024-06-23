#include "main.h"
#include <cassert>
#include <set>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

// Função para verificar se uma determinada atribuição é válida
bool atribuirMedico(map<int, int>& atribuicao, vector<Medico>& medicos, map<int, set<int>>& feriadosPorPeriodo, int dia, int medicoId, int c) {
    int contador = 0;
    for (const auto& par : atribuicao) {
        if (par.second == medicoId) {
            contador++;
        }
    }

    if (contador >= c) {
        cout << "Médico " << medicoId << " já foi atribuído a " << contador << " dias, limite é " << c << endl;
        return false;
    }

    if (!medicos[medicoId].diasDisponiveis.count(dia)) {
        cout << "Médico " << medicoId << " não está disponível no dia " << dia << endl;
        return false;
    }

    if (medicos[medicoId].diasFerias.count(dia)) {
        cout << "Dia " << dia << " é um dia de férias para o médico " << medicoId << endl;
        return false;
    }

    // Verificar se o médico já foi designado para outro dia dentro do mesmo período de férias
    for (const auto& periodo : feriadosPorPeriodo) {
        if (periodo.second.count(dia)) {
            for (int diaPeriodo : periodo.second) {
                if (atribuicao.count(diaPeriodo) && atribuicao[diaPeriodo] == medicoId) {
                    cout << "Médico " << medicoId << " já foi atribuído ao dia " << diaPeriodo << " no mesmo período de férias" << endl;
                    return false;
                }
            }
        }
    }

    return true;
}

// Função para encontrar uma atribuição de médicos para os feriados
bool encontrarAtribuicao(vector<int>& feriados, vector<Medico>& medicos, map<int, int>& atribuicao, map<int, set<int>>& feriadosPorPeriodo, int idx, int c) {
    if (idx == feriados.size()) {
        return true;
    }

    int dia = feriados[idx];
    cout << "Tentando atribuir médico para o dia " << dia << endl;

    for (auto& medico : medicos) {
        if (atribuirMedico(atribuicao, medicos, feriadosPorPeriodo, dia, medico.id, c)) {
            atribuicao[dia] = medico.id;
            cout << "Atribuindo médico " << medico.id << " ao dia " << dia << endl;
            if (encontrarAtribuicao(feriados, medicos, atribuicao, feriadosPorPeriodo, idx + 1, c)) {
                return true;
            }
            cout << "Revertendo atribuição do médico " << medico.id << " do dia " << dia << endl;
            atribuicao.erase(dia);
        }
    }

    cout << "Nenhum médico disponível para o dia " << dia << endl;
    return false;
}

void modoUsuario() {
    vector<int> feriados;
    map<int, set<int>> feriadosPorPeriodo;
    int escolha;

    cout << "Você deseja usar a lista de feriados padrão (1) ou fornecer sua própria lista (2)? ";
    cin >> escolha;

    if (escolha == 1) {
        // Lista de feriados padrão para Minas Gerais em 2024
        feriados = {
                1,    // 1 de Janeiro - Confraternização Universal
                43,   // 12 de Fevereiro - Carnaval
                44,   // 13 de Fevereiro - Carnaval
                88,   // 29 de Março - Sexta-feira Santa
                112,  // 21 de Abril - Tiradentes
                122,  // 1 de Maio - Dia do Trabalhador
                151,  // 30 de Maio - Corpus Christi
                251,  // 7 de Setembro - Independência do Brasil
                286,  // 12 de Outubro - Nossa Senhora Aparecida
                307,  // 2 de Novembro - Finados
                320,  // 15 de Novembro - Proclamação da República
                360   // 25 de Dezembro - Natal
        };

        feriadosPorPeriodo[1] = {1};
        feriadosPorPeriodo[2] = {43, 44};
        feriadosPorPeriodo[3] = {88};
        feriadosPorPeriodo[4] = {112};
        feriadosPorPeriodo[5] = {122};
        feriadosPorPeriodo[6] = {151};
        feriadosPorPeriodo[7] = {251};
        feriadosPorPeriodo[8] = {286};
        feriadosPorPeriodo[9] = {307};
        feriadosPorPeriodo[10] = {320};
        feriadosPorPeriodo[11] = {360};

    } else {
        int numFeriados;
        cout << "Quantos feriados você deseja fornecer? ";
        cin >> numFeriados;
        feriados.resize(numFeriados);
        cout << "Digite os dias dos feriados (em formato de dia do ano, de 1 a 365): ";
        for (int i = 0; i < numFeriados; ++i) {
            cin >> feriados[i];
        }
    }

    int numMedicos;
    cout << "Quantos médicos estão disponíveis? ";
    cin >> numMedicos;
    vector<Medico> medicos(numMedicos);

    for (int i = 0; i < numMedicos; ++i) {
        medicos[i].id = i;
        int numDiasDisponiveis;
        cout << "Quantos dias o médico " << i << " está disponível para trabalhar em feriados? ";
        cin >> numDiasDisponiveis;
        cout << "Digite os dias disponíveis para o médico " << i << ": ";
        for (int j = 0; j < numDiasDisponiveis; ++j) {
            int dia;
            cin >> dia;
            medicos[i].diasDisponiveis.insert(dia);
        }
        int numDiasFerias;
        cout << "Quantos dias de férias o médico " << i << " escolheu? ";
        cin >> numDiasFerias;
        cout << "Digite os dias de férias para o médico " << i << ": ";
        for (int j = 0; j < numDiasFerias; ++j) {
            int dia;
            cin >> dia;
            medicos[i].diasFerias.insert(dia);
        }
    }

    // Parâmetro c
    int c;
    cout << "Digite o valor de c (número máximo de dias que cada médico pode trabalhar): ";
    cin >> c;

    // Mapa para armazenar a atribuição final de médicos aos feriados
    map<int, int> atribuicao;

    if (encontrarAtribuicao(feriados, medicos, atribuicao, feriadosPorPeriodo, 0, c)) {
        cout << "Atribuição possível:" << endl;
        for (const auto& par : atribuicao) {
            cout << "Dia " << par.first << ": Medico " << par.second << endl;
        }
    } else {
        cout << "Não é possível fazer uma atribuição que satisfaça todas as restrições." << endl;
    }
}

void mostrarCronograma(const map<int, int>& atribuicao) {
    cout << "=====================================================" << endl;
    cout << "Cronograma de Atribuições:" << endl;
    cout << "=====================================================" << endl;
    for (const auto& par : atribuicao) {
        cout << "Dia " << par.first << ": Médico " << par.second << endl;
    }
    cout << "=====================================================" << endl;
}

void executarTestes() {
    vector<int> feriados;
    vector<Medico> medicos;
    map<int, int> atribuicao;
    map<int, set<int>> feriadosPorPeriodo;
    int c;

    // Teste 1
    feriados = {1, 43, 44, 88, 112, 122, 151, 251, 286, 307, 320, 360};
    feriadosPorPeriodo = {
            {1, {1}},
            {2, {43, 44}},
            {3, {88}},
            {4, {112}},
            {5, {122}},
            {6, {151}},
            {7, {251}},
            {8, {286}},
            {9, {307}},
            {10, {320}},
            {11, {360}}
    };
    medicos = {
            {0, {1, 43, 44, 88, 112, 122, 151}, {150, 200}},
            {1, {251, 286, 307, 320, 360}, {50, 100}},
            {2, {1, 112, 151, 251, 320, 360, 286}, {120, 240}},
            {3, {1, 43, 88, 112, 122, 251, 307}, {150, 200}},
            {4, {44, 151, 286, 320, 360}, {50, 100}},
            {5, {1, 43, 122, 151, 251, 307}, {100, 200}},
            {6, {44, 88, 112, 320, 360}, {120, 240}},
            {7, {1, 43, 44, 88, 112, 122, 151, 251, 286, 307, 320, 360}, {}}
    };
    c = 2;
    atribuicao.clear();
    cout << "Executando Teste 1" << endl;
    if (!encontrarAtribuicao(feriados, medicos, atribuicao, feriadosPorPeriodo, 0, c)) {
        cout << "Erro no Teste 1: encontrarAtribuicao falhou" << endl;
        assert(false);
    }
    cout << "Teste 1 passou!" << endl;
    mostrarCronograma(atribuicao);

// Teste 2
    feriados = {5, 23, 47, 89, 123};
    feriadosPorPeriodo = {
            {1, {5}},
            {2, {23}},
            {3, {47}},
            {4, {89}},
            {5, {123}}
    };
    medicos = {
            {0, {5, 47, 123}, {23, 89}},
            {1, {23, 89}, {5, 47, 123}},
            {2, {5, 23, 47}, {89, 123}},
            {3, {23, 47, 89}, {5, 123}},
            {4, {5, 89, 123}, {23, 47}},
            {5, {23, 123}, {5, 47, 89}}
    };
    c = 2;
    atribuicao.clear();
    cout << "Executando Teste 2" << endl;
    if (!encontrarAtribuicao(feriados, medicos, atribuicao, feriadosPorPeriodo, 0, c)) {
        cout << "Erro no Teste 2: encontrarAtribuicao falhou" << endl;
        assert(false);
    }
    cout << "Teste 2 passou!" << endl;
    mostrarCronograma(atribuicao);

// Teste 3
    feriados = {12, 45, 78, 134, 167, 201};
    feriadosPorPeriodo = {
            {1, {12}},
            {2, {45}},
            {3, {78}},
            {4, {134}},
            {5, {167}},
            {6, {201}}
    };
    medicos = {
            {0, {12, 45, 78}, {134, 167, 201}},
            {1, {45, 78, 134}, {12, 167, 201}},
            {2, {78, 134, 167}, {12, 45, 201}},
            {3, {12, 134, 201}, {45, 78, 167}},
            {4, {45, 167, 201}, {12, 78, 134}}
    };
    c = 2;
    atribuicao.clear();
    cout << "Executando Teste 3" << endl;
    if (!encontrarAtribuicao(feriados, medicos, atribuicao, feriadosPorPeriodo, 0, c)) {
        cout << "Erro no Teste 3: encontrarAtribuicao falhou" << endl;
        assert(false);
    }
    cout << "Teste 3 passou!" << endl;
    mostrarCronograma(atribuicao);

// Teste 4
    feriados = {21, 56, 101, 149, 198, 254, 312};
    feriadosPorPeriodo = {
            {1, {21}},
            {2, {56}},
            {3, {101}},
            {4, {149}},
            {5, {198}},
            {6, {254}},
            {7, {312}}
    };
    medicos = {
            {0, {21, 56, 101, 149}, {198, 254, 312}},
            {1, {56, 101, 149, 198}, {21, 254, 312}},
            {2, {101, 149, 198, 254}, {21, 56, 312}},
            {3, {149, 198, 254, 312}, {21, 56, 101}},
            {4, {21, 56, 254, 312}, {101, 149, 198}},
            {5, {21, 101, 198, 312}, {56, 149, 254}}
    };
    c = 2;
    atribuicao.clear();
    cout << "Executando Teste 4" << endl;
    if (!encontrarAtribuicao(feriados, medicos, atribuicao, feriadosPorPeriodo, 0, c)) {
        cout << "Erro no Teste 4: encontrarAtribuicao falhou" << endl;
        assert(false);
    }
    cout << "Teste 4 passou!" << endl;
    mostrarCronograma(atribuicao);

// Teste 5
    feriados = {13, 29, 63, 97, 142, 176, 221, 269, 315, 350};
    feriadosPorPeriodo = {
            {1, {13}},
            {2, {29}},
            {3, {63}},
            {4, {97}},
            {5, {142}},
            {6, {176}},
            {7, {221}},
            {8, {269}},
            {9, {315}},
            {10, {350}}
    };
    medicos = {
            {0, {13, 63, 142, 221, 315}, {29, 97, 176, 269, 350}},
            {1, {29, 97, 176, 269, 350}, {13, 63, 142, 221, 315}},
            {2, {13, 29, 97, 176, 269}, {63, 142, 221, 315, 350}},
            {3, {63, 142, 221, 315, 350}, {13, 29, 97, 176, 269}},
            {4, {29, 97, 142, 176, 315}, {13, 63, 221, 269, 350}},
            {5, {13, 63, 97, 221, 269}, {29, 142, 176, 315, 350}}
    };
    c = 3;
    atribuicao.clear();
    cout << "Executando Teste 5" << endl;
    if (!encontrarAtribuicao(feriados, medicos, atribuicao, feriadosPorPeriodo, 0, c)) {
        cout << "Erro no Teste 5: encontrarAtribuicao falhou" << endl;
        assert(false);
    }
    cout << "Teste 5 passou!" << endl;
    mostrarCronograma(atribuicao);

    cout << "Todos os testes passaram!" << endl;
}


int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "test") {
        executarTestes();
    } else {
        modoUsuario();
    }
    return 0;
}
