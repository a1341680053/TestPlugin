#include <iostream>
#include "ToolsLib/ToolsLib.h"

int main()
{
    // Test the ToolLib class
    ToolsLib *tool = ToolsLib::GetInstance();

    const int rows = 10000, cols = 10000;
    std::vector<LonLat> matrix;
    // 填充示例数据（实际应用中应替换为真实经纬度）
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            LonLat latlon;
            latlon.lat = -90.0 + 180.0 * i / rows;
            latlon.lon = -180.0 + 360.0 * j / cols;
            latlon.isLand = false; // 默认值
            matrix.push_back(latlon);
        }
    }
    // 处理矩阵数据
    tool->checkMatrixLandParallel(matrix, 10);
    return 0;
}