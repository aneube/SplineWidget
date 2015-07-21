#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSplineWidget2.h>
#include "vtkSplineRepresentation.h"
#include <vtkProperty.h>
#include <vtkIOStream.h>
#include <fstream>
#include <string>

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
  
 
  using namespace std;
  ifstream file;
  file.open("SplineSpine.txt");
  string word;
  double position[3];

  if (!file.is_open())
  {
	  rep1->SetNumberOfHandles(5);
	  position[0] = 0;
	  position[1] = 0.8;
	  position[2] = 0.1;
	  rep1->SetHandlePosition(0, position);

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

	  cout << "File not found, output by default \n";
  }
  else
  {
	  // Read the first word from the file
	  file >> word;
	  // Check if it matches the keyword
	  if (word.compare("SplineSpine"))
	  {
		  cout << "ERROR when reading input file - not the correct format." << endl;
		  return EXIT_FAILURE;
	  }
	  else
	  {
		  cout << "Input file is correct." << endl;
	  }

	  // Read the second word from the file - number of handles
	  file >> word;
	  int numberOfHandles = atoi(word.c_str());
	  cout << "Number of Handles: " << numberOfHandles << endl <<endl;
	  rep1->SetNumberOfHandles(numberOfHandles);
	  
	  for (int i = 0; i < numberOfHandles; i++)
	  {
		  file >> word;
		  double x = std::stod(word);

		  file >> word;
		  double y = std::stod(word);

		  file >> word;
		  double z = std::stod(word);
		 
		  cout << x <<" "<< y <<" "<< z << endl;
		  rep1->SetHandlePosition(i, x, y, z);
	  }
	  cout<<"Read Successfully \n"<<endl;
    }

  /*
  vtkSmartPointer<vtkProperty> colorProperty;
  colorProperty->SetColor(0.5, 0.5, 0.5);
  rep1->SetHandleProperty(colorProperty);
  */

  rep1->ProjectToPlaneOn();

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
  myfile.open("SplineSpine.txt");
  myfile <<"SplineSpine" << std::endl;
  myfile << rep1->GetNumberOfHandles() << std::endl;
  
  for (int i = 0; i<rep1->GetNumberOfHandles(); ++i)
  {
	  rep1->GetHandlePosition(i, position);
	  myfile << position[0] << "  " << position[1] << "  " << position[2] << std::endl;
  }
  cout<<"Written Successfully\n\n";
  myfile.close();
  
  return EXIT_SUCCESS;
}