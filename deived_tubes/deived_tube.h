#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<string>
using namespace cv;
using namespace std;
class deived_tube
{
public:
	static int cp;
	static int n_id;

	int id;
	int start;
	int end;
	int length;
	Mat **data;
	deived_tube*next;
	deived_tube(int astart,int aend)
	{
		id = ++n_id;
		next = nullptr;
		start = astart;
		end = aend;
		length = end - start + 1;
		data = new Mat*[length];
		for (int i = 0;i < length;++i)
		{
			data[i] = nullptr;
		}
	}
	void insert(int time,Mat * a)
	{

		if (data[time])
		{
			(*data[time]) |= *a;

			return;
		}

		data[time] = a;


	}
	void add(deived_tube& other, deived_tube& dst)
	{
		if (other.start > start)
		{
			dst.start = start;
		}
		else
		{
			dst.start = other.start;
		}
		if (other.end > end)
		{
			dst.end = other.end;
		}
		else
		{
			dst.end = end;
		}
		dst.length = dst.end - dst.start + 1;
		dst.data = new Mat*[length];
		for (int i = 0;i < length;++i)
		{
			dst.data[start - dst.start + i] = data[i];
		}
		for (int i = 0;i < other.length;++i)
		{
			if (dst.data[other.start - dst.start + i])
			{
				*dst.data[other.start - dst.start + i] |= *other.data[i];
			}
			else
			{
				dst.data[start - dst.start + i] = other.data[i];
			}
		}
		dst.id = other.id ;
		delete []data;
		data = nullptr;
		delete []other.data;
		other.data = nullptr;
		end = 0;
		other.end = 0;
	}


	void save(string file)
	{
		system((string("md ") + file + "\\" + to_string(++cp)).c_str());
		for (int i = 0;i < length;++i)
		{
			if (data[i])
			{
				imwrite(file + "\\" + to_string(cp) + "\\" + to_string(i + start) + ".png", *data[i]);
			}
			else
			{
				return;
			}
		}
	}
};
int deived_tube::cp = 0;
int deived_tube::n_id=0;
