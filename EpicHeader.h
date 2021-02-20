#ifndef _EPICHEADER_H
#define _EPICHEADER_H
#include <cmath>

//struct that represents a point
struct pt
{
	float x, y, z;
};

//get 3DPoint from user input, this is used for points and vectors as they share the same three dimensional properties
pt getp()
{
	pt p;
	std::cout << "Write coordinates for a 3D point/vector \nx:";
	std::cin >> p.x;
	std::cout << "y:";
	std::cin >> p.y;
	std::cout << "z:";
	std::cin >> p.z;
	return p;
}

//function for calculating 3Dvector substraction
pt subst(pt p, pt q)
{
	pt nyp;                                                                                                                                
	nyp.x = p.x - q.x;
	nyp.y = p.y - q.y;
	nyp.z = p.z - q.z;
	return nyp;
}

//function for calculating cross product of the vectors v and w
pt cross(pt v, pt w)
{
	pt nyv;
	nyv.x = v.y * w.z - v.z * w.y;
	nyv.y = v.z * w.x - v.x * w.z;
	nyv.z = v.x * w.y - v.y * w.x;
	
	return nyv;
}

//function to calculate the dot product of two vectors
float dot(pt v, pt w)
{
	float dotp = v.x* w.x + v.y * w.y + v.z * w.z;
	return dotp;
}

//neat function to calculate vector length
float length(pt v)
{
	float vlength = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return vlength;
}

//function that calculates distance between two points
void distanceBetweenTwoPoints()
{
	pt p = getp();
	pt q = getp();
	float distance = sqrt(pow((p.x - q.x), 2) + pow((p.y - q.y), 2) + pow((p.z - q.z), 2));
	std::cout << "The distance between the two points are: " << distance << std::endl;
}

//function to find a point in a parameterized vector or 3D line
pt findPoint(pt p1, pt v, float t)
{
	pt ansp;
	
	ansp.x = p1.x + t * v.x;
	ansp.y = p1.y + t * v.y;
	ansp.z = p1.z + t * v.z;
	return ansp;
}

//bool function that checks if two points on the same vectors are the same with t and s being t in a parameterized line.
//this is to check if the lines intersect
bool checkIfIntersect(pt p1, pt p2, pt v, pt w, float t, float s)
{
	pt point1 = findPoint(p1, v, t);
	pt point2 = findPoint(p2, w, s);

	if (point1.x == point2.x && point1.y == point2.y && point1.z == point2.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------

//This is a huge function for the formula to find an intersection between two lines and/or distance between them if they dont
void distanceLineAndIntersect()
{
	float t, s;
	//gets user input to create a direct description of a vector/line
	std::cout << "Create point p and q for vector v" << std::endl;
	pt p1 = getp();
	pt q1 = getp();

	pt v = subst(q1, p1); //calculate the vector between the two points (l)
	
	//gets user input for the second line that we are comparing to the other 
	std::cout << "Create points p and q for vector w" << std::endl;
	pt p2 = getp();
	pt q2 = getp();

	pt w = subst(q2, p2);
	pt tcross2 = cross(v, w); //the vector product of v1 and v2 early because we need to use it to check if the lines are paralell
	
	//checks if the cross product is not only zeros, if so, then lines are paralell
	if (tcross2.x != 0 || tcross2.y != 0 || tcross2.z != 0) {
		//micromanaging calculations for the t and s formula
		pt qmp = subst(p2, p1);
		pt tcross1 = cross(qmp, w);
		

		t = dot(tcross1, tcross2) / pow(length(tcross2), 2);

		pt pmq = subst(p1, p2);
		pt scross1 = cross(pmq, v);
		pt scross2 = cross(w, v);

		s = dot(scross1, scross2) / pow(length(scross2), 2);

		//uses the checkIfIntersect function to plot in the t values for the vectors to see if the points are the same, if so: the lines intersect.
		if (checkIfIntersect(p1, p2, v, w, t, s))
		{
			pt intersectp = findPoint(p1, v, t);
			std::cout << "The lines intersect! The intersection is at point: [" << intersectp.x << ", " << intersectp.y << ", " << intersectp.z << "]" << std::endl;
		}
		//if they dont intersect, find distance between the lines
		else
		{
			float dist;
			dist = dot(tcross2, qmp) / length(tcross2);
			std::cout << "The lines do not intersect, but their distance is:" << dist << std::endl;
		}
	}
	else
	{
		std::cout << "The lines are parallell or the same" << std::endl;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------

//function to calculate distance between a point and a line, the line is given by assigning a point and a vector heading
void distanceBetweenPointAndLine()
{
	
	std::cout << "Create vector origin" << std::endl;
	pt ori = getp(); //creating the line start point
	std::cout << "Create vector" << std::endl;
	pt v = getp(); //creating the "heading"
	std::cout << "Create point" << std::endl;
	pt p = getp(); //creating a point to calculate from

	pt oriToP = subst(p, ori); //creating a vector AB or in this case "pori"
	pt pvcrossed = cross(v, oriToP); //microcalculating vectorproduct for later use in formula
	
	float dist = length(pvcrossed) / length(v); //main formula to find the distance between the point and the line

	std::cout << "The distance between the line and point is: " << dist << std::endl;

}

//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------

//function to find an intersection between a plane and a line, if not, finds the distance between the line and the plane
void lineAndPlaneIntersect()
{
	float d, t; //declare d and t
	std::cout << "Insert values a, b, c for plane" << std::endl;
	pt plane = getp(); //since the plane only needs a 3D vector to function in this case, im using the pt struct again. 
	std::cout << "Insert value for Plane d\nd:";
	std::cin >> d; //getting user input for d since d is not included in the pt struct
	
	//getting a direct description for a line by providing two points
	std::cout << "Point P for line" << std::endl;
	pt p = getp();
	std::cout << "Point q for line" << std::endl;
	pt q = getp();

	//creating v to convert the line into parameterized form or just create a vector between the two points
	pt v = subst(q, p);

	//check if the dot product of the line and plane does not equal zero, if it does then the line is normal on the plane and they do not intersect.
	if (dot(v, plane) != 0)
	{
		//finding t value for the line in paramterized form
		t = (d - dot(p, plane)) / dot(v, plane);

		//plotting t into the parameterized line formula to find the intersection point on the line
		pt ans = findPoint(p, v, t);
		std::cout << "The intersection is at point: [" << ans.x << ", " << ans.y << ", " << ans.z << "]" << std::endl;
	}
	else
	{
		//because the line is normal on the normalized vector n or paralell with the plane, we can just find any point on the line and calculate distance from point to plane
		pt pnt = findPoint(p, v, 0.6); //finding random point on line
		float dist = (plane.x * pnt.x + plane.y * pnt.y + plane.z * pnt.z - d) / length(plane); //calculating distance between plane and point
		
		//if distance is higher or lower than 0 we know that the line is not on the plane, so we can display the distance between the plane and the line
		if (dist != 0) {
			std::cout << "The line is normal on the plane and has no intersection, the distance between the line and the plane is: " << dist << std::endl;
		}
		//if the distance is 0, then the line is paralell on the plane
		else
		{
			std::cout << "The line is parallell to the plane but has no distance, the line is in the plane";
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------

void distanceBetweenPlaneAndPoint()
{
	float d; //declare d
	std::cout << "Insert values a, b, c for plane" << std::endl;
	pt plane = getp(); //since the plane only needs a 3D vector to function in this case, im using the pt struct again. 
	std::cout << "Insert value for Plane d\nd:";
	std::cin >> d; //getting user input for d since d is not included in the pt struct

	//input for 3dPoint
	std::cout << "Insert value for 3dpoint" << std::endl;
	pt p = getp();

	//distance formula
	float dist = (plane.x * p.x + plane.y * p.y + plane.z * p.z - d) / length(plane);

	std::cout << "The distance between the point and plane is: " << dist << std::endl;

}




#endif // _EPICHEADER_H
