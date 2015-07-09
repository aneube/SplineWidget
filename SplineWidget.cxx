#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSplineWidget2.h>
#include "vtkSplineRepresentation.h"
#include <vtkProperty.h>
#include <vtkIOStream.h>
#include <fstream>


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
  rep1->SetHandleSize(9);
  rep1->SetNumberOfHandles(5);
  double position[3];
  position[0] = 0;
  position[1] = 0.8;
  position[2] = 0.1;
  rep1->SetHandlePosition(0,position);

  position[0] = 0;
  position[1] = 0.65;
  position[2] = 0.17;
  rep1->SetHandlePosition(1, position);

  position[0] = 0;
  position[1] = 0.5;
  position[2] = 0.32;
  rep1->SetHandlePosition(2, position);

  position[0] = 0;
  position[1] = 0.32;
  position[2] = 0.52;
  rep1->SetHandlePosition(3, position);

  position[0] = 0;
  position[1] = 0.2;
  position[2] = 0.9;
  rep1->SetHandlePosition(4, position);
  
  /*
  vtkSmartPointer<vtkProperty> colorProperty;
  colorProperty->SetColor(0.5, 0.5, 0.5);
  rep1->SetHandleProperty(colorProperty);
  */

  splineWidget->SetRepresentation(rep1);
  //splineWidget->GetRepresentation()->SetHandleSize(10);

  renderWindowInteractor->Initialize();
  renderWindow->Render();

  splineWidget->On();
  renderer->ResetCamera();
  renderWindowInteractor->Start();
  
  for(int i=0; i<rep1->GetNumberOfHandles();++i)
  {
	  rep1->GetHandlePosition(i,position);
	  std::cout << i << ": " << position[0] << " " << position[1] << " " << position[2] << std::endl;
  }

  ofstream myfile;
  myfile.open("basantSpline.txt");
  myfile << "SplineSpine" << std::endl;
  for (int i = 0; i<rep1->GetNumberOfHandles(); ++i)
  {
	  rep1->GetHandlePosition(i, position);
	  myfile << i << ": " << position[0] << " " << position[1] << " " << position[2] << std::endl;
  }
  myfile.close();
  
  return EXIT_SUCCESS;

}