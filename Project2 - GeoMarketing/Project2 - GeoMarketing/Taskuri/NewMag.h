#pragma once

#define MAX_ITERATION 1000
#define Rp 6380 //Raza pamantului

#include "../Clase/Magazin.h"
#include "../Clase/User.h"
#include "../SD/Array.h"
#include <ctime>
#include<cstdlib>
#include <climits>
#include <cfloat>

using namespace std;

struct Point
{
	double x, y;
	int label;
	bool operator==(Point& p)
	{
		if (this->x != p.x || this->y != p.y || this->label != p.label)
			return false;
		return true;
	}
};

class NewMag
{
private:

	Point** clienti;
	int nrClienti;
	Point** magazine;
	Point** centroids, **oldCentroids, **newCentroids;
	int nrMagazine;
	int k, *nrLabels;
	

	void GetRandomCentroids()
	{
		int i, randPoint;
		srand((unsigned int)time(NULL));
		for (i = 0; i < k; i++)
		{
			randPoint = rand() % nrClienti;
			centroids[i]->x = clienti[randPoint]->x;
			centroids[i]->y = clienti[randPoint]->y;
		}
	}

	bool Differ(Point** v1, Point** v2)
	{
		int i;
		for (i = 0; i < k; i++)
			if (!((*v1[i]) == (*v2[i])))
				return false;
		return true;
	}
	void Copy(Point** v1, Point** v2)
	{	
		int i;
		for (i = 0; i < k; i++)
			(*v1[i]) = (*v2[i]);
	}

	double Distance(double lat1, double lon1, double lat2, double lon2) {

		double x;

		x = sin((lat1 - lat2) / 2) * sin((lat1 - lat2) / 2) +
			cos(lat1) * cos(lat2) * sin((lon1 - lon2) / 2) * sin((lon1 - lon2) / 2);

		return 2 * Rp * atan2(sqrt(x), sqrt(1 - x));
	}


	bool ShouldStop(Point** oldCentroids, Point** centroids, int iterations)
	{
		if (iterations > MAX_ITERATION)
			return true;
		return (!Differ(oldCentroids, centroids));
	}

	void GetLabels()
	{
		double min, distance; 
		int i, label, j;
		for (i = 0; i < nrClienti; i++)
		{
			min = DBL_MAX;
			for (j = 0; i < k; i++)
			{
				distance = Distance(clienti[i]->x, clienti[i]->y,
					centroids[j]->y, centroids[j]->y);
				if (distance < min)
				{
					min = distance;
					label = j;
				}
			}
			clienti[i]->label = label;
		}
	}

	void GetCentroids()
	{
		int i;
		for (i = 0; i < k; i++)
		{
			newCentroids[i]->x = 0;
			newCentroids[i]->y = 0;
			nrLabels[i] = 0;
		}
		for (i = 0; i < nrClienti; i++)
		{
			nrLabels[clienti[i]->label]++;
			newCentroids[clienti[i]->label]->x += clienti[i]->x;
			newCentroids[clienti[i]->label]->y += clienti[i]->y;
		}
		for (i = 0; i < k; i++)
		{
			centroids[i]->x = newCentroids[i]->x / nrLabels[i];
			centroids[i]->y = newCentroids[i]->y / nrLabels[i];
		}		
	}

	// http://stanford.edu/~cpiech/cs221/handouts/kmeans.html
	void Kmeans()
	{
		int i, iterations;
		iterations = 0;

		GetRandomCentroids();

		for (i = 0; i < k; i++)
		{
			oldCentroids[i]->x = 0;
			oldCentroids[i]->y = 0;
			oldCentroids[i]->label = 0;
		}

		while (!ShouldStop(oldCentroids, centroids, iterations))
		{
			Copy(oldCentroids, centroids);
			iterations++;
			GetLabels();
			GetCentroids();
		}
	}

public:
	NewMag(Array <User> users, Array <Magazin> mags, int k)
	{
		int i;
		nrClienti = users.size() - 1;
		nrMagazine = mags.size() - 1;
		clienti = new Point*[nrClienti];
		magazine = new Point*[nrMagazine];
		for (i = 0; i < nrClienti; i++)
		{
			clienti[i] = new Point;
			clienti[i]->x = users[i + 1].getX();
			clienti[i]->y = users[i + 1].getY();
		}
		for (i = 0; i < nrMagazine; i++)
		{
			magazine[i] = new Point;
			magazine[i]->x = mags[i + 1].getX();
			magazine[i]->y = mags[i + 1].getY();
		}			 

		centroids = new Point*[k];
		oldCentroids = new Point*[k];
		newCentroids = new Point*[k];
		for (i = 0; i < k; i++)
		{
			centroids[i] = new Point;
			oldCentroids[i] = new Point;
			newCentroids[i] = new Point;
		}

		nrLabels = new int[k];
	}

	~NewMag()
	{
		int i;
		for (i = 0; i < nrMagazine; i++)
			delete magazine[i];
		for (i = 0; i < nrClienti; i++)
			delete clienti[i];
		for (i = 0; i < k; i++)
		{
			delete centroids[i];
			delete oldCentroids[i];
			delete newCentroids[i];
		}
			
		delete oldCentroids;
		delete magazine;
		delete clienti;
		delete centroids;
		delete nrLabels;
	}

	Point GetCoord()
	{
		int i, j, k, mag;
		double min, max, distance;
		
		max = 0;
		for (i = 0; i < k; i++)
		{
			min = DBL_MAX;
			for (j = 0; j < nrMagazine; j++)
			{
				distance = Distance(centroids[i]->x, centroids[j]->y,
					magazine[j]->x, magazine[j]->y);
				if (distance < min)
				{
					min = distance;
				}
			}
			if (min > max)
			{
				max = min;
				mag = i;
			}
		}
		
		return (*centroids[mag]);
	}
};