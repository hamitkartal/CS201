#include "favoriteseries.h"
using namespace std;

void ActorSort2(vector<actor> & v, int start, int end){
    int j, k, maxIndex, numElts = v.size();
    actor temp;
    for(k=start; k <= end - 1; k++){
        maxIndex = k;
        for(j=k+1; j <= end; j++)
            if (v[j].actorname < v[maxIndex].actorname)
               maxIndex = j;
        temp = v[k];
        v[k] = v[maxIndex];
        v[maxIndex] = temp;
    }
}

void ActorSort1(vector<actor> & v){
    int j, k, maxIndex, numElts = v.size();
    actor temp;
    for(k=0; k < numElts - 1; k++){
        maxIndex = k;
        for(j=k+1; j < numElts; j++)
            if (v[j].codes.size() > v[maxIndex].codes.size())
               maxIndex = j;
        temp = v[k];
        v[k] = v[maxIndex];
        v[maxIndex] = temp;
    }

	for (int i=0; i < v.size() - 1;){
	    int j=i+1;
	    for (; j < v.size(); j++){
	        if (v[i].codes.size() == v[j].codes.size() && j == v.size()-1){
				ActorSort2(v, i, j);
				break;
	        }
			else if(v[i].codes.size() == v[j].codes.size() && j != v.size()-1){
				continue;
			}
			else if (v[i].codes.size() != v[j].codes.size() && j == v.size()-1){
				ActorSort2(v, i, j-1);
				break;
			}
			else if (v[i].codes.size() != v[j].codes.size() && j != v.size()-1){
				ActorSort2(v, i, j-1);
				break;
			}
	    }
	    i = j;
    }
}

int actorCheck(const vector<actor>& v, const string& actor)
{
	for (int i=0; i < v.size(); i++){
		if (v[i].actorname == actor){
			return i;
		}
	}
	return -1;
}

void Insert(vector<episode>& a, episode newnum){  		// NOT const vector
// pre: a[0] <= … <= a[a.size()-1], a is sorted
// post: newnum inserted into a, a still sorted
    int count = a.size();  // size before insertion
    a.push_back(newnum);   // increase size –newnum is inserted at the
                   	// end but inserted value is not important
    int loc = count;      // start searching insertion loc from end
   
    while ((loc > 0 && a[loc-1].date > newnum.date) || (loc > 0 && a[loc-1].date == newnum.date && a[loc-1].slot > newnum.slot) ||	(loc > 0 && a[loc-1].date == newnum.date && a[loc-1].slot == newnum.slot && a[loc-1].seriesCode > newnum.seriesCode)){    
		a[loc] = a[loc-1]; 
		loc--;        // shift right until the proper insertion cell
    }
    
	a[loc] = newnum;  //actual insertion 
}


void removeseries(vector<series> & a, int pos){
    // post: original a[pos] removed, size decreased
    int lastIndex = a.size()-1;
    a[pos] = a[lastIndex];
    a.pop_back();
}


FavoriteSeries::FavoriteSeries(string uName, string uSurname)
{
	userName = uName;
	userSurname = uSurname;
}

string FavoriteSeries::getFullName() const
{
	return userName + " " + userSurname;
}

void FavoriteSeries::addSeries(const series & s)
{
	favSeries.push_back(s);
}

bool FavoriteSeries::ifExists(int seriesCode)
{
	for (int i=0; i < favSeries.size(); i++){
		if (favSeries[i].seriesCode == seriesCode){
			return true;
		}
	}
	return false;
}

bool FavoriteSeries::isListEmpty() const
{
	return (favSeries.size() == 0);
}

void FavoriteSeries::dropSeriesSorted(int seriesCode)
{
	int i=0;
	for (; i < favSeries.size(); i++){
		if (favSeries[i].seriesCode == seriesCode){
			break;
		}
	}
	cout << userName << " " << userSurname << ", " << favSeries[i].seriesName << " has been dropped from your favorite list!" << endl;

	removeseries(favSeries, i);
}

void FavoriteSeries::displayFavoriteList() const
{
	vector<episode> favEps;
	for (int i=0; i < favSeries.size(); i++){
		for (int j=0; j < favSeries[i].episodes.size(); j++){
			Insert(favEps, favSeries[i].episodes[j]);
		}
	}

	cout <<	"CODE,SERIES,EPISODE,DATE,SLOT" << endl;
	for (int i=0; i < favEps.size(); i++){
		cout << favEps[i].seriesCode << ",";
		int j=0;
		for (; j < favSeries.size(); j++){
			if (favSeries[j].seriesCode == favEps[i].seriesCode){
				break;
			}
		}
		cout << favSeries[j].seriesName << "," << favEps[i].episodeName << "," << favEps[i].date.ToString() << "," << favEps[i].slot.substr(1) << endl;
	}
}

void FavoriteSeries::displayFavoriteActors() const
{
	vector<actor> actors;
	for (int i=0; i < favSeries.size(); i++){
		for (int j=0; j < favSeries[i].actorNames.size(); j++){
			int indx = actorCheck(actors, favSeries[i].actorNames[j]);
			if ( indx == -1){
				actor act;
				act.actorname = favSeries[i].actorNames[j];
				act.codes.push_back(favSeries[i].seriesCode);
				actors.push_back(act);
			}
			else{
				actors[indx].codes.push_back(favSeries[i].seriesCode);
			}
		}
	}

	ActorSort1(actors);

	cout << userName << " " << userSurname << ", here is your favorite actors:" << endl;
	for (int i=0; i < actors.size(); i++){
		if (actors[i].codes.size() > 0){
			cout << actors[i].actorname << ": " << actors[i].codes.size() << endl;
		}
		else{
			break;
		}
	}
}

bool FavoriteSeries::isConflict(const series & inSeries) const
{
	for (int i=0; i < inSeries.episodes.size(); i++){
		for (int j=0; j < favSeries.size(); j++){
			for (int k=0; k < favSeries[j].episodes.size(); k++){
				if (inSeries.episodes[i].date == favSeries[j].episodes[k].date && inSeries.episodes[i].slot == favSeries[j].episodes[k].slot){
					return true;
				}
			}
		}
	}
	return false;
}