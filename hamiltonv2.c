#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int main (int argc, char *argv[]){
    
    srand ( time ( NULL));

    FILE * in;
    /* open the file for writing*/
    in = fopen ("hamiltonv2.cnf","w");

    FILE *out;
    /* open the file for reading*/
    out = fopen("hamiltonv2.out", "r");

    int n = strtol(argv[1],NULL,10);

    fprintf (in, "p cnf %d 100\n",n*n);

    int edges[n*n+1];
    edges[0]=163546;

    //char trueFalse= 0;

    /*Ecriture du fichier graphviz de base*/
    if(argc==2){
        /*Remplissage du tableau d'entiers*/
        //initialisation a 0
        for(int i=1;i<=n*n;++i){
            edges[i]=0;
        }
        
        for(size_t i=1;i<=n;++i){
            for(size_t j=1;j<=n;++j){
                if(i!=j){
                    double random_value;
                    random_value = (double)rand()/RAND_MAX*1.0;
                    if(random_value<0.08){
                        edges[(i-1)*n+j]=1;
                        edges[(j-1)*n+i]=1;
                    }
                }
            }
        }
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
    }else{  //ecriture dans edges a partir du graph en entree
        for(int i=1;i<=n*n;++i){
            edges[i]=0;
        }
        //lecture ligne par ligne dans le graph envoye en argument
        
        FILE *file = fopen ( argv[2], "r" );
        if ( file != NULL )
        {
            char line [ 1024 ]; 
            int firstApex=0,secondApex=0;
            while ( fgets ( line, sizeof line, file ) != NULL ) 
            {
                if(line[0]>='0'&&line[0]<='9'){
                    //Parcours de line pour affectuer les bonnes valeurs a firstApex et secondApex
                    firstApex=0;
                    secondApex=0;
                    int current=0;
                    //first apex
                    while(line[current]>='0'&&line[current]<='9'){
                        firstApex=firstApex*10+line[current]-'0';
                        ++current;
                    }

                    //Search for start of second Apex
                    while(line[current]<'0'||line[current]>'9'){
                        ++current;
                    }
                    
                    //Second Apex
                    while(line[current]>='0'&&line[current]<='9'){
                        secondApex=secondApex*10+line[current]-'0';
                        ++current;
                    }
                    edges[(firstApex-1)*n+secondApex]=1;
                    edges[(secondApex-1)*n+firstApex]=1;
                }
            }
            fclose ( file );
        }
        else
        {
            perror ( argv[2] ); 
        }
    }

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