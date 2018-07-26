#include <windows.h>
#include "stdio.h"
#include "stdlib.h"
typedef struct IMAGE_INFO_STRUCT
{
	int DataFilePTR;
}ImageInfoStruct;
typedef signed int          KF_INT32;
static HINSTANCE hInstLibrary;
/// \note 2017.03.28 hushiliang ��������
typedef  signed  int KF_INT32;

 
/// \note 2017.03.28 hushiliang �����ʼ������ָ��
typedef BOOL (__stdcall *DLLInitImageFileFunc)(ImageInfoStruct*,const char*);
DLLInitImageFileFunc InitImageFile;


//typedef  bool (__stdcall *DLLInitImageFileFunc)(ImageInfoStruct&, const char*);
/// \note 2017.03.28 hushiliang �����ȡͷ��Ϣ����ָ��
typedef int (_stdcall*DLLGetHeaderInfoFunc)(ImageInfoStruct, KF_INT32*, KF_INT32*, KF_INT32*, float*, double*, float*, KF_INT32*);
DLLGetHeaderInfoFunc GetHeaderInfo;
/// \note 2017.03.28 hushiliang �����ȡͼ����ָ��
typedef unsigned char* (_stdcall*DLLGetImageStreamFunc)(ImageInfoStruct*, float, KF_INT32, KF_INT32, KF_INT32*, unsigned char**);//Define pointer function type
DLLGetImageStreamFunc GetImageStream;
/// \note 2017.03.28 hushiliang �����ȡRGB��ͼ����ָ��
typedef unsigned char* (_stdcall*DLLGetRGBDataImageStreamFunc)(ImageInfoStruct*, float, KF_INT32, KF_INT32, KF_INT32*,KF_INT32*,KF_INT32*, unsigned char**);//Define pointer function type
DLLGetRGBDataImageStreamFunc GetRGBDataImageStream;//Define function pointer variables
/// \note 2017.03.28 hushiliang ����ɾ��ͼ����ָ��
typedef BOOL(_stdcall*DLLDeleteImageDataFunc)(LPVOID);//Define pointer function type
DLLDeleteImageDataFunc DeleteImageData;
/// \note 2017.03.28 hushiliang �����ͷ���Դ����ָ��
typedef BOOL(_stdcall*DLLUnInitImageFileFunc)(ImageInfoStruct*);//Define pointer function type 
DLLUnInitImageFileFunc UnInitImageFile;
/// \note 2017.03.28 hushiliang ��������ͼ����ָ��
typedef BOOL (_stdcall*DLLGetThumnailImageFunc)(ImageInfoStruct, unsigned char**, KF_INT32*, KF_INT32*, KF_INT32*);
DLLGetThumnailImageFunc GetThumnailImage;
int main(void)
    {

	KF_INT32*	khiImageHeight;//����ͼƬ�߶�
   KF_INT32*	khiImageWidth;//����ͼƬ���
   KF_INT32*	khiScanScale;//����ɨ�豶��
   float*	khiSpendTime;//����ɨ��ʱ��
   double*	khiScanTime;//����ɨ��ʱ��
   float*	khiImageCapRes;//����ɨ��ֱ���
   KF_INT32*	khiImageBlockSize;//����ɨ����С

   FILE* pf;
   unsigned char** ImageData;//�������ݿ�
   KF_INT32* nDataLength;//�������ݿ鳤��
	
	float fScale;//������Ҫ����
	KF_INT32 nImagePosX;//����X����
	KF_INT32 nImagePosY;//����Y����


   int ret;
   ImageInfoStruct* sImageInfo;//����������Ϣ

	HMODULE mylib;//����Handle���
    mylib = LoadLibrary(".\\ImageOperationLib.dll");//���ض�̬��

	
    InitImageFile = (DLLInitImageFileFunc)GetProcAddress(mylib, "InitImageFileFunc");//���س�ʼ������

	if(InitImageFile==NULL)
		return -1;
	sImageInfo=(ImageInfoStruct*)malloc(sizeof(ImageInfoStruct));//���ٿռ�
	ret=InitImageFile(sImageInfo,"k:\\2016-11-09 09_56_55.kfb");//ʹ�ó�ʼ������
	if(ret==0)
	{
		return -1;
	}  
	GetHeaderInfo = (DLLGetHeaderInfoFunc)GetProcAddress(mylib, "GetHeaderInfoFunc");//����ͷ��Ϣ��ȡ����
	if(GetHeaderInfo==NULL)
		return -1;
	khiImageHeight=(KF_INT32*)malloc(sizeof(KF_INT32));//���ٿռ�
	khiImageWidth=(KF_INT32*)malloc(sizeof(KF_INT32));
	khiScanScale=(KF_INT32*)malloc(sizeof(KF_INT32));
	khiSpendTime=(float*)malloc(sizeof(float));
	khiScanTime=(double*)malloc(sizeof(double));
	khiImageCapRes=(float*)malloc(sizeof(float));
	khiImageBlockSize=(KF_INT32*)malloc(sizeof(KF_INT32));
	GetHeaderInfo(*sImageInfo, khiImageHeight, khiImageWidth, khiScanScale, khiSpendTime, khiScanTime, khiImageCapRes, khiImageBlockSize);//ʹ��ͷ��Ϣ��ȡ����

	printf("%d",*khiImageHeight);//��ӡͼ��߶�


	 ImageData=(unsigned char**)malloc(sizeof(unsigned char*));
    nDataLength=(KF_INT32*)malloc(sizeof(KF_INT32));

	fScale=20.0f;
	nImagePosX=0;
	nImagePosY=0;
	GetRGBDataImageStream = (DLLGetRGBDataImageStreamFunc)GetProcAddress(mylib, "GetImageRGBDataStreamFunc");//���ؿ���Ϣ��ȡ����

	GetRGBDataImageStream(sImageInfo, fScale, nImagePosX, nImagePosY, nDataLength,khiImageWidth,khiImageHeight, ImageData);//ʹ�ÿ���Ϣ��ȡ����
    printf("\n%d\n",*nDataLength);      
	pf = fopen( "ImageRGBStreamFunc.raw", "wb" );
           fwrite( *ImageData, sizeof(unsigned char), *nDataLength, pf);
           fclose( pf );

	DeleteImageData= (DLLDeleteImageDataFunc)GetProcAddress(mylib, "DeleteImageDataFunc");//��������������
	DeleteImageData(*ImageData);//ʹ������������
	UnInitImageFile= (DLLUnInitImageFileFunc)GetProcAddress(mylib, "UnInitImageFileFunc");//�����ͷ���Դ����
	UnInitImageFile(sImageInfo);///ʹ���ͷ���Դ����
	getchar();
	return 0;
}