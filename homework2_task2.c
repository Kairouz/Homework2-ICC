#include <stdio.h>
#include <limits.h>
#define MAX_LINE 99
#define MAX_PATH 1000
#define MAX_NETWORK 50

struct Station {
    char type;
    unsigned short line_nb;
    int id;
};

struct Path{
    struct Station Station_Sequence [MAX_PATH];
    unsigned short path_size;
};

struct Network {
    unsigned int Network_size ;
    int adj_matrix[MAX_NETWORK][MAX_NETWORK];
    struct Station stations[MAX_NETWORK];
};

struct Network build_small_network(){
    struct Network Figure_1;

    Figure_1.Network_size=12;
    Figure_1.stations[0].type='m';
    Figure_1.stations[0].id=10;
    Figure_1.stations[0].line_nb=1;

    Figure_1.stations[1].type='m';
    Figure_1.stations[1].id=10;
    Figure_1.stations[1].line_nb=2;

    Figure_1.stations[2].type='m';
    Figure_1.stations[2].id=11;
    Figure_1.stations[2].line_nb=1;

    Figure_1.stations[3].type='b';
    Figure_1.stations[3].id=11;
    Figure_1.stations[3].line_nb=42;

    Figure_1.stations[4].line_nb=1;
    Figure_1.stations[4].type='m';
    Figure_1.stations[4].id=12;

    Figure_1.stations[5].line_nb=1;
    Figure_1.stations[5].type='m';
    Figure_1.stations[5].id=13;

    Figure_1.stations[6].line_nb=2;
    Figure_1.stations[6].type='m';
    Figure_1.stations[6].id=21;

    Figure_1.stations[7].line_nb=2;
    Figure_1.stations[7].type='m';
    Figure_1.stations[7].id=22;

    Figure_1.stations[8].line_nb=2;
    Figure_1.stations[8].type='m';
    Figure_1.stations[8].id=23;

    Figure_1.stations[9].line_nb=42;
    Figure_1.stations[9].type='b';
    Figure_1.stations[9].id=23;

    Figure_1.stations[10].line_nb=42;
    Figure_1.stations[10].type='b';
    Figure_1.stations[10].id=122;

    Figure_1.stations[11].type='b';
    Figure_1.stations[11].id=132;
    Figure_1.stations[11].line_nb=42;

    for(int i=0;i<Figure_1.Network_size;i++){
        for(int j=0;j<Figure_1.Network_size;j++){
            Figure_1.adj_matrix[i][j]=INT_MAX;
        }
    }
    Figure_1.adj_matrix[0][1]=11;
    Figure_1.adj_matrix[1][0]=11;
    Figure_1.adj_matrix[0][2]=6;
    Figure_1.adj_matrix[2][3]=10;
    Figure_1.adj_matrix[3][2]=15;
    Figure_1.adj_matrix[2][4]=7;
    Figure_1.adj_matrix[4][5]=8;
    Figure_1.adj_matrix[1][6]=8;
    Figure_1.adj_matrix[6][1]=8;
    Figure_1.adj_matrix[6][7]=9;
    Figure_1.adj_matrix[7][6]=9;
    Figure_1.adj_matrix[7][8]=3;
    Figure_1.adj_matrix[8][7]=3;
    Figure_1.adj_matrix[8][9]=9;
    Figure_1.adj_matrix[9][8]=7;
    Figure_1.adj_matrix[10][9]=13;
    Figure_1.adj_matrix[3][10]=14;
    Figure_1.adj_matrix[11][3]=12;
    Figure_1.adj_matrix[5][8]=5;
    Figure_1.adj_matrix[8][5]=5;

    return Figure_1;
}

unsigned short is_valid_network_station(const struct Network *n){
    for(int i=0;i<n->Network_size;i++){
    if(((n->stations[i].type!='m')&&(n->stations[i].type!='b'))||((n->stations[i].type=='m')&&(n->stations[i].type!=1)&&(n->stations[i].type!=2))||((n->stations[i].type=='b')&&(n->stations[i].line_nb>MAX_LINE)&&(n->stations[i].line_nb<0))){
        printf("Station %d is Invalid...",i);
        return 0;
    }
    }
    return 1;
}

unsigned short is_valid_adj_matrix(const struct Network *n){
    for(int i=0;i<n->Network_size;i++){
        for(int j=0;j<n->Network_size;j++){
            if(n->adj_matrix[i][j]<0){
                printf("Invalid adjacent matrix. \nProblem in line %d and column %d .\n",i,j);
                return 0;
            }
        }
    }
    return 1;
}

unsigned short is_valid_station_order(const struct Network *n){
    for (int i=0;i<n->Network_size-1;i++){
        if(n->stations[i].id>n->stations[i+1].id){
            printf("Invalid Id order for stations %d and %d\n",i,i+1);
        return 0;
        }
        else if((n->stations[i].id==n->stations[i+1].id)&&(n->stations[i].type=='b')&&(n->stations[i+1].type=='m')){
            printf("Same Id, but invalid type order for stations %d and %d\n",i,i+1);
        return 0;
        }
        else if((n->stations[i].id==n->stations[i+1].id)&&(n->stations[i].type==n->stations[i+1].type)&&(n->stations[i].line_nb>=n->stations[i+1].line_nb)){
            printf("Stations %d and %d are doublets or the line number order is invalid ",i,i+1);
            return 0;
        }
    }
    return 1;
}

unsigned short is_network_valid(const struct Network *n){
    int a=is_valid_network_station(n);
    int b=is_valid_station_order(n);
    int c=is_valid_adj_matrix(n);
    if(((a==b)==c)==1){
        return 1;
    }
    printf("Invalid Network...\n");
    return 0;
}

struct Line{
    char type;
    unsigned short line_nb;
    int station_number;
    int list_line_nb;
    int sum;
    float cost;};


int total_lines(struct Network *n) {
    int Total_lines=0;
    int list_line_nb [MAX_LINE];
    for (int i=0; i<MAX_LINE; i++) {
        list_line_nb[i]=-1;
    }
    for (int i=0; i<n->Network_size; i++) { //list_line est la liste contenant tous les id_line, faisant la distinction entre les bus et les métros en ajoutant 99
        int id_line = n->stations[i].line_nb;
        if (n->stations[i].type=='m') id_line+=99;

        for (int j=0; j<MAX_LINE; j++) {

            if (list_line_nb[j]==id_line) break;

            if (list_line_nb[j]==-1) {
                list_line_nb[j] = id_line;

                Total_lines++;
                break;
            }
        }
    }
    return Total_lines;
}

// int station_number_per_line(struct Network *n,struct Line *l){
//     for (int j=0;j<Total_lines;j++){ //compte le nombre de stations par ligne
//         l->station_number=0;
//         for (int i=0;i<n->Network_size;i++){
//             if((n->stations[i].type==l->type)&&(n->stations[i].id==l->line_nb))
//                 l->station_number+=1;
//             }
//         }
//         return l->station_number;
//     }

// int Calculate_Sum(struct Line *l, struct Network *n){
    
// }

int main (){
    struct Network Network1=build_small_network();
    printf("%d\n", total_lines(&Network1));
    return 0;
}