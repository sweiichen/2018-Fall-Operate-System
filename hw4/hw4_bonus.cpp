// Student ID:0510026
// Name      :陳司瑋
// Date      : 
#include "bmpReader.h"
#include "bmpReader.cpp"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;


#define MYRED	2
#define MYGREEN 1
#define MYBLUE	0

int imgWidth, imgHeight;
int MEAN_FILTER_SIZE=9;
int SOBEL_FILTER_SIZE;
int FILTER_SCALE;
int *filter_gx, *filter_gy;
//pthread_mutex_t *mutex;
sem_t *sem,*sem1,*sem2;



const char *inputfile_name[5] = {
	"input1.bmp",
	"input2.bmp",
	"input3.bmp",
	"input4.bmp",
	"input5.bmp"
};
const char *outputMed_name[5] = {
	"output1.bmp",
	"output2.bmp",
	"output3.bmp",
	"output4.bmp",
	"output5.bmp"
};


unsigned char *pic_in, *pic_grey, *pic_mean, *pic_gx, *pic_gy, *pic_sobel,*pic_final;

unsigned char RGB2grey(int w, int h)
{
	int tmp = (
		pic_in[3 * (h*imgWidth + w) + MYRED] +
		pic_in[3 * (h*imgWidth + w) + MYGREEN] +
		pic_in[3 * (h*imgWidth + w) + MYBLUE] )/3;

	if (tmp < 0) tmp = 0;
	if (tmp > 255) tmp = 255;
	return (unsigned char)tmp;
}
void* MeanFilter(void *data)
{
	int tmp = 0;
	int a, b , window[9],k=0,sum=0;
	int ws = (int)sqrt((float)MEAN_FILTER_SIZE);
	for (int h = 0; h<imgHeight; h++) {
		int row = h*imgWidth;
		if(h!= imgHeight-1){
					sem_wait(&sem1[h+1]);
					
		}
		for (int w = 0; w<imgWidth; w++){
			tmp=0;
			k=0;
			sum=0;
			for (int j = 0; j<ws; j++)
				for (int i = 0; i<ws; i++)
				{
					a = w + i - (ws / 2);
					b = h + j - (ws / 2);

					// detect for borders of the image
					if (a<0 || b<0 || a>=imgWidth || b>=imgHeight)continue;

					sum=sum+pic_grey[b*imgWidth + a];
				};

			tmp=sum/MEAN_FILTER_SIZE;
				
			if (tmp < 0) tmp = 0;
			if (tmp > 255) tmp = 255;

			pic_mean[row + w] = tmp;
					
				
		}
		sem_post(&sem[h]);

	}
	pthread_exit(NULL);
}


	

void* gxy_sobelFilter(void* data)
{
	int tmp = 0,tmp2=0;
	int a, b;
	int ws = (int)sqrt((float)SOBEL_FILTER_SIZE);

	for (int h = 0; h<imgHeight; h++) {
		int row = h*imgWidth;
		if(h!= imgHeight-1){
					sem_wait(&sem[h+1]);
					
		}
		for (int w = 0; w<imgWidth; w++){
			tmp = 0;
			tmp2 = 0;
			for (int j = 0; j<ws; j++)
				for (int i = 0; i<ws; i++){
					a = w + i - (ws / 2);
					b = h + j - (ws / 2);

					// detect for borders of the image
					if (a<0 || b<0 || a>=imgWidth || b>=imgHeight) continue;
					

					tmp += filter_gx[j*ws + i] * pic_mean[b*imgWidth + a];
					tmp2 += filter_gy[j*ws + i] * pic_mean[b*imgWidth + a];
				};
			if (tmp < 0) tmp = 0;
			if (tmp > 255) tmp = 255;
			if (tmp2 < 0) tmp2 = 0;
			if (tmp2 > 255) tmp2 = 255;
			pic_gx[row + w] = tmp;
			pic_gy[row + w] = tmp2;
				
		}
		sem_post(&sem2[h]);
	}
	pthread_exit(NULL);
	
	
}

// unsigned char gy_sobelFilter(int w, int h)
// {
// 	int tmp = 0;
// 	int a, b;
// 	int ws = (int)sqrt((float)SOBEL_FILTER_SIZE);
	
			
// 	for (int j = 0; j<ws; j++)
// 		for (int i = 0; i<ws; i++){
// 			a = w + i - (ws / 2);
// 			b = h + j - (ws / 2);

// 			// detect for borders of the image

// 			if (a<0 || b<0 || a>=imgWidth || b>=imgHeight) continue;
			
// 			tmp += filter_gy[j*ws + i] * pic_mean[b*imgWidth + a];
// 		};
// 	if (tmp < 0) tmp = 0;
// 	if (tmp > 255) tmp = 255;
// 	return (unsigned char)tmp;
// }

void* sobelFilter(void* data)
{
	int tmp = 0;
	for(int h =0; h<imgHeight;h++){
		sem_wait(&sem2[h]);
		int row = h*imgWidth;
		for(int w =0; w<imgWidth;w++){
			tmp = sqrt(pic_gx[h*imgWidth + w]*pic_gx[h*imgWidth + w] + pic_gy[h*imgWidth + w]*pic_gy[h*imgWidth + w]);
			if (tmp < 0) tmp = 0;
			if (tmp > 255) tmp = 255;
			pic_sobel[row + w] = tmp;
		}
	}
	pthread_exit(NULL);
	
}

// void* sobel(void* data){
// 	for (int j = 0; j < imgHeight; j++){
// 		sem_wait(&sem2[j]);
// 			for (int i = 0; i < imgWidth; i++){
// 				pic_sobel[j*imgWidth + i] = sobelFilter(i, j);
		
// 			}
// 	}
// 	pthread_exit(NULL);
// }
// void* sobel_xy(void *data){
// 	int t =0;
// 	for (int j = 0; j<imgHeight; j++) {
// 		if(j!= imgHeight-1){
// 					sem_wait(&sem[j+1]);
					
// 		}
				

// 		for (int i = 0; i<imgWidth; i++){

// 				pic_gx[j*imgWidth + i] = gx_sobelFilter(i, j);
// 				pic_gy[j*imgWidth + i] = gy_sobelFilter(i, j);

				
// 			}
// 	}
	
	
	
// 	pthread_exit(NULL);


// }


int main()
{
	// read mask file
	FILE* mask;

	mask = fopen("mask_Sobel.txt", "r");
	fscanf(mask, "%d", &SOBEL_FILTER_SIZE);

	filter_gx = new int[SOBEL_FILTER_SIZE];
	filter_gy = new int[SOBEL_FILTER_SIZE];

	for (int i = 0; i<SOBEL_FILTER_SIZE; i++)
		fscanf(mask, "%d", &filter_gx[i]);

	for (int i = 0; i<SOBEL_FILTER_SIZE; i++)
		fscanf(mask, "%d", &filter_gy[i]);

	fclose(mask);
	
	BmpReader* bmpReader = new BmpReader();
	for (int k = 0; k<5; k++){
		pthread_t t1,t2,t3;

		// read input BMP file
		pic_in = bmpReader->ReadBMP(inputfile_name[k], &imgWidth, &imgHeight);
		// allocate space for output image
		pic_grey = (unsigned char*)malloc(imgWidth*imgHeight*sizeof(unsigned char));
		pic_mean = (unsigned char*)malloc(imgWidth*imgHeight*sizeof(unsigned char));
		pic_gx = (unsigned char*)malloc(imgWidth*imgHeight*sizeof(unsigned char));
		pic_gy = (unsigned char*)malloc(imgWidth*imgHeight*sizeof(unsigned char));
		pic_sobel = (unsigned char*)malloc(imgWidth*imgHeight*sizeof(unsigned char));
		pic_final = (unsigned char*)malloc(3 * imgWidth*imgHeight*sizeof(unsigned char));
		
		
		sem = new sem_t [imgHeight];
		sem1 = new sem_t[imgHeight];
		sem2 = new sem_t [imgHeight];

		for(int i=0 ;i < imgHeight; i++){
			sem_init(&sem[i],0 , 0);
			sem_init(&sem1[i], 0, 0);
			sem_init(&sem2[i], 0, 0);
		 			 	
		}
	
		pthread_create(&t1,NULL,MeanFilter,NULL);
		pthread_create(&t2,NULL,gxy_sobelFilter,NULL);
		pthread_create(&t3,NULL,sobelFilter,NULL);
		//convert RGB image to grey image
		for (int j = 0; j<imgHeight; j++) {
			int row = j*imgWidth;
			for (int i = 0; i<imgWidth; i++){
				pic_grey[row + i] = RGB2grey(i, j);
			}
			sem_post(&sem1[j]);
		}
		
		
		
		
		
		pthread_join(t1,NULL);
		pthread_join(t2,NULL);

		pthread_join(t3,NULL);
		

		//apply the sobel filter to the image 
		// for (int j = 0; j < imgHeight; j++){
		// 	for (int i = 0; i < imgWidth; i++){
		// 		pic_sobel[j*imgWidth + i] = sobelFilter(i, j);
		// 	}
		// };

		//extend the size form WxHx1 to WxHx3
		for (int j = 0; j<imgHeight; j++) {
			for (int i = 0; i<imgWidth; i++){
				pic_final[3 * (j*imgWidth + i) + MYRED] = pic_sobel[j*imgWidth + i];
				pic_final[3 * (j*imgWidth + i) + MYGREEN] = pic_sobel[j*imgWidth + i];
				pic_final[3 * (j*imgWidth + i) + MYBLUE] = pic_sobel[j*imgWidth + i];
			}
		}

		bmpReader->WriteBMP(outputMed_name[k], imgWidth, imgHeight, pic_final);

		//free memory space
		free(pic_in);
		free(pic_grey);
		free(pic_mean);
		free(pic_final);
		free(pic_sobel);
		free(pic_gx);
		free(pic_gy);
		delete sem;
		delete sem1;
		//delete mutex;
	}

	return 0;
}