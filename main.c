#include <stdio.h>
#include <stdlib.h>



int main(void){
     int NumV=0;
     int NumN=0;
     int c;
	 FILE *MatrFile=fopen("matr.txt", "r");
	 if(MatrFile==NULL){
        printf("No such File");
        exit(5);
     }

        while(!feof(MatrFile)){              
            if((fgetc(MatrFile))==';'){
                NumV++;
            }
        } 
        fclose(MatrFile);

        FILE *MatrFile1=fopen("matr.txt", "r");
        while((c=fgetc(MatrFile))!=';'){
            if(c==',')
                NumN++;
        }
        NumN++;
        fclose(MatrFile1);

        int Arr [NumV][NumN]; // матрица инцендентности
        MatrFile=fopen("matr.txt", "r");
        for(int i=0;i<NumV;i++){
            int j=0;
            while((c=fgetc(MatrFile))!=';')
                fscanf(MatrFile,"%d",&Arr[i][j++]);
        }

        fclose(MatrFile);

    
        char VertNames[NumV]; // массив вершин
        for (int i = 0; i < NumV; i++)
            VertNames[i]='a' +i;
        char connect[NumN][2];// массив соединенных вершин
        for (int j = 0; j < NumN; j++){
            int k=0;
            for (int i = 0; i < NumV; i++){
                if(Arr[i][j]<0)
                    connect[j][1]=VertNames[i];
                if (Arr[i][j]>0)
                    connect[j][k++]=VertNames[i];   
             }
        }
        
        for (int i = 0; i < NumN; i++){
	        for (int j = 0; j < 2; j++){
                if(!connect[i][j]){
                    connect[i][j]=connect[i][j-1];
                }
		        printf("%c ",connect[i][j]);
            }
            printf("\n");
	    }  

       

        FILE *GraphFile=fopen("graph.dot", "w");
        if(GraphFile==NULL){
            printf("Problem with making a file");
        }else{
            printf("File is read\n");
            fprintf(GraphFile,"graph graf {\n");
             for (int i = 0; i < NumV; i++){
                    fprintf(GraphFile,"%c ;\n",VertNames[i]);
            }
            for (int i = 0; i < NumN; i++){
                    fprintf(GraphFile,"%c -- %c ;\n",connect[i][0],connect[i][1]);
            }
            fprintf(GraphFile,"}\n");
            fclose(GraphFile);
            system("dot -Tpng graph.dot -o graph.png");
            system("graph.png");
        }
        


        if(NumN>(((NumV-1)*(NumV-2))/2)){
            printf("This graph is connected\n");
        }else{
            printf("This graph is not connected\n");
        }
    


    // определение степени каждой вершины и поиск наименьшей степени
    int graph_step[NumV];
    for (int i = 0; i < NumV; ++i){
    	int sum = 0;
    	for (int j = 0; j < NumN; ++j){
    		sum += Arr[i][j];
    	}
    	printf("%d\n", sum);
        graph_step[i] = sum;
    }

    int min = 100;
    int* index = (int*) calloc(1, sizeof(int));
    int num_same = 1; 

    for (int i = 0; i < NumV; ++i){
        if (graph_step[i] < min){
            min = graph_step[i];
            free(index);
            int* index = (int*) calloc(1, sizeof(int));
            index[0] = i;
            num_same = 1;
        } else if (graph_step[i] == min){
            index[num_same] = i; 
            ++num_same;
            index = (int*)realloc(index, num_same);
        }
    }

    printf("Minimal grade is %d\n", min);
    for (int k = 0; k < num_same; ++k){
        for (int i = 0; i < NumN; ++i){
            if (Arr[index[k]][i]){
                for (int j = 0; j < NumV; ++j){
                    if (Arr[j][i] && (j != index[k])){
                        printf("%c -- %c\n", VertNames[index[k]], VertNames[j]);
                    }
                }
            }
        }
    }

 return 0;

}
