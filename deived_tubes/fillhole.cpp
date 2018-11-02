#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
void chao_fillHole(const cv::Mat srcimage, cv::Mat &dstimage)
{
	Size m_Size = srcimage.size();
	Mat temimage = Mat::zeros(m_Size.height + 2, m_Size.width + 2, srcimage.type());//ÑÓÕ¹Í¼Ïñ  
	srcimage.copyTo(temimage(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)));
	floodFill(temimage, Point(0, 0), Scalar(255));
	Mat cutImg;//²Ã¼ôÑÓÕ¹µÄÍ¼Ïñ  
	temimage(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)).copyTo(cutImg);
	dstimage = srcimage | (~cutImg);
}