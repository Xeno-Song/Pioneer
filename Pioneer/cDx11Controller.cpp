#include "cDx11Controller.h"

namespace pioEngine
{

    cDx11Controller::cDx11Controller()
    {
    }

    cDx11Controller::cDx11Controller(const cDx11Controller&)
    {
    }

    cDx11Controller::~cDx11Controller()
    {
    }

    bool cDx11Controller::Initialize(int screenWidth, int screenHeight, HWND hwnd)
    {
        bool result;

        m_device = new cDx11Device();
        if (m_device == nullptr)
            return false;

        result = m_device->Initialize(screenWidth, screenHeight, false, hwnd, false, 1000.0f, 0.1f);
        if (result == false)
        {
            MessageBox(hwnd, L"Could not initiazlie dx11 device", L"Error", MB_OK);
            return false;
        }

        return true;
    }

    void cDx11Controller::Cleanup()
    {
        if (m_device != nullptr)
        {
            m_device->Cleanup();
            delete m_device;
            m_device = nullptr;
        }
    }

    bool cDx11Controller::Frame()
    {
        bool result;

        result = Render();
        if (!result)
            return false;

        return true;
    }

    bool cDx11Controller::Render()
    {
        m_device->BeginScene(0.7f, 0.2f, 0.3f, 1.0f);
        m_device->EndScene();

        return true;
    }

}