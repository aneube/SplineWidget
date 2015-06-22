#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSplineWidget2.h>
#include "vtkSplineRepresentation.h"

int main(int, char *[])
{
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkSplineWidget2> splineWidget = 
    vtkSmartPointer<vtkSplineWidget2>::New();
  splineWidget->SetInteractor(renderWindowInteractor);
  

  //vtkSmartPointer<vtkSplineRepresentation> rep1 = vtkSmartPointer<vtkSplineRepresentation>::New();
  //rep1->SetHandleSize(10.);
  //splineWidget->SetRepresentation(rep1);
  splineWidget->GetRepresentation()->SetHandleSize(10);
  splineWidget->GetRepresentation()->SetNumberOfHandles(3);

  renderWindowInteractor->Initialize();
  renderWindow->Render();
  //splineWidget->SetResolution(10);
  splineWidget->On();
  renderer->ResetCamera();
  renderWindowInteractor->Start();
  
  std::cout << splineWidget->GetRepresentation()->GetNumberOfConsumers() << std::endl;
  std::cout << splineWidget->GetRepresentation()->GetNumberOfPaths() << std::endl;
  std::cout << splineWidget->GetRepresentation()-> << std::endl;

  return EXIT_SUCCESS;
}
