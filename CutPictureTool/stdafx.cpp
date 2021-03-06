
// stdafx.cpp : 只包括标准包含文件的源文件
// CutPictureTool.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "iostream"
#include "math.h"
#include "vector"

using namespace std;
using namespace cv;

#pragma comment(lib,"opencv_world341d.lib")
#pragma comment(lib,"libpngd.lib")
#pragma comment(lib,"IlmImfd.lib")
#pragma comment(lib,"ippicvmt.lib")
#pragma comment(lib,"ippiwd.lib")
#pragma comment(lib,"ittnotifyd.lib")
#pragma comment(lib,"libjasperd.lib")
#pragma comment(lib,"libjpegd.lib")
//#pragma comment(lib,"libprotobufd.lib")
#pragma comment(lib,"libtiffd.lib")
#pragma comment(lib,"libwebpd.lib")
#pragma comment(lib,"zlibd.lib")



int pic = 1;  //在使用指南中控制显示图片的页数
CString m_WideS1=_T("a");  //自定义尺寸宽度
CString m_LongS1=_T("a");  //自定义尺寸高度
CString m_suff=_T("1");   //用于存储用户选择的图片类型
CString m_SIZE;   //用于存储用户选择的图片切割单元的尺寸
CString m_SavePass;  //存储处理后图片的路径
CStringArray m_namePic;  //待处理图片路径
int k = 0; //用于记录处理了多少张图片
int k1 = 0; //用于记录共分割成多少张图片
int k2 = 0; //用于累计存储分割完成的图片数量
int k3 = 0; //用于累计处理过的图片数量
int num = 1;  //用于记录需要处理的图片数量

void CutPicture(CString name ,CString SavePath ,CString PictureSize,int l)   //分割图片
{
	string Name (CW2A(name.GetBuffer()));  //CString转string，图片名字初始化
	CString WIDE = PictureSize.Left(PictureSize.Find(_T("×"))); //获得分割后的小图片的宽度
	CString HIGH = PictureSize.Right(PictureSize.GetLength() - PictureSize.Find(_T("×")) -1); //获得分割后的小图像的高度
	if (SavePath[SavePath.GetLength() - 1] != _T('\\'))  //确保路径最后是'\'
		SavePath += _T('\\');
	string outpath(CW2A(SavePath.GetBuffer()));  //CString转string，存储路径初始化

	//将获取的高度宽度转换为整型
	int WiDe = _ttoi(WIDE);
	int HiGh = _ttoi(HIGH);

	Mat img = imread(Name, -1);
	
	//获取原图片会被分为多少块
	//double m1 = 1366.00 / 138;// img.cols / WiDe;
	int m = ceil((double)img.cols / WiDe);
	int n = ceil((double)img.rows / HiGh);

	vector <Mat> ceil_img;  //迭代器ceil_img存储子图像
	vector <int> name1;     //迭代器name1存储子图像的名字
	for (int t= 0; t < m*n; t++)
		name1.push_back(l+t);
	//int lll = ceil(9.056);
	k1 = k1 + m * n; //更新k1
	k2 = k2 + m * n; //更新k1

	Mat image_cut, roi_img, tim_img;
	int WideLast;
	int HighLast;
	for (int j = 0; j < n; j++)
	{
		if (j == n - 1)     //防止高不整除的时候丢失图片
			HighLast = img.rows - (n - 1)*HiGh;
		else
			HighLast = HiGh;
		for (int i = 0; i < m; i++)
		{
			if (i == m - 1)     //防止宽不整除的时候丢失图片
				WideLast = img.cols - (m - 1)*WiDe;
			else
				WideLast = WiDe;
			Rect rect(i * WiDe, j * HiGh, WideLast, HighLast);
			image_cut = Mat(img, rect);
			roi_img = image_cut.clone();
			ceil_img.push_back(roi_img);
		}
	}
	fstream PICTURE;
	for (int t = 0; t < m*n; t++)
	{
		while (1)  //防止覆盖已有图片
		{
			PICTURE.open((outpath + to_string(name1[t]) + ".jpg"), ios::in);
			if (!PICTURE)
				break;
			else
			{
				name1[t] = name1[t] + 1;
				PICTURE.close();
			}
		}
		imwrite(outpath + to_string(name1[t]) + ".jpg", ceil_img[t]);
	}
	k++;   //更新k
	return ;
}
