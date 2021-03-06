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
  

  vtkSmartPointer<vtkSplineRepresentation> rep1 = vtkSmartPointer<vtkSplineRepresentation>::New();
  rep1->SetHandleSize(5.);
  rep1->SetNumberOfHandles(3);
  double position[3];
  position[0] = 1;
  position[1] = 1;
  position[2] = 1;
  rep1->SetHandlePosition(0,position);


  splineWidget->SetRepresentation(rep1);
  //splineWidget->GetRepresentation()->SetHandleSize(10);

  renderWindowInteractor->Initialize();
  renderWindow->Render();

  splineWidget->On();
  renderer->ResetCamera();
  renderWindowInteractor->Start();

 for(unsigned int i=1; i<rep1->GetNumberOfHandles();++i)
 {
  rep1->GetHandlePosition(i,position);
  std::cout << i << ": " << position[0] << " " << position[1] << " " << position[2] << std::endl;
 } 

return EXIT_SUCCESS;
}
