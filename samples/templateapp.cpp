#include <mujinvision/mujinvisionmanager.h>

#ifndef USE_LOG4CPP // logging

#define VMSAMPLE_LOG_INFO(msg) std::cout << msg << std::endl;
#define VMSAMPLE_LOG_ERROR(msg) std::cerr << msg << std::endl;

#else

#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Appender.hh>
#include "log4cpp/OstreamAppender.hh"
#include <log4cpp/SyslogAppender.hh>

LOG4CPP_LOGGER_N(vmsamplelogger, "mujinvisionmanager.samples.app");

#define VMSAMPLE_LOG_INFO(msg) LOG4CPP_INFO_S(vmsamplelogger) << msg;
#define VMSAMPLE_LOG_ERROR(msg) LOG4CPP_ERROR_S(vmsamplelogger) << msg;

#endif // logging

using namespace mujinvision;

class UserImageSubscriberManager : public ImageSubscriberManager
{
public:
    UserImageSubscriberManager(){
    }

    virtual ~UserImageSubscriberManager() {
    }

    void Initialize(const std::map<std::string, CameraPtr >&mNameCamera, const std::string& streamerIp, const unsigned int streamerPort, const ptree& params, boost::shared_ptr<zmq::context_t>) {
    }

    void DeInitialize() {
    }

    ImagePtr GetColorImageFromBuffer(const std::string& cameraname, unsigned long long& timestamp, unsigned long long& endtimestamp, const double& timeout)
    {
        return ImagePtr();
    }
    ImagePtr SnapColorImage(const std::string& cameraname, unsigned long long& timestamp, unsigned long long& endtimestamp, const double& timeout=1.0)
    {
        return ImagePtr();
    }

    ImagePtr GetDepthImageFromBuffer(const std::string& cameraname, unsigned long long& starttime, unsigned long long& endtime, const double& timeout)
    {
        return ImagePtr();
    }
    ImagePtr SnapDepthImage(const std::string& cameraname, unsigned long long& starttime, unsigned long long& endtime, const double& timeout=1.0, const int numimages=-1)
    {
        return ImagePtr();
    }

    void GetImagePackFromBuffer(const std::vector<std::string>& colorcameranames, const std::vector<std::string>& depthcameranames, std::vector<ImagePtr>& colorimages, std::vector<ImagePtr>& depthimages, std::vector<ImagePtr>& resultimages, unsigned long long& starttime, unsigned long long& endtime, const double& timeout)
    {
    }
    void StartCaptureThread(const std::vector<std::string>& cameranames, const double& timeout=5.0, const int numimages=-1)
    {
    }

    void StopCaptureThread(const std::vector<std::string>& cameranames, const double& timeout=5.0)
    {
    }

    void WriteColorImage(const std::string& cameraname, const std::string& filename) {
    }

    void WriteDepthImage(const std::string& cameraname, const std::string& filename) {
    }

    void GetCollisionPointCloud(const std::string& cameraname, std::vector<double>& points, unsigned long long& starttime, unsigned long long& endtime, const double voxelsize, const double stddev, const size_t numnn) {
    }
};

typedef boost::shared_ptr<UserImageSubscriberManager> UserImageSubscriberManagerPtr;
typedef boost::shared_ptr<UserImageSubscriberManager const> UserImageSubscriberManagerConstPtr;
typedef boost::weak_ptr<UserImageSubscriberManager> UserImageSubscriberManagerWeakPtr;

class UserObjectDetector : public ObjectDetector
{
public:
    UserObjectDetector() {
    }

    virtual ~UserObjectDetector() {
    }

    void Initialize(const ptree& oparams_pt, const ptree& dparams_pt, const std::string& targetname, const std::map<std::string, RegionPtr >& mNameRegion, const std::map<std::string, std::map<std::string, CameraPtr > >& mRegionColorCameraMap, const std::map<std::string, std::map<std::string, CameraPtr > >& mRegionDepthCameraMap, const std::map< std::string, std::string>& extraInitializationOptions = std::map< std::string, std::string>(), const bool getgil=false) {
    }

    void DeInitialize() {
    }

    void DetectObjects(const std::string& regionname, const std::string& colorcameraname, const std::string& depthcameraname, std::vector<DetectedObjectPtr>& detectedobjects, std::string& resultstate, const bool fastdetection, const bool bindetection) {
    }

    void DetectObjects(const std::string& regionname, const std::vector<std::string>& colorcameranames, const std::vector<std::string>& depthcameranames, const std::vector<ImagePtr>& resultimages, std::vector<DetectedObjectPtr>& detectedobjects, std::string& resultstate, const bool fastdetection, const bool bindetection) {
    }

    void DetectInImage(const std::string& regionname, const std::string& colorcameraname, std::vector<DetectedObjectPtr>& resultscolorcamera) {
    }

    void RefineDetectionWithDepthData(const std::string& regionname, const std::string& colorcameraname, const std::string& depthcameraname, const std::vector<DetectedObjectPtr>& resultscolorcamera, std::vector<DetectedObjectPtr>& resultsdepthcamera, std::vector<unsigned int>& indicescolorcamera) {
    }

    void GetPointCloudObstacle(const std::string& regionname, const std::string& depthcameraname, const std::vector<DetectedObjectPtr>& resultsdepthcamera, std::vector<double>& points, const double voxelsize=0.01, const bool fast=false, const bool getgil=false, const double stddev=0.01, const size_t numnn=80) {
    }

    void GetCameraPointCloud(const std::string& regionname, const std::string& depthcameraname, ImageConstPtr depthimage, std::vector<double>& points) {
    }

    void SetImage(const std::string& colorcameraname, ImageConstPtr colorimage) {
    }
};
typedef boost::shared_ptr<UserObjectDetector> UserObjectDetectorPtr;

class UserDetectorManager : public DetectorManager
{
public:
    UserDetectorManager() {
    }
    virtual ~UserDetectorManager() {
    }

    ObjectDetectorPtr CreateObjectDetector(const ptree& objectparams_pt, const ptree& detectionparams_pt, const std::string& targetname, std::map<std::string, RegionPtr > mNameRegion, std::map<std::string, std::map<std::string, CameraPtr > > mRegionColorCameraMap, std::map<std::string, std::map<std::string, CameraPtr > > mRegionDepthCameraMap, const boost::function<void(const std::string& msg, const std::string& err)>& setstatusfn)
    {
        UserObjectDetectorPtr detector(new UserObjectDetector());
        return boost::dynamic_pointer_cast<ObjectDetector>(detector);
    }
};

typedef boost::shared_ptr<UserDetectorManager> UserDetectorManagerPtr;
typedef boost::shared_ptr<UserDetectorManager const> UserDetectorManagerConstPtr;
typedef boost::weak_ptr<UserDetectorManager> UserDetectorManagerWeakPtr;

int main(int argc, char* argv[])
{
#ifdef USE_LOG4CPP
    std::string logPropertiesFilename = "sample.properties";
    try{
        log4cpp::PropertyConfigurator::configure(logPropertiesFilename);
    } catch (log4cpp::ConfigureFailure& e) {
        log4cpp::Appender *consoleAppender = new log4cpp::OstreamAppender("console", &std::cout);
        std::string pattern = "%d %c [%p] %m%n";
        log4cpp::PatternLayout* patternLayout0 = new log4cpp::PatternLayout();
        patternLayout0->setConversionPattern(pattern);
        consoleAppender->setLayout(patternLayout0);

        log4cpp::Category& rootlogger = log4cpp::Category::getRoot();
        rootlogger.setPriority(log4cpp::Priority::INFO);
        rootlogger.addAppender(consoleAppender);
        rootlogger.error("failed to load logger properties at %s, using default logger. error: %s", logPropertiesFilename.c_str(), e.what());
    }

#endif

    UserImageSubscriberManagerPtr imagesubscribermanager(new UserImageSubscriberManager());
    UserDetectorManagerPtr detectormanager(new UserDetectorManager());
    MujinVisionManagerPtr visionmanager;
    visionmanager.reset(new MujinVisionManager(imagesubscribermanager, detectormanager,50001, 50002, 50003, "/tmp"));
    while (!visionmanager->IsShutdown()) {
        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    }

}
