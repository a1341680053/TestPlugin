#ifndef TOOLLIB_H
#define TOOLLIB_H

#include <QObject>
#include <map>
#include <mutex>
#include <atomic>
#include "ToolsLib/ToolsLib_global.h"

// class GDALDataset;

struct LonLat
{
    double lat;
    double lon;
    bool isLand;
};

class TOOLSLIB_EXPORT ToolsLib : public QObject
{
    Q_OBJECT
private:
    ToolsLib(QObject *parent = nullptr);
    ~ToolsLib();

    void init();

    static ToolsLib *mInstance;
public:
    static ToolsLib *GetInstance();

    /// @brief 设置陆海判断的shp文件路径
    /// @param path 路径
    void setPath(const char *path);

    /// @brief 检查经纬度是否在陆地上(线程池处理)
    /// @param latlon 
    /// @param maxThreads 
    void checkMatrixLandParallel(std::vector<LonLat> &latlon, int maxThreads = 10);

private:
    /// @brief 并行处理矩阵的线程任务
    /// @param data 
    /// @param startRow 
    /// @param endRow 
    /// @param mtx 
    /// @param progress 
    void processRow(std::vector<LonLat> &data, int startRow,int endRow, std::mutex &mtx, std::atomic<int> &progress);

    /// @brief 判断经纬度是否在陆地上(单线程处理)
    /// @param path shp文件路径
    /// @param latlon 经纬度数据集
    /// @return false = 路径错误
    bool isLand(const char *path, std::vector<LonLat> &latlon);

private:
    std::string mPath;
};

#endif // TOOLLIB_H