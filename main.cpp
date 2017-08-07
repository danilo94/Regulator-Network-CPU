#include <iostream>
#include <math.h>
#include <map>
#include <stdio.h>
#include <cstring>

#define SIZE 5

using namespace std;
void pass (bool *vet);
bool equals(bool *vet1,bool *vet2,int size);
void print (bool *vet1);
void initialState(unsigned long int valor,bool *vet1,bool *vet2,int size);
string boolArraytoString (bool *vet,int size);

int main() {
    std::map<string,int> atratores;
    std::map<int,int> transiente;
    std::map<int,int>::iterator it2;
    std::map<string,int>::iterator it;
    double estadosIniciais = (((pow(2,5) - 1)));
    unsigned int period=0;
    unsigned int transient=0;
 //   unsigned int histogramaTransiente[SIZE*10];
 //   for (int i=0; i<SIZE*10; i++){
 //       histogramaTransiente[i]=0;
 //   }
    bool s0[SIZE];
    bool s1[SIZE];
    for (unsigned long int i=0; i<estadosIniciais; i++) {
        initialState(i,s0,s1,SIZE);
        do {
           // pass(s0);
            pass(s1);
            memcpy(s0,s1,sizeof(s1));
            pass(s1);
            transient++;
        } while (!equals(s0, s1, SIZE));
 //           histogramaTransiente[transient]++;
        if( transiente.find(transient)==transiente.end()){
            transiente.insert(std::pair<int,int>(transient,1));
        }
        else{
           it2 = transiente.find(transient);
            it2->second+=1;
        }
        do {
            pass(s1);
            period++;
        } while (!equals(s0, s1, SIZE));
	
        string chave = boolArraytoString(s0,SIZE);
        if( atratores.find(chave)==atratores.end()){
            atratores.insert(std::pair<string,int>(chave,1));
        }
        else{
           it = atratores.find(chave);
            it->second+=1;
        }
        int tamanho = atratores.find(chave)->second;
        period=0;
        transient=0;
    }

    std::cout << "Histograma"<< endl;
    for (std::map<int,int>::iterator it = transiente.begin(); it !=transiente.end(); ++it){
	std::cout << it->first << " " << it->second << " " << endl;	
    }

  

    return 0;
}

void pass (bool *vet){
vet[0] = ( vet[0] | vet[1] ) & ( ~ vet[4] ) & ( ~ vet[2] ) ;

vet[1] = vet[3] & ~ vet[0] ;

vet[2] = vet[0] & ~ vet[3] ;

vet[3] = vet[0] & vet[4] & ( ~ vet[1] ) & ( ~ vet[3] ) ;

vet[4] = vet[0] & ( ~ vet[4] ) & ( ~ vet[2] ) ;
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
void initialState(unsigned long int valor, bool *vet1, bool *vet2,int size){
    for (int i=0;i<size; i++){
        vet1[i]= false;
        vet2[i]= false;
    }
    int j=0;
    while (valor>0 && j<size){
        if (valor%2==1 && j<size){
            vet1[j]=true;
            vet2[j]=true;
        }
        j++;
        valor = valor /2;
    }
}

bool equals(bool *vet1,bool *vet2,int size){
    for (int i=0; i<size; i++){
        if (vet1[i]!=vet2[i]){
            return false;
        }
    }
    return true;
}

string boolArraytoString(bool *vet,int size) {
    string out;

    for (int i=0; i<size; i++ ){
        if (vet[i]==true){
            out = out + "1";
        }
        else{
            out = out + "0";
        }
    }
    return out;
}
