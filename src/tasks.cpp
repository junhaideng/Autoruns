#define _WIN32_DCOM
#include <windows.h>
#include "tasks.h"
#include <taskschd.h>
#include <QTableWidget>
#include <vector>
#include "comdef.h"
#include "utils.h"

using std::string, std::vector;

#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "comsupp.lib")

Tasks::Tasks()
{
}

// refer: https://docs.microsoft.com/en-us/windows/win32/taskschd/displaying-task-names-and-state--c---

void walkFolders(ITaskFolder *rootFolder, HRESULT hr, vector<info> &infos)
{
  ITaskFolderCollection *pFolders = NULL;
  // 获取rootFolder下面的目录
  hr = rootFolder->GetFolders(0, &pFolders);

  if (FAILED(hr))
  {
    return;
  }

  LONG numFolders = 0;
  // 获取子目录个数
  hr = pFolders->get_Count(&numFolders);
  //printf("Number of Folders:%d", numFolders);
  if (FAILED(hr))
  {
    return;
  }

  for (LONG i = 0; i < numFolders; i++)
  {
    ITaskFolder *pRootFolder = NULL;
    // 遍历子目录
    hr = pFolders->get_Item(_variant_t(i + 1), &pRootFolder);
    if (SUCCEEDED(hr))
    {

      // 递归遍历
      walkFolders(pRootFolder, hr, infos);

      BSTR name = NULL;
      hr = pRootFolder->get_Name(&name);
      if (FAILED(hr))
      {
        return;
      }
      //      printf("\nFolder Name: %S", name);
      SysFreeString(name);

      // 遍历tasks
      IRegisteredTaskCollection *pTaskCollection = NULL;
      hr = pRootFolder->GetTasks(NULL, &pTaskCollection);
      LONG numTasks = 0;
      pTaskCollection->get_Count(&numTasks);

      for (LONG i = 0; i < numTasks; i++)
      {
        IRegisteredTask *pRegisterdTask = NULL;
        hr = pTaskCollection->get_Item(_variant_t(i + 1), &pRegisterdTask);
        BSTR name = NULL, path = NULL, imagePath = NULL;
        if (SUCCEEDED(hr))
        {
          hr = pRegisterdTask->get_Name(&name);
          if (SUCCEEDED(hr))
          {
            hr = pRegisterdTask->get_Path(&path);
            if (SUCCEEDED(hr))
            {
              ITaskDefinition *taskDefination = NULL;
              hr = pRegisterdTask->get_Definition(&taskDefination);
              if (SUCCEEDED(hr))
              {
                // 获取actions中的
                IActionCollection *taskActions = NULL;
                hr = taskDefination->get_Actions(&taskActions);
                if (SUCCEEDED(hr))
                {
                  IAction *action = NULL;
                  hr = taskActions->get_Item(1, &action);
                  if (SUCCEEDED(hr))
                  {
                    taskActions->Release();
                    IExecAction *execAction = NULL;
                    hr = action->QueryInterface(IID_IAction, (void **)&execAction);
                    if (SUCCEEDED(hr))
                    {
                      action->Release();
                      hr = execAction->get_Path(&imagePath);
                      if (FAILED(hr))
                      {
                        printf("Can not get path: %lx\n", hr);
                      }
                    }
                    else
                    {
                      printf("Can not query interface: %lx\n", hr);
                    }
                  }
                  else
                  {
                    printf("Can not get item: %lx\n", hr);
                  }
                }
                else
                {
                  printf("Can not get actions: %lx\n", hr);
                }
                taskDefination->Release();
              }
              else
              {
                printf("Can not get definition: %lx\n", hr);
              }
            }
            else
            {
              printf("Can not get path: %lx\n", hr);
            }
          }
          else
          {
            printf("Can not get name: %lx\n", hr);
          }
        }
        else
        {
          printf("Can not get task item: %lx\n", hr);
        }

        string parsed_path = parse(bstr2std(imagePath));
        infos.push_back(info{
            .name = QString::fromStdString(bstr2std(path)),
            .desc = QString::fromStdString(GetFileDetailInfoByValue("FileDescription", parsed_path)),
            .company = QString::fromStdString(GetFileDetailInfoByValue("CompanyName", parsed_path)),
            .image_path = QString::fromStdString(parsed_path),
            .isVerified = VerifyEmbeddedSignature(QString::fromStdString(parsed_path).toStdWString().data())});
      }
    }
  }
  pFolders->Release();
}

int Tasks::setTableData(QTableWidget *table)
{
  //  ------------------------------------------------------
  //  Initialize COM.
  HRESULT hr = NULL;

  //  ------------------------------------------------------
  //  Create an instance of the Task Service.
  ITaskService *pService = NULL;
  hr = CoCreateInstance(CLSID_TaskScheduler,
                        NULL,
                        CLSCTX_INPROC_SERVER,
                        IID_ITaskService,
                        (void **)&pService);
  vector<info> infos;
  if (FAILED(hr))
  {
    printf("Failed to CoCreate an instance of the TaskService class: %lx", hr);
    CoUninitialize();
    return 1;
  }

  //  Connect to the task service.
  hr = pService->Connect(_variant_t(), _variant_t(),
                         _variant_t(), _variant_t());
  if (FAILED(hr))
  {
    printf("ITaskService::Connect failed: %lx", hr);
    pService->Release();
    CoUninitialize();
    return 1;
  }

  //  ------------------------------------------------------
  //  Get the pointer to the root task folder.
  ITaskFolder *pRootFolder = NULL;
  hr = pService->GetFolder(_bstr_t(L"\\"), &pRootFolder);

  walkFolders(pRootFolder, hr, infos);

  pService->Release();
  if (FAILED(hr))
  {
    printf("Cannot get Root Folder pointer: %lx", hr);
    CoUninitialize();
    return 1;
  }

  table->setRowCount(infos.size());
  for (size_t i = 0; i < infos.size(); i++)
  {
    table->setItem(i, 0, new QTableWidgetItem(infos[i].name));
    table->setItem(i, 1, new QTableWidgetItem(infos[i].desc));
    table->setItem(i, 2, new QTableWidgetItem(infos[i].company));
    table->setItem(i, 3, new QTableWidgetItem(verifyStr(infos[i].isVerified)));
    table->setItem(i, 4, new QTableWidgetItem(infos[i].image_path));
  }

  return 0;
}
