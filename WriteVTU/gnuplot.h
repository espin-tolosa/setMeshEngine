#ifndef GNUPLOT_H_INCLUDED
#define GNUPLOT_H_INCLUDED

//*t/tfin;
//360*t/tfin;


    ofstream outFile_ofstream; //create an object type ofstream called outFile_ofstream
    ofstream gnuPlot_ofstream;
    ofstream outCell_ofstream;
    ofstream outXPC4_ofstream;
    ofstream outXPC8_ofstream;
    ofstream outOCT1_ofstream;
    ofstream outOCT2_ofstream;
    ofstream outOCT3_ofstream;
    ofstream outOCT4_ofstream;

    string outputGNUFile  = "temp/gnu.data";
    string outputFileName = "temp/data.msh";
    string outputFileCell = "temp/cell.msh";
    string outputFileXPC4 = "temp/xpC4.msh";
    string outputFileXPC8 = "temp/xpC8.msh";
    string outputFileOCT1 = "temp/oct1.msh";
    string outputFileOCT2 = "temp/oct2.msh";
    string outputFileOCT3 = "temp/oct3.msh";
    string outputFileOCT4 = "temp/oct4.msh";

    gnuPlot_ofstream.open(outputGNUFile .c_str()); //C++03 or below: .c_str()
    outFile_ofstream.open(outputFileName.c_str());
    outCell_ofstream.open(outputFileCell.c_str());
    outXPC4_ofstream.open(outputFileXPC4.c_str());
    outXPC8_ofstream.open(outputFileXPC8.c_str());
    outOCT1_ofstream.open(outputFileOCT1.c_str());
    outOCT2_ofstream.open(outputFileOCT2.c_str());
    outOCT3_ofstream.open(outputFileOCT3.c_str());
    outOCT4_ofstream.open(outputFileOCT4.c_str());

//  outFile_fstream.open(outFile_fstream, ios::out); //Error in the compiler by now

   if(gnuPlot_ofstream.is_open())
   {
        gnuPlot_ofstream<<"#!/usr/bin/gnuplot -persist"<<std::endl;
        gnuPlot_ofstream<<"set xrange [-2:2]"<<std::endl;
        gnuPlot_ofstream<<"set yrange [-2:2]"<<std::endl;
        gnuPlot_ofstream<<"set zrange [-5:5]"<<std::endl;
//        gnuPlot_ofstream<<"set view equal xyz"<<std::endl;
        gnuPlot_ofstream<<"set xlabel 'x-axis'"<<std::endl;
        gnuPlot_ofstream<<"set ylabel 'y-axis'"<<std::endl;
        gnuPlot_ofstream<<"set zlabel 'ts: "<<t<<"/"<<MyCube.Total_Cell_Divided<<"'"<<std::endl;

        gnuPlot_ofstream<<"set grid"<<std::endl;

        gnuPlot_ofstream<<"set hidden3d"<<std::endl;
        gnuPlot_ofstream<<"set term png"<<std::endl;

        gnuPlot_ofstream<<"set style line 1 lc rgb \"gray\""<<std::endl;
        gnuPlot_ofstream<<"set style line 2 lc rgb \"red\""<<std::endl;
        gnuPlot_ofstream<<"set view "<<VIEW_ROTX<<", "<<VIEW_ROTZ<<", 1, 1"<<std::endl;

        gnuPlot_ofstream<<"set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb\"gray\""<<endl;
 //       gnuPlot_ofstream<<"set term png"<<std::endl;
        gnuPlot_ofstream<<"set output \"printem."<<t+100<<".png\""<<std::endl;
        gnuPlot_ofstream<<"splot 'temp/data.msh'using 1:2:3 lc 1,\\"<<std::endl;
        gnuPlot_ofstream<<"      'temp/cell.msh'using 1:2:3 notitle lc 1 with lines,\\"<<std::endl;
        gnuPlot_ofstream<<"      'temp/oct1.msh'using 1:2:3 notitle lc 2 with lines,\\"<<std::endl;
        gnuPlot_ofstream<<"      'temp/oct2.msh'using 1:2:3 notitle lc 2 with lines,\\"<<std::endl;
        gnuPlot_ofstream<<"      'temp/oct3.msh'using 1:2:3 notitle lc 2 with lines,\\"<<std::endl;
        gnuPlot_ofstream<<"      'temp/oct4.msh'using 1:2:3 notitle lc 2 with lines,\\"<<std::endl;
        gnuPlot_ofstream<<"      'temp/xpC8.msh'using 1:2:3 notitle lc 2 with lines\n"<<std::endl;

//        gnuPlot_ofstream<<"replot"<<std::endl;
//        gnuPlot_ofstream<<"set term x11"<<std::endl;
//        gnuPlot_ofstream<<"exit"<<std::endl;

        gnuPlot_ofstream.close();
   }
   if(outFile_ofstream.is_open())
   {
//        for(int i=0;i<MyCube.Log_Verts();i++)
//        {
//            outFile_ofstream<<MyCube.Mesh[i]<<std::endl;
//        }
        outFile_ofstream.close();
    }

   if(outCell_ofstream.is_open())
   {
        for(int j=0; j<MyCube.Log_Cells_Max(); j++)
        {

	MyCube.loadVertexId(j);
    	MyCube.loadCellEdges();

            for(int i=0;i<12;i++)
            {
                outCell_ofstream<<*MyCube.Edge_i[i]<<endl;
                outCell_ofstream<<*MyCube.Edge_j[i]<<endl;
//                cout<<"SALIDA DE MALLA:"<<*MyCube.Edge_i[i]<<endl;
                outCell_ofstream<<"\n\n"<<endl;
            }
        }
        outCell_ofstream.close();
    }

   if(outOCT1_ofstream.is_open())
   {
	for(int j=0; j<Octree1->Log_Cells_Max(); j++)
        {
	Octree1->loadVertexId(j);
	Octree1->loadCellEdges();

	        for(int i=0;i<12;i++)
	        {
//		outOCT1_ofstream<<Octree1->Cell_Centroids[j]<<std::endl;

               outOCT1_ofstream<<*Octree1->Edge_i[i]<<endl;
                outOCT1_ofstream<<*Octree1->Edge_j[i]<<endl;
//                cout<<"SALIDA DE MALLA:"<<*MyCube.Edge_i[i]<<endl;
                outOCT1_ofstream<<"\n\n"<<endl;
	        }
        }
        outOCT1_ofstream.close();
    }


   if(outOCT2_ofstream.is_open())
   {
	for(int j=0; j<Octree2->Log_Cells_Max(); j++)
        {
	Octree2->loadVertexId(j);
	Octree2->loadCellEdges();

	        for(int i=0;i<12;i++)
	        {
//		outOCT1_ofstream<<Octree1->Cell_Centroids[j]<<std::endl;

               	outOCT2_ofstream<<*Octree2->Edge_i[i]<<endl;
               	outOCT2_ofstream<<*Octree2->Edge_j[i]<<endl;
//                cout<<"SALIDA DE MALLA:"<<*MyCube.Edge_i[i]<<endl;
                outOCT2_ofstream<<"\n\n"<<endl;
	        }
        }
        outOCT2_ofstream.close();
    }


   if(outOCT3_ofstream.is_open())
   {
	for(int j=0; j<Octree3->Log_Cells_Max(); j++)
        {
	Octree3->loadVertexId(j);
	Octree3->loadCellEdges();

	        for(int i=0;i<12;i++)
	        {
//		outOCT1_ofstream<<Octree1->Cell_Centroids[j]<<std::endl;

               	outOCT3_ofstream<<*Octree3->Edge_i[i]<<endl;
               	outOCT3_ofstream<<*Octree3->Edge_j[i]<<endl;
//                cout<<"SALIDA DE MALLA:"<<*MyCube.Edge_i[i]<<endl;
                outOCT3_ofstream<<"\n\n"<<endl;
	        }
        }
        outOCT3_ofstream.close();
    }
  
   if(outOCT4_ofstream.is_open())
   {
	for(int j=0; j<Octree4->Log_Cells_Max(); j++)
        {
	Octree4->loadVertexId(j);
	Octree4->loadCellEdges();

	        for(int i=0;i<12;i++)
	        {
//		outOCT1_ofstream<<Octree1->Cell_Centroids[j]<<std::endl;

               	outOCT4_ofstream<<*Octree4->Edge_i[i]<<endl;
               	outOCT4_ofstream<<*Octree4->Edge_j[i]<<endl;
//                cout<<"SALIDA DE MALLA:"<<*MyCube.Edge_i[i]<<endl;
                outOCT4_ofstream<<"\n\n"<<endl;
	        }
        }
        outOCT4_ofstream.close();
    }

   if(outXPC8_ofstream.is_open())
   {
      for(int j=0; j<number_of_points; j++)
        {
            outXPC8_ofstream<<point[j]<<std::endl;
		    //MyCube.Centroids[j]<<std::endl;
        }
        outXPC8_ofstream.close();
    }

   if(outXPC4_ofstream.is_open())
   {
//       for(int i=1;i<13;i++)
//        {
//            outXPC4_ofstream<<MyCube.Centroids[i]<<std::endl;
//        }
        outXPC4_ofstream.close();
    }

    else
    {
        cout<<"Could not create file: "<<outputFileName<<std::endl;
    }

//std::cout<<"DISTANCE OF CENTROID TO VERTEX: "<<MyCube.Centroids[0];

#endif // GNUPLOT_H_INCLUDED
