#include <iostream>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include "FontEngine.hpp"


int failure(const std::string& msg) {
	std::cout << msg << std::endl;
	system("pause");
	return 1;
}

void readLine(const cv::Mat& frame) {
	cv::Mat output, stats, centroids;
	int n = cv::connectedComponentsWithStats(frame, output, stats, centroids, 4);
	
	// Results
	cv::Mat results;
	cv::cvtColor(frame, results, cv::COLOR_GRAY2BGR);

	for (int i = 1; i < n; i++) {
		cv::Rect rect(
			stats.at<int>(cv::Point(0, i))-2,
			stats.at<int>(cv::Point(1, i))-2,
			stats.at<int>(cv::Point(2, i))+4,
			stats.at<int>(cv::Point(3, i))+4
		);

		//cv::Scalar color(rand() % 255, rand() % 255, rand() % 255);
		//cv::rectangle(results, rect, color);

		cv::imshow("line " + std::to_string(i), frame(rect));
	}

	cv::imshow("readLine", results);
}

int main() {
	// Font engine
	FontEngine font("dofusFont.png");
	return 0;

	// Open image
	cv::Mat rawFrame(cv::imread("screen.png"));
	if (rawFrame.empty())
		return failure("Can't open image");

	// Select ROIs
	cv::Rect caractZone(584, 448, 384, 145);
	std::vector<cv::Rect> caractLines = {
		cv::Rect(0, 36*0, 300, 36),
		cv::Rect(0, 36*1, 300, 36),
		cv::Rect(0, 36*2, 300, 36),
		cv::Rect(0, 36*3, 300, 36)
	};

	// Pre-filter
	std::vector<cv::Mat> linesFrame;
	for (auto rect : caractLines) {
		cv::Rect roi(caractZone.x + rect.x + 2, caractZone.y + rect.y + 2, rect.width - 4, rect.height - 4);
		cv::Mat frame = rawFrame(roi);
		cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
		cv::threshold(frame, frame, 100, 255, cv::THRESH_BINARY_INV);

		linesFrame.emplace_back(frame);
	}

	// Read
	readLine(linesFrame[0]);

	// Draw debug
	cv::rectangle(rawFrame, caractZone, cv::Scalar(255, 0, 0), 1, cv::LINE_AA);
	for (const cv::Rect& rect : caractLines) {
		cv::Rect roi(caractZone.x + rect.x, caractZone.y + rect.y, rect.width, rect.height);
		cv::rectangle(rawFrame, roi, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
	}

	//for (size_t i = 0; i < linesFrame.size(); i++) {
	//	cv::imshow("line " + std::to_string(i), linesFrame[i]);
	//}

	cv::imshow("frame", rawFrame);
	cv::waitKey(0);

	return 0;
}