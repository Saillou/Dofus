#include "FontEngine.hpp"

FontEngine::FontEngine(const std::string& fontImgPath) :
	_internalFrame(cv::imread(fontImgPath)),
	_DRECT(10, 10, 36, 30),
	_validCtx(false)

{
	if (_internalFrame.empty())
		return;

	_validCtx = true;

	_cell(0, 1);
}

void FontEngine::_cell(int x, int y) {
	if (!_validCtx)
		return;

	const int px = _DRECT.width*x + _DRECT.x;
	const int py = _DRECT.height*y + _DRECT.y;

	cv::rectangle(_internalFrame, cv::Rect(px, py, _DRECT.width, _DRECT.height), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);

	cv::imshow("_internalFrame", _internalFrame);
	cv::waitKey(0);
}