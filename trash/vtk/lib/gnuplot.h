#ifndef GNUPLOT_H_INCLUDED
#define GNUPLOT_H_INCLUDED

//*t/tfin;
//360*t/tfin;


    ofstream outFile_ofstream; //create an object type ofstream called outFile_ofstream
    ofstream gnuPlot_ofstream;
    ofstream outCell_ofstream;
    ofstream outXPC4_ofstream;
    ofstream outXPC8_ofstream;

    string outputGNUFile  = "temp/gnu.data";
    string outputFileName = "temp/data.msh";
    string outputFileCell = "temp/cell.msh";
    string outputFileXPC4 = "temp/xpC4.msh";
    string outputFileXPC8 = "temp/xpC8.msh";


    gnuPlot_ofstream.open(outputGNUFile .c_str()); //C++03 or below: .c_str()
    outFile_ofstream.open(outputFileName.c_str());
    outCell_ofstream.open(outputFileCell.c_str());
    outXPC4_ofstream.open(outputFileXPC4.c_str());
    outXPC8_ofstream.open(outputFileXPC8.c_str());

//  outFile_fstream.open(outFile_fstream, ios::out); //Error in the compiler by now

    std::cout<<"ENTRANDO EN GNUPLOT DATA"<<std::endl;
   if(gnuPlot_ofstream.is_open())
   {
	   std::cout<<"HA ENTRADO CORRECTAMENTE"<<std::endl;
        gnuPlot_ofstream<<"#!/usr/bin/gnuplot -persist"<<std::endl;
        gnuPlot_ofstream<<"set xrange [-10:10]"<<std::endl;
        gnuPlot_ofstream<<"set yrange [-10:10]"<<std::endl;
        gnuPlot_ofstream<<"set zrange [-10:10]"<<std::endl;
//        gnuPlot_ofstream<<"set view equal xyz"<<std::endl;
        gnuPlot_ofstream<<"set xlabel 'x-axis'"<<std::endl;
        gnuPlot_ofstream<<"set ylabel 'y-axis'"<<std::endl;
        gnuPlot_ofstream<<"set zlabel 'ts: "<<t<<"/"<<tfin<<"'"<<std::endl;

        gnuPlot_ofstream<<"set grid"<<std::endl;

        gnuPlot_ofstream<<"set hidden3d"<<std::endl;
        gnuPlot_ofstream<<"set term png"<<std::endl;

        gnuPlot_ofstream<<"set style line 1 lc rgb \"red\""<<std::endl;
        gnuPlot_ofstream<<"set style line 2 lc rgb \"blue\""<<std::endl;
        gnuPlot_ofstream<<"set view "<<VIEW_ROTX<<", "<<VIEW_ROTZ<<", 1, 1"<<std::endl;

        gnuPlot_ofstream<<"set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb\"gray\""<<endl;
 //       gnuPlot_ofstream<<"set term png"<<std::endl;
        gnuPlot_ofstream<<"set output \"printem."<<t+100<<".png\""<<std::endl;
        gnuPlot_ofstream<<"splot 'temp/data.msh'using 1:2:3 lc 1,\\"<<std::endl;
        gnuPlot_ofstream<<"      'temp/cell.msh'using 1:2:3 notitle lc 1 with lines,\\"<<std::endl;
//        gnuPlot_ofstream<<"      'temp/xpC4.msh'using 1:2:3 notitle lc 2,\\"<<std::endl;
        gnuPlot_ofstream<<"      'temp/xpC8.msh'using 1:2:3 notitle lc 2\n"<<std::endl;

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
            MyCube.getCellConnections(j);

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

   if(outXPC8_ofstream.is_open())
   {
      for(int j=0; j<MyCube.Log_Cells_Max(); j++)
        {
            outXPC8_ofstream<<MyCube.Centroids[j]<<std::endl;
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
