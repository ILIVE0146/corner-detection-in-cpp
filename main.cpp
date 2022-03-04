#include <SFML/Graphics.hpp>
#include <iostream>

#include <opencv2/photo.hpp>
#include "opencv2/imgcodecs.hpp"

#include "globalVariables.hpp"
#include "gui/TextBox.hpp"
#include "gui/button.hpp"

#include "lodepng.h"

#include "nncam.h"

#include "Line.hpp"
#include "ControlPanel.hpp"
#include "errorMessage.hpp"

using namespace cv;

struct ImageData
{
    HNncam g_hcam = NULL;
    void *g_pImageData = NULL;
    unsigned char *out = NULL;
    std::size_t outSize;
    NncamFrameInfoV2 info = {0};
    bool isFrameReady = false;
} Data;

struct Detection
{
    void autoDetect();
    std::vector<cv::Point2f> corners;

    bool isReady = false;
    bool isThreadActive = false;
    bool error = false;
};

void Detection::autoDetect()
{
    isThreadActive = true;

    int MAX_KERNEL_LENGTH = 200;
    cv::Mat src, dst;

    sf::Image image;
    if (!image.loadFromMemory(Data.out, Data.outSize))
    {
        printf("Failed to load data from memory, please try again");
        error = true;
    }
    else if (!image.saveToFile("resources/img/input.png"))
    {
        printf("Failed to save image, please try again");
        error = true;
    }
    else
    {
        // src = imdecode(std::vector<char>(Data.out, Data.out + Data.outSize), cv::IMREAD_GRAYSCALE);
        src = imread("resources/img/input.png", cv::IMREAD_GRAYSCALE);

        fastNlMeansDenoising(src, dst, 35);
        threshold(dst, src, 100, 255, THRESH_BINARY);
        fastNlMeansDenoising(src, dst, 50);

        Mat sharpeningKernel = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
        filter2D(dst, src, -1, sharpeningKernel);

        int maxCorners = 4;
        double qualityLevel = 0.2;
        double minDistance = 10;
        int blockSize = 10, gradientSize = 3;
        bool useHarrisDetector = true;
        double k = 0.04;
        goodFeaturesToTrack(src, corners, maxCorners, qualityLevel, minDistance, cv::Mat(), blockSize, gradientSize, useHarrisDetector, k);
    }

    isReady = true;
    isThreadActive = false;
}

static void __stdcall EventCallback(unsigned nEvent, void *pCallbackCtx)
{
    if (NNCAM_EVENT_IMAGE == nEvent)
    {

        HRESULT hr = Nncam_PullImageV2(Data.g_hcam, Data.g_pImageData, 24, &Data.info);
        if (FAILED(hr))
            printf("failed to pull image, hr = %08x\n", hr);
        else if (lodepng_encode24(&Data.out, &Data.outSize, reinterpret_cast<unsigned char *>(Data.g_pImageData), Data.info.width, Data.info.height) == 0)
        {
            Data.isFrameReady = true;
        }
    }
}

int main()
{
    sf::Font opensans;
    opensans.loadFromFile(FONT);

    NncamDeviceV2 tdev[NNCAM_MAX] = {0};
    unsigned ncam = Nncam_EnumV2(tdev);
    if (0 == ncam)
    {
        printf("no camera found\n");
        errorMessage("no camera found", opensans);
        return 1;
    }

    Data.g_hcam = Nncam_Open(tdev[0].id);
    if (NULL == Data.g_hcam)
    {
        printf("failed to open camera\n");
        errorMessage("failed to open camera", opensans);
        return 2;
    }

    int nWidth = 0, nHeight = 0;
    HRESULT hr = Nncam_get_Size(Data.g_hcam, &nWidth, &nHeight);
    if (FAILED(hr))
    {
        printf("failed to get size, hr = %08x\n", hr);
        errorMessage("failed to get size, " + hr, opensans);
        return 3;
    }
    else
    {
        Data.g_pImageData = malloc(TDIBWIDTHBYTES(24 * nWidth) * nHeight);
        if (NULL == Data.g_pImageData)
        {
            printf("failed to malloc\n");
            errorMessage("failed to malloc", opensans);
            return 4;
        }
        else
        {
            hr = Nncam_StartPullModeWithCallback(Data.g_hcam, EventCallback, NULL);
            if (FAILED(hr))
            {
                printf("failed to start camera, hr = %08x\n", hr);
                errorMessage("failed to start camera, " + hr, opensans);
                return 5;
            }
        }
    }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "app", sf::Style::Close, settings);

    ControlPanel panel(opensans);

    sf::Texture imageTex;
    sf::Sprite imgDisplay;

    sf::Clock deltaClock;
    sf::Time dt = sf::seconds(0.f);
    imgDisplay.setScale({IMAGE_SCALE, IMAGE_SCALE});
    sf::Vector2i mousePrevPos = {0, 0};

    Detection obj;
    sf::Thread detector(&Detection::autoDetect, &obj);
    std::vector<sf::CircleShape> Detectedpoints;

    while (window.isOpen())
    {

        auto mousePos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                panel.checkLine(event, mousePos);
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                panel.resetSelected();
            }
            panel.eventHandler(event, window);
        }

        panel.update(dt, window, mousePrevPos);

        if (panel.checkOpencvstatus() == true && obj.isThreadActive == false && Data.isFrameReady == true)
        {
            detector.launch();
            panel.getOpencvBtn().getSFText().setString("detecting...");
            panel.checkOpencvstatus() = false;
        }
        if (obj.isReady == true)
        {
            Detectedpoints.clear();
            obj.isReady = false;
            panel.getOpencvBtn().getSFText().setString("Auto Detect");

            auto lines = panel.getLines();
            if (obj.corners.size() < 4 || obj.error == true)
            {
                obj.error = false;
                printf("couldn't Detecting 4 points\n");
                errorMessage("couldn't Detecting 4 points", opensans);
            }
            else
            {
                sf::Vector2i vl = {SCREEN_WIDTH, 0}, vr = {0, 0}, hu = {0, SCREEN_HEIGHT}, hd = {0, 0};
                std::vector<int> xbuf, ybuf;
                for (auto i = obj.corners.begin(); i != obj.corners.end(); i++)
                {
                    xbuf.push_back(static_cast<int>(i->x));
                    ybuf.push_back(static_cast<int>(i->y));
                }
                std::stable_sort(xbuf.begin(), xbuf.end());
                std::stable_sort(ybuf.begin(), ybuf.end());
                lines.at(0)->getRectangle().setPosition(lines.at(0)->getRectangle().getPosition().x, ybuf.front() * IMAGE_SCALE);
                lines.at(1)->getRectangle().setPosition(lines.at(1)->getRectangle().getPosition().x, ybuf.back() * IMAGE_SCALE);
                lines.at(2)->getRectangle().setPosition(xbuf.front() * IMAGE_SCALE, lines.at(2)->getRectangle().getPosition().y);
                lines.at(3)->getRectangle().setPosition(xbuf.back() * IMAGE_SCALE, lines.at(3)->getRectangle().getPosition().y);
            }
        }

        if (Data.isFrameReady == true)
        {

            if (imageTex.loadFromMemory(Data.out, Data.outSize))
            {
                imgDisplay.setTexture(imageTex);
            }
            Data.isFrameReady = false;
        }

        window.clear(sf::Color::Green);

        window.draw(imgDisplay);

        if (Detectedpoints.size() != 0)
        {
            for (auto i = Detectedpoints.begin(); i != Detectedpoints.end(); i++)
            {
                window.draw(*i);
            }
        }

        panel.drawTo(window);

        window.display();

        mousePrevPos = mousePos;

        dt = deltaClock.restart();
    }
    /* cleanup */
    Nncam_Close(Data.g_hcam);
    if (Data.g_pImageData)
        free(Data.g_pImageData);
    if (Data.out)
        free(Data.out);
    return 0;
}
