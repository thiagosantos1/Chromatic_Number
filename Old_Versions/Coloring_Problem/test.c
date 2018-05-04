#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int arr[11][11][2];

	for (int d = 0; d < 11; d++){
		for (int i = 0; i < 11; i++){
			for (int j = 0; j < 2; j++){
				arr[d][i][j] = 1;
			}
		}
	}

	for (int d = 0; d < 11; d++){
		printf("Vertex %d \n",d );
		for (int i = 0; i < 11; i++){
			for (int j = 0; j < 2; j++){
				printf("%d ", arr[d][i][j]);
			}
			printf("\n");
		}
		
	}
	return 0;
}