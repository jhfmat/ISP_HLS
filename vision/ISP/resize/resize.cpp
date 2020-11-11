#include<iostream>
#include<cmath>
#include<math.h>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

cv::Mat org, dst, img, tmp, large_img;
int drawing = 0;

Mat enlarge_img(Mat src, int scaleW, int scaleH, int method = 1)
{
	int  width = (src.cols)*scaleW;
	int  height = (src.rows)*scaleH;
	if (method == 1)// Nearest Neighbor Interpolation 
	{
		resize(src, large_img, Size(width, height), 0, 0, 1);
	}
	else if (method == 2)// Bilinear interpolation 
	{
		resize(src, large_img, Size(width, height), 0, 0, 2);
	}
	else if (method == 3)// Area Interpolation
	{
		resize(src, large_img, Size(width, height), 0, 0, 3);
	}
	else
	{
		printf("%s\n", "����ģʽʧ�ܣ�����ģʽ1,2,3�н���ѡ�񣩣�");
		system("pause");
	}
	return large_img;
}
void on_mouse(int event, int x, int y, int flags, void *ustc)//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���  
{
	static Point pre_pt = Point(-1, -1);//��ʼ����  
	static Point cur_pt = Point(-1, -1);//ʵʱ����  
	char temp[16];
	if (event == CV_EVENT_LBUTTONDOWN)//������£���ȡ��ʼ���꣬����ͼ���ϸõ㴦��Բ  
	{
		org.copyTo(img);//��ԭʼͼƬ���Ƶ�img��
		pre_pt = Point(x, y);
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//��Բ  
		imshow("img", img);
		drawing = 1;
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//���û�а��µ����������ƶ��Ĵ�����  
	{
		img.copyTo(tmp);//��img���Ƶ���ʱͼ��tmp�ϣ�������ʾʵʱ����  
		cur_pt = Point(x, y);
		imshow("img", tmp);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//�������ʱ������ƶ�������ͼ���ϻ�����  
	{
		img.copyTo(tmp);
		cur_pt = Point(x, y);
		rectangle(tmp, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//����ʱͼ����ʵʱ��ʾ����϶�ʱ�γɵľ���  
		imshow("img", tmp);
	}
	else if (event == CV_EVENT_LBUTTONUP)//����ɿ�������ͼ���ϻ�����  
	{
		if (drawing == 1)
		{
			drawing = 0;
			org.copyTo(img);
			cur_pt = Point(x, y);
			circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
			rectangle(img, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//���ݳ�ʼ��ͽ����㣬�����λ���img��  
			imshow("img", img);
			img.copyTo(tmp);
			//��ȡ���ΰ�Χ��ͼ�񣬲����浽dst��  
			int width = abs(pre_pt.x - cur_pt.x);
			int height = abs(pre_pt.y - cur_pt.y);
			dst = org(Rect(min(cur_pt.x, pre_pt.x), min(cur_pt.y, pre_pt.y), width, height));
			namedWindow("dst");
			imshow("dst", dst);
			waitKey(0);

			int scaleW = 5;//�Ŵ���
			int scaleH = 5;
			int method = 3;//ѡ�񷽷�
			large_img = enlarge_img(dst, scaleW, scaleH, method);
			namedWindow("large_img");
			imshow("large_img", large_img);
			waitKey(0);
		}



	}

}


int main()
{
	string image_name = "meat1";
	string path = "c:/users/wpp/desktop/����/isp-master";
	org = imread(path + "/images/images/" + image_name + ".jpg");
	org.copyTo(img);
	org.copyTo(tmp);
	namedWindow("img");//����һ��img����  
	setMouseCallback("img", on_mouse, 0);//���ûص�����  ��on_mouse����ѡ��ʽ1,2,3
	imshow("img", img);
	waitKey(0);
}
