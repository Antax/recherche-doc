#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main (){
    

    FILE * in;
    /* open the file for writing*/
    in = fopen ("hamiltonv2.cnf","w");

    FILE *out;
    /* open the file for reading*/
    out = fopen("hamiltonv2.out", "r");

    printf("number of apexes :\n");
    char buf[256];
    scanf("%s", buf);
    int n=strtol(buf,NULL,10);
    //int n=(int)(getc(stdin))-48;
    printf("%i",n);
    fprintf (in, "p cnf %d 100\n",n*n);

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
    fprintf(graph1,"graph G {\n");
    for(int i=0;i<n;++i){
        for(int j=i+1;j<n+1;++j){
            if(edges[i*n+j]==1){
                fprintf(graph1,"%d -- %d;\n",i+1,j);
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