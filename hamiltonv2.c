#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*struct edge{
    int one;
    int two;
};

struct graph{
    int numOfEdges;
    int numOfApexes;
    struct edge *data;
};

void printEdge(struct edge data){
    printf("(%d-%d)",data.one,data.two);
}

void printGraph(struct graph self){
    for(int i=0;i<self.numOfEdges;++i){
        printEdge(self.data[i]);
        printf (" ");
    }
}

struct edge createEdge(int a,int b){
    struct edge data;
    data.one=a;
    data.two=b;
    return data;
}

struct graph createGraph(){
    struct graph data;
    data.numOfApexes=0;
    data.numOfEdges=0;
    data.data=malloc(sizeof(struct edge)*100);
    return data;
}

void addEdge(struct edge edge,struct graph *graph){
    bool newApex1=true;
    bool newApex2=true;
    for(int i =0;i<graph->numOfEdges;i++){
        if ((edge.one==graph->data[i].one)||(edge.one==graph->data[i].two)){
            newApex1=false;
        }
        if ((edge.two==graph->data[i].one)||(edge.two==graph->data[i].two)){
            newApex2=false;
        }
    }
    if(newApex1){
        graph->numOfApexes++;
    }
    if(newApex2){
        graph->numOfApexes++;
    }
    printf("%d\n",graph->numOfApexes);
    graph->data[graph->numOfEdges]=edge;
    graph->numOfEdges++;
}
*/
int main (){
    /*struct graph gr=createGraph();
    struct edge ed1=createEdge(1,2);
    struct edge ed2=createEdge(1,3);
    struct edge ed3=createEdge(2,3);
    addEdge(ed1,&gr);
    addEdge(ed2,&gr);
    addEdge(ed3,&gr);
    printGraph(gr);
    printf("%d",gr.numOfApexes);*/

    FILE * in;
    /* open the file for writing*/
    in = fopen ("hamiltonv2.cnf","w");

    FILE *out;
    /* open the file for reading*/
    out = fopen("hamiltonv2.out", "r");

    printf("number of apexes :\n");
    int n=(int)(getc(stdin))-48;
    printf("******%d*******\n",n);
    fprintf (in, "p cnf %d 100\n",n*n);

    /*int edges[n*n+1];

    edges[0]=4654;

    //1
    edges[1]=0;
    edges[2]=1;
    edges[3]=0;
    edges[4]=0;
    edges[5]=0;
    edges[6]=0;
    edges[7]=0;

    //2
    edges[8]=1;
    edges[9]=0;
    edges[10]=1;
    edges[11]=0;
    edges[12]=0;
    edges[13]=0;
    edges[14]=0;

    //3
    edges[15]=0;
    edges[16]=1;
    edges[17]=0;
    edges[18]=0;
    edges[19]=1;
    edges[20]=0;
    edges[21]=0;

    //4
    edges[22]=0;
    edges[23]=0;
    edges[24]=0;
    edges[25]=0;
    edges[26]=1;
    edges[27]=1;
    edges[28]=1;

    //5
    edges[29]=0;
    edges[30]=0;
    edges[31]=1;
    edges[32]=1;
    edges[33]=0;
    edges[34]=1;
    edges[35]=0;

    //6
    edges[36]=0;
    edges[37]=0;
    edges[38]=0;
    edges[39]=1;
    edges[40]=1;
    edges[41]=0;
    edges[42]=0;

    //7
    edges[43]=0;
    edges[44]=0;
    edges[45]=0;
    edges[46]=1;
    edges[47]=0;
    edges[48]=1;
    edges[49]=0;*/

    int edges[n*n+1];
    edges[0]=45687;

    char trueFalse= 0;

    /*Remplissage du tableau d'entiers*/
    //initialisation a 0
    for(int i=1;i<=n*n;++i){
        edges[i]=0;
    }
    
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n+1;++j){
            if(j==i+1){
                edges[i*n+j]=0;
            }else{
                printf("{%d-%d} t or f\n",i+1,j);
                scanf(" %c", &trueFalse);
                if(trueFalse=='t'){
                    edges[i*n+j]=1;
                    edges[(j-1)*n+i+1]=1;
                }
            }
        }
    }

    /*Ecriture du fichier graphviz de base*/
    FILE *graph1=fopen("graph1.txt","w");
    if(graph1==NULL){
        return 1;
        perror("fopen");
    }
    fprintf(graph1,"digraph G {\n");
    for(int i=0;i<n;++i){
        for(int j=i+1;j<n+1;++j){
            if(edges[i*n+j]==1){
                fprintf(graph1,"%d -> %d;\n",i+1,j);
            }
        }
    }
    fprintf(graph1,"}\n");

    fclose(graph1);

    //pas plus d'un sommet par etape du chemin
    //5 car 5 etapes puisque 5 noeuds
    for(int a=0;a<n;a++){
        for(int i=1;i<n+1;++i){
            for(int j=1;j<n+1;++j){
                if(j!=i){
                    fprintf(in,"-%d -%d 0\n",a*n+i,a*n+j);
                }
            }
        }
    }

    //au moins un sommet par etape
    for(int i=0;i<n;++i){
        for(int j=1;j<n+1;++j){
            fprintf(in,"%d ",i*n+j);
        }
        fprintf(in,"0\n");
    }
    
    //Pas deux fois sur le meme sommet
    for(int a=1;a<n+1;a++){
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                if(j!=i){
                    fprintf(in,"-%d -%d 0\n",a+i*n,a+j*n);
                }
            }
        }
    }

    //Verification que les chemins empruntes sont les bons
    for(int i=1; i<n*n+1; i++){
        if(edges[i]==0){
            int startApex=0;
            int endApex=0;
            if(i%n==0){
                endApex=n;
                startApex=i/n;
            }else{
                endApex=i%n;
                startApex=i/n+1;
            }

            for(int j=0; j<n-1;++j){
                fprintf(in,"-%d -%d 0\n",j*n+startApex,(j+1)*n+endApex);
            }
        }
    }

    /* close the in file*/  
    fclose (in);
    
    //close the out file
    fclose(out);
}