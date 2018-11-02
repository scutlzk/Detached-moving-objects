/*

https://github.com/scutlzk/Detached-moving-objects
							by l1005152@gmail.com

*/
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stack>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include"bwlable.h"
#include"fillhole.h"
#include"deived_tube.h"
using namespace std;
using namespace cv;
string file;
int astart;
int aend;
int alength;
int main()
{
	int *fnum;
	Mat ***ftube;
	cout << "file£º";cin >> file;
	cout << "start frame: ";cin >> astart;
	cout << "end frame: ";cin >> aend;
	alength = aend - astart + 1;
	fnum = new int[alength];
	ftube = new Mat**[alength];
	for (int i = 0;i < alength;++i)
	{
		fnum[i] = 0;
		ftube[i] = nullptr;
	}
	for (int i = 0;i < alength;++i) 
	{

		cv::Mat binImage = cv::imread(file+"\\"+to_string(i+astart)+".png", 0);

		dilate(binImage, binImage, getStructuringElement(MORPH_CROSS, Size(5, 5)));
		chao_fillHole(binImage, binImage);
		erode(binImage, binImage, getStructuringElement(MORPH_CROSS, Size(5, 5)));

		cv::Mat labelImg;
		Two_PassNew(binImage, labelImg);

		cv::Mat colorLabelImg;
		int thissum;
		LabelColor(labelImg, colorLabelImg, thissum);

		fnum[i] = thissum;
		ftube[i] = new Mat*[thissum];
		for (int j = 0;j < thissum;++j)
		{
			ftube[i][j] = new Mat(Mat::zeros(colorLabelImg.size(), 0));
		}
		int sum = 0;

		for (int ii = 0;ii < colorLabelImg.rows;++ii)
		{
			for (int j = 0;j < colorLabelImg.cols;++j)
			{
				if (colorLabelImg.at<uchar>(ii, j))
				{

					ftube[i][colorLabelImg.at<uchar>(ii, j) - 1]->at<uchar>(ii, j) = 255;

				}
			}
		}

		for (int j = 0;j < thissum;++j)
		{
			if (countNonZero(*ftube[i][j]) < 30)
			{
				for (int asd = j;asd < thissum - 1;++asd)
				{
					ftube[i][asd] = ftube[i][asd + 1];
				}
				--j;
				--thissum;
			}
		}
		fnum[i] = thissum;
	}
	deived_tube head(0, 0);
	deived_tube* q = &head;
	for (int j = 0;j < fnum[0];++j)
	{

		deived_tube* p = new deived_tube(astart, aend);


		p->insert(0,ftube[0][j]);

		q->next = p;
		q = p;
	}

	for (int i = 1;i < alength;++i)
	{
		int **flag = new int*[fnum[i]];
		for (int j = 0;j < fnum[i];++j)
		{
			flag[j] = new int[2];
			flag[j][0] = 0;
			flag[j][1] = 0;
		}
		deived_tube* temp = head.next;
		while (temp)
		{

			for (int j = 0;j < fnum[i];++j)
			{
				if (temp->end&&temp->data[astart + i-temp->start - 1])
				{
					int qasd = countNonZero((*temp->data[astart + i - temp->start - 1])&(*ftube[i][j]));
					if (qasd)
					{
						//if ((!flag[j][0]))
						//{
							temp->insert(i+ astart - temp->start, ftube[i][j]);
							flag[j][0] = 1;
							flag[j][1] = temp->id;
					//	}
						/*else
						{
							deived_tube * dfg = &head;
							while (dfg->next)
							{
								if (dfg->next->id == flag[j][1])
								{
									deived_tube * zaq = new deived_tube(1,1);
									temp->add(*(dfg->next), *zaq);
									zaq->next = dfg->next->next;
									dfg->next = zaq;
								}
							}

						}*/
					}

				}
			}
			temp = temp->next;
		}

		for (int j = 0;j < fnum[i];++j)
		{
			if (!flag[j][0])
			{
				deived_tube* p = new deived_tube(astart+i, aend);

				p->insert(i + astart - p->start, ftube[i][j]);

				q->next = p;

				q = p;

			}
		}
	}
	deived_tube* lol = head.next;
	while (lol)
	{
		if (lol->end)
		{
			lol->save(file);
			cout << lol->id << endl;
		}
		lol = lol->next;
	}
}


