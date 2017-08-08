#include <iostream>
#include <math.h>
#include <map>
#include <stdio.h>
#include <cstring>

#define SIZE 5

using namespace std;

void pass(bool *vet);

bool equals(bool *vet1, bool *vet2, int size);

void print(bool *vet1);

void initialState(unsigned long int valor, bool *vet1, bool *vet2, int size);

string boolArraytoString(bool *vet, int size);

int boolArraytoInt(bool *vet, int size);

int main() {
    std::map<int, int> atratores;
    std::map<int, int> transiente;
    std::map<int, int> periodo;
    double estadosIniciais = pow(2, 5);
    unsigned int period = 0;
    unsigned int transient = 0;
    bool s0[SIZE];
    bool s1[SIZE];
    for (unsigned long int i = 0; i < estadosIniciais; i++) {
        initialState(i, s0, s1, SIZE);
        std::cout << "Inicial: " << i << std::endl;
        do {
            pass(s0);
            pass(s1);
            pass(s1);
            std::cout << boolArraytoInt(s0, SIZE) << " " << boolArraytoInt(s1, SIZE) << std::endl;
            transient++;
        } while (!equals(s0, s1, SIZE));

        int atrator = boolArraytoInt(s0, SIZE);
        if (atrator == i)
            transient = 0;

        if (transiente.find(transient) == transiente.end()) {
            transiente[transient] = 1;
        } else {
            transiente[transient]++;
        }

        do {
            pass(s1);
            period++;
        } while (!equals(s0, s1, SIZE));
        period--;

        if (periodo.find(period) == periodo.end()) {
            periodo[period] = 1;
        } else {
            periodo[period]++;
        }

        std::cout << "Found: " << boolArraytoInt(s0, SIZE) << " " << boolArraytoInt(s1, SIZE) << std::endl;

        if (atratores.find(atrator) == atratores.end()) {
            atratores[atrator] = 1;
        } else {
            atratores[atrator]++;
        }
        period = 0;
        transient = 0;
    }
    std::cout << "Histograma Atratores:" << endl;
    for (std::map<int, int>::iterator it = atratores.begin(); it != atratores.end(); ++it) {
        std::cout << it->first << " " << it->second << " " << endl;
    }

    std::cout << "Histograma Transiente:" << endl;
    for (std::map<int, int>::iterator it = transiente.begin(); it != transiente.end(); ++it) {
        std::cout << it->first << " " << it->second << " " << endl;
    }

    std::cout << "Histograma Periodo:" << endl;
    for (std::map<int, int>::iterator it = periodo.begin(); it != periodo.end(); ++it) {
        std::cout << it->first << " " << it->second << " " << endl;
    }
    return 0;
}

void initialState(unsigned long int valor, bool *vet1, bool *vet2, int size) {
    // std::cout <<" initialState: "<< std::endl;
    for (int i = 0; i < size; i++) {
        vet1[i] = (valor & 1) != 0;
        vet2[i] = vet1[i];
        valor >>= 1;
        //     std::cout <<vet1[i] << " ";
    }
    //std::cout <<" = "<< boolArraytoInt(vet1,size) << std::endl;
}

bool equals(bool *vet1, bool *vet2, int size) {
    for (int i = 0; i < size; i++) {
        if (vet1[i] != vet2[i]) {
            return false;
        }
    }
    return true;
}

string boolArraytoString(bool *vet, int size) {
    string out;
    for (int i = size - 1; i >= 0; i--) {
        if (vet[i]) {
            out = out + "1";
        } else {
            out = out + "0";
        }
    }
    return out;
}

int boolArraytoInt(bool *vet, int size) {
    int out = 0;
    // std::cout <<"boolArraytoInt:"<< std::endl;
    for (int i = size - 1; i >= 0; i--) {
        //   std::cout << vet[i] << " ";
        if (vet[i]) {
            out |= 1;
        }
        if (i > 0) out <<= 1;
    }
    //  std::cout << " = " << out << std::endl;
    return out;
}


void pass(bool *vet) {
    bool aux[5];
    for (int i = 0; i < 5; i++)
        aux[i] = vet[i];

    vet[0] = (aux[0] | aux[1]) & (~aux[4]) & (~aux[2]);

    vet[1] = aux[3] & ~aux[0];

    vet[2] = aux[0] & ~aux[3];

    vet[3] = aux[0] & aux[4] & (~aux[1]) & (~aux[3]);

    vet[4] = aux[0] & (~aux[4]) & (~aux[2]);

    return;
}


/*
//  CAC Network ( 69 Vértices )
void pass (bool *vet){
vet[0] = vet[41] ;
vet[1] = vet[21] ;
vet[2] = vet[41] & ~ vet[33] ;
vet[3] = vet[36] & ~ ( vet[37] | vet[7] ) ;
vet[4] = ( ( vet[51] | vet[34] ) & vet[37] ) & ~ vet[3] ;
vet[5] = ~ ( vet[21] & vet[1] ) ;
vet[6] = ( vet[49] | vet[32] ) & ~ ( vet[34] | vet[37] ) ;
vet[7] = ( vet[8] | vet[9] ) & ~ vet[22] ;
vet[8] = vet[18] & ~ ( vet[11] | vet[33] ) ;
vet[9] = vet[14] & ~ ( vet[22] | vet[33] ) ;
vet[10] = vet[47] & ~ vet[48] ;
vet[11] = vet[32] ;
vet[12] = vet[43] & vet[53] ;
vet[13] = ( vet[5] | vet[49] | vet[27] ) & ~ vet[21] ;
vet[14] = vet[31] ;
vet[15] = vet[35] ;
vet[16] = vet[29] ;
vet[17] = vet[65] ;
vet[18] = vet[53] | vet[17] ;
vet[19] = vet[16] ;
vet[20] = vet[60] ;
vet[21] = ~ ( vet[15] | vet[3] ) ;
vet[22] = ( vet[32] | vet[49] ) & ~ vet[44] ;
vet[23] = ~ vet[24] ;
vet[24] = ( vet[3] | ( vet[43] & vet[53] ) ) ;
vet[25] = vet[20] & ~ vet[50] ;
vet[26] = vet[2] | vet[30] ;
vet[27] = ( ( vet[5] | vet[16] ) & vet[26] ) & ~ vet[21] ;
vet[28] = ( vet[34] & vet[3] ) & ~ ( vet[21] | vet[0] ) ;
vet[29] = vet[39] | vet[41] ;
vet[30] = vet[10] | vet[52] | vet[53] ;
vet[31] = ( vet[4] | vet[51] | vet[10] ) & ~ vet[6] ;
vet[32] = ~ vet[23] ;
vet[33] = ( vet[34] | vet[45] ) & ~ ( vet[21] | vet[7] ) ;
vet[34] = ( vet[38] | vet[26] | vet[0] ) & ~ vet[28] ;
vet[35] = vet[12] ;
vet[36] = ( vet[15] | vet[40] ) & ~ vet[38] ;
vet[37] = vet[10] & ~ vet[3] ;
vet[38] = vet[34] & ~ ( vet[32] | vet[27] ) ;
vet[39] = vet[10] | vet[40] ;
vet[40] = vet[15] | vet[20] ;
vet[41] = vet[53] & ~ vet[42] ;
vet[42] = vet[32] | vet[49] ;
vet[43] = vet[48] ;
vet[44] = vet[31] ;
vet[45] = vet[52] & ~ vet[27] ;
vet[46] = vet[45] | vet[32] ;
vet[47] = vet[34] | vet[18] ;
vet[48] = vet[16] | vet[53] ;
vet[49] = vet[25] ;
vet[50] = vet[49] ;
vet[51] = vet[8] & ~ vet[6] ;
vet[52] = vet[58] & ~ vet[46] ;
vet[53] = vet[55] ;
vet[54] = ( vet[63] | vet[66] ) & ~ vet[60] ;
vet[55] = vet[59] ;
vet[56] = vet[61] & ~ ( vet[64] | vet[58] ) ;
vet[57] = ( vet[62] | vet[64] ) & ~ ( vet[63] | vet[58] | vet[61] ) ;
vet[58] = vet[54] ;
vet[59] = ( vet[64] | vet[67] ) & ~ vet[63] ;
vet[60] = vet[59] | vet[66] | vet[32] ;
vet[61] = vet[66] | vet[56] ;
vet[62] = vet[66] | vet[59] ;
vet[63] = vet[54] | vet[56] ;
vet[64] = vet[57] | vet[65] ;
vet[65] = vet[64] & ~ vet[58] ;
vet[66] = ( vet[67] | vet[55] ) & ~ vet[63] ;
vet[67] = vet[32] ;
vet[68] = ( vet[19] & vet[13] ) & ~ ( vet[33] | vet[7] ) ;
vet[69] = vet[7] ;
}
*/

// Equações Biológicas
/*
 * CAC network Reduzida (21 Vértices)
void pass (bool *vet){
    vet[0] = ~ vet[16] ;
    vet[1] = ~ ( vet[15] & vet[4] ) ;
    vet[2] = vet[5] & ~ vet[7] ;
    vet[3] = ( vet[1] | vet[18] | vet[10] ) & ~ vet[4] ;
    vet[4] = ~ ( vet[19] | vet[0] ) ;
    vet[5] = vet[2] ;
    vet[6] = vet[0] | vet[19] ;
    vet[7] = ~ vet[5] ;
    vet[8] = ~ vet[17] ;
    vet[9] = vet[19] ;
    vet[10] = vet[9] & ~ vet[4] ;
    vet[11] = ( vet[5] | vet[13] ) & ~ vet[7] ;
    vet[12] = ( vet[15] & vet[0] ) & ~ vet[4] ;
    vet[13] = vet[6] ;
    vet[14] = vet[15] & ~ vet[4] ;
    vet[15] = ( vet[16] | vet[9] ) & ~ vet[12] ;
    vet[16] = vet[15] & ~ ( vet[13] | vet[10] ) ;
    vet[17] = vet[18] ;
    vet[18] = vet[8] ;
    vet[19] = vet[11] ;
    vet[20] = vet[3] & ~ vet[14] ;
}
*/
/*
 // MAPK ( 54 Vértices)
void pass(bool *vet){
    vet[0] = vet[37] ;
    vet[1] = vet[37] & ~ vet[43] ;
    vet[2] = vet[24] & ( vet[16] | vet[4] ) ;
    vet[3] = ~ vet[6] & ~ vet[13] & vet[17] & vet[35] ;
    vet[4] = vet[23] | vet[34] ;
    vet[5] = vet[8] ;
    vet[6] = vet[7] & vet[1] ;
    vet[7] = vet[29] ;
    vet[8] = vet[0] ;
    vet[9] = vet[7] ;
    vet[10] = ( vet[11] | vet[49] ) & ~ ( vet[39] | vet[21] ) ;
    vet[11] = vet[0] ;
    vet[12] = vet[13] | vet[23] | vet[34] ;
    vet[13] = vet[28] ;
    vet[14] = vet[15] & ~ ( vet[21] | vet[39] ) ;
    vet[15] = vet[0] ;
    vet[16] = vet[13] & vet[46] & ( vet[12] | vet[7] ) ;
    vet[17] = vet[23] & ~ vet[1] ;
    vet[18] = vet[14] & ~ vet[49] & ~ vet[21] ;
    vet[19] = vet[21] | vet[38] ;
    vet[20] = vet[47] | vet[35] ;
    vet[21] = vet[10] | vet[18] | vet[52] ;
    vet[22] = vet[33] ;
    vet[23] = ( vet[51] & vet[25] ) | ( vet[25] & vet[30] ) | ( vet[51] & vet[30] ) | ( vet[50] & vet[30] ) |( vet[50] & vet[25] ) | ( vet[50] & vet[51] ) | (( vet[51] | vet[30] | vet[25] | vet[50] ) & ~ vet[9] ) ;
    vet[24] = vet[23] ;
    vet[25] = vet[45] ;
    vet[26] = vet[34] ;
    vet[27] = ( vet[35] | vet[1] ) & ~ vet[32] ;
    vet[28] = ( vet[44] | vet[25] ) & ~ ( vet[41] | vet[2] ) ;
    vet[29] = vet[13] | vet[34] ;
    vet[30] = vet[20] ;
    vet[31] = ( vet[29] & vet[26] ) | ( vet[29] & vet[1] ) ;
    vet[32] = vet[31] ;
    vet[33] = ~ vet[1] & vet[35] ;
    vet[34] = ( vet[51] & vet[25] ) | ( vet[25] & vet[30] ) | ( vet[51] & vet[30] ) | ( vet[50] & vet[30] ) |( vet[50] & vet[25] ) | ( vet[50] & vet[51] ) | (( vet[51] | vet[30] | vet[25] | vet[50] ) & ~ vet[9] ) ;
    vet[35] = ( vet[5] & vet[34] ) | (( vet[5] | vet[34] ) & ~ vet[27] ) ;
    vet[36] = vet[37] & vet[13] ;
    vet[37] = vet[38] ;
    vet[38] = vet[19] | ( vet[45] & vet[48] ) ;
    vet[39] = vet[40] ;
    vet[40] = vet[10] | vet[14] ;
    vet[41] = vet[34] ;
    vet[42] = vet[36] & vet[31] & ~ vet[33] ;
    vet[43] = vet[35] ;
    vet[44] = ( vet[45] | vet[39] ) & ~ ( vet[13] | vet[1] ) ;
    vet[45] = vet[48] | vet[40] ;
    vet[46] = vet[13] ;
    vet[47] = vet[52] ;
    vet[48] = vet[21] & ~ vet[46] ;
    vet[49] = vet[13] ;
    vet[50] = vet[52] ;
    vet[51] = vet[5] ;
    vet[52] = vet[53] ;
    vet[53] = vet[0] ;
}
*/
