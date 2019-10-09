/*[BUG INFO:]

    Issue found on: 08/10/2019
    --------------------------

    WriteVec3 still not implemented in the same way as WriteMesh

END OF REPORT*/

//Temporal code to write Item Verex in CSV file I will implement WriteVec3 in the future
	meshFileOF.open(nameFile.c_str(), std::ios::app);
	if(meshFileOF.is_open())
	{
		for(int i = 0; i<number_of_points; i++)
		{
			meshFileOF << Item[i]<<", 8"<<std::endl;
		}
		meshFileOF.close();
	}

//	MyCube.RotateYMesh(0.02f);
//	MyCube.RotateXMesh(0.02f);
//	MyCube.RotateZMesh(0.02f);
//	MyCube.DisplaceMesh(vec3(0.l,0.l,0.l));
