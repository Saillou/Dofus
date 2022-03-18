#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class FontEngine {
public:
	FontEngine(const std::string& fontImgPath);

private:
	// Methods
	void _cell(int x, int y);

	// Members
	const cv::Rect	_DRECT;
	cv::Mat			_internalFrame;
	bool			_validCtx;
};