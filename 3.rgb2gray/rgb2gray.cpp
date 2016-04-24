#include<stdio.h>
#include<stdlib.h>

#include "cv.h"
#include "cxcore.h"
#include "c6x.h"

void AcCvtColor(unsigned char* image1,unsigned char* image2,int coder)
{
	unsigned char red,green,blue,gray;
	if(coder==CV_BGR2GRAY)
	{
		int imagedatasize=320*240;
		for(int i=0;i<imagedatasize;i++)
			{
				red=image1[i*3];
				green=image1[i*3+1];
				blue=image1[i*3+2];
				gray=(red*76+green*150+blue*30)>>8;
				image2[i]=gray;
			}
	}
}

void CvtColor(IplImage*image1,IplImage*image2,int coder)
{
	unsigned char red,green,blue,gray;
	if(coder==CV_BGR2GRAY&&image1->nChannels==3&&image2->nChannels==1)
	{
		int imagedatasize=image1->width*image1->height;
		for(int i=0;i<imagedatasize;i++)
			{
				red=(image1->imageData)[i*3];
				green=(image1->imageData)[i*3+1];
				blue=(image1->imageData)[i*3+2];
				gray=(red*76+green*150+blue*30)>>8;
				(image2->imageData)[i]=gray;
			}
	}
}
int main(int argc,char **argv)
{
	FILE  *fp=NULL;
	fp=fopen("E:\\Code\\CCS\\workspace_v5_2\\rgb2gray\\in.rgb","rb");
	if(fp==NULL)
	{
		printf("open file failed\n");
	}
	unsigned char *inBuf=NULL;
	unsigned char *outBuf=NULL;
	inBuf=(unsigned char*)malloc(320*240*3);
	outBuf=(unsigned char*)malloc(320*240);
	if(inBuf==NULL||outBuf==NULL)
	{
		printf("malloc Buf failed\n");
	}

	printf("inBuf address 0x%x\n",inBuf);
	printf("outBuf address 0x%x\n",outBuf);
	fread(inBuf,320*240*3,1,fp);

	IplImage*image1=NULL;
	image1=cvCreateImageHeader(cvSize(320,240),IPL_DEPTH_8U,3);
	cvSetData(image1,inBuf,320*3);

	IplImage*image2=NULL;
	image2=cvCreateImageHeader(cvSize(320,240),IPL_DEPTH_8U,1);

	CvtColor(image1,image2,CV_BGR2GRAY);

	for(int i=0;i<320*240;i++)
		outBuf[i]=(image2->imageDataOrigin)[i];


	FILE  *fq=NULL;
	fq=fopen("E:\\Code\\CCS\\workspace_v5_2\\rgb2gray\\out.rgb","wb");
	if(fq==NULL)
	{
		printf("write file failed\n");
	}
	fwrite(outBuf,sizeof(outBuf),1,fq);

	free(inBuf);
	free(outBuf);
	fclose(fp);

	cvReleaseImageHeader(&image1);
	cvReleaseImage(&image2);

	return 0;
}
