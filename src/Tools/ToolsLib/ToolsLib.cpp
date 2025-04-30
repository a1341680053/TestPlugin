#include "ToolsLib/ToolsLib.h"
#include "gdal.h"
#include "ogr_api.h"
#include "ogr_geometry.h"
#include "gdaljp2abstractdataset.h"
#include "ogrsf_frmts.h"
#include <QApplication>
#include "ToolsLib.h"
#include <QDebug>
#include <cerrno>
#include <thread>

ToolsLib* ToolsLib::mInstance = nullptr;

ToolsLib::ToolsLib(QObject *parent) : QObject(parent)
{
    init();
}

void ToolsLib::init()
{
    mPath = QApplication::applicationDirPath().toStdString() + "/../data/land.shp";
    // Initialize GDAL and OGR
    GDALAllRegister();
    // OGRRegisterAll();
}

ToolsLib::~ToolsLib()
{
}

ToolsLib* ToolsLib::GetInstance()
{
    if (mInstance == nullptr)
    {
        mInstance = new ToolsLib();
    }
    return mInstance;
}

void ToolsLib::setPath(const char *path)
{
    mPath = path;
}

void ToolsLib::checkMatrixLandParallel(std::vector<LonLat> &latlon, int maxThreads)
{
    std::vector<std::thread> threads;
    std::mutex mtx;
    std::atomic<int> progress(0);

    size_t rows = latlon.size() / maxThreads;
 
    
   for (int i = 0; i < maxThreads; ++i) {
       size_t startRow = i * rows;
       size_t endRow = (i == maxThreads - 1) ? latlon.size() : startRow + rows;

       threads.emplace_back(&ToolsLib::processRow, this, std::ref(latlon), startRow, endRow - 1, std::ref(mtx), std::ref(progress));

       if (threads.size() >= maxThreads) {
           for (auto &t : threads) t.join();
           threads.clear();
       }
   }
}

void ToolsLib::processRow(std::vector<LonLat> &data, int startRow, int endRow, std::mutex &mtx, std::atomic<int> &progress)
{
    std::vector<LonLat> tempV(data.begin() + startRow, data.begin() + endRow);
    bool retB = isLand(mPath.c_str(), tempV);

    if (retB)
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::copy(tempV.begin(), tempV.end(), data.begin() + startRow);
        progress++;
    }
}

bool ToolsLib::isLand(const char *path, std::vector<LonLat> &latlon)
{
    // 每个线程独立打开数据集，避免共享资源冲突
    GDALDataset *poDS = (GDALDataset *)GDALOpenEx(path, GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
    if (!poDS) {
        // std::cerr << "Failed to open shapefile." << std::endl;
        return false;
    }

    for (auto i : latlon)
    {
        OGRLayer *poLayer = poDS->GetLayer(0);
        poLayer->ResetReading();

        // 创建点几何对象（WGS84 坐标系）
        OGRPoint point(i.lon, i.lat);
        point.assignSpatialReference(poLayer->GetSpatialRef());

        bool isLand = false;
        OGRFeature *poFeature;
        while ((poFeature = poLayer->GetNextFeature()) != nullptr) {
            OGRGeometry *poGeometry = poFeature->GetGeometryRef();
            if (poGeometry && poGeometry->Contains(&point)) {
                isLand = true;
                OGRFeature::DestroyFeature(poFeature);
                break;
            }
            OGRFeature::DestroyFeature(poFeature);
        }
        i.isLand = isLand;
    }
    return true;
}
