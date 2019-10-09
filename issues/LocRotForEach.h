/*[BUG INFO:]

    Issue found on: 08/10/2019
    --------------------------

    I've founded an issue in return of LocRotForEach it gives me a vector that
    has lower Norm() than before operation. The proble should be related with
    function pointers, or function returns because vec3::Rot works nicelly.

    Now the code is contained in this header as it was yanked from its original
    place with the purpose of keep clean the main thread.

    The code writen here should be implemente in a proper way inside its class
    in order to close and fix this bug

    UPDATE: It seems ArithmeticForEach is also affected. I've measured a known
    distance (1.0, 0.0, 0.0) and each time it gives a random value close and lower
    than expected Norma() = 1.0

END OF REPORT*/

//[Info] Updating position of points insertion
		int iop = 0; //{iop = 0 (Add); iop = 1 (Substract)} //this line will remove after suit documentation
//		Item[0].ArithmeticForEach(Item, number_of_points, vec3(0.0003, 0.0001, 0.0001), 0);
        double alpha = 0.02;
//		Item[0].LocRotForEach(Item, number_of_points, alpha, 2);
//EL LOOP FOR DE AQUI DEBAJO HACE LO MISMO QUE LocRotForEach pero bien ME CAGO EN LA PUTA!!!!
        for(int i=0; i<number_of_points; i++)
        {
            Item[i] = Item[i].RotZ(Item[i], alpha);
        }
//        std::cout<<"Disante to center: "<<Item[1].Norma()<<std::endl;

//Item[0].ArithmeticForEach(Item, number_of_points, vec3(1.0, 0.0, 0.0), 0);
///////////////////////////////////////////////////////////////////////////////////////////////
// Quizas tnga que aoptar una solucion tipo RotateMeshZ
///////////////////////////////////////////////////////////////////////////////////////////////
